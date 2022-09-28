#include "crankshaft.hpp"
#include "angle.hpp"

const int CRANKSHAFT_PIN = 12;
//CCrankshaft *cshaft;
CAngle *angle;
//
//void edge(int id, unsigned long ts, void * arg) {
//  Serial.print("EDGE ");
//  Serial.print(id);
//  Serial.print(" ");  
//  Serial.println(ts);
//}

void setup() {
  Serial.begin(115200);
  Serial.println("Started");
//  cshaft = new CCrankshaft(edge, NULL);
  angle = new CAngle(60, 2);
  pinMode(CRANKSHAFT_PIN, INPUT);
}

void loop() {
  uint32_t now = micros();
  int state = digitalRead(CRANKSHAFT_PIN);
  angle->tick(now, state);
  
}
