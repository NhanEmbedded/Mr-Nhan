/** Include library **/
#include "SoftwareSerial.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "SoftwareSerial.h"
/** Definiton data pin**/ 
RF24 radio(7, 8); // CE, CSN
/** Definition variable**/
const byte diachi[6] = "12345"; //Mảng kí tự dạng chuỗi có 6 kí tự
int mang[2];
int X,Y;
int ENA = 2;
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 9;
int ENB = 3;
int Speed = 150;
char dieu_khien;
void setup() {
  /** Init communication serial**/
  Serial.begin(9600);
  /**Set up the comunication with NRF24L01**/
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }
  radio.openReadingPipe(0, diachi); 
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);  
  radio.startListening();
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với TX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }
  else if(radio.available()) {
    Serial.println("ĐÃ KẾT NỐI.......");
  }

  /**Definition OUTPUT PIN**/
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
}

void loop() {
    if(radio.available()){
      radio.read(&mang, sizeof(mang));
      Serial.print("accAngleX : ");Serial.print(mang[0]); 
      Serial.print("\taccAngleY : ");Serial.println(mang[1]);
      if(mang[0]<-50){
        trai();
      }
      else if(mang[0]>50){
        phai();
      }
      else if(mang[1]<-50){
        tien();
      }
      else if(mang[1]>50){
        lui();
      }
      else if(mang[0]>-250&&mang[0]<25&&mang[1]>-25&&mang[1]<25){
        Stop();
      }
      else if(mang[0]<-30&&mang[1]<-30){
        tien_trai();  

      }
      else if(mang[0]<-30&&mang[1]>30){
        tien_phai();
      }
      else if(mang[0]>30&&mang[1]<-30){
        lui_trai();
      }
      else if(mang[0]>30&&mang[1]>30){
        lui_phai();
      }
      delay(75);
      }
}

void trai() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void phai() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void tien() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void lui() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void tien_trai() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}
void tien_phai() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

}
void lui_phai() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

}
void lui_trai() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
