#include <typeinfo>
using namespace std;

template<class T>
SVector<T>::SVector(int size){
 
  strVec=new vector<string>(size);
  
}

template<class T>
void SVector<T>::push_back(const string in, const int value){

  StringMap::iterator itr=strMap.find(in);
  assert(itr==strMap.end());
  if(itr==strMap.end()){
    strMap.insert(StringMap::value_type(in, value));
    (*strVec).push_back(in);
  }
  else{
    throw Whoops("Duplicated index: " + in);
  }
}

template<class T>
T SVector<T> :: operator [] (const string in){

  assert(strMap[in]);
  if(!strMap[in]){
    throw range_error("Range error: "+in);
  }
  return strMap[in];
}

template<class T>
void SVector<T>::pop_back(){

  assert(!(*strVec).empty());

  if(!(*strVec).empty()){
    strMap.erase((*strVec).back());
    (*strVec).pop_back();
  }
  else{
    throw underflow_error("Underflow error");
  }
}
