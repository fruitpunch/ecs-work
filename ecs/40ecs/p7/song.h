//Hiu Hong Yu && Wen Xi Zhang
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <sstream>

#pragma once
using namespace std;
class song
{

 private:
  string title;
  string artist;
  string album;
  friend ifstream& operator >> (ifstream&, song&);
  friend ostream& operator << (ostream&, song&);
  void edit();
 public:

  song();
  ~song();
  string getTitle();
  string getArtist();
  string getAlbum();

};
