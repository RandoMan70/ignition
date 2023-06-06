#include "crankshaft.hpp"
#include "angle.hpp"
#include "be.hpp"

const int CRANKSHAFT_PIN = 12;
CAngle angle(60, 2);

void angle_yield(unsigned int max_micros) {
//  Serial.println(max_micros);
//  delayMicroseconds(max_micros);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Started");
  angle.yield = angle_yield;
  pinMode(CRANKSHAFT_PIN, INPUT);
}

BEWriteScheduler bt_scheduler;
BEValue o2(&bt_scheduler, 'O');

int idx = 0;

void loop() {
  uint32_t now = micros();
  int state = digitalRead(CRANKSHAFT_PIN);
  angle.tick(now, state);  
  unsigned long after = micros();

//  uint32_t t1 = micros();
//  o2.set(String(int(idx++)));
//  uint32_t t2 = micros();
//  Serial.println(t2-t1);
  
//  if (after - now >= 32) {
//    Serial.println();
//    Serial.print(now);
//    Serial.print(" ");
//    Serial.println(after - now);
//  }
}
