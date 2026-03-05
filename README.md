acchtml is a class derived from WebServer that adds methods to generate HTML code in your applications for ESP32 and Arduino.

The usage is very simple, in the example file there are several comments to understand it.

All methods of acchtml uses absolute coordinates to locate their outputs

It not uses filesystem to store images, they are embedded in the code to make the burn process more easy. See the file graph.inc in the example.
You can use the utility img2hex.cpp supplied to dump image files to hex text format.

The example is a simple webserver application using acchtml library.
