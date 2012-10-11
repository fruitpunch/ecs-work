#pragma once

class List;
class ListNode{

  int data;
  ListNode *next;
  friend class List;
  ListNode(int, ListNode*);

};
