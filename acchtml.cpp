#include <WString.h>
#include <WebServer.h>
#include <acchtml.h>



void acchtml::start(uint16_t port) {
  server.begin(port);
}



void acchtml::stop() {
  server.stop();
}



void acchtml::begin(String rurl, uint16_t rtime) {
  html_buffer= "<!DOCTYPE html> <html>\n<HEAD>\n";
  html_buffer+="<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n";
  html_buffer+="<meta http-equiv=\"Pragma\" content=\"no-cache\">\n";
  if (rurl!="") {
    html_buffer+="<META HTTP-EQUIV=\"Refresh\" CONTENT=\"";
    html_buffer+=String(rtime);
    html_buffer+="; URL=";
    html_buffer+=rurl;
    html_buffer+="\">\n";
  }
  html_buffer+="</HEAD><BODY>\n";
}



void acchtml::end() {
  html_buffer+="</BODY></HTML>\n";
  server.send(200,"text/html",html_buffer);
  html_buffer="";
}



void acchtml::redirectto(String url) {
  begin(url,0);
  end();
}



void acchtml::adddivxy(uint16_t x, uint16_t y) {
  html_buffer+="<div style=\"position:absolute;left:";
  html_buffer+=String(x);
  html_buffer+="px;top:";
  html_buffer+=String(y);
  html_buffer+="px;\">\n";
}



void acchtml::addtext(String txt, uint16_t fsize, uint16_t x, uint16_t y, String fcolor, String font) {
  adddivxy(x,y);
  html_buffer+="<font style=\"font-size:";
  html_buffer+=String(fsize);
  html_buffer+="px\" color=\"#";
  html_buffer+=fcolor;
  html_buffer+="\" face=\"";
  html_buffer+=font;
  html_buffer+="\">";
  html_buffer+=txt;
  html_buffer+="</font></div>\n";
}



void acchtml::addtextcenter(String txt, uint16_t fsize, uint16_t x, uint16_t y, uint16_t width, String fcolor, String font) {
  html_buffer+="<div style=\"position:absolute;left:";
  html_buffer+=String(x);
  html_buffer+="px;top:";
  html_buffer+=String(y-16);
  html_buffer+="px;width:";
  html_buffer+=String(width);
  html_buffer+="px\">\n";
  html_buffer+="<font style=\"font-size:";
  html_buffer+=String(fsize);
  html_buffer+="px\" color=\"#";
  html_buffer+=fcolor;
  html_buffer+="\" face=\"";
  html_buffer+=font;
  html_buffer+="\"><p align=\"center\">";
  html_buffer+=txt;
  html_buffer+="</p></font></div>\n";
}



void acchtml::addlink(String url, String txt, uint16_t x, uint16_t y) {
  adddivxy(x,y);
  html_buffer+="<a href=\"";
  html_buffer+=url;
  html_buffer+="\">";
  html_buffer+=txt;
  html_buffer+="</a></div>\n";
}



void acchtml::addlinkstyle(String url, String txt, uint16_t fsize, uint16_t x, uint16_t y, String fcolor, String font) {
  adddivxy(x,y);
  html_buffer+="<a href=\"";
  html_buffer+=url;
  html_buffer+="\"style=\"text-decoration:none\"><font style=\"font-size:";
  html_buffer+=String(fsize);
  html_buffer+="px\" color=\"#";
  html_buffer+=fcolor;
  html_buffer+="\" face=\"";
  html_buffer+=font;
  html_buffer+="\">";
  html_buffer+=txt;
  html_buffer+="</a></font></div>\n";
}



void acchtml::addimage(String img, uint16_t x, uint16_t y) {
  html_buffer+="<img style=\"position:absolute;left:";
  html_buffer+=String(x);
  html_buffer+="px;top:";
  html_buffer+=String(y);
  html_buffer+="px\" src=\"";
  html_buffer+=img;
  html_buffer+="\">\n";
}



