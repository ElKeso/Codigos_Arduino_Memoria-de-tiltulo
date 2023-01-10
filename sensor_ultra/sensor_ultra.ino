  int trig = 10;
  int eco = 9;
  int buzz =4;
  int duracion;
  int distancia;


void setup() {

  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  pinMode(buzz, OUTPUT);

}

void loop() {
  digitalWrite(trig,HIGH);
  delay(1);
  digitalWrite(trig,LOW);
  duracion=pulseIn(eco,HIGH);
  distancia=duracion/58.2;
  delay(200);
  if (distancia>10){
    digitalWrite(buzz,HIGH);
  } else {
    digitalWrite(buzz,LOW);
  }
}
