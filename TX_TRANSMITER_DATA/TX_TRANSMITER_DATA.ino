
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
MPU6050 mpu6050(Wire);  
RF24 radio(7, 8); // CE, CSN  
const byte diachi[6] = "12345"; //Mảng kí tự dạng chuỗi có 6 kí tự
int mang[2];
int X,Y;
void setup() 
{
  Serial.begin(9600);
  Wire.begin(); 
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  } 
  
  radio.openWritingPipe(diachi);
  //Lệnh openWritingPipe mặc định là đường truyền 0
 //mở 1 kênh có địa chỉ 12345 trên đường truyền 0
  // kênh này ghi data lên địa chỉ 12345  
  radio.setPALevel(RF24_PA_MIN); 
  //Cài bộ khuyết địa công suất ở mức MIN, MAX, HIGH, LOW
  radio.setChannel(80); // 125 kênh từ 0-124; TX và RX phải cùng kênh
  radio.setDataRate(RF24_250KBPS); //Tốc độ truyền dữ liệu trong không khí

  radio.stopListening(); //Cài đặt module là TX
  
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }  
}

void loop() 
{
  if(Serial.available() > 0) {
    Serial.print("Co Du Lieu");
  }
  else{
  mpu6050.update();
  Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
  Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
  mang[0] = mpu6050.getAccAngleX();
  mang[1] = mpu6050.getAccAngleY();
  radio.write(&mang, sizeof(mang));
  Serial.println("đã gửi");
  delay(10);
  }
}
