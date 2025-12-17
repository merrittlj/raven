// image_handler.cpp
#include "sys/image_handler.hpp"
#include <cstring>

namespace Sys {

ImageHandler::ImageHandler() {
    imageData = new uint8_t[CAPACITY]();
    chunkWrites.reset();
}

ImageHandler::~ImageHandler() {
    delete[] imageData;
}

bool ImageHandler::ProcessChunk(uint8_t *data, size_t length) {
    if (!data || length <= 1) return false;

    uint8_t chunkIndex = data[0];
    size_t dataSize = length - 1;

    // Validate chunk index and size
    if (chunkIndex >= NUM_CHUNKS || dataSize > DATA_PER_CHUNK) {
        return false;
    }

    size_t chunkOffset = DATA_PER_CHUNK * chunkIndex;
    size_t available = CAPACITY - chunkOffset;

    if (available <= 0) return false;

    // Copy data to buffer
    size_t bytesToCopy = (available >= dataSize) ? dataSize : available;
    memcpy(&imageData[chunkOffset], &data[1], bytesToCopy);
    chunkWrites.set(chunkIndex);

    // Check if this is the final chunk (index 20)
    bool isFinalChunk = (chunkIndex == NUM_CHUNKS - 1);
    
    if (isFinalChunk) {
        if (onCompleteCallback) {
            onCompleteCallback();
        }
        return true;
    }

    return false;
}

bool ImageHandler::IsComplete() const {
    // Check if the last chunk (index 20) has been received
    return chunkWrites.test(NUM_CHUNKS - 1);
}

uint8_t ImageHandler::GetReadyStatus() const {
    // Return 0 if complete (final chunk received), 1 if ready for more
    return IsComplete() ? 0 : 1;
}

void ImageHandler::Reset() {
    chunkWrites.reset();
    // memset(imageData, 0, CAPACITY);
}

} // namespace Sys
