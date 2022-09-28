class CCrankshaft {
  typedef void (*edge_cb_t)(int edge_id, unsigned long ts, void * arg);  
  public:
    CCrankshaft(edge_cb_t cb, void * cb_arg);
    void tick(unsigned long ts, int state);
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
    void *m_edge_cb_arg;
};
