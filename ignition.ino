 #include <assert.h>
#include "crankshaft.hpp"

const int CRANKSHAFT_PIN = 12;
CCrankshaft *cshaft;

void edge(int id, unsigned long ts) {
  Serial.print("EDGE ");
  Serial.print(id);
  Serial.print(" ");  
  Serial.println(ts);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Started");
  cshaft = new CCrankshaft;
  pinMode(CRANKSHAFT_PIN, INPUT);
  cshaft->set_edge_cb(edge);
}

void loop() {
  uint32_t now = micros();
  int state = digitalRead(CRANKSHAFT_PIN);
  cshaft->tick(now, state);
}
