#ifndef _SM_MATRIX_H
#define _SM_MATRIX_H

#include <math.h>
#include <iostream>

/* SM_Matrix helper macros */
#define _MATRIX_DIVPROTECT(num,den) (abs(den) < 1e-8) ? num : (num/den)

/* SM_Matrix global definitions */
//#define _MATRIX_MAX_DIM 50
//double _SM_Matrix_First_Buffer_[_MATRIX_MAX_DIM][_MATRIX_MAX_DIM] = { 0.0 };
//double _SM_Matrix_Second_Buffer_[_MATRIX_MAX_DIM][_MATRIX_MAX_DIM] = { 0.0 };

template<class Type>
class SM_RowProxy {
private:

public:
    SM_RowProxy() {}
    ~SM_RowProxy() {}

    /* RowProxy getter operator */
    Type operator[](const int col) const
    {
        return rowData[col];
    }

    /* RowProxy setter operator */
    Type& operator[](const int col)
    {
        return rowData[col];
    }

    Type* rowData;
    int  Ncolumns;
};

namespace Math
{
    template <class Type, size_t Num_Rows, size_t Num_Columns>
    class SM_Matrix
    {
    private:
        /************************************************************************/
        /**************************** Private members ***************************/
        /************************************************************************/
        int	        It; /* Iterator member */
        SM_RowProxy<Type>  Prxy;
        //SM_Matrix<Type, NumRows, Num_Columns> Buffer;
        Type Buffer[Num_Rows * Num_Columns]; // Buffer member to serve as intermediate memory for matrix operations

        /************************************************************************/
        /************************ Utility private methods ************************/
        /************************************************************************/

        /* Copies elements to matrix from a given SM_Matrix object input */
        SM_Matrix ValueCopy(const SM_Matrix& other)
        {
            for (It = 0; It < NumEl; It++) {
                Mat[It] = other.Mat[It];
            }
            return *this;
        }
        /* Copies elements to matrix from a given pointer to an array */
        SM_Matrix ValueCopy(const Type* otherMat)
        {
            for (It = 0; It < NumEl; It++) {
                Mat[It] = otherMat[It];
            }
            return *this;
        }


        bool CheckBounds(int row, int col)
        {
            return (row >= 0 && row < Nrows && col >= 0 && col < Ncolumns);
        }
        bool CompareDims(const SM_Matrix& other)
        {
            return (Nrows == other.Nrows && Ncolumns == other.Ncolumns);
        }
        bool isSquare()
        {
            return (Nrows == Ncolumns);
        }

        Type RowNorm(int row)
        {
            int j;
            Type Norm = 0;
            for (j = 0; j < Ncolumns; j++) {
                Norm += Mat[row * Ncolumns + j] * Mat[row * Ncolumns + j];
            }

            return sqrt(Norm);
        }

        Type ColNorm(int col)
        {
            int i;
            Type Norm = 0;
            for (i = 0; i < Nrows; i++) {
                Norm += Mat[i * Ncolumns + col] * Mat[i * Ncolumns + col];
            }
            return sqrt(Norm);
        }
    public:
        /************************************************************************/
        /**************************** Public members ****************************/
        /************************************************************************/
        Type Mat[Num_Rows * Num_Columns];
        int	Nrows, Ncolumns, NumEl;

        /* Default SM_Matrix constructor */
        SM_Matrix() : Nrows(Num_Rows), Ncolumns(Num_Columns), NumEl(Num_Rows* Num_Columns)
        {
            Zeroize();
        }

        /* Predefined matrix dimensions & allocated memory constructor */
        SM_Matrix(Type* ref) : Nrows(Num_Rows), Ncolumns(Num_Columns), NumEl(Num_Rows* Num_Columns)
        {
            Mat = ref;
        }


        SM_Matrix(SM_Matrix& ref) : Nrows(ref.Nrows), Ncolumns(ref.Ncolumns), NumEl(ref.Nrows* ref.Ncolumns)
        {
            ValueCopy(ref);
        }

        ~SM_Matrix() {};

