

#include <iostream>
#include "ringbuffer.h"
#include <unistd.h>
#include <string.h>


// Size is specified as #items, not bytes.

template<typename FloatType>
RingBuffer<FloatType>::RingBuffer(const uint64 size, const std::string& name) :
    size(size),
    buffer(new FloatType[size]),
    tail(0),
    head(0),
    name(name),
    blockingPush(false),
    blockingPop(false)
{

}


template<typename FloatType>
RingBuffer<FloatType>::~RingBuffer()
{
    delete[] buffer;
}


template<typename FloatType>
auto RingBuffer<FloatType>::numItemsAvailableForWrite() const -> uint64
{
    // signed space between head and tail index
    const long pointerSpace = head.load() - tail.load();

    // NB: > 0 so NOT including 0
    return pointerSpace > 0 ? pointerSpace : pointerSpace + size;
}


template<typename FloatType>
auto RingBuffer<FloatType>::numItemsAvailableForRead() const -> uint64
{
    // signed space between tail and head index
    const long pointerSpace = tail.load() - head.load();

    // NB: >= 0 so including 0
    return pointerSpace >= 0 ? pointerSpace : pointerSpace + size;
}


template<typename FloatType>
auto RingBuffer<FloatType>::pushMayBlock(bool block) -> void
{
    blockingPush = block;
}


template<typename FloatType>
auto RingBuffer<FloatType>::popMayBlock(bool block) -> void
{
    blockingPop = block;
}


template<typename FloatType>
auto RingBuffer<FloatType>::setBlockingNap(const uint64 newBlockingNap) -> void
{
    blockingNap = newBlockingNap;
}


// Try to write as many items as possible and return the number actually written

template<typename FloatType>
auto RingBuffer<FloatType>::push(FloatType* data, const uint64 numSamples) -> uint64
{
    auto space = size;

    if(blockingPush)
        while((space = numItemsAvailableForWrite()) < numSamples)
            usleep(static_cast<useconds_t>(blockingNap));

    if(space == 0) return 0;

    const auto numToWrite = numSamples <= space ? numSamples : space;

    const auto currentTail = tail.load();

    // wrap if needed
    if(currentTail + numToWrite <= size)
    {
        memcpy(buffer + currentTail, data, numToWrite * itemSize);
    }
    else
    {
        const auto firstChunk = size - currentTail;
        memcpy(buffer + currentTail, data, firstChunk * itemSize);
        memcpy(buffer, data + firstChunk, (numToWrite - firstChunk) * itemSize);
    }

    tail.store((currentTail + numToWrite) % size);

    return numToWrite;
}



// Try to read as many items as possible and return the number actually read

template<typename FloatType>
auto RingBuffer<FloatType>::pop(FloatType* data, const uint64 numSamples) -> uint64
{
    auto space = size;

    if(blockingPop)
        while((space = numItemsAvailableForRead()) < numSamples)
            usleep(static_cast<useconds_t>(blockingNap));

    if(space == 0) return 0;

    const auto numToRead = numSamples <= space ? numSamples : space;

    const auto currentHead = head.load();

    //wrap if needed
    if(currentHead + numToRead <= size)
    {
        memcpy(data, buffer + currentHead, numToRead * itemSize);
    }
    else
    {
        const auto firstChunk = size - currentHead;
        memcpy(data, buffer + currentHead, firstChunk * itemSize);
        memcpy(data + firstChunk, buffer, (numToRead - firstChunk) * itemSize);
    }

    head.store((currentHead + numToRead) % size);

    return numToRead;
}


template<typename FloatType>
auto RingBuffer<FloatType>::isLockFree() const -> bool
{
    return (tail.is_lock_free() && head.is_lock_free());
}

//three available types as of now...
template class RingBuffer<float>;
template class RingBuffer<double>;
template class RingBuffer<long double>;
