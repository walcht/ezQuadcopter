/*------------------------ RC Module Libraries\Defines --------------------------*/
#include <SPI.h>        // Arduino Serial Peripheral Interface protocol library
#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>   

#define CE    10        // necessary for RC tranceiver
#define CSN   11  
/*-------------------------------------------------------------------------------*/

/*--------------------- BLDC Motor\ESC Libraries\Defines ------------------------*/
#include <Servo.h>      // for controlling the ESCs

//
//  motor_1     motor_2
//     \           /
//      \---------/
//      |          >      This arrow indicates which side of the quadcopter is forward
//      /---------\
//     /           \
//  motor_3     motor_4
//

#define motor_00    4     // PWM pin to connect with corresponding ESC
#define motor_01    5
#define motor_02    6
#define motor_03    7

#define IDLE_VX0    0     // idle values for thrust, pitch, roll and yaw
#define IDLE_VY0    0
#define IDLE_VX1    0
#define IDLE_VY1    0

/*-------------------------------------------------------------------------------*/

/*---------------------------- PID-related defines ------------------------------*/
#define PID_PITCH_P   
#define PID_PITCH_D   
#define PID_PITCH_I   

#define PID_ROLL_P
#define PID_ROLL_D
#define PID_ROLL_I

#define PID_YAW_P
#define PID_YAW_D
#define PID_YAW_I
/*-------------------------------------------------------------------------------*/

#define LOOP_TIME


/*------------- Uncomment any of these lines for specific behavior --------------*/
//#define DEBUG_MODE

/*-------------------------------------------------------------------------------*/

void inline ExecutePID(const int16_t& set_point, int16_t& pid_output);
void inline MeasurePitchRollYaw(int16_t& pitch, int16_t& roll, int16_t& yaw);  // MPU 9250


RF24 receiver(CE, CSN);         // check link for class methods: https://nrf24.github.io/RF24/classRF24.html

uint8_t address[] = "00001";    // logical address: this address must be the same on the transmitting end

void setup() {
  
  #ifdef DEBUG_MODE
    Serial.begin(9600);
  #endif

  receiver.begin();                      // setting-up nRF module configuration
  receiver.openReadingPipe(1, address);  // which pipe to receive data from and what is its address?
  receiver.startListening();             // set RC module to receiver mode
  
}

uint16_t values_received[4] = {IDLE_VX0, IDLE_VY0, IDLE_VX1, IDLE_VY1};           // [VX0, VY0, VX1, VY1]

void loop() {

  // if (there is received data that is waiting to be processed)
  if (receiver.available()) {
    
    receiver.read(values_received, sizeof(uint16_t)*4);
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
  
  // code for applying received data to the ESCs
  
  ExecutePitchPID();
  ExecuteRollPID();
  ExecuteYawPID();
  
  updateMotorsValues();
}

void inline ExecutePitchPID(const int16_t& set_point, const int16_t& measured_pitch, int16_t& pid_output) {
  float error;
  static float previous_error = .0;
  static float integral = .0;
  
  float proportional;
  float derivative;
  
  error = set_point - measured_angle_value;
  
  proportional = PID_PITCH_P * error;
  derivative = PID_PITCH_D * (error - (previous_error));
  integral += PID_PITCH_I * (previous_error + error)/2;
  
  
  pid_output = proportional + integral + derivative;
  
  previous_error = error;
  
}

void inline UpdateMotorsValues() {
  
}

void inline MeasurePitchRollYaw() {
  
}
