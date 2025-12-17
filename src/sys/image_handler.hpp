// image_handler.hpp
#ifndef IMAGE_HANDLER_HPP
#define IMAGE_HANDLER_HPP

#include <cstdint>
#include <cstddef>
#include <bitset>
#include <functional>

namespace Sys {

class ImageHandler {
public:
    static constexpr size_t CHUNK_SIZE = 240;
    static constexpr size_t DATA_PER_CHUNK = CHUNK_SIZE - 1; // 1 byte for index
    static constexpr size_t NUM_CHUNKS = 21; // 0-20 chunks
    static constexpr size_t CAPACITY = 5000;

    ImageHandler();
    ~ImageHandler();

    // Process a chunk of image data
    // Returns true if this was the final chunk
    bool ProcessChunk(uint8_t *data, size_t length);

    // Check if all chunks have been received
    bool IsComplete() const;

    // Get the assembled image data
    uint8_t* GetImageData() { return imageData; }
    size_t GetImageSize() const { return CAPACITY; }

    // Reset for new image
    void Reset();

    // Set callback for when image is complete
    void SetCompleteCallback(std::function<void()> callback) {
        onCompleteCallback = callback;
    }

    // Get ready status (1 = ready for next chunk, 0 = complete)
    uint8_t GetReadyStatus() const;

private:
    uint8_t *imageData;
    std::bitset<NUM_CHUNKS> chunkWrites;
    std::function<void()> onCompleteCallback;
};

} // namespace Sys

#endif // IMAGE_HANDLER_HPP
