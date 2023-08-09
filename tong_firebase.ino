
// Include the necessary libraries
#include <FirebaseESP32.h>         //thư viện firebase
#include <Wire.h>                  //thư viện giao tiếp i2c
#include <LiquidCrystal_I2C.h>     //thư viện lcd i2c
#include <OneWire.h>               //thư viện dây cb ds18b20
#include <DallasTemperature.h>     //thư viện cb ds18b20
#include <WiFi.h>                  //thư viện wifi
#include <ESP32Servo.h>            //thư viện động cơ servo
#include <RTClib.h>                //thư viện rtos ds1307
// Define the pin numbers
#define ECHO_PIN 12         // Input pin for the distance sensor
#define TRIGGER_PIN 13      // Output pin for the distance sensor
#define XA 4                // Relay pin for val motor control
#define BOM 5               // Relay pin for pump motor control
#define oneWireBus 18       // OneWire bus pin
int sensorPin = 34;
#define FIREBASE_HOST "pj2-aquarium-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "RW0koxDD6VRmkeLlOiJyYSLK7CAkQMrChz4eHEbT"

//Define FirebaseESP32 data object
FirebaseData fbdo;

// Create instances of necessary libraries
OneWire oneWire(oneWireBus);                        // OneWire instance
DallasTemperature sensors(&oneWire);                // DallasTemperature instance
Servo servo;
// Variables
unsigned long duration;                             // Time duration for distance measurement
int distance;                                       // Distance value
char ssid[] = "vietpham";                         // Wi-Fi network SSID
char pass[] = "11111111";                       // Wi-Fi network password            // Wi-Fi network password

RTC_DS1307 rtc;                                    // khởi tạo một đối tượng của lớp RTC_DS1307, cho phép tương tác với mô-đun RTC DS1307. Đối tượng này được đặt tên là rtc.
LiquidCrystal_I2C lcd(0x27, 16,2);                 // khởi tạo biến lcd trong liquidcrystal
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


void setup() {
  // Set trạng thái các chân ra hoặc vào
    servo.attach(19);  // động cơ servo ở chân 19 của esp
    pinMode(ECHO_PIN, INPUT); // hcsr04
    pinMode(TRIGGER_PIN, OUTPUT); // hcsr04
    pinMode(XA, OUTPUT);  // relay xả
    pinMode(BOM, OUTPUT); // relay bơm

  // Initialize Serial communication
    Serial.begin(115200);                              

  // Kết nối Wifi
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());

    //kết nối firebase
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    //Set database read timeout to 1 minute (max 15 minutes)
    Firebase.setReadTimeout(fbdo, 1000 * 60);
    //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
    Firebase.setwriteSizeLimit(fbdo, "tiny");

  // khởi tạo lcd 
    lcd.init();                         // initialize the lcd 
    lcd.init();
    lcd.backlight();                    //To Power ON the back light
    if (! rtc.begin())                  // nếu rtos không kết nối
     {
       lcd.print("Couldn't find RTC");  // màn hình lcd hiện ko tìm thấy rtos
       while (1);                       // để vòng lặp vô tân cho tới khi có rtos kết nối
     }
    if (! rtc.isrunning())              // nếu rtos không chạy, hoạt động
      {
        lcd.print("RTC is NOT running!");  // màn hình lcd hiện rtos không chạy
      }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   //rtos tự cập nhật thời gian từ máy tính
    // Start the DS18B20 sensor
    sensors.begin();       // sensor ds18b20 bắt đầu hoạt động                            
}
// hiển thị ngày và giờ lên LCD
void LCD()
{
    DateTime now = rtc.now();
    lcd.setCursor(0, 1);
    lcd.print("TIME");
    lcd.print(" ");
    lcd.print(now.hour());
    lcd.print(':');
    lcd.print(now.minute());
  //  lcd.print(':');
   // lcd.print(now.second());
    lcd.print("  ");

    lcd.setCursor(0, 0);
    lcd.print("DATE");
    lcd.print(" ");
    //lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    //lcd.print(" ");
    lcd.print(now.day());
    lcd.print('/');
    lcd.print(now.month());
    lcd.print('/');
    lcd.print(now.year());
    lcd.print("  ");    
}
// Đo mực nước
int getWaterLevel() {
  long duration;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = int(duration / 2 / 29.412);
  return distance;
}

