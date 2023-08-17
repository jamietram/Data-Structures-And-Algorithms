#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "queue.h"

using namespace std;

Queue::Queue(int size){
  data_ = new int[size];
  size_ = size;
  front_ = 0;
  rear_ = -1;
  count_ = 0;
}

void Queue::enqueue(float value){
  if (count_ == size_){
    printf("Overflow");
    exit(EXIT_FAILURE);
  }
  rear_ = (rear_ + 1) % size_;
  data_[rear_] = value;
  count_++;
}

float Queue::dequeue(){
  if (count_ == 0){
    printf("Underflow");
    exit(EXIT_FAILURE);
  }
  float x = data_[front_];
  front_ = (front_ + 1) % size_;
  count_--;
  return x;
}

Queue::~Queue(){
  delete[] data_;
}