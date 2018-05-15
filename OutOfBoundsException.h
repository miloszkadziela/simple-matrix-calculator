#include <ostream>
#include <exception>

class OutOfBoundsException : public std::exception {
    std::string msg;

    public:
        OutOfBoundsException(size_t i);
        const char* what() const noexcept override;
};
