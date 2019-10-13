#include <iostream>
#include "ringbuffer.h"

//this makes the whole thing need C++17, but the RingBuffer class
//on its own should also be able to work with C++14
template<typename...Args>
auto print(Args... args){
    ([](auto&& arg){ std::cout << arg << ' '; }(args), ...);
    std::cout << '\n';
}

auto main() -> int
{
    //could also be RingBuffer<double> or RingBuffer<long double> for more precision,
    //To test this, change the using FloatType to double or long double
    using FloatType = float;

    RingBuffer<FloatType> buffer { 10, "Buffer" };

    FloatType inputdata[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
    FloatType anadata[8];

    buffer.isLockFree() ? print("Lock free") : print("Not lock free");

    print("Available for write:",   buffer.numItemsAvailableForWrite());
    print("Available for read:",    buffer.numItemsAvailableForRead());

    buffer.push(inputdata, 1);
    buffer.push(inputdata, 5);
    buffer.pop(anadata, 5);

    print("Available for write:",   buffer.numItemsAvailableForWrite());
    print("Available for read:",    buffer.numItemsAvailableForRead());

    buffer.push(inputdata, 5);

    print("Available for write:",   buffer.numItemsAvailableForWrite());
    print("Available for read:",    buffer.numItemsAvailableForRead());

    buffer.push(inputdata, 1);

    print("Available for write:",   buffer.numItemsAvailableForWrite());
    print("Available for read:",    buffer.numItemsAvailableForRead());

    buffer.push(inputdata, 1);

    print("Available for write:",   buffer.numItemsAvailableForWrite());
    print("Available for read:",    buffer.numItemsAvailableForRead());

    if(buffer.numItemsAvailableForRead() >= 5)
    {
        buffer.pop(anadata, 5);
        print("Available for write:",   buffer.numItemsAvailableForWrite());
        print("Available for read:",    buffer.numItemsAvailableForRead());
        for(int i = 0; i < 5; ++i) print("Anadata: i =", i, ":", anadata[i]);
    }
    else print("Not enough data");

    buffer.push(inputdata, 1);

    print("Available for write:",   buffer.numItemsAvailableForWrite());
    print("Available for read:",    buffer.numItemsAvailableForRead());

    buffer.push(inputdata, 1);

    print("Available for write:",   buffer.numItemsAvailableForWrite());
    print("Available for read:",    buffer.numItemsAvailableForRead());

    if(buffer.numItemsAvailableForRead() >= 5)
    {
        buffer.pop(anadata, 5);
        print("Available for write:",   buffer.numItemsAvailableForWrite());
        print("Available for read:",    buffer.numItemsAvailableForRead());
        for(int i = 0; i < 5; ++i) print("Anadata: i =", i, ":", anadata[i]);
    }
    else print("Not enough data\n");


    return 0;
}
