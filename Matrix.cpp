#include <iostream>
#include "Matrix.h"
#include "MemoryAllocationErrorException.h"
#include "DifferentSizeException.h"
#include "OutOfBoundsException.h"

using namespace std;

struct Matrix::MatrixRepresentation {
    double** matrix;
    size_t rows;
    size_t columns;
    size_t references;

    MatrixRepresentation(size_t columns, size_t rows) {
        references = 1;
        this -> rows = rows;
        this -> columns = columns;

        try {
            matrix = allocateArray(columns, rows);
        } catch (...) {
            deallocateArray(columns, matrix);
            throw;
        }
    }

    MatrixRepresentation(size_t columns, size_t rows, double** matrix) {
        if (matrix == nullptr) {
            throw MemoryAllocationErrorException();
        }

        references = 1;

        this -> columns = columns;
        this -> rows = rows;
        try {
            this -> matrix = allocCopyArray(columns, rows, matrix);
        } catch (...) {
            deallocateArray(columns, matrix);
            throw;
        }
    }

    ~MatrixRepresentation() {
        deallocateArray(columns, matrix);
    }

    MatrixRepresentation* detach() {
        if(references == 1) {
            return this;
        }

        --references;
        MatrixRepresentation* newMatrix = new MatrixRepresentation(columns, rows, matrix);
        return newMatrix;
    }
    
	double** allocateArray(size_t columns, size_t rows) {
		double** matrix = new double*[columns]();

		for(size_t i = 0 ; i < columns ; i++) {
			matrix[i] = new double[rows]();
		}
		return matrix;
	}

	double** allocCopyArray(size_t columns, size_t rows, double** src) {
		double** matrix = new double*[columns]();

		for(size_t i = 0 ; i < columns ; i++) {
			matrix[i] = new double[rows]();
			for(size_t j = 0 ; j < rows ; j++) {
				matrix[i][j] = src[i][j];
			}
		}
		return matrix;
	}
	
	void deallocateArray(size_t columns, double** matrix) {
		for (size_t i = 0 ; i < columns ; i++) {
			delete [] matrix[i];
		}
		delete [] matrix;
	}
};

double Matrix::read(size_t columns, size_t rows) {
    return data->matrix[columns][rows];
}

void Matrix::write(size_t columns, size_t rows, double val) {
    data = data->detach();
    data->matrix[columns][rows] = val;
}

Matrix::~Matrix() {
    if(!(--data -> references)) {
        delete data;
    }
}

class Matrix::Cref {
    friend class Matrix;

    Matrix& output;
    size_t column;
    size_t row;

    Cref(Matrix& input, size_t inputColumn, size_t inputRow) : output(input), column(inputColumn), row(inputRow) {};

    public:
        operator double() const {
            return output.read(column, row);
        }

        Matrix::Cref& operator = (double val) {
            output.write(column, column, val);
            return *this;
        }
};

Matrix::Cref Matrix::operator()(size_t columns, size_t rows) {
    if(this->data->columns <= columns) {
        throw OutOfBoundsException(this->data->columns);
    }

    if(this->data->rows <= rows) {
        throw OutOfBoundsException(this->data->rows);
    }

    return Cref(*this, columns, rows);
}


double Matrix::operator()(size_t columns, size_t rows) const{
    if(this->data->columns <= columns) {
        throw OutOfBoundsException(this->data->columns);
    }

    if(this->data->rows <= rows) {
        throw OutOfBoundsException(this->data->rows);
    }

    return data->matrix[columns][rows];
}

Matrix& Matrix::operator=(const Matrix& RHS) {
	RHS.data->references++;
    if(--data->references == 0)
        delete data;
    data = RHS.data;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& RHS) {
	if (data->rows != RHS.data->rows || data->columns != RHS.data->columns) {
        throw DifferentSizeException(data -> columns, data -> rows, 
                RHS.data -> columns, RHS.data -> rows);
	}
	
    data = data->detach();
    for (size_t i = 0; i < data->columns; ++i) {
        for (size_t j = 0; j < data->rows; ++j) {
            data->matrix[i][j] += RHS.data->matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& RHS) {
	if (data->rows != RHS.data->rows || data->columns != RHS.data->columns) {
        throw DifferentSizeException(data -> columns, data -> rows, 
                RHS.data -> columns, RHS.data -> rows);
	}
	
    data = data->detach();
    for (size_t i = 0; i < data->columns; ++i) {
        for (size_t j = 0; j < data->rows; ++j) {
            data->matrix[i][j] -= RHS.data->matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& RHS) {
	*this = *this * RHS;
    return *this;
}

Matrix Matrix::operator+(const Matrix& RHS) {
	return Matrix(*this) += RHS;
}

Matrix Matrix::operator-(const Matrix& RHS) {
	return *this + (-RHS);
}

Matrix Matrix::operator*(const Matrix& RHS) {
	if (data->columns != RHS.data->rows)
        throw DifferentSizeException(data -> columns, data -> rows, 
                RHS.data -> columns, RHS.data -> rows);
		
    Matrix outputMatrix(RHS.data->columns, data->rows);
    for (size_t i = 0; i < RHS.data->columns; i++) {
        for (size_t j = 0; j < data->rows; j++) {
            double tempSum = 0;
            for (size_t k = 0; k < data->columns; k++)
                tempSum += data->matrix[k][j] * RHS.data->matrix[i][k];
            outputMatrix.data->matrix[i][j] = tempSum;
        }
    }
    return outputMatrix;
}

Matrix Matrix::operator-() const {
    Matrix negation(*this);
    for (size_t i = 0; i < data->columns; ++i) {
        for (size_t j = 0; j < data->rows; ++j) {
            negation.data->matrix[i][j] *= -1;
        }
    }
    return negation;
}

bool Matrix::operator==(const Matrix& RHS) {
    if(!(data->columns - RHS.data->columns) && !(data->rows - RHS.data->rows)) {
        for(size_t i = 0 ; i < data->columns ; i++) {
            for (size_t j = 0 ; j < data->rows ; j++) {
                if(data->matrix[i][j] != RHS.data->matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

Matrix::Matrix(const Matrix& input) {
    ++input.data -> references;
    data = input.data;
}

Matrix::Matrix(size_t columns, size_t rows) {
    data = new MatrixRepresentation(columns, rows);
}

Matrix::Matrix(size_t columns, size_t rows, double** matrix) {
    data = new MatrixRepresentation(columns, rows, matrix);
}

ostream& operator<<(ostream& Out, const Matrix& target)
{
    for(size_t i = 0 ; i < target.data -> columns ; i++) {
        for(size_t j = 0 ; j < target.data -> rows ; j++) {
            Out << target.data -> matrix[i][j] << "\t";
        }
        Out << endl;
    }

    return Out;
}

istream& operator>>(istream& In, const Matrix& target) {
    for(size_t i = 0 ; i < target.data->columns ; i++) {
        for(size_t j = 0 ; j < target.data->rows ; j++) {
            std::cout << "Enter value for cell [" << i << "," << j << "]: ";
            In >> target.data->matrix[i][j];
        }
    }
    return In;
}
