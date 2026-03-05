#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;



int main (int argc, char *argv[]) {
  FILE *f1;
  ofstream f2;
  stringstream s;
  unsigned int c,i;

  if (argc!=2) {
    cout << "img2hex. Converts image file to text in hex format\n";
    cout << "to be embedded in C source code\n\n";
    cout << "Usage:\nimg2hex image_file\n\n";
    return 0;
  }

  f1=fopen(argv[1],"r");
  if (f1==NULL) {
    cout << "Error opening the file: " << argv[1] << "\n\n";
    return 1;
  }
  f2.open("result.txt");
  if (!f2.is_open()) {
    fclose(f1);
    cout << "Error creating the file: result.txt\n\n";
    return 1;
  }

  i=0;
  while(!feof(f1)) {
    c=fgetc(f1);
    if (!feof(f1)) {
      s.str("");
      s << "0x" << uppercase << setfill('0') << setw(2) << hex << c;
      f2 << s.str();
      f2 << ",";
      i++;
      if (i==32) {
        i=0;
        f2 << "\n";
      }
    }
  }
  f2 << "\n";
  cout << "Done\n\n";

  fclose(f1);
  f2.close();
  return 0;
}
