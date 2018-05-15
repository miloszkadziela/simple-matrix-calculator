#include <ostream>
#include <exception>

class DifferentSizeException : public std::exception {
    std::string msg;

    public:
        DifferentSizeException(size_t, size_t, size_t, size_t);
        const char* what() const noexcept override;
};
