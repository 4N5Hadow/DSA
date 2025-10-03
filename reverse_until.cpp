#include "linked-list.h"

void LinkedList::reverse_until(int x)
{
  // TODO: Implement the linked list reversal function
  // Don't forget to set tail ptr correctly as well !

  // - DO NOT ALLOCATE ANY MEMORY
  // - DO NOT USE RECURSION (RECURSION ALLOCATES MEMORY)
  ListNode* tmp = head;
  bool isThere = false;
  int n = 1;
  while(tmp){
    if(tmp->data == x){
      isThere = true;
      break;
    }
    tmp = tmp->next;
    n++;
  }
  if(!isThere) return;
  if(!tmp->next) tail = head;
  if(n==1) return;
  tmp = tmp->next;
  ListNode* prev = head;
  ListNode* curr = head->next;
  for(int i=1; i<n; i++){
    ListNode* nex = curr->next;
    curr->next = prev;
    prev = curr;
    curr = nex;
  }
  head->next = tmp;
  head = prev;
}
