#include "angle.hpp"

CAngle::CAngle(int teeth_total, int teeth_gap) {
  m_edge_count = (teeth_total - teeth_gap) * 2 - 1;
  m_edge_angle = (int *) malloc(m_edge_count * sizeof(int));

  for (int idx = 0; idx < m_edge_count; idx++) {
    unsigned long a = (unsigned long) 3600 * (unsigned long) idx / (unsigned long) (teeth_total * 2);
    m_edge_angle[idx] = a;
  }
  cshaft = new CCrankshaft(edge_cb, this);
}

void CAngle::tick(unsigned long ts, int state) {
  cshaft->tick(ts, state);
}

unsigned int compute_idle_prediction(unsigned int delta){ 
  int clearance = delta >> 4;
  if (clearance < 20) {
    clearance = 20;
  }
  int idle_prediction = delta - clearance;
  if (idle_prediction < 48) {
    idle_prediction = 48;
  }

  return idle_prediction;
}

unsigned int CAngle::edge_delta(unsigned long ts) {
  unsigned long delta32 = ts - m_last_edge_ts;
  m_last_edge_ts = ts;
  if (delta32 < UINT16_MAX) {
    return delta32;
  } else {
    return UINT16_MAX;
  }
}

void CAngle::edge(int id, unsigned long ts) {
  if (id >= m_edge_count) {
    return;
  }

//  unsigned int idle_prediction = compute_idle_prediction(edge_delta(ts));
//  Seri

  if (id == 0) {  
    unsigned long t1 = micros();
    int rpm = 60000000 / (ts - m_last_turn_ts);
    unsigned long t2 = micros();
    Serial.println(String(t2-t1) + " " + String(rpm));
    m_last_turn_ts = ts;
  }

//  yield(idle_prediction);
}

void CAngle::edge_cb(int id, unsigned long ts, void * arg) {
  ((CAngle *) arg )->edge(id, ts);
}