// In khoảng cách lên serial monitor
/*void printDistance() {
  int waterLevel = getWaterLevel();
  Serial.print("Distance: ");
  Serial.print(waterLevel);
  Serial.println("cm");
}
*/
// Chương trình đo nhiệt độ bằng ds18b20
float measureTemperature() {
  sensors.requestTemperatures();                    // Gửi yêu cầu đo nhiệt độ từ cảm biến
  float temperatureC = sensors.getTempCByIndex(0);  // Đọc nhiệt độ đo được theo độ Celsius từ cảm biến
  float temperatureF = sensors.getTempFByIndex(0);  // Đọc nhiệt độ đo được theo độ Fahrenheit từ cảm biến
  //Serial.print("Temperature: ");                    // In ra dòng chữ "Temperature: " trên cổng Serial
  //Serial.print(temperatureC);                       // In ra giá trị nhiệt độ Celsius trên cổng Serial         
  //Serial.print("°C  ");                             // In ra ký tự độ Celsius trên cổng Serial
  //Serial.print(temperatureF);                       // In ra giá trị nhiệt độ Fahrenheit trên cổng Serial
  //Serial.println("°F");                             // In ra ký tự độ Fahrenheit và xuống dòng trên cổng Serial
  return temperatureC;
}

// mode tự động của bơm nước
void automode() {
  int waterLevel = getWaterLevel();                 // Lấy giá trị mức nước từ cảm biến
  if (waterLevel > 10) {                            // Nếu mức nước lớn hơn 10
    digitalWrite(XA, HIGH);                         // Bật motor theo chiều một chiều
    digitalWrite(BOM, LOW);                         // Tắt motor theo chiều ngược lại
  }
  else if (waterLevel >= 6 && waterLevel <= 10) {   // Nếu mức nước nằm trong khoảng từ 6 đến 10
    digitalWrite(XA, LOW);                          // Tắt motor theo chiều một chiều
    digitalWrite(BOM, LOW);                         // Tắt motor theo chiều ngược lại
  }
  else if (waterLevel < 6) {                        // Nếu mức nước nhỏ hơn 6
    digitalWrite(BOM, HIGH);                        // Bật motor theo chiều ngược lại
    digitalWrite(XA, LOW);                          // Tắt motor theo chiều một chiều
  }
}

// mode tự chỉnh của bơm nước
void manualmode() {
  if(Firebase.getString(fbdo, "/pj2-aqua/sw_pump"))
  {
   // Serial.println("pump success");
    if(fbdo.stringData() == "ON") {
      digitalWrite(BOM, HIGH);
    } else {
      digitalWrite(BOM, LOW);
    }  
  }//else {
  //  Serial.println("pump fail"); 
  
  
  if(Firebase.getString(fbdo, "/pj2-aqua/sw_val"))
  {
    //Serial.println("val success");
    if(fbdo.stringData() == "ON") {
      digitalWrite(XA, HIGH); 
    } else {
      digitalWrite(XA, LOW);
    }  
  }//else {
    //Serial.println("val fail"); 
 // }
  
}

// nút cho cá ăn
void fishfeeder()
{
  if(Firebase.getString(fbdo, "/pj2-aqua/sw_feed"))
  {
    //Serial.println("feed success");
    if(fbdo.stringData() == "ON") {
      servo.write(180);
    } else {
      servo.write(0);
    }  
  }
  //else {
   // Serial.println("feed fail"); 
  }


void loop() {
  //delay(200);            // chờ 1s
  DateTime now = rtc.now();
    LCD();                 // hiển thị ngày và giờ lên lcd

  float temp = measureTemperature();
  int waterLevel = getWaterLevel();
  int sensorValue = analogRead(sensorPin);
  int turbidity = map(sensorValue, 0, 2600, 100, 0);
  //set dữ liệu nhietdo, doduc, mucnuoc lên firebase
  if(Firebase.setDouble(fbdo, "/pj2-aqua/nhietdo",temp) && Firebase.setDouble(fbdo, "/pj2-aqua/mucnuoc",waterLevel)&& Firebase.setDouble(fbdo, "/pj2-aqua/doduc",turbidity))  
    Serial.println("Upload success");  
  else
    Serial.println("Upload fail"); 
  
  //get dữ liệu 
  if(Firebase.getString(fbdo, "/pj2-aqua/sw_mode"))
  {
    //Serial.println("mode success");
    if(fbdo.stringData() == "ON")
      automode();
    else
      manualmode();   
  }
  //else {
   // Serial.println("mode fail"); 
  

  fishfeeder();          // chương trình cho cá ăn
//  printDistance();       // chương trình in khoảng cách lên serial
  //LCD();                 // hiển thị ngày và giờ lên lcd
  //DateTime now = rtc.now();
   // Serial.print(now.hour());
    //Serial.print(':');
  ////  Serial.print(now.minute());
  //  Serial.print(now.second());
}
