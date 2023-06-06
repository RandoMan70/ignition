// Support for Bluetooth Electronics dashboard https://keuwl.com/apps/bluetoothelectronics/

class BEWriteScheduler {
public:
  void publish(const char * s) {
    strcpy(buffer, s);
  }
  void publish(const String &s) {
    strcpy(buffer, s.c_str());    
  }
private:
  char buffer[256];
};

class BEGenericWriter {
public:
  explicit BEGenericWriter(BEWriteScheduler *scheduler){
    m_scheduler = scheduler;
  }
protected:
  void start(const char sign) {
    buf = "*";
    buf += sign;
  }
  void append(const char c) {
    buf += c;
  }
  void append(const char *c) {
    buf += c;
  }
  void append(const String &s) {
    buf += s;
  }
  void commit() {
    buf += "*";
    m_scheduler->publish(buf);
    buf = "";
  }
  void reserve(int value) {
    buf.reserve(value);
  }
private:
  String buf;
  BEWriteScheduler *m_scheduler;
};

class BEValue : public BEGenericWriter {
public:
  BEValue(BEWriteScheduler *scheduler, const char sign) : BEGenericWriter(scheduler) {
    m_sign = sign;
    reserve(16);
  };
  void set(String s) {
    if (s == m_text) {
      return;
    }
    start(m_sign);
    append(s);
    commit();
    m_text = s;
  }
  void set(int v) {
    set(String(v));
  }
  void set(long int v) {
    set(String(v));
  }  
  void set(unsigned int v) {
    set(String(v));
  }  
  void set(unsigned long int v) {
    set(String(v));
  }  
  void set(float v) {
    set(String(v));
  }
  const String value() {
    return m_text;
  }
private:
  char m_sign;
  String m_text;
};

class BEColor{
public:
  BEColor() {
    r = 0;
    g = 0;
    b = 0;
  }
  BEColor(int r_value, int g_value, int b_value) {
    r = r_value;
    g = g_value;
    b = b_value;
  }
  bool operator == (BEColor &other) {
    return r == other.r && g == other.g && b == other.b;
  }
  int r, g, b;
};

class BELamp : BEGenericWriter {
public:
  BELamp(BEWriteScheduler *scheduler, const char sign) : BEGenericWriter(scheduler) {
    m_sign = sign;
    reserve(16);
  }
  void set(BEColor color) {
    if (color == m_color) {
      return;
    }
    start(m_sign);
    append('R');
    append(color.r);
    append('G');
    append(color.g);
    append('B');
    append(color.b);
    commit();
    m_color = color;
  }
private:
  char m_sign;
  BEColor m_color;
};

class BEGraph : BEGenericWriter {
public:
  BEGraph(BEWriteScheduler *scheduler, const char sign, int count) : BEGenericWriter(scheduler) {
    m_sign = sign;
    m_count = count;
    m_values = new float[count];
    reserve(count * 6 + 3);
  }
  void update(int idx, float value) {
    if (idx < 0 || idx >= m_count) {
      return;
    }
    m_values[idx] = value;
  }
  void flush() {
    start(m_sign);
    for(int idx = 0; idx < m_count; idx++) {
      if (idx != 0) {
        append(",");
      }
      append(m_values[idx]);
    }
    commit();
  }
  ~BEGraph() {
    delete m_values;
  }
private:
  char m_sign;
  int m_count;
  float *m_values;
};
