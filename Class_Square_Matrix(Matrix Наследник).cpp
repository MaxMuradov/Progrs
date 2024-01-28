#include <iostream>
#include <iomanip>

class Matrix
{
protected:

    double** _matrix;
    int _rows;
    int _cols;

public:
    //Mefault construct
    Matrix() = default;

    //Construct
    Matrix(int rows, int cols)
    {
        _rows = rows;
        _cols = cols;

        _matrix = new double* [_rows];
        for (int i = 0; i < _rows; ++i)
        {
            _matrix[i] = new double[_cols];
        }

        for (int i = 0; i < _rows; ++i)
        {
            for (int j = 0; j < _cols; ++j)
                _matrix[i][j] = 0;
        }
    }

    //Copy construct
    Matrix(Matrix& matrix_other)
    {
        _rows = matrix_other._rows;
        _cols = matrix_other._cols;

        _matrix = new double* [_rows];
        for (int i = 0; i < _cols; ++i)
        {
            _matrix[i] = new double[_cols];
        }

        for (int i = 0; i < matrix_other.get_rows(); ++i)
        {
            for (int j = 0; j < matrix_other.get_cols(); ++j)
            {
                _matrix[i][j] = matrix_other._matrix[i][j];
            }
        }
    }

    //Move-copy construct
    Matrix(Matrix&& matrix_rval)
    {
        _matrix = matrix_rval._matrix;
        _rows = matrix_rval._rows;
        _cols = matrix_rval._cols;
    }

    //Destructor
    ~Matrix()
    {
        for (int i = 0; i < _rows; ++i)
            delete[] this->_matrix[i];
    }

    void clear()
    {
        for (int i = 0; i < _rows; ++i)
            delete[] _matrix[i];
    }

    int get_rows()
    {
        return _rows;
    }

    int get_cols()
    {
        return _cols;
    }

    int get_int(int indexI, int indexJ)
    {
        return _matrix[indexI][indexJ];
    }

    virtual void fullMatrix(int indexI, int indexJ, int value = 0)
    {
        _matrix[indexI][indexJ] = value;
    }

    virtual void print()
    {
        std::cout << "\n";
        for (int i = 0; i < _rows; ++i, std::cout << "\n")
        {
            for (int j = 0; j < _cols; ++j)
            {
                if (j == 0)
                    std::cout << " | " << _matrix[i][j] << std::setw(3) << " | ";
                else
                    std::cout << _matrix[i][j] << std::setw(3) << " | ";
            }
        }
        std::cout << "\n";
        std::cout << "\n";
    }

    Matrix summ(Matrix& summ_matrix)
    {
        if (_rows != summ_matrix._rows || _cols != summ_matrix._cols)
            std::cout << "Error";
        else
        {
            Matrix res(_rows, _cols);
            for (int i = 0; i < _rows; ++i)
            {
                for (int j = 0; j < _cols; ++j)
                {
                    res._matrix[i][j] = this->_matrix[i][j] + summ_matrix._matrix[i][j];
                }
            }
            return res;
        }
    }

    Matrix mult(Matrix& mult_matrix)
    {
        if (_cols != mult_matrix._rows)
            std::cout << "Error";
        else
        {
            Matrix res(_rows, mult_matrix._cols);
            for (int i = 0; i < res._rows; ++i)
            {
                for (int j = 0; j < res._cols; ++j)
                {
                    for (int z = 0; z < mult_matrix._rows; ++z)
                        res._matrix[i][j] += this->_matrix[i][z] * mult_matrix._matrix[z][j];
                }
            }
            //res.print();
            //std::cout << "\n" << res.get_cols() << res.get_rows();
            return res;
        }
    }

    Matrix& operator = (const Matrix& other)
    {
        this->clear();
        this->_cols = other._cols;
        this->_rows = other._rows;
        for (int i = 0; i < _rows; ++i)
            for (int j = 0; j < _rows; ++j)
                this->_matrix[i][j] = other._matrix[i][j];
        return *this;
    }

    Matrix& operator = (Matrix&& other)
    {
        std::swap(this->_cols, other._cols);
        std::swap(this->_rows, other._rows);
        std::swap(this->_matrix, other._matrix);
        return *this;
    }