        /* Stream operators */
        friend std::istream& operator>>(std::istream& s, SM_Matrix& self)
        {
            int i;
            for (i = 0; i < self.NumEl; i++)
            {
                s >> self.Mat[i];
            }
            return s;
        }
        friend std::ostream& operator<<(std::ostream& s, const SM_Matrix& self)
        {
            int i, j;
            for (i = 0; i < self.Nrows; i++)
            {
                for (j = 0; j < self.Ncolumns; j++) {
                    if (abs(self.Mat[i * self.Ncolumns + j]) < 1e-6)
                        self.Mat[i * self.Ncolumns + j] = 0;
                    s << self.Mat[i * self.Ncolumns + j] << "\t";
                }
                s << std::endl;
            }
            return s;
        }

        /* Getter & setter operators */

        /* 2D getter operator */
        Type operator()(const int i, const int j) const { return this->Mat[i * Ncolumns + j]; }
        /* 2D setter operator */
        Type& operator()(const int i, const int j) { return this->Mat[i * Ncolumns + j]; }
        /* Proxy getter operator */
        SM_RowProxy<Type> operator[](const int i) const
        {
            Prxy.rowData = &Mat[i * Ncolumns];
            Prxy.Ncolumns = Ncolumns;

            return this->Prxy;
        }
        /* Proxy setter operator */
        SM_RowProxy<Type>& operator[](const int i)
        {
            Prxy.rowData = &Mat[i * Ncolumns];
            Prxy.Ncolumns = Ncolumns;

            return this->Prxy;
        }
        /* Matrix copy assignment operator (copy by value) */
        void operator=(const SM_Matrix& other)
        {
            ValueCopy(other);
        }

        /* Array pointer copy to matrix operator */
        SM_Matrix operator=(const Type other[])
        {
            int i, j;
            for (i = 0; i < Nrows; i++) {
                for (j = 0; j < Ncolumns; j++) {
                    Mat[i * Ncolumns + j] = other[i * Ncolumns + j];
                }
            }
            return *this;
        }

        /* Equality operators */

        /* '==' operator overload */
        bool operator==(const SM_Matrix& other)
        {
            if (CompareDims(other))
            {
                for (It = 0; It < NumEl; It++)
                {
                    if (Mat[It] != other.Mat[It])
                    {
                        return false;
                    }
                }
                return true;
            }
            else
            {
                return false;
            }
        }

        /* '!=' operator overload */
        bool operator!=(const SM_Matrix& other)
        {
            return !(*this == other);
        }

        // Addition operators

        // Matrix addition
        SM_Matrix operator+(const SM_Matrix& other)
        {
            if (CompareDims(other))
            {
                SM_Matrix<Type, Nrows, Ncolumns> MatSum(other.Buffer);
                for (It = 0; It < NumEl; It++)
                {
                    MatSum.Mat[It] = Mat[It] + other.Mat[It];
                }
                return MatSum;
            }
        }

        // Addition by scalar (constant matrix of the same size, where Mat[i] = k)
        SM_Matrix operator+(const Type k)
        {
            SM_Matrix<Type, Nrows, Ncolumns> MatSum(Buffer);
            for (It = 0; It < NumEl; It++)
            {
                MatSum.Mat[It] = Mat[It] + k;
            }

            return MatSum;
        }

        // Addition assignment operator
        SM_Matrix operator+=(const SM_Matrix& other)
        {
            //if (CompareDims(other))
            //{
            for (It = 0; It < NumEl; It++)
            {
                Mat[It] += other.Mat[It];
            }
            return *this;
            //}
        }

        // Subtraction operators

        // Matrix subtraction
        SM_Matrix operator-(const SM_Matrix& other)
        {
            //if (CompareDims(other))
            //{
            SM_Matrix<Type, Nrows, Ncolumns> MatSub(other.Buffer);
            for (It = 0; It < NumEl; It++)
            {
                MatSub.Mat[It] = Mat[It] - other.Mat[It];
            }

            return MatSub;
            //}
        }

        // Subtraction by scalar (constant matrix of the same size, where Mat[i] = k)
        SM_Matrix operator-(const Type k)
        {
            SM_Matrix<Type, Nrows, Ncolumns> MatSub(Buffer);
            for (It = 0; It < NumEl; It++)
            {
                MatSub.Mat[It] = Mat[It] - k;
            }

            return MatSub;
        }

        // Self negation operator
        SM_Matrix operator-()
        {
            SM_Matrix<Type, Nrows, Ncolumns> Neg(Buffer);
            for (It = 0; It < NumEl; It++)
            {
                Neg.Mat[It] = -Mat[It];
            }
            return Neg;
        }

