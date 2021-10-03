#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
    Matrix() {
        num_rows = 0;
        num_cols = 0;
    }

    Matrix(int row_count, int col_count) {
        if (row_count < 0 || col_count < 0)
            throw out_of_range("");

        num_rows = row_count;
        num_cols = col_count;

        AssignMatrix();
    }

    void Reset(int row_count, int col_count) {
        if (row_count < 0 || col_count < 0)
            throw out_of_range("");

        num_rows = row_count;
        num_cols = col_count;

        AssignMatrix();
    }

    int At(int row, int col) const {
        if (row < 0 || row >= num_rows || col < 0 || col >= num_cols)
            throw out_of_range("");

        return rows[row][col];
    }

    int& At(int row, int col) {
        if (row < 0 || row >= num_rows || col < 0 || col >= num_cols)
            throw out_of_range("");

        return rows[row][col];
    }

    int GetNumRows() const {
        return num_rows;
    }

    int GetNumColumns() const {
        return num_cols;
    }

    bool IsEmpty() const {
        return num_rows == 0 || num_cols == 0;
    }

private:
    int num_rows;
    int num_cols;
    vector<vector<int>> rows;

    void AssignMatrix() {
        rows.assign(num_rows, vector<int>(num_cols, 0));
    }
};

istream& operator>>(istream& stream, Matrix& matrix) {
    int rows, cols;
    stream >> rows >> cols;

    matrix.Reset(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            stream >> matrix.At(i, j);
        }
    }

    return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {
    stream << matrix.GetNumRows() << ' ' << matrix.GetNumColumns() << endl;

    for (int i = 0; i < matrix.GetNumRows(); ++i) {
        for (int j = 0; j < matrix.GetNumColumns(); ++j) {
            stream << matrix.At(i, j) << ' ';
        }
        stream << endl;
    }

    return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.IsEmpty() && rhs.IsEmpty())
        return true;

    if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns())
        return false;

    for (int i = 0; i < lhs.GetNumRows(); ++i) {
        for (int j = 0; j < lhs.GetNumColumns(); ++j) {
            if (lhs.At(i, j) != rhs.At(i, j))
                return false;
        }
    }

    return true;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.IsEmpty() && rhs.IsEmpty())
        return {};

    if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns())
        throw invalid_argument("");

    Matrix result = Matrix(lhs.GetNumRows(), rhs.GetNumColumns());

    for (int i = 0; i < lhs.GetNumRows(); ++i) {
        for (int j = 0; j < lhs.GetNumColumns(); ++j) {
            result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }

    return result;
}
