#ifndef MATRIX_H
#define MATRIX_H

#include "Utilities.h"

void MatrixUnittest();

template<class Type>
class RowProxy {
private:

public:
    RowProxy() {}
    //RowProxy(Type* data, const int numCols) : rowData(data), Ncolumns(numCols)

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

    Type*   rowData;
    int  Ncolumns;
};

namespace Math {
    template <class Type>
    class Matrix
    {
    private:
        /************************************************************************/
        /**************************** Private members ***************************/
        /************************************************************************/
        int	        It; /* Iterator member */
        /* int	  MatProdNumEl = 1; // Matrix product number of elements */
        Type* MatProd; /* private array for fast matrix multiplications */
        RowProxy<Type>  Prxy;

        /************************************************************************/
        /*************************** Helper functions ***************************/
        /************************************************************************/
        void ReallocateMemory()
        {
            Mat = new Type[NumEl];
            MatProd = new Type[NumEl];

            for (It = 0; It < NumEl; It++)
            {
                MatProd[It] = (Type)0;
            }
        }

        Matrix FastCopy(const Matrix& other)
        {
            if (CompareDims(other)) {
                for (It = 0; It < NumEl; It++) {
                    Mat[It] = other.Mat[It];
                }
                return *this;
            }
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: dimensions mismatch, cannot perform fast copy." << std::endl;
                std::exit(1);
            }
#endif
        }

        BOOLEAN CheckBounds(int row, int col)
        {
            return (row >= 0 && row < Nrows && col >= 0 && col < Ncolumns);
        }
        BOOLEAN CompareDims(const Matrix& other)
        {
            return (Nrows == other.Nrows && Ncolumns == other.Ncolumns);
        }
        BOOLEAN isSquare()
        {
            return (Nrows == Ncolumns);
        }

        Type RowNorm(int row)
        {
            int j;
            Type Norm = 0;
            for (j = 0; j < Ncolumns; j++) {
                Norm += SQR(Mat[row * Ncolumns + j]);
            }

            return sqrt(Norm);
        }

        Type ColNorm(int col)
        {
            int i;
            Type Norm = 0;
            for (i = 0; i < Nrows; i++) {
                Norm += SQR(Mat[i * Ncolumns + col]);
            }
            return sqrt(Norm);
        }
    public:
        /************************************************************************/
        /**************************** Public members ****************************/
        /************************************************************************/
        Type* Mat;
        int	Nrows, Ncolumns, NumEl;

        /************************************************************************/
        /***************************** Constructors *****************************/
        /************************************************************************/

        /* Default constructor */
        Matrix() : Nrows(1), Ncolumns(1), NumEl(1)
        {
            this->ReallocateMemory();
            Mat[0] = (Type)0;
        }

        /* Predefined matrix dimensions constructor */
        Matrix(int rows, int cols) : Nrows(rows), Ncolumns(cols), NumEl(rows* cols)
        {
            this->ReallocateMemory();
            for (It = 0; It < NumEl; It++) {
                Mat[It] = (Type)0;
            }
        }

        /* Matrix copy constructor */
        Matrix(const Matrix& other) : Nrows(other.Nrows), Ncolumns(other.Ncolumns), NumEl(other.Nrows* other.Ncolumns)
        {
            this->ReallocateMemory();
            for (It = 0; It < NumEl; It++) {
                Mat[It] = (Type)other.Mat[It];
            }
        }

        /* Matrix copy constructor from an array */
        Matrix(int rows, int cols, const Type other[]) : Nrows(rows), Ncolumns(cols), NumEl(rows* cols)
        {
            this->ReallocateMemory();
            int i, j;
            for (i = 0; i < Nrows; i++) {
                for (j = 0; j < Ncolumns; j++) {
                    Mat[i * Ncolumns + j] = other[i * Ncolumns + j];
                }
            }
        }

        /************************************************************************/
        /****************************** Destructor ******************************/
        /************************************************************************/
        ~Matrix()
        {
            delete[] Mat;
            delete[] MatProd;
        };

        /************************************************************************/
        /************************* Operator overloading *************************/
        /************************************************************************/

