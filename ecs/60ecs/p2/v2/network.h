#pragma once

#include<cstdlib>
#include<cstring>
#include<iostream>
#include<cctype>

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class llist;
class road{

 public:

  int c1, c2, distance, region, id, common;
  bool visited;
  llist *adj;

  road(int, int, int, int);


  int commonNode(road*);
  bool checkDup(road*);
  bool checkAdj(road*);
  bool checkCycle(int);
  bool setRegion(int, int);
  bool roadCmp(road*);
  void insertRoad(road*);
  void print();
  void removeSelf();
  


};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class node{

 public:
  node *next;
  road *data;

  node(road*, node*);

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class llist{

 public:

  node *head;
  int size;

  llist();
  road* top();
  bool setCheck(road*);
  bool visit(int, int, road*);
  bool empty();
  bool setAdjRegion(int, int, int,road*);
  bool llistCmp(llist*);
  int setRegion();
  void insert(road*);
  void getAdj(road*);
  void remove(int);
  void removeAll(int);
  void resetVisit();
  void clear();
  void printList();
  void setList(llist*, int);

};