        // Subtraction assignment operator
        SM_Matrix operator-=(const SM_Matrix& other)
        {
            //if (CompareDims(other))
            //{
            for (It = 0; It < NumEl; It++)
            {
                Mat[It] -= other.Mat[It];
            }
            return *this;
            //}
        }

        // Multiplication operators

        // Matrix multiplication by matrix (for now only supports multiplications of matrices of the same size)
        SM_Matrix operator*(const SM_Matrix& other)
        {
            if (Ncolumns == other.Nrows)
            {
                int i, j, k;
                SM_Matrix<Type, Nrows, other.Ncolumns> MatMul;
                for (i = 0; i < Nrows; i++) {
                    for (j = 0; j < other.Ncolumns; j++) {
                        for (k = 0; k < Ncolumns; k++) {
                            MatMul.Mat[i * other.Ncolumns + j] += Mat[i * Ncolumns + k] * other.Mat[k * other.Ncolumns + j];
                        }
                    }
                }
                return MatMul;
            }
        }

        // Matrix multiplication by scalar k
        void operator*(const Type k)
        {
            for (It = 0; It < NumEl; It++) {
                Mat[It] = Mat[It] * k;
            }
        }

        // Matrix multiplication assignment by matrix (applies only to square matrices)
        SM_Matrix operator*=(const SM_Matrix& other)
        {
            if (isSquare())
            {
                SM_Matrix<Type, Nrows, Ncolumns> MatMul(other.Buffer);
                int i, j, k;
                for (i = 0; i < Nrows; i++) {
                    for (j = 0; j < other.Ncolumns; j++) {
                        MatMul.Mat[i * other.Ncolumns + j] = 0;
                        for (k = 0; k < Ncolumns; k++) {
                            MatMul.Mat[i * other.Ncolumns + j] += Mat[i * Ncolumns + k] * other.Mat[k * other.Ncolumns + j];
                        }
                    }
                }

                ValueCopy(MatMul);
                //for (It = 0; It < NumEl; It++)
                //{
                //    Mat[It] = MatMul.Mat[It];
                //}
            }
            return *this;
        }

        // Matrix multiplication assignment by scalar
        void operator*=(const Type k)
        {
            for (It = 0; It < NumEl; It++) {
                Mat[It] *= k;
            }
        }

        // Division operators

        // Matrix division by scalar
        SM_Matrix operator/(const Type k)
        {
            SM_Matrix<Type, Nrows, Ncolumns> MatDiv(Buffer);
            for (It = 0; It < NumEl; It++) {
                MatDiv.Mat[It] = Mat[It] / k;
            }
            return MatDiv;
        }

        // Matrix division by scalar
        void operator/=(const Type k)
        {
            for (It = 0; It < NumEl; It++) {
                Mat[It] /= k;
            }
        }

        // multiplying by inverse of other
        SM_Matrix operator/(const SM_Matrix& other)
        {
            return *this * other.Invert();
        }

        // Matrix exponentiation (takes only integer exponents)
        SM_Matrix operator^(const signed int& exponent)
        {
            if (isSquare())
            {
                if (abs(exponent) == 0)
                {
                    return Identity();
                }
                else if (exponent > 0)
                {
                    SM_Matrix<Type, Nrows, Ncolumns> Result(Buffer);
                    Result.ValueCopy(this);

                    for (It = 1; It < exponent; It++) {
                        Result *= *this;
                    }
                    return Result;
                }
                else
                {
                    SM_Matrix<Type, Nrows, Ncolumns> Result;
                    Result.ValueCopy(this->Invert());
                    Result = Result ^ (-exponent);

                    return Result;
                }
            }
        }

        /************************************************************************/
        /************************ Utility public methods ************************/
        /************************************************************************/

        /* Zeroize matrix elements */
        void Zeroize()
        {
            for (It = 0; It < NumEl; It++)
            {
                Mat[It] = (Type)0;
            }
        }

        /* Identity matrix operation                                                        */
        /* it returns a matrix for which the elements are either 1 or 0 based on i == j     */
        /* where i is the row index & j is the column index                                 */
        SM_Matrix Identity()
        {
            int i, j;
            SM_Matrix<Type, Nrows, Ncolumns> ID(Buffer);
            for (i = 0; i < Nrows; i++) {
                for (j = 0; j < Ncolumns; j++) {
                    ID.Mat[i * Ncolumns + j] = (i == j);
                }
            }
            return ID;
        }