    virtual void multNum(int val)
    {
        for (int i = 0; i < _rows; ++i)
        {
            for (int j = 0; j < _cols; ++j)
            {
                this->_matrix[i][j] = this->_matrix[i][j] * val;
            }
        }
    }

    //изменить саму матрицу
    virtual void upper_triangle()
    {
        if (_rows != _cols)
            std::cout << "Error";
        else
        {
            int koef_dif = 0;

            for (int i = 0; i < _rows - 1; ++i)
            {
                if (_matrix[i][i] != 0)
                {
                    for (int j = i + 1; j < _rows; ++j)
                    {
                        if (_matrix[j][i] != 0)
                        {
                            koef_dif = _matrix[j][i] / _matrix[i][i];
                            for (int z = i; z < _rows; ++z)
                                _matrix[j][z] -= _matrix[i][z] * koef_dif;
                        }
                    }
                }
                else
                {
                    for (int j = ++i; j < _rows; )
                    {
                        if (_matrix[j][i] != 0)
                        {
                            std::swap(_matrix[i], _matrix[j]);
                        }
                        else
                        {
                            ++j;
                        }
                    }
                }
            }
        }
    }

    //вспомогательная функция для детерминанта (не меняющая саму матрицу)
    Matrix upper_triangle(int& det_counter)
    {
        if (_rows != _cols)
            std::cout << "Error";
        else
        {
            Matrix copy(*this);
            double koef_dif = 0;

            for (int i = 0; i < copy._rows - 1; ++i)
            {
                if (copy._matrix[i][i] != 0)
                {
                    for (int j = i + 1; j < copy._rows; ++j)
                    {
                        if (copy._matrix[j][i] != 0)
                        {
                            koef_dif = copy._matrix[j][i] / copy._matrix[i][i];
                            for (int z = i; z < copy._rows; ++z)
                                copy._matrix[j][z] -= copy._matrix[i][z] * koef_dif;
                        }
                    }
                }
                else
                {
                    for (int j = ++i; j < copy._rows; )
                    {
                        if (copy._matrix[j][i] != 0)
                        {
                            std::swap(copy._matrix[i], copy._matrix[j]);
                            ++det_counter;
                        }
                        else
                        {
                            ++j;
                        }
                    }
                }
            }
            return copy;
        }
    }

    virtual void transpon()
    {
        for (int i = 0; i < _rows; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                std::swap(_matrix[i][j], _matrix[j][i]);
            }
        }
    }

    virtual int det()
    {
        int det_counter = 0;
        double det = 1;
        Matrix copy(this->upper_triangle(det_counter));
        for (int i = 0; i < copy._rows; ++i)
            det *= copy._matrix[i][i];
        if (det_counter % 2 == 1)
            det = -det;
        return det;
    }

    virtual int tray()
    {
        if (_rows != _cols)
            std::cout << "Error";
        else
        {
            int summ = 0;
            for (int i = 0; i < _rows; ++i)
            {
                summ += _matrix[i][i];
            }
            return summ;
        }
    }

};

class Square_Matrix :public Matrix
{
public:

    //Construct
    Square_Matrix(int size) : Matrix(size, size) {}

    //Copy construct
    //Cast!
    Square_Matrix(Square_Matrix& sqMat) : Matrix(static_cast<Matrix&>(sqMat)) {}

    //Move construct
    Square_Matrix(Square_Matrix&& R_val_sqMat) : Matrix(R_val_sqMat) {}

    //Destructor
    ~Square_Matrix() {}

    void fullMatrix2(int indexI, int indexJ, int value = 0)
    {
        //Matrix* ptr = this;
        Matrix* ptr_this = static_cast<Matrix*>(this);
        ptr_this->fullMatrix(indexI, indexJ, value);
    }

    void print2()
    {
        //Matrix* ptr = this;
        Matrix* ptr_this = static_cast<Matrix*>(this);
        ptr_this->print();
    }

    Square_Matrix& operator = (Square_Matrix& other)
    {
        //Matrix* ptr_this = this;
        Matrix* ptr_this = static_cast<Matrix*>(this);
        //Matrix* ptr_other = &other;
        Matrix* ptr_other = static_cast<Matrix*>(&other);
        ptr_this = ptr_other;

        return *this;
        /*ptr_this->clear();
        this->_cols = other._cols;
        this->_rows = other._rows;
        for (int i = 0; i < _rows; ++i)
            for (int j = 0; j < _rows; ++j)
                this->_matrix[i][j] = other._matrix[i][j];*/
    }

