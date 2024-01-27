#include "allocator.cpp"
#include <random>
#include <unistd.h>
#include <vector>
#include <cstdlib>

void* tFunc3(void* arg){
  HeapManager* heap = static_cast<HeapManager*>(arg);

  int idx1 = (*heap).myMalloc(pthread_self(), 40);
  int success1 = (*heap).myFree(pthread_self(), idx1);
  int idx2 = (*heap).myMalloc(pthread_self(), 20);
  int success2 = (*heap).myFree(pthread_self(), idx2);

  return NULL;
}

void* tFunc4(void* arg){
  HeapManager* heap = static_cast<HeapManager*>(arg);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist1(1,30);
  uniform_int_distribution<> dist2(1,5);
  
  int alloc_space = dist1(gen);
  int sleep_time = dist2(gen);

  int idx1 = (*heap).myMalloc(pthread_self(), alloc_space);
  sleep(sleep_time);
  int success1 = (*heap).myFree(pthread_self(), idx1);

  return NULL;
}

int main(int argc, char* argv[]){
  HeapManager heap;
  heap.initHeap(100);
 
  int run = atoi(argv[1]);

  if (run == 1){
    int idx = heap.myMalloc(0, 40);
  }else if (run == 2){
    int idx = heap.myMalloc(0, 40);
    int success = heap.myFree(0, idx);
  }else if (run == 3){
    pthread_t t1, t2;

    pthread_create(&t1, NULL, tFunc3, static_cast<void*>(&heap));
    pthread_create(&t2, NULL, tFunc3, static_cast<void*>(&heap));

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

  }else if (run == 4){
    vector<pthread_t> threads;

    for (int i = 0; i < 5; i++){
      pthread_t t;

      threads.push_back(t);
    }

    for (int i = 0; i < threads.size(); i++){
      pthread_create(&(threads[i]), NULL, tFunc4, static_cast<void*>(&heap));
    }

    for (int i = 0; i < threads.size(); i++){
      pthread_join(threads[i], NULL);
    }
  }else{
    ;
  }
  
  cout << "Execution is done" << endl;
  heap.print();

  return 0;
}
