#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <algorithm>

using namespace std;
class Matrix {
public:
    Matrix();
    // Construct an identity matrix.
    Matrix(long long N) {
        this->n = N;
        this->data = new long long *[N];
        for (long long i = 0; i < N; i++) {
            this->data[i] = new long long[N];
            for (long long j = 0; j < N; j++) {
                if (i == j) {
                    this->data[i][j] = 1;
                } else {
                    this->data[i][j] = 0;
                }
            }
        }
    }
    // Construct a matrix with the given data.
    Matrix(long long N, long long **Data) {
        this->n = N;
        this->data = new long long *[N];
        for (long long i = 0; i < N; i++) {
            this->data[i] = new long long[N];
            for (long long j = 0; j < N; j++) {
                this->data[i][j] = Data[i][j];
            }
        }
    }
    ~Matrix() {
        for (long long i = 0; i < this->n; i++) {
            delete[] this->data[i];
        }
        delete[] this->data;
    };
    // Print out the matrix.
    void print() {
        for (long long i = 0; i < this->n; i++) {
            for (long long j = 0; j < this->n; j++) {
                cout << this->data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // TODO:
    void Matrix::add(const Matrix &rhs) {
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                this->data[i][j] += rhs.data[i][j];
            }
        }
    }

    void Matrix::subtract(const Matrix &rhs) {
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                this->data[i][j] -= rhs.data[i][j];
            }
        }
    }

    void Matrix::multiply(const Matrix &rhs) {
        long long **result = new long long*[n];
        for (int i = 0; i < n; i++) {
            result[i] = new long long[n];
            for(int j = 0; j < n; j++){
                result[i][j] = 0;
                for(int k = 0; k < n; k++){
                    result[i][j] += this->data[i][k] * rhs.data[k][j];
                }
            }
        }

        for(int i = 0; i < n; i++){
            delete [] this->data[i];
        }
        delete[] this->data;

        this->data = result;
    }

    void Matrix::transpose() {
        for (int i = 0; i < this->n; i++) {
            for (int j = i+1; j < this->n; j++) {
                swap(this->data[i][j], this->data[j][i]);
            }
        }
    }

    void Matrix::power(long long x) {
        Matrix result(n);
        Matrix base(n, this->data);

        while (x > 0) {
            if (x % 2 == 1) {
                result.multiply(base);
            }
            base.multiply(base);
            x = x/2;
        }

        // Copy result back to current matrix
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                this->data[i][j] = result.data[i][j];
            }
        }
    }

private:
    long long n;
    long long **data;
};
#endif
