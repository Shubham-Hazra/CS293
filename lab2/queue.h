#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

template <typename T> class DynamicQueue {
private:
  T *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+CONST_GROWTH; }
public:
  DynamicQueue() // default constructor
  {
    A = new T[INIT_SIZE];
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
  } 
  ~DynamicQueue(){delete[] A;}; // default destructor
  
  bool isEmpty()
  {
    if (head == tail)
    {
        return true;
    }
    return false;
  }
  bool isFull()
  {
    if(tail == N)
    {
        return true;
    }
    return false;
  }
  void grow()
  {
    int nextsize = nextSize();
    int *B = new int[nextsize];
    for(int i = head;i<tail;i++)
    {
        B[i-head] = A[i];
    }
    N = nextsize;
    head = 0;
    tail = tail - head;
    A = B;
  }
  unsigned int size()
  {
    if(head == tail)
    {
        return 0;
    }
        return tail - head;
  }
  void QInsert(T x)
  {
    if(tail == N)
    {
        grow();
        A[tail] = x;
        tail = tail + 1;
    }

    A[tail] = x;
    tail = tail + 1;
  }
  bool QDelete(T *x)
  {
    if(head == tail)
    {
        return false;
    }
    *x = A[head];
    head = head +1;
    return true;
  }
};

#endif
