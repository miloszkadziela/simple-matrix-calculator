#include <exception>

class MemoryAllocationErrorException : public std::exception {
    const char* what() const noexcept override;
};
