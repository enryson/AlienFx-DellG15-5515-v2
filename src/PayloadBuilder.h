#include <vector>
#include <cstdint>
#include <iostream>
#include <vector>
#include <stdexcept>

class PayloadBuilder
{
private:
    std::vector<uint8_t> initalPayload;

public:
    // Construtor
    PayloadBuilder(const uint8_t payload, size_t size) {
        initalPayload.assign(payload, payload + size);
    }

    /// Method to push an element to the start of the vector
    void pushStart(uint8_t value) {
        initalPayload.insert(initalPayload.begin(), value);
    }

    // Method to push an element to the end of the vector
    void pushEnd(uint8_t value) {
        initalPayload.push_back(value);
    }

    // Method to pad the vector to 32 bytes with 0x00
    void padTo32Bytes() {
        if (initalPayload.size() > 32) {
            throw std::length_error("Vector size exceeds 32 bytes");
        }
        initalPayload.resize(32, 0x00);
    }

    // Method to convert the vector back to a uint8_t array
    const uint8_t* toUint8Array() {
        return initalPayload.data();
    }

    // Method to print the array for debugging purposes
    void print() const {
        for (size_t i = 0; i < initalPayload.size(); ++i) {
            std::cout << std::hex << static_cast<int>(initalPayload[i]) << " ";
        }
        std::cout << std::dec << std::endl;
    }
};
