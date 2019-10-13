
//ringbuffer.h

#include <atomic>
#include <string>


template<typename FloatType>
class RingBuffer
{
public:

    using uint64 = unsigned long;

    RingBuffer(uint64 size, const std::string& name);
    ~RingBuffer();

    auto push(FloatType* data, uint64 numSamples) -> uint64;
    auto pop(FloatType* data, uint64 numSamples) -> uint64;
    auto numItemsAvailableForWrite() const -> uint64;
    auto numItemsAvailableForRead() const -> uint64;

    auto isLockFree() const -> bool;
    auto pushMayBlock(bool block) -> void;
    auto popMayBlock(bool block) -> void;
    auto setBlockingNap(uint64 blockingNap) -> void;

private:

    uint64 size;
    FloatType* buffer;

    std::atomic<uint64> tail; // write index
    std::atomic<uint64> head; // read index

    static constexpr uint64 itemSize { sizeof(FloatType) };

    const std::string name;

    bool blockingPush;
    bool blockingPop;

    uint64 blockingNap { 500 };
};
