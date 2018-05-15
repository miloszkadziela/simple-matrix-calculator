#include "OutOfBoundsException.h"

OutOfBoundsException::OutOfBoundsException(size_t i) {
    msg.append(std::to_string(i));
    msg.append(" is out of bounds!");
}

const char* OutOfBoundsException::what() const noexcept {
    return msg.c_str();
}
