//Hiu Hong Yu && Wen Xi Zhang
#include "song.h"
#include <vector>

using namespace std;

void searchTitle(vector<song> ls)
{

  vector<song> found;
  cout << "Please enter the title: " ;
  string g;
  cin.ignore();
  getline(cin, g);
  
  vector<song> :: iterator itr, itr2;

  //search the linklist for the title user entered
  for(itr = ls.begin(); itr != ls.end(); itr++)
    {
      if((*itr).getTitle() == g)//if found
	{
	  found.push_back(*itr);//sort them
	  for(itr2 = found.begin(); itr2 != found.end(); itr2++)
	    {
	      if(found.back().getArtist() < (*itr2).getArtist())//if the title need to sort
		{
		  swap(found.back(), *itr2);//swap if needed
		}//end if
	    }//end for
	}//end if
    }//end for

  //print out sorted title that were found
  for(itr	=	found.begin();	itr	!=	found.end();	itr++)
    {
      cout	<<	*itr;
    }//end for
}//end searchTitle()

void searchArtist(vector<song> ls)
{
  vector<song> found;
  cout	<<	"Please enter the artist's name: ";
  string g;
  cin.ignore();
  getline(cin, g);//get user input for artist's name
  vector<song>	::	iterator itr, itr2;
  for(itr	=	ls.begin(); itr != ls.end(); itr++)//search for match articts
    {
      if((*itr).getArtist() == g)//if found
	{
	  found.push_back(*itr);//sort them
	  for(itr2 = found.begin(); itr2 != found.end(); itr2++)
	    {
	      if(found.back().getTitle() < (*itr2).getTitle())//if the articts name suppose to be in front
		{
		  swap(found.back(), *itr2);//swap them
		}//end if
	    }//end for
	}//end if
    }//end for
	
  //print the sorted list of artices's song
  for(itr	=	found.begin();	itr	!=	found.end();	itr++)
    {
      cout	<<	*itr;
    }//end for
}//end searchArtist()

void searchAlbum(vector<song> ls)
{
 
  vector<song> found;
  cout << "Please enter the album: ";
  cin.ignore();
  string g;
  getline(cin, g);
  vector<song> :: iterator itr, itr2;
  for(itr = ls.begin(); itr != ls.end(); itr++)
    {
      if((*itr).getAlbum() == g)
	{
	  found.push_back(*itr);
	  for(itr2 = found.begin(); itr2 != found.end(); itr2++)
	    {
	      if(found.back().getTitle() < (*itr2).getTitle())//sort
		{
		  swap(found.back(), *itr2);
		}//end if
	    }//end for
	}//end if
    }//end for
  for(itr = found.begin(); itr != found.end(); itr++)
    {
      cout << *itr;
    }//end for
}//end searchAlbum()

void searchWord(vector<song> ls)
{  

  vector<song> found;
  cout << "Please enter the phrase: "; 
  string g;
  cin.ignore();
  getline(cin, g);
  vector<song>::iterator itr, itr2;
  for(itr = ls.begin(); itr != ls.end(); itr++)
    {
      if((*itr).getTitle().find(g) != string :: npos)
	{
	  found.push_back(*itr);
	  for(itr2 = found.begin(); itr2 != found.end(); itr2++)
	    {
	      if(found.back().getArtist() < (*itr2).getArtist())
		{
		  swap(found.back(), *itr2);
		}//end if
	    }//end for
	}//end if
    }//end for
  for(itr = found.begin(); itr != found.end(); itr++)
    {
      cout << *itr;
    }//end for
}//end searchWord()


int main()
{
  ifstream infile("songs.txt", ios :: in);//open file
  vector<song> ls;
  song s;
  int choice;

  while(infile >> s)//read in the file
    {  
      ls.push_back(s);
    }//end while

  while(1)//menu for user to choice
    {
      cout << endl << "Song Menu"	<< endl
	   << "0. Done." << endl
	   << "1. Search for Artist." << endl
	   << "2. Search for Title." << endl
	   << "3. Search for Album." << endl
	   << "4. Search for title phrase." << endl
	   << endl << "Your Choice: ";

      cin>>choice;//take in the info


      switch(choice)//switch case to match user input
	{
    	case 0://done
	  return 0;
    	case 1:
	  searchArtist(ls);
	  break;
    	case 2:
	  searchTitle(ls);
	  break;
    	case 3:
	  searchAlbum(ls);
	  break;
    	case 4:
	  searchWord(ls);
	  break;
    	default://if not 0 to 4
	  cout << "Your choice must be between 0 and 4." << endl;
	  break;
	}//end switch
    }//end while

  return 0;
}//end main
