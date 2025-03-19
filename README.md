acchtml is a class derived from WebServer that adds methods to generate HTML code in your applications for ESP32 and Arduino.

The usage is very simple, in the example file there are several comments to understand it.

All methods of acchtml uses absolute coordinates to locate their outputs

It not uses filesystem to store images, they are embedded in the code to make the burn process very easy. See the file graph.inc in the example.
you can use any tool to dump the images to text files in the style of graph.inc

The example is a simple webserver application using acchtml library.
