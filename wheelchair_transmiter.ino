//wheel chair nsic nrf

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>  //To create PWM signals we need this lybrary
    int stateee = 0;

RF24 radio(PB0, PA4); // CE, CSN

// const byte address[6] = "0xF0F0F0F0E1LL";
const uint64_t address = 0xF0F0F0F0E1LL;
int INA=PB8;
int INB=PA1;
int PWM_pin = PB6;
int speed=0;
int INA2=PC14;
int INB2=PC13;
int PWM_pin2 = PB7;
int Switch_pin = PB12;
int Switch_pin_data=0;



int forward_channel,backward_channel,right_channel,left_channel;
int ch1 = -1;
  int ch2= -1;  
  int ch3= -1;
  int ch4= -1;
  int ch5= -1;
  int ch6= -1;
  int ch7= -1;


  Servo channel_1;
Servo channel_2;
Servo channel_3;
Servo channel_4;
Servo channel_5;
Servo channel_6;
Servo channel_7;

void reset_the_Data() 
{
  // 'safe' values to use when NO radio input is detected
  ch1 = 0;      //Throttle (channel 1) to 0
  ch2 = 127;
  ch3 = 127;
  ch4 = 127;
  ch5 = 0;
  ch6 = 0;
  ch7 = 0;
}



void setup() {
  Serial.begin(9600);
pinMode(INA,OUTPUT);
pinMode(INB,OUTPUT);
pinMode(Switch_pin,INPUT_PULLUP);
pinMode(PWM_pin,OUTPUT);


pinMode(INA2,OUTPUT);
pinMode(INB2,OUTPUT);
pinMode(PWM_pin2,OUTPUT);
   channel_1.attach(2);
  channel_2.attach(3);
  channel_3.attach(4);
  channel_4.attach(5);
  channel_5.attach(6);
//  channel_6.attach(7);
//  channel_7.attach(8);
   //We reset the received values
radio.begin();
Serial.print("ADDRESS :");
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();   


ch1 = 491;
ch2 =501;
ch3 =127;
ch4 = 127;
}

unsigned long lastRecvTime = 0;

int numbers[10];  // Array to store the extracted numbers

int ch1_value = 0;
int ch2_value = 0;
int ch3_value = 0;
int ch4_value = 0;
int ch5_value = 0;
int ch6_value = 0;
int ch7_value = 0;

int direction_changed =0;
int direction_state =0;

