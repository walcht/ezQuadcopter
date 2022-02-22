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
// motor_00     motor_01
//    \           /
//     \---------/
//                >
//     /---------\
//    /           \
// motor_02     motor_03
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

// uncomment any of these lines for specific behavior
//#define DEBUG_MODE

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
  
}