        /* Application of a single argument function to the object */
        SM_Matrix ApplyEach(Type(*func)(Type))
        {
            SM_Matrix res(Buffer);
            for (It = 0; It < NumEl; It++)
            {
                res.Mat[It] = func(Mat[It]);
            }
            return res;
        }
        SM_Matrix ApplyEach(Type(*func)(Type&))
        {
            SM_Matrix res(Buffer);
            for (It = 0; It < NumEl; It++)
            {
                Mat[It] = func(Mat[It]);
            }
            return res;
        }

        /* Element-wise multiplication */
        SM_Matrix EMultiply(const SM_Matrix& other)
        {
            SM_Matrix res(Buffer);
            if (NumEl == other.NumEl)
            {
                for (It = 0; It < NumEl; It++)
                {
                    res.Mat[It] = Mat[It] * other.Mat[It];
                }

                return res;
            }
        }

        /* Multiply instance with vector-like object (make sure the multiplications is mathematically legal!). */
        /* as input & output, put the addresses of the first elements in the Vin/Vout data structures. */
        void MultiplyVector(Type* Vin, Type* Vout)
        {
            int i, j;
            for (i = 0; i < Nrows; i++)
            {
                *(Vout + i) = Type(0);
                for (j = 0; j < Ncolumns; j++)
                {
                    *(Vout + i) += Mat[i * Ncolumns + j] * (*(Vin + j));
                }
            }
        }

        /* Swaps between 2 matrix elements */
        SM_Matrix Swap(int r1, int c1, int r2, int c2)
        {
            if (CheckBounds(r1, c1) && CheckBounds(r2, c2))
            {
                Type temp = Mat[r1 * Ncolumns + c1];
                Mat[r1 * Ncolumns + c1] = Mat[r2 * Ncolumns + c2];
                Mat[r2 * Ncolumns + c2] = temp;
                return *this;
            }
        }

        /* Swap matrix rows */
        SM_Matrix SwapRows(int row1, int row2)
        {
            for (It = 0; It < Ncolumns; It++)
            {
                this->Swap(row1, It, row2, It);
            }
            return *this;
        }

        /* Swap matrix columns */
        SM_Matrix SwapColumns(int col1, int col2)
        {
            for (It = 0; It < Nrows; It++)
            {
                this->Swap(It, col1, It, col2);
            }
            return *this;
        }

        /* Transpose matrix */
        SM_Matrix Transpose()
        {
            int i, j;
            SM_Matrix TMat(Buffer);

            for (i = 0; i < Nrows; i++) {
                for (j = 0; j < Ncolumns; j++) {
                    TMat.Mat[j * Nrows + i] = Mat[i * Ncolumns + j];
                }
            }
            return TMat;
        }

        /* Diagonal product */
        Type DiagProduct()
        {
            Type Prod = 1;
            if (isSquare()) {
                for (It = 0; It < Nrows; It++) {
                    Prod *= this->Mat[It * Ncolumns + It];
                }
            }
            return Prod;
        }

        /* Matrix trace (sum of diagonal elements) */
        Type Trace()
        {
            Type Sum = 0;
            if (isSquare()) {
                for (It = 0; It < Nrows; It++) {
                    Sum += this->Mat[It * Ncolumns + It];
                }
            }
            return Sum;
        }

        /* Minor of matrix given by (row,column) position */
        SM_Matrix Minor(int row, int col)
        {
            SM_Matrix<Type, Nrows - 1, Ncolumns - 1> Minor;
            int i, j, m_tracker = 0;
            if (CheckBounds(row, col))
            {
                for (i = 0; i < Nrows; i++) {
                    if (i == row) { continue; }

                    for (j = 0; j < Ncolumns; j++) {
                        if (j == col) { continue; }
                        Minor.Mat[m_tracker] = Mat[i * Ncolumns + j];
                        m_tracker++;
                    }
                }
                return Minor;
            }
        }

        /* Matrix determinant */
        Type Det()
        {
            if (isSquare()) {
                SM_Matrix<Type, Nrows, Nrows> L;
                SM_Matrix U(Buffer);
                LU_Decompose(L, U);

                return U.DiagProduct(); // Diagonal product of L is 1

            }
        }

