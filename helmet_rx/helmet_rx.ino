#include <VirtualWire.h>
#include <SoftwareSerial.h>
SoftwareSerial GPRS(7, 6); //11 = TX, 12 = RX
unsigned char buffer[64]; //port
int count = 0;

int led = 3;
int rece[] = {3};
void setup() {
  GPRS.begin(9600); // the GPRS baud rate
  Serial.begin(9600);
  vw_setup(2000);
  vw_set_rx_pin(4);
  vw_rx_start();
  Serial.print("I'm ready");
  Serial.print("Hello?");

  for (int i = 0; i < 3; i++)
  {
    pinMode(rece[i], OUTPUT);
  }


}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    // Flash a light to show received good message
    // Message with a good checksum received, dump it.
    for (i = 0; i < buflen; i++)
    {
      // Serial.print(buf[i]);//print received command
      if (buf[i] == '1') //if button 1 is pressed.... i.e.forward buton
      {
        digitalWrite(led, HIGH);
        Serial.println("YES");
      }
      if (buf[i] == '2') //if button 2 is pressed.... i.e.back buton
      {

        digitalWrite(led, LOW);
        delay(100);
        MSGALCOHOL();


      }

      if (buf[i] == '3') //if button 2 is pressed.... i.e.back buton
      {
        digitalWrite(led, LOW);


      }
      if (buf[i] == '4') //if button 1 is pressed.... i.e.forward buton
      {
        MSG();
      }
      if (buf[i] == '5') //if button 1 is pressed.... i.e.forward buton
      {
      }
      Serial.print(" ");
    }
    Serial.println("");

  }
}

void MSG()
{ // if no data transmission ends, write buffer to hardware serial port


  GPRS.write("AT+CMGF=1\r"); //sending SMS in text mode
  delay(1000);
  Serial.println("AT+CMGF=1\r");
  GPRS.write("AT+CMGS=\"9425961701\"\r"); // phone number
  delay(1000);
  Serial.println("AT+CMGS=\"+919425961701\"\r");
  GPRS.write("Accident!! Latitude = 22.7203616 && Longitude = 75.8681996 \r"); // message
  delay(1000);
  Serial.println("Hello how are you?\r");
  delay(1000);
  GPRS.write(0x1A);
  //send a Ctrl+Z (end of the message)
  delay(1000);
  Serial.println("SMS sent successfully");

}
void MSGALCOHOL()
{ // if no data transmission ends, write buffer to hardware serial port


  GPRS.write("AT+CMGF=1\r"); //sending SMS in text mode
  delay(1000);
  Serial.println("AT+CMGF=1\r");
  GPRS.write("AT+CMGS=\"9425961701\"\r"); // phone number
  delay(1000);
  Serial.println("AT+CMGS=\"+919425961701\"\r");
  GPRS.write("9425961701       DRUNK!!!!          UNSAFE"); // message
  delay(1000);
  Serial.println("Hello how are you?\r");
  delay(1000);
  GPRS.write(0x1A);
  //send a Ctrl+Z (end of the message)
  delay(1000);
  Serial.println("SMS sent successfully");

}
