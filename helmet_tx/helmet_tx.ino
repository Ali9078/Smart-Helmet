#include<VirtualWire.h>

int shock =5;
int alcohol =3;
int limit =2;
int sensor[]={3,5};
int sense[]={2};


void setup()
{
Serial.begin(9600);   
    Serial.println("setup");
    vw_setup(2000);  
    vw_set_tx_pin(4);// set TX Pin As RF 434 Module

     for(int i = 0; i<4 ; i++)
    {
      pinMode(sensor[i], INPUT);
     pinMode(sense[i],INPUT);
     digitalWrite(sense[i],HIGH);
    }  

}

void loop() {
 char *msg;
  alcohol = digitalRead(3);
  shock = digitalRead(5);
  Serial.println(digitalRead(limit));
  delay(200);
  if(alcohol == 1 && digitalRead(limit) == HIGH)//IF HELMET IS WORN
  {
    char *msg = "1";//send 1 to the receiver
    vw_send((uint8_t *)msg, strlen(msg));//send the byte to the receiver
    vw_wait_tx(); // Wait until the whole message is gone
  }
  
  if(alcohol == 0 && digitalRead(limit) == HIGH )//IF ALCOHOL IS SENSED
  {
    char *msg = "2";///send 2 to the receiver
    vw_send((uint8_t *)msg, strlen(msg));//send the byte to the receiver
    vw_wait_tx(); // Wait until the whole message is gone
  }

    if(digitalRead(limit) == LOW)//if helmet is not worn
  {
    char *msg = "3";///send 2 to the receiver
    vw_send((uint8_t *)msg, strlen(msg));//send the byte to the receiver
    vw_wait_tx(); // Wait until the whole message is gone
  }
  if(shock == HIGH)//if the back button is pressed
  {
    char *msg = "4";///send 2 to the receiver
    vw_send((uint8_t *)msg, strlen(msg));//send the byte to the receiver
    vw_wait_tx(); // Wait until the whole message is gone
  }
  if(shock == LOW)//if the back button is pressed
  {
    char *msg = "5";///send 2 to the receiver
    vw_send((uint8_t *)msg, strlen(msg));//send the byte to the receiver
    vw_wait_tx(); // Wait until the whole message is gone
  }
}
