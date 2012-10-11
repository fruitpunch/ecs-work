friend ifstream& operator >> ( ifstream &is, Results &results){

  stringstream i;
  string g, dir, name;
  Vector<bool>b, Vector<float> f;
  bool a;
  float fl;
  Normal *in;

  getline(is, g);
  while(getline(is, g)){
    i<<g;
    getline(i, dir, ',');
    getline(i, name, ',');
    
    for(int i=0; i<5; i++){
      getline(i, g, ',');
      bool a=(g=='Y')?true: false;
      b.push_back(a);
      getline(i, g, ',');
      fl=atof(g);
      f.push_back(fl);
    }

    if(b.front()){

      in=new Normal(name, b, f);
    }
    else{

      in=new Multiple(name, b, f);
    }

    map.insert(ResultMap::value_type(dir, in));
  }
  return is;
}
