#include <iostream>

class Matrix {
    private:
        struct MatrixRepresentation;
        MatrixRepresentation* data;
        double read(size_t, size_t);
        void write(size_t, size_t, double);
    public:
        Matrix(const Matrix&);
        Matrix(size_t, size_t);
        Matrix(size_t, size_t, double**);
        ~Matrix();

        class Cref;
        Cref operator()(size_t, size_t);
        double operator()(size_t, size_t) const;

        Matrix& operator=(const Matrix&);
        Matrix& operator+=(const Matrix&);
        Matrix& operator-=(const Matrix&);
        Matrix& operator*=(const Matrix&);
        Matrix operator-() const;
        bool operator==(const Matrix&);
        friend std::ostream& operator<<(std::ostream&, const Matrix&);
        friend std::istream& operator>>(std::istream&, const Matrix&);
		Matrix operator+(const Matrix&);
		Matrix operator-(const Matrix&);
		Matrix operator*(const Matrix&);
};
