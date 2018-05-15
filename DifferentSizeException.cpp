#include "DifferentSizeException.h"

DifferentSizeException::DifferentSizeException
(size_t x1, size_t y1, size_t x2, size_t y2) {
    msg.append("Detected dimensions mismatch. Dimensions of LHS: ");
    msg.append(std::to_string(x1));
    msg.append(" x ");
    msg.append(std::to_string(y1));
    msg.append(" vs dimensions of RHS: ");
    msg.append(std::to_string(x2));
    msg.append(" x ");
    msg.append(std::to_string(y2));
}

const char* DifferentSizeException::what() const noexcept {
    return msg.c_str();
}
