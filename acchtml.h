class acchtml {
  private:
  String html_buffer;
  public:
  WebServer server;
  void start(uint16_t port);
  void stop();
  void begin(String rurl, uint16_t rtime);
  void end();
  void redirectto(String url);
  void adddivxy(uint16_t x, uint16_t y);
  void addtext(String txt, uint16_t fsize, uint16_t x, uint16_t y, String fcolor, String font);
  void addtextcenter(String txt, uint16_t fsize, uint16_t x, uint16_t y, uint16_t width, String fcolor, String font);
  void addlink(String url, String txt, uint16_t x, uint16_t y);
  void addlinkstyle(String url, String txt, uint16_t fsize, uint16_t x, uint16_t y, String fcolor, String font);
  void addimage(String img, uint16_t x, uint16_t y);
  void addimagelink(String img, uint16_t x, uint16_t y, String url);
  void formbegin(String action, uint16_t x, uint16_t y);
  void formend(String submit);
  void forminput(String varname, String val, String title, uint16_t maxlen, uint16_t sz);
  void forminputln(String varname, String val, String title, uint16_t maxlen, uint16_t sz);
  void formpassword(String title);
  void formcheck(String title, String varname, bool val);
  void addbr();
  void addp(String txt);
  void addgauge1(uint16_t x, uint16_t y, uint16_t p);
};
