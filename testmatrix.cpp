#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    try {
		cout << "Testing multiplying:" << endl;
        Matrix A(2, 6);
        Matrix B(3, 2);
        cin >> A;
        cin >> B;
        cout << "-----Matrix A:-----" << endl;
        cout << A;
        cout << "-----Matrix B:-----" << endl;
        cout << B;
        cout << "-----Result:-----" << endl;
        Matrix C = A * B;
        cout << C << endl << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    try {
		cout << "Testing addition:" << endl;
        Matrix A(2, 2);
        Matrix B(2, 2);
        cin >> A;
        cin >> B;
        cout << "-----Matrix A:-----" << endl;
        cout << A;
        cout << "-----Matrix B:-----" << endl;
        cout << B;
        cout << "-----Result:-----" << endl;
        Matrix C = A + B;
        cout << C << endl << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    try {
		cout << "Testing subtraction:" << endl;
        Matrix A(2, 2);
        Matrix B(2, 2);
        cin >> A;
        cin >> B;
        cout << "-----Matrix A:-----" << endl;
        cout << A;
        cout << "-----Matrix B:-----" << endl;
        cout << B;
        cout << "-----Result:-----" << endl;
        Matrix C = A - B;
        cout << C << endl << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }


    try {
		cout << "Testing incorrect multiplication:" << endl;
        Matrix A(2, 3);
        Matrix B(2, 1);
        cin >> A;
        cin >> B;
        cout << "-----Matrix A:-----" << endl;
        cout << A;
        cout << "-----Matrix B:-----" << endl;
        cout << B;
        cout << "-----Result:-----" << endl;
        Matrix C = A * B;
        cout << C << endl << endl;
	} catch (exception& e) {
        cout << e.what() << endl;
    }

    try {
		cout << "Testing incorrect addition:" << endl;
        Matrix A(2, 1);
        Matrix B(2, 2);
        cin >> A;
        cin >> B;
        cout << "-----Matrix A:-----" << endl;
        cout << A;
        cout << "-----Matrix B:-----" << endl;
        cout << B;
        cout << "-----Result:-----" << endl;
        Matrix C = A + B;
        cout << C << endl << endl;
	} catch (exception& e) {
        cout << e.what() << endl;
    }

    try {
		cout << "Testing incorrect subtraction:" << endl;
        Matrix A(2, 2);
        Matrix B(1, 2);
        cin >> A;
        cin >> B;
        cout << "-----Matrix A:-----" << endl;
        cout << A;
        cout << "-----Matrix B:-----" << endl;
        cout << B;
        cout << "-----Result:-----" << endl;
        Matrix C = A - B;
        cout << C;
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}
