#ifndef QUEUE_H
#define QUEUE_H

#define SIZE 1000

class Queue
{
  public:
    Queue(){}
    /* implement copy constructor, assignment, destructor if needed */
    Queue(int size = SIZE);
    ~Queue();

    void enqueue(float value);
    float dequeue();

  private:
  /* declare your data */
    int *data_;
    int size_;
    int front_;
    int rear_;
    int count_;
};


#endif
