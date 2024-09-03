//#include <WiFi.h>
//#include "ThingSpeak.h"
#include "ACS712.h"

#define IPV_Pin  13
#define IBat_Pin 12
#define VPV_Pin  14
#define VBat_Pin  27
ACS712 SensIPV(ACS712_20A, IPV_Pin);
ACS712 SensIBat(ACS712_20A, IBat_Pin);

#define Detik 1000
#define TOKirim 60

#define SENSITIVITY 0.185
#define OFFSET 0

char ssid[] = "Pohon Belimbing";
char password[] = "klentang25";
int keyIndex = 0;            // your network key Index number (needed only for WEP)
//WiFiClient  client;
unsigned long myChannelNumber = 2031006;
const char * myWriteAPIKey = "S0EF93DYB4TMUAD6";

int VPV, VBat = 0;
float IPV, IBat = 0;
unsigned long prevmillis = 0;
bool TimeToSend, Kirim = false;
uint8_t detik = 0;

void setup() {
  Serial.begin(115200);
  pinMode(IPV_Pin, INPUT);
  pinMode(IBat_Pin, INPUT);
  pinMode(VPV_Pin, INPUT);
  pinMode(VBat_Pin, INPUT);

  int zero = SensIPV.calibrate();
  Serial.printf("Zero point PV = %d\r\n", zero);
  SensIPV.setZeroPoint(zero);
  zero = SensIBat.calibrate();
  Serial.printf("Zero point Bat = %d\r\n", zero);
  SensIBat.setZeroPoint(zero);

  delay(500);
  
//  WiFi.mode(WIFI_STA);
//  uint8_t x = 0;
//  do {
//    WifiStatus();
//    x++;
//    delay(1000);
//  }
//  while(x < 5);
//  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  int ADCPV = analogRead(VPV_Pin);
  int ADCBat = analogRead(VBat_Pin);

  if(millis() - prevmillis >= Detik) {
    prevmillis = millis();
    detik++;
    VPV = ADCPV;
    VBat = ADCBat;
    IPV = readIPV();
    IBat = readIBat();
    Serial.printf("VPV: %d|VBat: %d|IPV: %0.2f|IBat: %0.2f\r\n", VPV, VBat, IPV, IBat);
    if(detik > TOKirim) { detik = 0; TimeToSend = true; }
    
//    if(TimeToSend) {
//      if(WifiStatus()) {
//        TimeToSend = false;
//        Kirim = true;
//      }
//      else {
//        TimeToSend = false;
//      }
//    }
  }

  if(Kirim) {
//    SendToThinspeak();
    Kirim = false;
  }
}

float readIPV() {
  float I = 0.0;
  for (int g = 0; g < 5; g++) {
    I += SensIPV.getCurrentDC();
    delay(5);
  }
  I /= 5.0;
  float Amp = I;
  return Amp;
}

float readIBat() {
  float I = 0.0;
  for (int g = 0; g < 5; g++) {
    I += SensIBat.getCurrentDC();
    delay(5);
  }
  I /= 5.0;
  float Amp = I;
  return Amp;
}

void SendToThinspeak() {
  // set the fields with the values
//  ThingSpeak.setField(1, VPV);
//  ThingSpeak.setField(2, IPV);
//  ThingSpeak.setField(3, VBat);
//  ThingSpeak.setField(4, IBat);
//
//  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
//  if(x == 200) { Serial.println("Channel update successful."); }
//  else { Serial.println("Problem updating channel. HTTP error code " + String(x)); }
}

bool WifiStatus() {
/* // Jika harus dipastikan sampai terkoneksi dulu
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print("."); //delay(1000);
    }
    Serial.println("\nConnected.");
  }
 */
/* // Jika hanya cek saja sekali, lalu kembali ke loop
 */
//  WiFi.begin(ssid, password);
//  if(WiFi.status() != WL_CONNECTED) {
//    Serial.println("Connecting to WiFi...");
//    return false;
//  }
//  else {
//    Serial.println("Connected to WiFi");
//    return true;
//  }
}
