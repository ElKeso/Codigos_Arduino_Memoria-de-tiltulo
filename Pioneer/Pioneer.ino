
#include "HX711.h"
#include "ros.h"
#include "std_msgs/Float64.h"

ros::NodeHandle nh;

std_msgs::Float64 data;

ros::Publisher pub("/peso", &data);

//variables
//sensor seguridad
  int trig = 10;
  int eco = 9;
  int buzz = 11;
  int duracion;
  int distancia;

//peso
const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;
HX711 scale;
//
void setup() {
  nh.initNode();
  nh.advertise(pub);
  
  //setup sensor de seguridad
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  pinMode(buzz, OUTPUT);
  //

  //peso
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  //
}

void loop() { 
    //peso
    if (scale.is_ready()) {
    float reading = scale.read();
    data.data=reading;
    Serial.print("HX711 reading: ");
    Serial.println(reading);
    } else {
    Serial.println("HX711 not found.");
    }
    //

    //seguridad
    digitalWrite(trig,HIGH);
    delay(1);
    digitalWrite(trig,LOW);
    duracion=pulseIn(eco,HIGH);
    distancia=duracion/58.2; 
    if (distancia>15){
    digitalWrite(buzz,HIGH);
    } else {
    digitalWrite(buzz,LOW);
    }
    //
    pub.publish(&data);
    delay(100);
    nh.spinOnce();
}
