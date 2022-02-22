#include <SPI.h>  // Arduino Serial Peripheral Interface protocol library

#include <RF24.h>       // RC transceiver module libraries
#include <nRF24L01.h>   

#define CE    10        // necessary for RC tranceiver
#define CSN   11      


#define VX0 A0  // left analog input
#define VY0 A1
#define VX1 A2  // right analog input
#define VY1 A3

// uncomment any of these lines for specific behavior
//#define DEBUG_MODE

RF24 transmitter(CE, CSN);      // check link for class methods: https://nrf24.github.io/RF24/classRF24.html

uint8_t address[] = "00001";    // logical address: this address must be the same on the receiving end
void setup() {
  #ifdef DEBUG_MODE
    Serial.begin(9600);
  #endif

  transmitter.begin();                    // setting-up nRF module configuration
  transmitter.stopListening();            // set RC module to transmitter mode
  transmitter.openWritingPipe(address);   // which address to write to?
  
}

void loop() {

  uint16_t values_to_send[4];           // [VX0, VY0, VX1, VY1]
  values_to_send[0] = analogRead(VX0);
  values_to_send[1] = analogRead(VY0);
  values_to_send[2] = analogRead(VX1);
  values_to_send[3] = analogRead(VY1);
  #ifdef DEBUG_MODE
    Serial.print(values_to_send[0]);
    Serial.print("\t");

    Serial.print(values_to_send[1]);
    Serial.print("\t");

    Serial.print(values_to_send[2]);
    Serial.print("\t");
    
    Serial.println(values_to_send[3]);
  #endif

  // if (packet didn't reach the receiver)
  if (!transmitter.write(values_to_send, sizeof(uint16_t)*4))
  {
    #ifdef DEBUG_MODE
      Serial.print("packet lost!");
    #endif
    // some code to inform the user of the transmitter of packet loss
  }
}