        /* Stream operators */
        friend std::istream& operator>> (std::istream& s, Matrix& self)
        {
            int i;
            for (i = 0; i < self.NumEl; i++)
            {
                s >> self.Mat[i];
            }
            return s;
        }
        friend std::ostream& operator<<  (std::ostream& s, const Matrix& self)
        {
            int i, j;
            for (i = 0; i < self.Nrows; i++)
            {
                for (j = 0; j < self.Ncolumns; j++) {
                    if (abs(self.Mat[i * self.Ncolumns + j]) < MathConsts::EPS_d)
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
        RowProxy<Type> operator[](const int i) const
        {
            Prxy.rowData = &Mat[i * Ncolumns];
            Prxy.Ncolumns = Ncolumns;

            return this->Prxy;
        }

        /* Proxy setter operator */
        RowProxy<Type>& operator[](const int i)
        {
            Prxy.rowData = &Mat[i * Ncolumns];
            Prxy.Ncolumns = Ncolumns;

            return this->Prxy;
        }

        /* Matrix copy assignment operator (copy by value) */
        Matrix operator=(const Matrix& other)
        {
            if (!CompareDims(other)) {
                this->~Matrix();
                Nrows = other.Nrows;
                Ncolumns = other.Ncolumns;
                NumEl = other.NumEl;
                this->ReallocateMemory();
            }

            for (It = 0; It < NumEl; It++)
            {
                Mat[It] = other.Mat[It];
            }
            return *this;
        }

        /* Array pointer copy to matrix operator */
        Matrix operator=(const Type other[])
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
        BOOLEAN operator==(const Matrix& other)
        {
            if (CompareDims(other))
            {
                for (It = 0; It < NumEl; It++)
                {
                    if (Mat[It] != other.Mat[It])
                    {
                        return FALSE;
                    }
                }
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }

        /* '!=' operator overload */
        BOOLEAN operator!=(const Matrix& other)
        {
            return !(*this == other);
        }

        // Addition operators

        // Matrix addition
        Matrix operator+(const Matrix& other)
        {
            if (CompareDims(other))
            {
                Matrix MatSum(Nrows, Ncolumns);
                for (It = 0; It < NumEl; It++)
                {
                    MatSum.Mat[It] = Mat[It] + other.Mat[It];
                }

                return MatSum;
            }
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: matrix dimensions mismatch, cannot perform addition." << std::endl;
                std::exit(1);
            }
#endif
        }

        // Addition by scalar (constant matrix of the same size, where Mat[i] = k)
        Matrix operator+(const Type k)
        {
            Matrix MatSum(Nrows, Ncolumns);
            for (It = 0; It < NumEl; It++)
            {
                MatSum.Mat[It] = Mat[It] + k;
            }

            return MatSum;
        }

        // Addition assignment operator
        Matrix operator+=(const Matrix& other)
        {
            if (CompareDims(other))
            {
                for (It = 0; It < NumEl; It++)
                {
                    Mat[It] += other.Mat[It];
                }
                return *this;
            }
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: matrix dimensions mismatch, cannot perform addition." << std::endl;
                std::exit(1);
            }
#endif
        }

        // Subtraction operators

        // Matrix subtraction
        Matrix operator-(const Matrix& other)
        {
            if (CompareDims(other))
            {
                Matrix MatSub(Nrows, Ncolumns);
                for (It = 0; It < NumEl; It++)
                {
                    MatSub.Mat[It] = Mat[It] - other.Mat[It];
                }

                return MatSub;
            }
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: matrix dimensions mismatch, cannot perform subtraction." << std::endl;
                std::exit(1);
            }
#endif
        }

        // Subtraction by scalar (constant matrix of the same size, where Mat[i] = k)
        Matrix operator-(const Type k)
        {
            Matrix MatSub(Nrows, Ncolumns);
            for (It = 0; It < NumEl; It++)
            {
                MatSub.Mat[It] = Mat[It] - k;
            }

            return MatSub;
        }

        // Self negation operator
        Matrix operator-()
        {
            Matrix Neg(Nrows, Ncolumns);
            for (It = 0; It < NumEl; It++)
            {
                Neg.Mat[It] = -Mat[It];
            }
            return Neg;
        }

        // Subtraction assignment operator
        Matrix operator-=(const Matrix& other)
        {
            if (CompareDims(other))
            {
                for (It = 0; It < NumEl; It++)
                {
                    Mat[It] -= other.Mat[It];
                }
                return *this;
            }
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: matrix dimensions mismatch, cannot perform subtraction." << std::endl;
                std::exit(1);
            }
#endif
        }

