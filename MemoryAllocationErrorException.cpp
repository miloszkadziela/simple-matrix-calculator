#include "MemoryAllocationErrorException.h"

const char* MemoryAllocationErrorException::what() const noexcept {
    return "Matrix cannot be null!";
}
