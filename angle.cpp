#include "angle.hpp"

CAngle::CAngle(int teeth_total, int teeth_gap) {
  m_edge_count = (teeth_total - teeth_gap - 1) * 2;
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

void CAngle::edge(int id, unsigned long ts) {
  if (id >= m_edge_count) {
    return;
  }
  Serial.print(id);
  Serial.print(" ");  
  Serial.println(ts);
}

void CAngle::edge_cb(int id, unsigned long ts, void * arg) {
  ((CAngle *) arg )->edge(id, ts);
}