        // Multiplication operators

        // Matrix multiplication by matrix
        Matrix operator*(const Matrix& other)
        {
            if (Ncolumns == other.Nrows)
            {
                int i, j, k;
                Matrix MatMul(Nrows, other.Ncolumns);
                for (i = 0; i < Nrows; i++) {
                    for (j = 0; j < other.Ncolumns; j++) {
                        for (k = 0; k < Ncolumns; k++) {
                            MatMul.Mat[i * other.Ncolumns + j] += Mat[i * Ncolumns + k] * other.Mat[k * other.Ncolumns + j];
                        }
                    }
                }
                return MatMul;
            }
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: matrix dimensions mismatch, cannot perform multiplication." << std::endl;
                std::exit(1);
            }
#endif
        }

        // Matrix multiplication by scalar k
        void operator*(const Type k)
        {
            for (It = 0; It < NumEl; It++) {
                this->Mat[It] = Mat[It] * k;
            }
        }

        // Matrix multiplication assignment by matrix (applies only to square matrices)
        void operator*=(const Matrix& other)
        {
            if (isSquare())
            {
                int i, j, k;
                for (i = 0; i < Nrows; i++) {
                    for (j = 0; j < other.Ncolumns; j++) {
                        MatProd[i * other.Ncolumns + j] = 0;
                        for (k = 0; k < Ncolumns; k++) {
                            MatProd[i * other.Ncolumns + j] += Mat[i * Ncolumns + k] * other.Mat[k * other.Ncolumns + j];
                        }
                    }
                }

                for (i = 0; i < Nrows; i++) { /* Why not just iterate over NumEl if MatProd is by definition of the same size as Mat?... */
                    for (j = 0; j < other.Ncolumns; j++) {
                        this->Mat[i * Ncolumns + j] = MatProd[i * Ncolumns + j];
                    }
                }
            }
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: not a square matrix, cannot perform multiplication assignment." << std::endl;
                std::exit(1);
            }