    Square_Matrix& operator = (Square_Matrix&& other)
    {
        std::swap(this->_rows, other._rows);
        std::swap(this->_cols, other._cols);
        std::swap(this->_matrix, other._matrix);
        return *this;
    }

    Square_Matrix summ(Square_Matrix& summ_matrix)
    {
        //Matrix* ptr_this = this;
        Matrix* ptr_this = static_cast<Matrix*>(this);
        //Matrix* ptr_summ = &summ_matrix;
        Matrix* ptr_summ = static_cast<Matrix*>(&summ_matrix);
        Square_Matrix res(this->_cols);
        //Matrix* ptr_res = &res;
        Matrix* ptr_res = static_cast<Matrix*>(&res);
        *ptr_res = ptr_this->summ(*ptr_summ);
        return res;
    }

    Square_Matrix mult(Square_Matrix& mult_matrix)
    {
        //Matrix* ptr_this = this;
        Matrix* ptr_this = static_cast<Matrix*>(this);
        //Matrix* ptr_mult = &mult_matrix;
        Matrix* ptr_mult = static_cast<Matrix*>(&mult_matrix);
        Square_Matrix res(this->_cols);
        //Matrix* ptr_res = &res;
        Matrix* ptr_res = static_cast<Matrix*>(&res);
        *ptr_res = ptr_this->mult(*ptr_mult);
        return res;
    }

    void multNum2(int val)
    {
        //Matrix* ptr_this = this;
        Matrix* ptr_this = static_cast<Matrix*>(this);
        ptr_this->multNum(val);
    }

    //изменить саму матрицу
    void upper_triangle2()
    {
        //Matrix* ptr_this = this;
        Matrix* ptr_this = static_cast<Matrix*>(this);
        this->upper_triangle();
    }

    //вспомогательная функция для детерминанта (не меняющая саму матрицу)
    Square_Matrix upper_triangle2(int& det_counter)
    {
        //Matrix* ptr_this = this;
        Matrix* ptr_this = static_cast<Matrix*>(this);
        Square_Matrix res(this->_cols);
        //Matrix* ptr_res = &res;
        Matrix* ptr_res = static_cast<Matrix*>(&res);
        *ptr_res = ptr_this->upper_triangle(det_counter);
        return res;
    }

    void transpon2()
    {
        //Matrix* ptr_this = this;
        Matrix* ptr_this = static_cast<Matrix*>(this);
        this->transpon();
    }

    int det2()
    {
        //Matrix* ptr_this = this;
        Matrix* ptr_this = static_cast<Matrix*>(this);
        return this->det();
    }

    int tray2()
    {
        //Matrix* ptr_this = this;
        Matrix* ptr_this = static_cast<Matrix*> (this);
        return this->tray();
    }
};


//First main

//int main()
//{
//    int counter = 0;
//
//    std::cout << "Matrix from internet: \n";
//    Matrix I(4, 4);
//
//    I.fullMatrix(0, 0, 1);
//    I.fullMatrix(0, 1, 2);
//    I.fullMatrix(0, 2, 3);
//    I.fullMatrix(0, 3, 4);
//    I.fullMatrix(1, 0, 2);
//    I.fullMatrix(1, 1, 0);
//    I.fullMatrix(1, 2, 2);
//    I.fullMatrix(1, 3, 3);
//    I.fullMatrix(2, 0, 3);
//    I.fullMatrix(2, 1, 5);
//    I.fullMatrix(2, 2, 1);
//    I.fullMatrix(2, 3, 0);
//    I.fullMatrix(3, 0, 4);
//    I.fullMatrix(3, 1, 1);
//    I.fullMatrix(3, 2, 0);
//    I.fullMatrix(3, 3, 0);
//
//    I.print();
//
//    std::cout << "Determinant: \n" << I.det() << "\n";
//
//    std::cout << "construct " << "\n";
//    Matrix m1(3, 3);
//    for (int i = 0; i < m1.get_rows(); ++i)
//    {
//        for (int j = 0; j < m1.get_cols(); ++j)
//        {
//            m1.fullMatrix(i, j, ++counter);
//        }
//    }
//    m1.print();
//
//    std::cout << "transpon " << "\n";
//    Matrix m_trans(m1);
//    m_trans.transpon();
//    m_trans.print();
//
//    std::cout << "new matrix " << "\n";
//    Matrix mm(Matrix(3, 3));
//    mm.fullMatrix(0, 0, 10);
//    mm.fullMatrix(1, 1, 20);
//    mm.fullMatrix(2, 2, 30);
//    mm.print();
//    Matrix mm_copy(mm);
//    std::cout << "new copy " << "\n";
//    mm_copy.print();
//
//    std::cout << "summ" << "\n";
//    Matrix m_summ(m1.summ(mm));
//    m_summ.print();
//
//    std::cout << "summ tray" << "\n" << m_summ.tray() << "\n";
//
//    Matrix A(4, 3);
//    counter = 13;
//    for (int i = 0; i < A.get_rows(); ++i)
//    {
//        for (int j = 0; j < A.get_cols(); ++j)
//        {
//            A.fullMatrix(i, j, ++counter);
//        }
//    }
//    A.print();
//
//    counter = 8;
//    Matrix B(3, 2);
//    for (int i = 0; i < B.get_rows(); ++i)
//    {
//        for (int j = 0; j < B.get_cols(); ++j)
//        {
//            B.fullMatrix(i, j, ++counter);
//        }
//    }
//    B.print();
//
//    std::cout << "\n" << "mult A*B \n";
//    Matrix C(A.mult(B));
//    C.print();
//
//    std::cout << "\n" << "mult A * num: \n";
//    A.multNum(3);
//    A.print();
//}

