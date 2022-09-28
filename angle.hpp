#ifndef IGNITION_ANGLE_HPP
#define IGNITION_ANGLE_HPP

#include <arduino.h>
#include "crankshaft.hpp"

class CAngle {
  public:
    CAngle(int teeth_total, int teeth_gap);
    void tick(unsigned long ts, int state);
  private:
    void edge(int id, unsigned long ts);
    static void edge_cb(int id, unsigned long ts, void * arg);
    int m_edge_count;
    int *m_edge_angle;

//    int m_last_edge_ts;
//    int m_last_segment_duration;
    
    
    CCrankshaft *cshaft;
};

#endif // IGNITION_ANGLE_HPP