#endif
        }

        // Matrix multiplication assignment by scalar
        void operator*=(const Type k)
        {
            for (It = 0; It < NumEl; It++) {
                this->Mat[It] *= k;
            }
        }

        // Division operators

        // Matrix division by scalar
        Matrix operator/(const Type k)
        {
            Matrix MatDiv(Nrows, Ncolumns);
            for (It = 0; It < NumEl; It++) {
                //Mat[It] /= k;
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
        Matrix operator/(const Matrix other)
        {
            return *this * other.Invert();
        }

        // Matrix exponentiation (takes only integer exponents)
        Matrix operator^(const SInt32 exponent)
        {
            int i, j;
            if (isSquare())
            {
                if (abs(exponent) == 0)
                {
                    Matrix Result(Nrows, Ncolumns);

                    for (i = 0; i < Nrows; i++) {
                        for (j = 0; j < Ncolumns; j++) {
                            Result.Mat[i * Ncolumns + j] = (i == j);
                        }
                    }
                    return Result;
                }
                else if (exponent > 0)
                {
                    Matrix Result(*this);

                    for (It = 1; It < exponent; It++) {
                        Result *= *this;
                    }
                    return Result;
                }
                else
                {
                    Matrix Result(Nrows, Ncolumns);
                    Result.FastCopy(this->Invert());
                    Result = Result ^ (-exponent);

                    return Result;
                }
            }
#ifdef _MATRIX_DEBUG
            else
            {
                std::cout << "Error: Not a square matrix, cannot exponentiate, terminating program" << std::endl;
                std::exit(1);
            }
#endif
        }

        /* Multiply instance with vector - like object(make sure the multiplications is mathematically legal!). */
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

        /* Element-wise multiplication */
        Matrix EMultiply(const Matrix& other)
        {
            if (NumEl == other.NumEl)
            {
                for (It = 0; It < NumEl; It++)
                {
                    Mat[It] *= other.Mat[It];
                }

                return *this;
            }
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: matrix dimensions mismatch, cannot perform multiplication." << std::endl;
                std::exit(1);
            }
#endif
        }

        /* Identity matrix operation */
        Matrix Identity()
        {
            //if (isSquare())
            //{
            int i, j;
            Matrix ID(Nrows, Ncolumns);
            for (i = 0; i < Nrows; i++) {
                for (j = 0; j < Ncolumns; j++) {
                    ID.Mat[i * Ncolumns + j] = (i == j);
                }
            }
            return ID;
            //}
            //return *this; // in case matrix is not square
        }

        /* Zeroize matrix elements */
        void Zeroize()
        {
            for (It = 0; It < NumEl; It++)
            {
                Mat[It] = (Type)0;
            }
        }

        /* Element-wise division (Skips 0 values) */
        Matrix EDivide(const Matrix& other)
        {
            if (NumEl == other.NumEl)
            {
                for (It = 0; It < NumEl; It++)
                {
                    if (abs(other.Mat[It]) < MathConsts::EPS_d)
                    {
                        continue;
                    }
                    Mat[It] /= other.Mat[It];
                }

                return *this;
            }
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: matrix dimensions mismatch, cannot perform division." << std::endl;
                std::exit(1);
            }
#endif
        }

        /* Application of a single argument function to the object */
        Matrix ApplyEach(Type(*func)(Type))
        {
            Matrix res(Nrows, Ncolumns);
            for (It = 0; It < NumEl; It++)
            {
                res.Mat[It] = func(Mat[It]);
            }
            return res;
        }
        Matrix ApplyEach(Type(*func)(Type&))
        {
            Matrix res(Nrows, Ncolumns);
            for (It = 0; It < NumEl; It++)
            {
                res.Mat[It] = func(Mat[It]);
            }
            return res;
        }

        /* Swaps between 2 matrix elements */
        Matrix Swap(int r1, int c1, int r2, int c2)
        {
            if (CheckBounds(r1, c1) && CheckBounds(r2, c2))
            {
                Type temp = Mat[r1 * Ncolumns + c1];
                Mat[r1 * Ncolumns + c1] = Mat[r2 * Ncolumns + c2];
                Mat[r2 * Ncolumns + c2] = temp;
                return *this;
            }
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: one or more indices out of bounds, cannot perform swap." << std::endl;
                std::exit(1);
            }
