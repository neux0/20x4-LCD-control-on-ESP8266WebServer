#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
LiquidCrystal_I2C lcd(0x27, 20, 4);

const String wSSID = "YOUR-SSID";
const String wPASS = "YOUR-PASS";

String satir0 = "";
String satir1 = "";
String satir2 = "";
String satir3 = "";

void setup() {
  Serial.begin(115200);
  Serial.println();
  lcd.begin(20,4);
  lcd.init();
  lcd.backlight();
  wifiConnect();
  server.on("/",rootPageHandler);
  server.on("/degistir",degistirPageHandler);
  server.begin();
}

void loop() {
  server.handleClient();

}

void rootPageHandler(){
  String icerik = "<html lang=\"tr\"> <head> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>LCD Control</title> <style> body{background-color: #424342;} form{ display: flex; flex-direction: column; align-items: center; background-color: #256D1B; width: 300px; height: 300px; border-radius: 20px; } input{ margin-bottom: 5px; height: 30px; border-radius: 10px; border: none; padding: 5px; } input:focus{ border: none; background-color: white; } h2{ color: #1EFC1E; font-family: Arial, Helvetica, sans-serif; font-size: 30px; text-shadow: black 0px 1px 3px; letter-spacing: 4px; } .buton{ width: 100px; margin-top: 5px; } span{ margin-top: 10px; color: #149911; } </style> </head> <body> <center> <form action=\"/degistir\" method=\"get\"> <h2>LCD Control</h2> <input type=\"text\" name=\"satir0\" maxlength=\"20\" placeholder=\"Satir 0\" value=\"" + satir0 + "\"> <input type=\"text\" name=\"satir1\" maxlength=\"20\" placeholder=\"Satir 1\" value=\"" + satir1 + "\"> <input type=\"text\" name=\"satir2\" maxlength=\"20\" placeholder=\"Satir 2\" value=\"" + satir2 + "\"> <input type=\"text\" name=\"satir3\" maxlength=\"20\" placeholder=\"Satir 3\" value=\"" + satir3 + "\"> <input class=\"buton\" type=\"submit\" value=\"Değiştir\"> <span>by neux</span> </form> </center> </body> </html>";
  server.send(200,"text/html",icerik);
}

void degistirPageHandler(){
  lcd.clear();
  satir0 = server.arg("satir0");
  satir1 = server.arg("satir1");
  satir2 = server.arg("satir2");
  satir3 = server.arg("satir3");
  lcd.setCursor(0,0);
  lcd.print(satir0);
  lcd.setCursor(0,1);
  lcd.print(satir1);
  lcd.setCursor(0,2);
  lcd.print(satir2);
  lcd.setCursor(0,3);
  lcd.print(satir3); 
  server.sendHeader("Location","/");
  server.send(301,"text/html","");
}

void wifiConnect(){
  WiFi.begin(wSSID,wPASS);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WIFI'YE BAGLANILIYOR");
  lcd.setCursor(0,1);
  lcd.print("SSID: " + wSSID);
  lcd.setCursor(0,2);
  lcd.print("PASS: " + wPASS);
  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BAGLANILAMADI!");
    lcd.setCursor(0,1);
    lcd.print("RESTART ATILIYOR");
    delay(500);
    ESP.restart();
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BAGLANTI KURULDU ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP()); 
}