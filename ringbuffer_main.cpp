#include <iostream>
#include "ringbuffer.h"


int main()
{
RingBuffer buffer(10,"Buffer");
float inputdata[8]={1,2,3,4,5,6,7,8};
float anadata[8];

  if(buffer.isLockFree()) std::cout << "Lock free\n";
  else std::cout << "Not lock free\n";

  std::cout << "Avail for write: " << buffer.items_available_for_write() << std::endl;
  std::cout << "Avail for read: " << buffer.items_available_for_read() << std::endl;
  buffer.push(inputdata,1);
  buffer.push(inputdata,5);
    buffer.pop(anadata,5);
  std::cout << "Avail for write: " << buffer.items_available_for_write() << std::endl;
  std::cout << "Avail for read: " << buffer.items_available_for_read() << std::endl;

  buffer.push(inputdata,5);
  std::cout << "Avail for write: " << buffer.items_available_for_write() << std::endl;
  std::cout << "Avail for read: " << buffer.items_available_for_read() << std::endl;
  buffer.push(inputdata,1);
  std::cout << "Avail for write: " << buffer.items_available_for_write() << std::endl;
  std::cout << "Avail for read: " << buffer.items_available_for_read() << std::endl;
  buffer.push(inputdata,1);
  std::cout << "Avail for write: " << buffer.items_available_for_write() << std::endl;
  std::cout << "Avail for read: " << buffer.items_available_for_read() << std::endl;

  if(buffer.items_available_for_read() >= 5){
    buffer.pop(anadata,5);
  std::cout << "Avail for write: " << buffer.items_available_for_write() << std::endl;
  std::cout << "Avail for read: " << buffer.items_available_for_read() << std::endl;
    for(unsigned long i=0; i<5; i++) std::cout << anadata[i] << " ";
  }
  else std::cout << "Not enough data" << std::endl;

  buffer.push(inputdata,1);
  std::cout << "Avail for write: " << buffer.items_available_for_write() << std::endl;
  std::cout << "Avail for read: " << buffer.items_available_for_read() << std::endl;
  buffer.push(inputdata,1);
  std::cout << "Avail for write: " << buffer.items_available_for_write() << std::endl;
  std::cout << "Avail for read: " << buffer.items_available_for_read() << std::endl;

  if(buffer.items_available_for_read() >= 5){
    buffer.pop(anadata,5);
  std::cout << "Avail for write: " << buffer.items_available_for_write() << std::endl;
  std::cout << "Avail for read: " << buffer.items_available_for_read() << std::endl;
    for(unsigned long i=0; i<5; i++) std::cout << anadata[i] << " ";
  }
  else std::cout << "Not enough data" << std::endl;

  std::cout << std::endl;
  return 0;
}

