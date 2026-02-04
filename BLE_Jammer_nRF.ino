//RF24 Lib by TMRh20

 #include "RF24.h"

RF24 radio(9, 10);  
byte i = 45;  // initial channel
unsigned int flag = 0;  // flag to control channel hopping direction

void setup() {
  Serial.begin(115200);  
 if (radio.begin()) {
    delay(200);
    Serial.println("radio initialized!");
    radio.setAutoAck(false);       // Ack off
    radio.stopListening();         // Tx
    radio.setRetries(0, 0);        // ard lite
    radio.setPayloadSize(5);       // 5 bytes
    radio.setAddressWidth(3);      // address width - 3 bytes
    radio.setPALevel(RF24_PA_MAX, true); // max power ampl
    radio.setDataRate(RF24_2MBPS); // 2Mbps data rate
    radio.setCRCLength(RF24_CRC_DISABLED); // crc lite
    radio.printPrettyDetails();    // print details
    radio.startConstCarrier(RF24_PA_MAX, i);  // continuous carrier
  } else {
    Serial.println("Failed to initialize radio!");
  }
}

void loop() {
  // sweep through all channels (0 to 79)
   for (int i = 0; i < 79; i++) {
    radio.setChannel(i);
   }
    // BLE advertising channels (37, 38, 39)
  byte ble_channels[] = {37, 38, 39};
  for (int j = 0; j < 3; j++) {
    radio.setChannel(ble_channels[j]);
  }
}