void loop() {
// Switch_pin_data
    // vehicle_left();
//   while (!radio.available()) {
// forward_channel=0;
// backward_channel=0;;

// right_channel = 0;
// left_channel = 0;
// vehicle_stop();

// ch1 = 491;
// ch2 =501;
// ch3 =127;
// ch4 = 127;

// }

// //    delay(200);


// //  digitalWrite(INA2,HIGH);
// //  digitalWrite(INB2,LOW);
  //  vehicle_right();
//  analogWrite(PWM_pin2,forward_channel);
//   analogWrite(PWM_pin,forward_channel);

// vehicle_forward();
// Serial.println("forward");

// Serial.print("xraw: ");
  // Serial.println(String(ch1));
  if (radio.available()) {
    char text[50] = "";
    
    int numCount = 0; // Counter for the number of extracted numbers

    radio.read(&text, sizeof(text));


// Remove first "=" symbol
  memmove(text, text + 1, strlen(text));

         
  // Split the string at "=" symbols and convert each number to int
  char* token = strtok(text, "=");
  while (token != NULL && numCount < 10) {
    int num = atoi(token);
    numbers[numCount] = num;
    numCount++;
    token = strtok(NULL, "=");
  }

  ch1 = numbers[0];
  ch2 = numbers[1];
  ch3 = numbers[2];
  ch4 = numbers[3];
  ch5 = numbers[4];
  ch6 = numbers[5];
  ch7 = numbers[6];

  // Serial.print("forward Channel: ");
  // Serial.println(forward_channel);
  // Serial.println(backward_channel);
  // Serial.println(right_channel);
  // Serial.println(left_channel);
  // delay(1000);


//forward_channel=map(ch2,501,1019,0,speed);
//backward_channel=map(ch2,501,0,0,speed);

//right_channel = map(ch1,491,0,0,speed);
//left_channel = map(ch1,491,1019,0,speed);

forward_channel=120;
backward_channel=120;

right_channel = 120;
left_channel = 120;

// forward y = 2100   y= 1800

// right x = 2100   x = 1800

// if(ch1==0 && ch2==0 && ch3 == 0 && ch4==0)
// {
// speed=0;

  
//   if(ch2>1800) 
//   {

// speed=150;

//   }

//     else if(ch2>1950) 
//   {

// speed=200;

//   }
  

// }

// else {

// delay(1000);

// }
  ch1_value = map(ch1,0,255,1000,2000);
  ch2_value = map(ch2,0,255,1000,2000);
  ch3_value = map(ch3,0,255,1000,2000);
  ch4_value = map(ch4,0,255,1000,2000);
  ch5_value = map(ch5,0,1,1000,2000);
  ch6_value = map(ch6,0,1,1000,2000);
  ch7_value = map(ch7,0,255,1000,2000);

  Serial.print("ch1: ");
  Serial.println(String(ch1));   
  Serial.print("ch2: ");
  Serial.println(String(ch2));// forward >1850  //  back <1400      ch1>>= 1600to 1700
  // Serial.print("zraw: ");
  // Serial.println(String(ch3));
  // Serial.print("Channe5: ");
  // Serial.println(String(ch4));
  // Serial.print("Channe5: ");
  // Serial.println(String(ch5));
  // Serial.print("Channe7: ");
  // Serial.println(String(ch7));
  //Creathe the PWM signals
  channel_1.writeMicroseconds(ch1_value);  
  channel_2.writeMicroseconds(ch2_value);  
  channel_3.writeMicroseconds(ch3_value);  
  channel_4.writeMicroseconds(ch4_value);  
  channel_5.writeMicroseconds(ch5_value);  
//  channel_6.writeMicroseconds(ch6_value);  
//  channel_7.writeMicroseconds(ch7_value); 
   
  Serial.println("========================================================");

//   analogWrite(PWM_pin2,speed);
// analogWrite(PWM_pin,speed);
// Serial.println("right");


// m2_back();
// m1_forward();
// delay(1000);
  
  if(ch2>1800) 
  {

//     if(ch2>1950)
// {
//  analogWrite(PWM_pin2,200);
// analogWrite(PWM_pin,200);

// }
// else{



 analogWrite(PWM_pin2,160);
analogWrite(PWM_pin,160);
Serial.println("right");
// }



m2_forward();
m1_forward();
  }

  else if(ch2<1500)
  {
// if(ch2<1400)
// {
//  analogWrite(PWM_pin2,200);
// analogWrite(PWM_pin,200);

// }
// else{



 analogWrite(PWM_pin2,160);
analogWrite(PWM_pin,160);
Serial.println("right");
// }


m2_back();
m1_back();

  }




  else if((ch2>1600 && ch2<1750) && (ch2>1600 && ch2<1750)  && ch1>1600 && ch1<1750  )
  {

 for (int i = 170; i >= 0; i--) {
    analogWrite(PWM_pin2, i);
    analogWrite(PWM_pin, i);
    delay(5); // Delay for smooth transition
  }
m1_stop();
m2_stop();
  }



  if(ch1>1800) 
  {
 analogWrite(PWM_pin2,170);
analogWrite(PWM_pin,170);
// Serial.println("right");


// m2_stop();

//  for (int i = 255; i >= 0; i--) {
//     analogWrite(PWM_pin2, i);
// //     // analogWrite(PWM_pin, i);
//     delay(1); // Delay for smooth transition

//   }

//   // }

// m2_stop();

m1_forward();
m2_back();


  }




 if(ch1<1500) 
  {
 analogWrite(PWM_pin2,170);
analogWrite(PWM_pin,170);
// Serial.println("right");

m2_forward();
m1_back();



  }



  }

  else {


      m1_stop();
m2_stop();
  }



  //////////This small if will reset the data if signal is lost for 1 sec.
/////////////////////////////////////////////////////////////////////////
  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
    // signal lost?
    reset_the_Data();
  
    //Go up and change the initial values if you want depending on
    //your aplications. Put 0 for throttle in case of drones so it won't
    //fly away
  } 

  
  
}


void m1_stop()


{

  digitalWrite(INA,LOW);
  digitalWrite(INB,LOW);
  analogWrite(PWM_pin,0);



}



void m2_stop()


{

  digitalWrite(INA2,LOW);
  digitalWrite(INB2,LOW);
  analogWrite(PWM_pin,0);



}

void vehicle_forward()
{

m2_forward();
m1_forward();



}

void vehicle_backward()

{

m2_back();
  
m1_back();


}

void vehicle_right()
{
m2_forward();
m1_back();

// m2_stop();
// m1_stop();

}

void vehicle_left()
{


m1_forward();
m2_stop();

// Serial.println("left");


}

void m2_back()
{

  digitalWrite(INA2,LOW);
  digitalWrite(INB2,HIGH);


}




void m2_forward()
{

  digitalWrite(INA2,HIGH);
  digitalWrite(INB2,LOW);


}


void m1_forward()


{

  digitalWrite(INA,HIGH);
  digitalWrite(INB,LOW);
  // analogWrite(PWM_pin2,255);



}



void m1_back()


{

  digitalWrite(INA,LOW);
  digitalWrite(INB,HIGH);



}

void vehicle_stop()
{
m1_stop();
m2_stop();


  
}