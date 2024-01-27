#include <iostream>
#include <list>
#include <pthread.h>

using namespace std;

class HeapManager{
  public:
    HeapManager(){
      lock = PTHREAD_MUTEX_INITIALIZER; // Initialising the lock
    }

    int initHeap(int size){
      node free_node(-1, size, 0);
      
      memory.push_back(free_node);
      
      cout << "Memory initialized" << endl;
      print();

      return 1;
    }
    
    int myMalloc(int ID, int size){
      pthread_mutex_lock(&lock);

      for (list<node>::iterator it = memory.begin(); it != memory.end(); ++it){
        if (it->ID == -1 && it->size >= size){ // Found suitable free space
          int rem_size = it->size - size; // Remaining free space
          int new_index = it->index + size; // New index of the free node
          
          node rem_node(it->ID, rem_size, new_index); // The free node (post-allocation)
          
          if (rem_node.size != 0){ // Free space was not fully consumed
            memory.insert(next(it), rem_node); // Inserting the new free node (remaining free space) right after the newly allocated node
          }else{ // Free space was fully consumed; no need to add a node with size 0 to the list
            ;
          }
            
          // Setting the parameters for the newly allocated node
          it->ID = ID;
          it->size = size;

          cout << "Allocated for thread " << ID << endl;
          print();
          
          pthread_mutex_unlock(&lock);
          return it->index;
        }else{
          ;
        }
      }
      
      cout << "Can not allocate, requested size " << size << " for thread " << ID << " is bigger than remaining size" << endl;

      pthread_mutex_unlock(&lock);
      return -1; // Returning -1 if the list is empty (should never be the case as long as initHeap() is used first) or the available free space is insufficient
    }
    
    int myFree(int ID, int index){
      pthread_mutex_lock(&lock);

      for (list<node>::iterator it = memory.begin(); it != memory.end(); ++it){
        if (it->ID == ID && it->index == index){ // Found the node to be freed
          it->ID = -1; 
          coalesce();

          cout << "Freed for thread " << ID << endl;
          print();
          
          pthread_mutex_unlock(&lock);
          return 1;
        }else{
          ;
        }
      }
      
      cout << "Unsuccessful freeing attempt!" << endl;

      pthread_mutex_unlock(&lock);
      return -1; // Returning -1 if freeing was unsuccessful
    }
    
    void print(){
      for (list<node>::iterator it = memory.begin(); it != memory.end(); ++it){
        if (it == prev(memory.end())){ // Last node
          cout << "[" << it->ID << "][" << it->size << "][" << it->index << "]";
        }else{
          cout << "[" << it->ID << "][" << it->size << "][" << it->index << "]---";
        }
      }

      cout << endl;
    }
  private:
    struct node{
      int ID;
      int size;
      int index;

      node(int ID, int size, int index): ID(ID), size(size), index(index){}
      node(): ID(-1), size(-1), index(-1){}

      bool operator==(const node& other) const {
        return (ID == other.ID && size == other.size && index == other.index);
      }
    };
    
    void coalesce(){
      list<node> delete_list; // The list of nodes to remove to finalise coalescing

      for (list<node>::iterator it = memory.begin(); it != memory.end(); ++it){
        if (it != memory.begin()){
          if ((prev(it)->index + prev(it)->size == it->index) && (it->ID == -1) && (prev(it)->ID == -1)){ // Found two adjacent free nodes
            // Enlarging one of the free nodes to include the other
            it->size = it->size + prev(it)->size;
            it->index = prev(it)->index;

            delete_list.push_back(*(prev(it))); // Adding the previous free node to the list of nodes to remove
          }else{
            ;
          }
        }else{
          ;
        }
      }

      for (list<node>::iterator it = delete_list.begin(); it != delete_list.end(); ++it){ // Removing leftover nodes from the memory
        for (list<node>::iterator that = memory.begin(); that != memory.end(); ++that){
          if ((*that) == (*it)){ // Found the match for a leftover node
            that = memory.erase(that); // Removing the match from the memory
          }else{
            ;
          }
        }
      }
    }

    list<node> memory; // Linked list to keep track of the memory
    pthread_mutex_t lock; // Mutex to ensure mutual exclusion for multi-threaded runs
};