        /* Calculates the adjugate (cofactor) matrix */
        SM_Matrix Adjugate()
        {
            SM_Matrix Adj(Buffer);
            SM_Matrix<Type, Nrows - 1, Ncolumns - 1> _Minor;
            int i, j;
            Type sign;
            bool ODD;

            for (i = 0; i < Nrows; i++) {
                for (j = 0; j < Ncolumns; j++) {
                    ODD = ((i + 1) + (j + 1)) % 2;
                    sign = ODD ? -1 : 1;

                    _Minor.ValueCopy(Minor(i, j));
                    Adj.Mat[j * Nrows + i] = sign * _Minor.Det();
                }
            }
            return Adj;
        }

        /* Calculates the inverse of the matrix instance */
        SM_Matrix Invert()
        {
            Type MatDet = Det();

            //SM_Matrix MInverse(Buffer);
            //MInverse.ValueCopy(Adjugate());
            //MInverse /= MatDet;

            return Adjugate()/MatDet;
        }

        /* Matrix QR decomposition, Q is orthogonal to A & R is upper triangular matrix */
        void QR_Decompose(SM_Matrix& Q, SM_Matrix<Type, Num_Columns, Num_Columns>& R)
        {
            SM_Matrix<Type, Nrows, 1> CurrentA;
            SM_Matrix U(this);
            Type Norm;
            int row, row_inloop, col;

            if (Nrows >= Ncolumns)
            {
                R.Zeroize();

                for (It = 0; It < Ncolumns; It++)
                {
                    if (It == 0) {
                        Norm = U.ColNorm(It);
                        for (row = 0; row < Nrows; row++) {
                            Q.Mat[row * Ncolumns + It] = U.Mat[row * Ncolumns + It] / Norm;
                        }
                    }
                    else {
                        /* Initialize current a_i & u_i vectors */
                        for (row = 0; row < Nrows; row++) {
                            CurrentA.Mat[row] = U.Mat[row * Ncolumns + It] = Mat[row * Ncolumns + It];
                        }

                        /* Projecting vectors to current direction i */
                        for (col = 0; col < It; col++) {
                            Norm = U.ColNorm(It);

                            for (row = 0; row < Nrows; row++) {
                                for (row_inloop = 0; row_inloop < Nrows; row_inloop++) {
                                    U.Mat[row * Ncolumns + It] -= Q.Mat[row_inloop * Ncolumns + col] * CurrentA.Mat[row_inloop] * Q.Mat[row * Ncolumns + col];
                                }
                            }
                        }

                        /* Dividing u_i by its norm to get q_i (if Norm > 0) */
                        Norm = U.ColNorm(It);
                        if (Norm < 1e-6) {
                            for (row = 0; row < Nrows; row++) {
                                Q.Mat[row * Ncolumns + It] = 0;
                            }
                        }
                        else {
                            for (row = 0; row < Nrows; row++) {
                                Q.Mat[row * Ncolumns + It] = U.Mat[row * Ncolumns + It] / Norm;
                            }
                        }
                    }
                }

                R.ValueCopy(Q.Transpose() * (*this));
            }
            else
            {
                this->Transpose().QR_Decompose(Q, R);
            }
        }

        /* Decompose a square matrix A to Lower triangular & Upper triangular matrices such that A = LU */
        void LU_Decompose(SM_Matrix<Type, Num_Rows, Num_Rows>& L, SM_Matrix& U)
        {
            int i, j, k;
            Type Sum;

            L.Zeroize();
            U.Zeroize();

            for (i = 0; i < Nrows; i++) {

                /* Upper triangular matrix */
                for (j = i; j < Ncolumns; j++) {
                    Sum = 0;
                    for (k = 0; k < i; k++) {
                        Sum += L.Mat[i * Nrows + k] * U.Mat[k * Ncolumns + j];
                    }
                    U.Mat[i * Ncolumns + j] = Mat[i * Ncolumns + j] - Sum;
                }

                /* Lower triangular matrix */
                for (j = i; j < Nrows; j++) {
                    if (i == j) {
                        L.Mat[i * Nrows + j] = 1;
                    }
                    else {
                        Sum = 0;
                        for (k = 0; k < i; k++) {
                            Sum += L.Mat[j * Nrows + k] * U.Mat[k * Ncolumns + i];
                        }
                        L.Mat[j * Nrows + i] = _MATRIX_DIVPROTECT(Mat[j * Ncolumns + i] - Sum, U.Mat[i * Ncolumns + i]);
                    }
                }
            }
        }
    };
}

#endif