void acchtml::addimagelink(String img, uint16_t x, uint16_t y, String url) {
  html_buffer+="<a href=\"";
  html_buffer+=url;
  html_buffer+="\"><img style=\"position:absolute;left:";
  html_buffer+=String(x);
  html_buffer+="px;top:";
  html_buffer+=String(y);
  html_buffer+="px\" src=\"";
  html_buffer+=img;
  html_buffer+="\"></a>\n";
}



void acchtml::formbegin(String action, uint16_t x, uint16_t y) {
  adddivxy(x,y);
  html_buffer+="<FORM ACTION=\"";
  html_buffer+=action;
  html_buffer+="\" METHOD=\"POST\">";
}



void acchtml::formend(String submit) {
  html_buffer+="<BR><BR><BR><BR><INPUT TYPE=\"SUBMIT\" VALUE=\"";
  html_buffer+=submit;
  html_buffer+="\"></FORM></div>\n";
}



void acchtml::forminput(String varname, String val, String title, uint16_t maxlen, uint16_t sz) {
  html_buffer+=title;
  html_buffer+="&nbsp;&nbsp;<INPUT TYPE=\"TEXT\" NAME=\"";
  html_buffer+=varname;
  html_buffer+="\" maxlength=\"";
  html_buffer+=String(maxlen);
  html_buffer+="\" VALUE=\"";
  html_buffer+=val;
  html_buffer+="\" SIZE=";
  html_buffer+=String(sz);
  html_buffer+=">&nbsp;&nbsp;\n";
}



void acchtml::forminputln(String varname, String val, String title, uint16_t maxlen, uint16_t sz) {
  html_buffer+="<INPUT TYPE=\"TEXT\" NAME=\"";
  html_buffer+=varname;
  html_buffer+="\" maxlength=\"";
  html_buffer+=String(maxlen);
  html_buffer+="\" VALUE=\"";
  html_buffer+=val;
  html_buffer+="\" SIZE=";
  html_buffer+=String(sz);
  html_buffer+=">&nbsp;&nbsp;";
  html_buffer+=title;
  html_buffer+="<BR>\n";
}



void acchtml::formpassword(String title) {
  html_buffer+="<BR>";
  html_buffer+=title;
  html_buffer+="&nbsp;&nbsp;<INPUT TYPE=\"PASSWORD\" NAME=\"PWD\" maxlength=\"20\" VALUE=\"\" SIZE=12><BR>\n";
}





void acchtml::formcheck(String title, String varname, bool val) {
  String s;

  if (val) s="CHECKED";
  else s="";
  html_buffer+=title;
  html_buffer+="&nbsp;&nbsp;<INPUT TYPE=\"CHECKBOX\" NAME=\"";
  html_buffer+=varname;
  html_buffer+="\"";
  html_buffer+=s;
  html_buffer+=">&nbsp;&nbsp;\n";
}





void acchtml::addbr() {
  html_buffer+="<BR>\n";
}





void acchtml::addp(String txt) {
  html_buffer+="<P>";
  html_buffer+=txt;
  html_buffer+="</P>\n";
}





void acchtml::addgauge1(uint16_t x, uint16_t y, uint16_t p) {
  html_buffer+="<img style=\"position:absolute;left:";
  html_buffer+=String(x);
  html_buffer+="px;top:";
  html_buffer+=String(y);
  html_buffer+="px\" src=\"graph_pb\">\n";
  x=x+3;
  y=y+4;
  if (p>100) p=100;
  p=100-p;
  p=p*2;
  if (p==200) p=208;
  html_buffer+="<img style=\"position:absolute;left:";
  html_buffer+=String(x);
  html_buffer+="px;top:";
  html_buffer+=String(y);
  html_buffer+="px;width:99px;height:";
  html_buffer+=String(p);
  html_buffer+="px\" src=\"graph_bl\">\n";
}
