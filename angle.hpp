#ifndef IGNITION_ANGLE_HPP
#define IGNITION_ANGLE_HPP

#include <Arduino.h>
#include "crankshaft.hpp"

typedef void (*angle_yield_func)(unsigned int max_micros);
  
class CAngle {
  public:
    CAngle(int teeth_total, int teeth_gap);
    void tick(unsigned long ts, int state);

    angle_yield_func yield;
  private:
    void edge(int id, unsigned long ts);
    unsigned int edge_delta(unsigned long ts);
    static void edge_cb(int id, unsigned long ts, void * arg);
    int m_edge_count;
    int *m_edge_angle;
    unsigned long m_last_edge_ts;
    unsigned long m_last_turn_ts;
    CCrankshaft *cshaft;
};

#endif // IGNITION_ANGLE_HPP
