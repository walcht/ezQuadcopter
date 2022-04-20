/*------------------------ RC Module Libraries\Defines --------------------------*/
#include <Arduino.h>
#include <SPI.h>        // Arduino Serial Peripheral Interface protocol library
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>   

#define CE    4        // necessary for RC tranceiver
#define CSN   5  
/*-------------------------------------------------------------------------------*/

/*--------------------- BLDC Motor\ESC Libraries\Defines ------------------------*/
#include <ESP32_Servo.h>      // for controlling the ESCs
#include <MPU9250.h>

//
//
//  motor_00     motor_01
//     \           /
//      \---------/
//      |          >      This arrow indicates which side of the quadcopter is forward
//      /---------\
//     /           \
//  motor_02     motor_03
//
//
//  This 
//  ////////////// Min ////// Max //// 
//  // THROTTLE : -200 ///// +200 ////
//  // ROLL     : -75  ///// +75  ////
//  // PITCH    : -75  ///// +75  ////
//  // YAW      : -50  ///// +50  ////
//  //////////////////////////////////
//
//


#define MOTOR_00    13     // PWM pin to connect with corresponding ESC
#define MOTOR_01    12     // These pins control the rotation speed of the BLDC motors
#define MOTOR_02    33
#define MOTOR_03    32

#define IDLE_THROTTLE     0         // idle values in percentage for thrust, pitch, roll and yaw
#define IDLE_PITCH        0     
#define IDLE_ROLL         0
#define IDLE_YAW          0

#define MIN_THROTTLE      1000      // minimum throttle in percentage that can be applied to motors
#define MAX_THROTTLE      1400      // maximum throttle in percentage that can be applied to motors 

//#define PERCENTAGE_TO_MOTOR_VALUE(x) (x/100) * 180
/*-------------------------------------------------------------------------------*/

/*---------------------------- PID-related defines ------------------------------*/
#define PID_PITCH_P   0
#define PID_PITCH_D   0
#define PID_PITCH_I   0

#define PID_ROLL_P    0
#define PID_ROLL_D    0
#define PID_ROLL_I    0

#define PID_YAW_P     0
#define PID_YAW_D     0
#define PID_YAW_I     0
/*-------------------------------------------------------------------------------*/


/*------------- Uncomment any of these lines for specific behavior --------------*/
#define DEBUG_MODE          // for printing some useful information
//#define CALIBRATION_MODE    // for calibrating the magnetometer and writing calibration
                            // values to the ROM
/*-------------------------------------------------------------------------------*/

int16_t inline ExecutePitchPID(const int16_t& pitch_set_point, const int16_t& measured_pitch);
int16_t inline ExecuteRollPID(const int16_t& roll_set_point, const int16_t& measured_roll);
int16_t inline ExecuteYawPID(const int16_t& yaw_set_point, const int16_t& measured_yaw);
void inline UpdateMotorsValues( const int16_t throttle, const int16_t pitch_pid_output, const int16_t roll_pid_output, const int16_t yaw_pid_output);
void inline MeasurePitchRollYaw(int16_t& pitch, int16_t& roll, int16_t& yaw);  // MPU 9250


RF24 receiver(CE, CSN);         // check link for class methods: https://nrf24.github.io/RF24/classRF24.html
Servo motor_00;
Servo motor_01;
Servo motor_02;
Servo motor_03;

uint8_t address[] = "00001";    // logical address: this address must be the same on the transmitting end

//                           [  THROTTLE,      PITCH,      ROLL,       YAW]
int16_t values_received[4] = {  IDLE_THROTTLE, IDLE_PITCH, IDLE_ROLL,  IDLE_YAW};

MPU9250 mpu;

