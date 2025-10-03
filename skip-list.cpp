#include "skip-list.h"

/* 
The insert function has been implemented as follows:
1. Randomly decide the number of levels for the new node(newLevel) using coin flips.
2. Now to search position for inserting it, we need to do in O(log n) average time complexity,
    for that, we go to highest level(as it has least num of nodes) and traverse through it till
    we find an element larger than the inserting element, then we go a level down after storing 
    the pointer to node just smaller than inserting element. We go down till we reach level = 0.
3. Now we have, at each level, the pointer to node just smaller than inserting ;element. Now 
    we insert this node in each level from 0 to newLevel.
*/
bool skipList::insert(int data) 
{
    // TODO 1: IMPLEMENT YOUR CODE HERE
    int lnum = 1;
    while(coin_flip() and lnum<=MAX_LEVEL) lnum++;
    Level = max(Level,lnum+1);
    vector<Node*> update(lnum,head);
    Node* curr=head->next[lnum-1];
    for (int i=lnum-1; i>=0; i--)
    {
        while(curr){
            int temp = curr->getData();
            if(temp > data ) break;
            if(temp == data) return false;
            update[i]=curr;
            curr = curr->next[i];
        }
        if(i!=0){
            update[i-1] = update[i];
            curr = update[i]->next[i-1];
        }
    }
    Node* ins = new Node(data,lnum);
    for(int i=0; i<lnum; i++){
        Node* tmp = update[i]->next[i];
        update[i]->next[i] = ins;
        ins->next[i] = tmp;
    }
    return true;
}


/*
The remove function is implemented as follows:
1. Starting fromt he highest level, we traverse through the list to find the position
    of the node to be deleted, at each level we store the pointer to the node just smaller
    than the node to be deleted.
2. At level 0, we check whether the node to be deleted exists or not.
3. If it does exist, we delete it from each level that it exists on.
4. Finally, we do some cleanup, we remove the levels which don't have any nodes.
*/
bool skipList::remove(int data) 
{
    // TODO 2: IMPLEMENT YOUR CODE HERE
    int lnum = Level;
    vector<Node*> update(lnum+1,head);
    Node* curr=head->next[lnum];
    bool isThere = false;
    int foundlevel = -1;
    for (int i=lnum; i>=0; i--)
    {   
        while(curr){
            int temp = curr->getData();
            if(temp > data ) break;
            if(temp == data){
                if(isThere == false) foundlevel = i+1;
                isThere = true;
                break;
            }
            update[i]=curr;
            curr = curr->next[i];
        }
        if(i!=0){
            update[i-1] = update[i];
            curr = update[i]->next[i-1];
        }
    }
    if(!isThere) return false;
    Node* todel = update[0]->next[0];
    for(int i=0; i<foundlevel;i++){
        Node* tmp = (update[i]->next[i])->next[i];
        update[i]->next[i] = tmp;
    }
    delete todel;
    return true;
}


/*
The search function is implemented as follows:
1. Starting from the highest level and head node, we traverse
    through the list to find the position of the node to be searched.
2. At level 0, we check whether the node to be searched exists or not.
3. If it exists, we return true, else false.
*/
bool skipList::search(int data) 
{
    
    // TODO 3: IMPLEMENT YOUR CODE HERE
    Node* curr=head->next[Level];
    vector<Node*> update(Level+1,head);
    for (int i=Level; i>=0; i--)
    {
        while(curr){
            int temp = curr->getData();
            if(temp == data) return true;
            if(temp > data ) break;
            update[i]=curr;
            curr = curr->next[i];
        }
        if(i!=0){
            update[i-1] = update[i];
            curr = update[i]->next[i-1];
        }
    }
    return false;
}

