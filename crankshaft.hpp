class CCrankshaft {
  typedef void (*edge_cb_t)(int edge_id, unsigned long ts);  
  public:
    CCrankshaft();
    void tick(unsigned long ts, int state);
    void set_edge_cb(edge_cb_t cb);
  private:
    void push(unsigned int value);
    void reset();
    bool is_gap();

    int m_edge_count;
    int m_edge_id;
    int m_pin_state;
    unsigned long m_pin_ts;
    int m_recent[4];
    edge_cb_t m_edge_cb;
};
