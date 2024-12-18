#include <WiFi.h>
#include <HTTPClient.h>
#include<UrlEncode.h>
const char* ssid = "";
const char* password = "";
String phoneNumber = "";
String apiKey = "";

Page | 7
int LED[] ={27,13,19,21,22,23,25};
int one[] ={1,0,0,1,1,1,1};
int two[]={0,0,1,0,0,1,0};
int three[]={0,0,0,0,1,1,0};
int four[]={1,0,0,1,1,0,0};
int five[]={0,1,0,0,1,0,0};
int six[]={0,1,0,0,0,0,0};
int seven[]={0,0,0,1,1,1,1};
int eight[]={0,0,0,0,0,0,0};
int nine[]={0,0,0,0,1,0,0};
int zero[]={0,0,0,0,0,0,1};
int trigPin1=2;
int echoPin1=4;
int trigPin2=5;
int echoPin2=18;
int measureDistance(int trigPin, int echoPin){

 digitalWrite(trigPin,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin,LOW);
 int duration=pulseIn(echoPin,HIGH);
 return ((duration/2)/29.1);

}
int timeoutCounter=0;
int currentPeople=0;
String sequence="";
int distance1, distance2;

Page | 8
int initialDistance =30;
void sendMessage(char* message){
 // Data to send with HTTP POST
 String url = "https://api.callmebot.com/whatsapp.php?phone=" +
phoneNumber + "&apikey=" + apiKey + "&text=" +
urlEncode(message);
 HTTPClient http;
 http.begin(url);
 // Specify content-type header
 http.addHeader("Content-Type", "application/x-www-formurlencoded");

 // Send HTTP POST request
 int httpResponseCode = http.POST(url);
 if (httpResponseCode == 200){
 Serial.print("Message sent successfully");
 }
 else{
 Serial.println("http response code error: ");
 Serial.println(httpResponseCode);
 }
 http.end();
}
void setup() {
 // put your setup code here, to run once:
 WiFi.begin(ssid, password);
 Serial.println("Connecting");
 while(WiFi.status() != WL_CONNECTED) {
 delay(100);
 Serial.print(".");

Page | 9
 }
 Serial.println("");
 Serial.print("Connected to WiFi network with IP Address: ");
 Serial.println(WiFi.localIP());
 // Send Message to WhatsAPP
 sendMessage("hello we are iot rookies");

 for(int i=0;i<7;i++)pinMode(LED[i],OUTPUT);

 pinMode(trigPin1,OUTPUT);
 pinMode(echoPin1,INPUT);
 pinMode(trigPin2,OUTPUT);
 pinMode(echoPin2,INPUT);
 Serial.begin(115200);
}
void loop() {
delay(700);
 // put your main code here, to run repeatedly:
 distance1=measureDistance(trigPin1,echoPin1);
 distance2=measureDistance(trigPin2,echoPin2);
 if(distance1 < initialDistance && sequence.charAt(0)!='1'){
 sequence +="1";
 }else if(distance2 < initialDistance && sequence.charAt(0)!='2'){
 sequence +="2";
 }
 if(sequence.equals("12")){
 currentPeople++;
 sequence="";
 delay(100);

Page | 10
 }else if(sequence.equals("21") && currentPeople>0){
 currentPeople--;
 sequence="";
 delay(100);
 }
 //Reset the sequence if it is invalid or timeouts
 if(sequence.length()>2 || sequence.equals("11") ||
sequence.equals("22") || timeoutCounter >200){
 sequence="";
 }
 if(sequence.length()==1){
 timeoutCounter++;
 }else{
 timeoutCounter=0;
 }

 Serial.println("Number of people in the room : ");
 Serial.println(currentPeople);
 if(ssd>9){
 ssd=0;
 }
 switch(currentPeople){
 case 1:
 for(int i=0;i<7;i++)digitalWrite(LED[i],one[i]);
 delay(20);
 break;
 case 2:
 for(int i=0;i<7;i++)digitalWrite(LED[i],two[i]);
 delay(20);

Page | 11
 break;
 case 3:
 for(int i=0;i<7;i++)digitalWrite(LED[i],three[i]);
 delay(20);
 break;
 case 4:
 for(int i=0;i<7;i++)digitalWrite(LED[i],four[i]);
 delay(20);
 break;
 case 5:
 for(int i=0;i<7;i++)digitalWrite(LED[i],five[i]);
 delay(20);
 break;
 case 6:
 for(int i=0;i<7;i++)digitalWrite(LED[i],six[i]);
 delay(20);
 break;
 case 7:
 for(int i=0;i<7;i++)digitalWrite(LED[i],seven[i]);
 delay(20);
 break;
 case 8:
 for(int i=0;i<7;i++)digitalWrite(LED[i],eight[i]);
 delay(20);
 break;
 case 9:
 for(int i=0;i<7;i++)digitalWrite(LED[i],nine[i]);
 delay(20);
 break;
 case 0:
 for(int i=0;i<7;i++)digitalWrite(LED[i],zero[i]);
 delay(20);
 break;
 }

Page | 12
 Serial.println(distance1);
 Serial.println(distance2);

 if(currentPeople>7){
 sendMessage("number of people exceeds the limit of 5 people");

 }
}