/*
 * ringbuffer.h
 */

#include <atomic>
#include <string>

class RingBuffer
{
public:
  RingBuffer(unsigned long size,std::string name);
  ~RingBuffer();
  unsigned long push(float *data,unsigned long n);
  unsigned long pop(float *data,unsigned long n);
  unsigned long items_available_for_write();
  unsigned long items_available_for_read();
  bool isLockFree();
  void pushMayBlock(bool block);
  void popMayBlock(bool block);
  void setBlockingNap(unsigned long blockingNap);
private:
  unsigned long size;
  float *buffer;
  std::atomic<unsigned long> tail; // write pointer
  std::atomic<unsigned long> head; // read pointer
  unsigned long itemsize; // also depends on #channels
  std::string name;
  bool blockingPush;
  bool blockingPop;
  unsigned long blockingNap=500;
}; // RingBuffer{}