void setup() {
  int16_t pitch_pid_output = 0;
  int16_t roll_pid_output = 0;
  int16_t yaw_pid_output = 0;

  #ifdef DEBUG_MODE
    Serial.begin(9600);
  #endif

  motor_00.attach(MOTOR_00, MIN_THROTTLE, MAX_THROTTLE);
  motor_01.attach(MOTOR_01, MIN_THROTTLE, MAX_THROTTLE);
  motor_02.attach(MOTOR_02, MIN_THROTTLE, MAX_THROTTLE);
  motor_03.attach(MOTOR_03, MIN_THROTTLE, MAX_THROTTLE);

  receiver.begin();                    // setting-up nRF module configuration
  //receiver.setDataRate(RF24_250KBPS);
  receiver.openReadingPipe(1, address);  // which pipe to receive data from and what is its address?
  receiver.startListening();             // set RC module to receiver mode

  Wire.begin();
  delay(2000);

  /*----------------------------MPU CONFIGURATION----------------------------*/
  //MPU9250Setting setting;
  //setting.accel_fs_sel = ACCEL_FS_SEL::A2G;
  //setting.gyro_fs_sel = GYRO_FS_SEL::G1000DPS;
  //setting.mag_output_bits = MAG_OUTPUT_BITS::M16BITS;
  //setting.fifo_sample_rate = FIFO_SAMPLE_RATE::SMPL_200HZ;
  //setting.gyro_fchoice = 0x03;
  //setting.gyro_dlpf_cfg = GYRO_DLPF_CFG::DLPF_41HZ;
  //setting.accel_fchoice = 0x01;
  //setting.accel_dlpf_cfg = ACCEL_DLPF_CFG::DLPF_45HZ;

  if (!mpu.setup(0x68)) {
    while (1) {
      Serial.println("IMU connection failure!");
      delay(500);
    }
  }
  //mpu.setMagneticDeclination(+2.51f); // Apr 25, Tunisia

  #ifdef CALIBRATION_MODE
    Serial.println("Calibrating IMU's accelerometer and gyroscope...");
    Serial.println("Please keep IMU on a still surface!");
    for (int i = 5; i > 0; --i) {
      Serial.printf("Starting calibration in %d seconds\n", i);
      delay(1000);
    }
    mpu.calibrateAccelGyro();
    Serial.println("Calibrating IMU's magnetometer...");
    Serial.println("Please rotate the IMU around when notified");
    for (int i = 5; i > 0; --i) {
      Serial.printf("Starting calibration in %d seconds\n", i);
      delay(1000);
    }
    mpu.calibrateMag();
    Serial.println("calibration is done");

  #endif
  /*-------------------------------------------------------------------------*/
}

void loop() {

  values_received[0] = IDLE_THROTTLE;
  values_received[1] = IDLE_PITCH;
  values_received[2] = IDLE_ROLL;
  values_received[3] = IDLE_YAW;
  
  // if (there is received data that is waiting to be processed)
  if (receiver.available()) {
    
    receiver.read(values_received, sizeof(int16_t)*4);
    #ifdef DEBUG_MODE
    Serial.print(values_received[0]);
    Serial.print("\t");

    Serial.print(values_received[1]);
    Serial.print("\t");

    Serial.print(values_received[2]);
    Serial.print("\t");
    
    Serial.println(values_received[3]);
    #endif
  }
  if (mpu.update()) {
    #ifdef DEBUG
      Serial.print(mpu.getYaw()); Serial.print(", ");
      Serial.print(mpu.getPitch()); Serial.print(", ");
      Serial.println(mpu.getRoll());
    #endif
  }

  UpdateMotorsValues(values_received[0], 0, 0, 0);
}

int16_t inline ExecutePitchPID(const int16_t& pitch_set_point, const int16_t& measured_pitch) {
  float error;
  static float previous_error = .0;
  static float integral = .0;
  
  float proportional;
  float derivative;
  
  error = static_cast<float>(pitch_set_point - measured_pitch);
  
  proportional = PID_PITCH_P * error;
  derivative = PID_PITCH_D * (error - (previous_error));
  integral += PID_PITCH_I * (previous_error + error)/2;
    
  previous_error = error;
  
  return static_cast<int16_t>(proportional + integral + derivative);
}

int16_t inline ExecuteRollPID(const int16_t& roll_set_point, const int16_t& measured_roll) {
  float error;
  static float previous_error = .0;
  static float integral = .0;
  
  float proportional;
  float derivative;
  
  error = roll_set_point - measured_roll;
  
  proportional = PID_ROLL_P * error;
  derivative = PID_ROLL_D * (error - (previous_error));
  integral += PID_ROLL_I * (previous_error + error)/2;
  
  previous_error = error;
  
  return proportional + integral + derivative;
}

int16_t inline ExecuteYawPID(const float& yaw_set_point, const float& measured_yaw) {
  float error;
  static float previous_error = .0;
  static float integral = .0;
  
  float proportional;
  float derivative;
  
  error = yaw_set_point - measured_yaw;
  
  proportional = PID_YAW_P * error;
  derivative = PID_YAW_D * (error - (previous_error));
  integral += PID_YAW_I * (previous_error + error)/2;
  
    
  previous_error = error;

  return proportional + integral + derivative;
}

void inline UpdateMotorsValues( const int16_t throttle, const int16_t pitch_pid_output,
                                const int16_t roll_pid_output, const int16_t yaw_pid_output) {
  motor_00.write(throttle + pitch_pid_output + roll_pid_output + yaw_pid_output);
  motor_01.write(throttle - pitch_pid_output + roll_pid_output - yaw_pid_output);
  motor_02.write(throttle + pitch_pid_output - roll_pid_output - yaw_pid_output);
  motor_03.write(throttle - pitch_pid_output - roll_pid_output + yaw_pid_output);
}

void inline MeasurePitchRollYaw(int16_t& measured_pitch, int16_t& measured_roll, int16_t& measured_yaw) {
  measured_pitch = static_cast<int16_t>(mpu.getEulerX());
  measured_roll = static_cast<int16_t>(mpu.getEulerY());
  measured_yaw = static_cast<int16_t>(mpu.getEulerZ());
}