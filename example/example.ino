/**************************************************************
Example code using acchtml library (HTML generator)

- All methods of acchtml uses absolute coordinates to locate their outputs
- In the file graph.inc there are graphics that will be placed embedded in the bin code
  you can use any tool to dump the images to text file
  I don't use filesystem because is more easy burn the ESP32 with only one binary
- Uses WiFi and WebServer standard libraries
- Set your WIFI settings properly. The IP is set manual to 192.168.1.250. Change it if needed
***************************************************************/


#include <WiFi.h>
#include <WebServer.h>
#include <acchtml.h>
#include "graph.inc"



const char* ssid = "ACC";
const char* password = "1234567890.";

IPAddress myip = {192,168,1,250};
IPAddress mygateway = {192,168,1,1};
IPAddress mymask = {255,255,255,0};
IPAddress mydns1 = {194,179,1,100};
IPAddress mydns2 = {194,179,1,101};

acchtml html;
String input1="";
String input2="";
String pwd="";


void cgi_index() {                                                   // This is de default page
  String s;

  html.begin("",0);                                                  // begins the html code without refresh by time
  html.addimagelink("graph_google",20,20,"http://www.google.com");   // imagelink graph_google in coordinates (20,20)
  html.addlink("http://www.google.com","link to GOOGLE",20,120);     // normal link in (20,120)
  s="Values entered: ";
  s+=input1;
  s+=", ";
  s+=input2;
  s+=", ";
  s+=pwd;
  html.addtext(s,20,20,160,"000000","Arial");                         // text with the values entered in the form. FSize 20, coord. (20,160), color "000000", font Arial
  html.addtextcenter("Text centered",20,20,200,300,"0000FF","Monospace"); // text centered in a space of 300 pixels
  html.addlinkstyle("/","Link with style to myself",30,20,250,"ff0000","Arial"); // link with style atributes
  html.formbegin("formok.cgi",20,350);                                // begin of a form in (20,350). Page to call on submit "formok.cgi"
  html.forminputln("v1","","Input 1",30,30);                          // input for var "v1" without default value, max 30 chars, width 30 px
  html.forminputln("v2","","Input 2",30,30);                          // input for var "v2"
  html.formpassword("Password:");                                     // input for password. the var name is fixet to "PWD"
  html.formend("Accept");                                             // ends the form with "Accept" in de submit button
  html.addimage("graph_pbs",500,100);                                 // normal image at (500,100)
  html.end();                                                         // ends de html code and sends it
}



void cgi_formok() {                                                  // This cgi is called by the submit of the form
  input1=html.server.arg("v1");                                      // saves the received data into variables input1, input2 and pwd
  input2=html.server.arg("v2");
  pwd=html.server.arg("PWD");
  html.redirectto("/");                                              // redirects to the default page
}



void cgi_404() {                                                     // cgi called by error 404 (page not found)
  html.server.send(404, "text/plain", "This page does not exist!");
}



void cgi_graph_google() {                                            // cgi called when the navigator asks for the file graph_google
  html.server.send_P(200,"image/png",graph_google,sizeof(graph_google));
}



void cgi_graph_pbs() {
  html.server.send_P(200,"image/png",graph_pb,sizeof(graph_pb));     // cgi called when the navigator asks for the file graph_pbs
}



void task_web (void * parameter ) {                                  // RTOS task to run the webserver
  for(;;) {
    html.server.handleClient();
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}



void setup() {
  Serial.begin(115200);

  if (!WiFi.config(myip, mygateway, mymask, mydns1, mydns2)) {
    Serial.println("STA Failed to configure");
  }
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi Network ..");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }
  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  html.server.on("/",cgi_index);                                     // sets the supported pages to our management functions
  html.server.on("/formok.cgi",cgi_formok);
  html.server.on("/graph_google",cgi_graph_google);
  html.server.on("/graph_pbs",cgi_graph_pbs);
  html.server.onNotFound(cgi_404);                                   // starts the webserver on port 80
  html.start(80);

  xTaskCreate(task_web,"task_web",50000,NULL,1,NULL);                // runs the webserver in a RTOS task
}



void loop() {
}
