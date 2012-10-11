//Hiu Hong Yu && Wen Xi Zhang
#include "song.h"
using namespace std;

song :: song()
{

}//end song()

song :: ~song()
{

}//end ~song()

//overloading operator for read in the file song.txt
ifstream& operator >> (ifstream &in, song &s)
{
  string g;
  string u;
  stringstream i;
  //read in the first 256 character into g, if file can be open
  if(getline(in, g))
    {
      i<<g;
      getline(i, s.title, '_');
      i.ignore(1,'_');
      i.ignore(1,'_');
      getline(i, s.artist, '_');
      i.ignore(1,'_');
      i.ignore(1,'_');
      getline(i, u, '_');
      i.ignore(1,'_');
      i.ignore(1,'_');
      getline(i, s.album, '_');
    }//end if
  s.edit();
  return in;
}//end >>

//overloading operator << to print
ostream& operator << (ostream &out, song &s)
{
  out << s.title << ":"
      << s.artist << ":"
      << s.album << endl;
  return out;
}//end <<

void song :: edit()
{
  string str;
  string :: iterator itr;

  while(1)
    {
      str = "A ";
      if(title.find(str) == 0)//if found the title with A
	{
	  title.erase(0, 2);//delete first 2 characters
	  title = title + ", A";//title add the word  A at the end
	  break;
	}//end if
      //else not found
      str = "THE ";
      if(title.find(str) == 0)
	{
	  title.erase(0, 4);//delete first 4 characters
	  title = title + ", THE";//title add the word  The at the end
	  break;
	}//end if
      break;
    }//end while

  str = "CD+G";
  if(album.find(str) == (album.length() - 4))//if found the album with CD+G
    {
      album.erase((album.length() - 5), 5);//delete the last 5 characters
    }//end if

  transform(artist.begin(), artist.end(), artist.begin(), :: tolower);
  *artist.begin() = toupper((unsigned char) *artist.begin());
  for(itr = artist.begin(); itr != artist.end(); itr++)
    {
      if(itr != artist.begin())
	{
	  --itr;
	  if((unsigned char)*itr	== ' ')
	    {
	      itr++;
	      *itr = toupper((unsigned char)*itr);//change the character to upper case
	      --itr;
	    }//end if
	  itr++;
	}//end if
    }//end for  
}//end edit()
string song::getTitle(){
  return title;
}
string song::getArtist(){
  return artist;
}
string song::getAlbum(){
  return album;
}