// Second main

int main()
{
    int counter = 0;

    std::cout << "Matrix from internet: \n";
    Square_Matrix I(4);

    I.fullMatrix2(0, 0, 1);
    I.fullMatrix2(0, 1, 2);
    I.fullMatrix2(0, 2, 3);
    I.fullMatrix2(0, 3, 4);
    I.fullMatrix2(1, 0, 2);
    I.fullMatrix2(1, 1, 0);
    I.fullMatrix2(1, 2, 2);
    I.fullMatrix2(1, 3, 3);
    I.fullMatrix2(2, 0, 3);
    I.fullMatrix2(2, 1, 5);
    I.fullMatrix2(2, 2, 1);
    I.fullMatrix2(2, 3, 0);
    I.fullMatrix2(3, 0, 4);
    I.fullMatrix2(3, 1, 1);
    I.fullMatrix2(3, 2, 0);
    I.fullMatrix2(3, 3, 0);

    I.print2();

    std::cout << "Determinant: \n" << I.det2() << "\n";

    std::cout << "construct " << "\n";
    Square_Matrix m1(3);
    for (int i = 0; i < m1.get_rows(); ++i)
    {
        for (int j = 0; j < m1.get_cols(); ++j)
        {
            m1.fullMatrix2(i, j, ++counter);
        }
    }
    m1.print2();

    std::cout << "transpon " << "\n";
    Square_Matrix m_trans(m1);
    m_trans.transpon2();
    m_trans.print2();

    std::cout << "new matrix " << "\n";
    Square_Matrix mm(Square_Matrix(3));
    mm.fullMatrix2(0, 0, 10);
    mm.fullMatrix2(1, 1, 20);
    mm.fullMatrix2(2, 2, 30);
    mm.print2();
    Square_Matrix mm_copy(mm);
    std::cout << "new copy " << "\n";
    mm_copy.print2();

    std::cout << "summ" << "\n";
    Square_Matrix m_summ(m1.summ(mm));
    m_summ.print2();

    std::cout << "summ tray" << "\n" << m_summ.tray2() << "\n";

    Square_Matrix A(3);
    counter = 13;
    for (int i = 0; i < A.get_rows(); ++i)
    {
        for (int j = 0; j < A.get_cols(); ++j)
        {
            A.fullMatrix2(i, j, ++counter);
        }
    }
    A.print2();

    counter = 8;
    Square_Matrix B(3);
    for (int i = 0; i < B.get_rows(); ++i)
    {
        for (int j = 0; j < B.get_cols(); ++j)
        {
            B.fullMatrix2(i, j, ++counter);
        }
    }
    B.print2();

    std::cout << "\n" << "mult A*B \n";
    Square_Matrix C(A.mult(B));
    C.print2();

    std::cout << "\n" << "mult A * num: \n";
    A.multNum2(3);
    A.print2();
    return 0;
}