#endif
        }

        /* Swap matrix rows */
        Matrix SwapRows(int row1, int row2)
        {
            for (It = 0; It < Ncolumns; It++)
            {
                this->Swap(row1, It, row2, It);
            }
            return *this;
        }

        /* Swap matrix columns */
        Matrix SwapColumns(int col1, int col2)
        {
            for (It = 0; It < Nrows; It++)
            {
                this->Swap(It, col1, It, col2);
            }
            return *this;
        }

        /* Transpose matrix */
        Matrix Transpose()
        {
            int i, j;
            Matrix TMat(Ncolumns, Nrows);

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
        Matrix Minor(int row, int col)
        {
            Matrix Minor(Nrows - 1, Ncolumns - 1);
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
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: indices out of bounds, cannot calculate minor at(" << row << ", " << col << std::endl;
                std::exit(1);
            }
#endif
        }

        /* Matrix determinant */
        Type Det()
        {
            if (isSquare()) {
                Matrix L(Nrows, Nrows), U(Nrows, Ncolumns);
                this->LU_Decompose(L, U);

                return U.DiagProduct(); // Diagonal product of L is 1

            }
#ifdef _MATRIX_DEBUG
            else {
                std::cout << "Error: matrix is not squared, cannot calculate determinant" << std::endl;
                std::exit(1);
            }
#endif
        }

        /* Calculates the adjugate (cofactor) matrix */
        Matrix Adjugate()
        {
            Matrix Adj(Nrows, Ncolumns);
            //Matrix Minor(Nrows - 1, Ncolumns - 1);
            int i, j;
            Type sign;
            BOOLEAN ODD;

            for (i = 0; i < Nrows; i++) {
                for (j = 0; j < Ncolumns; j++) {
                    ODD = ((i + 1) + (j + 1)) % 2;
                    sign = ODD ? -1 : 1;

                    //Minor.FastCopy(Minor(i, j));
                    Adj.Mat[j * Nrows + i] = sign * Minor(i,j).Det();
                }
            }
            return Adj;
        }

        /* Calculates the inverse of the matrix instance */
        Matrix Invert()
        {
            Type MatDet = Det();
#ifdef _MATRIX_DEBUG
            if (MatDet == 0) {
                std::cout << "Error: Matrix is irreversible, cannot perform inversion." << std::endl;
                std::exit(1);
            }
#endif

            Matrix MInverse(Nrows, Ncolumns);
            MInverse.FastCopy(Adjugate());
            MInverse /= MatDet;

            return MInverse;
        }

        /* Matrix rank */
        int Rank()
        {
            Matrix Q(Nrows, Ncolumns), R(Ncolumns, Ncolumns);
            int i, j, Rank = 0;

            QR_Decompose(Q, R);

            /* Analyazing R's rows to check how many are fully zeroed */
            for (i = 0; i < R.Ncolumns; i++) {
                for (j = 0; j < R.Ncolumns; j++) {
                    if (abs(R.Mat[i * R.Ncolumns + j]) > MathConsts::EPS_d) {
                        /* Found a non zero element in row, thus it is valid for rank */
                        Rank++;
                        break;
                    }
                }
            }
            return Rank;
        }

        /* Matrix QR decomposition, Q is orthogonal to A & R is upper triangular matrix */
        void QR_Decompose(Matrix& Q, Matrix& R)
        {
            Matrix U(*this), CurrentA(Nrows, 1);
            Type Norm;
            int row, row_inloop, col;

            if (Nrows >= Ncolumns)
            {
                if (R.Nrows != Ncolumns || R.Ncolumns != Ncolumns) {
                    R.~Matrix();
                    R.Nrows = R.Ncolumns = Ncolumns;
                    R.NumEl = Ncolumns * Ncolumns;
                    R.ReallocateMemory();

                    R.Zeroize();
                }
                if (!CompareDims(Q)) {
                    Q = *this;
                }

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
                        if (Norm < MathConsts::EPS_d) {
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

                R.FastCopy(Q.Transpose() * (*this));
            }
            else
            {
                this->Transpose().QR_Decompose(Q, R);
            }
        }

        /* Decompose a square matrix A to Lower triangular & Upper triangular matrices such that A = LU */
        void LU_Decompose(Matrix& L, Matrix& U)
        {
            int i, j, k;
            Type Sum;

            if (L.Nrows != Nrows || L.Ncolumns != Nrows) {
                L.~Matrix();
                L.Nrows = L.Ncolumns = Nrows;
                L.NumEl = Nrows * Nrows;
                L.ReallocateMemory();
            }
            for (L.It = 0; L.It < L.NumEl; L.It++) { L.Mat[L.It] = 0; }

            if (!CompareDims(U)) {
                U.~Matrix();
                U.Nrows = Nrows;
                U.Ncolumns = Ncolumns;
                U.NumEl = Nrows * Ncolumns;
                U.ReallocateMemory();
            }
            for (U.It = 0; U.It < U.NumEl; U.It++) { U.Mat[U.It] = 0; }

            for (i = 0; i < Nrows; i++) {

                /* Upper triangular matrix */
                for (j = i; j < Ncolumns; j++) {
                    Sum = 0;
                    for (k = 0; k < i; k++) {
                        Sum += L.Mat[i * Nrows + k] * U.Mat[k * Ncolumns + j];
                    }
                    U.Mat[i * Ncolumns + j] = this->Mat[i * Ncolumns + j] - Sum;
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
                        if (abs(U.Mat[i * Ncolumns + i]) < 1e-12)
                        {
                            L.Mat[j * Nrows + i] = this->Mat[j * Ncolumns + i] - Sum;
                        }
                        else
                        {
                            L.Mat[j * Nrows + i] = (this->Mat[j * Ncolumns + i] - Sum)/ U.Mat[i * Ncolumns + i];
                        }
                    }
                }
            }
        }
    };
}

#endif
