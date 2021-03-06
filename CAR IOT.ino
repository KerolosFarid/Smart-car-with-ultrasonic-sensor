//////define L298N or L293D enable pins ///////////////
#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
//////// define motors enable pins ///////////////////
#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)
////////////// define ultrasonic enable pins /////////////////
#define trigerpin  D0
#define  echopin   D1

int Time=0;
int distance_cm=0;
//////////////////////////////////libraries used :
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
const char* ssid = "CAR IOT PROJECT";
ESP8266WebServer server(80);

void setup() {
 
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
 ///////////////////////////////initialize BUZZER pin as output ////////
  
  pinMode (D2,OUTPUT);///buzzer
  digitalWrite(D2,LOW);
  
  /////////////// initialize ULTRASONIC pins //////////////////
  
  pinMode(trigerpin,OUTPUT);
  pinMode(echopin,INPUT);
  digitalWrite(trigerpin,LOW);  

  
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 

     server.begin();    
}

void goAhead(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goBack(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }
void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
          /////////////////////ultrasonic sensor////////////////////
    
     /* OUT PULSE SIGNAL WITH 10 MICRO SEC HIGH ON TRIGER PIN TO OPERATE UTRASONIC SENSORE */
    digitalWrite(trigerpin,HIGH);  
    delayMicroseconds(10);
     digitalWrite(trigerpin,LOW);  

     /* calculate the time of high signal on echo pin */
     Time=pulseIn(echopin,HIGH);   /* time is the time of wave go and back */
     /* Calculate distance = v(cm/microsec)* t(microsec) = 0.034*(time/2);*/
     distance_cm=(0.034*Time)/2;
     /* print distance on serial monitor*/
     Serial.print(distance_cm);
     Serial.println("cm");
     
     if (distance_cm<=30)
     {
        digitalWrite (D2,HIGH);///buzzer
        stopRobot();

      }
      else
      {
        digitalWrite (D2,LOW);///buzzer
         command = server.arg("State");
      }
      delay(100);
}


void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
