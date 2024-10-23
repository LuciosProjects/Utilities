#ifndef _SM_MATRIX_H
#define _SM_MATRIX_H

#include <array>
#include <thread>
#include <mutex>
#include <iostream>

/* SM_Matrix global definitions */
#define _SM_MATRIX_VERSION  "1.1.1"
#define _NUM_THREADS_4_SM_MATRIX_CYCLICALBUFFER 1
#define _MATRIX_MAX_DIM 30
#define _MATRIX_MAX_SIZE  (_MATRIX_MAX_DIM * _MATRIX_MAX_DIM)
#define _SM_MATRIX_MEMORYPOOL_SIZE _MATRIX_MAX_SIZE * 15
#define _SM_MATRIX_BUFFERPOOL_SIZE _SM_MATRIX_MEMORYPOOL_SIZE/5
//#define _SM_Matrix_NumBufferCycles (5*_NUM_THREADS_4_SM_MATRIX_CYCLICALBUFFER)

/* SM_Matrix helper macros */
#define _MATRIX_DIVPROTECT(num,den) (abs(den) < 1e-8) ? num : (num/den)

// Singleton memory pool class
template<typename Type = double>
class SM_Matrix_MemoryPool {
private:
    static constexpr size_t PoolSize = _SM_MATRIX_MEMORYPOOL_SIZE;
    static constexpr size_t BufferSize = _SM_MATRIX_BUFFERPOOL_SIZE;
    inline static Type memory[PoolSize] = { 0 }; // Memory pool array
    inline static Type buffer[BufferSize] = { 0 };
    inline static bool allocatedMemory[PoolSize] = { false }; // Allocation tracker for instance memory
    inline static bool allocatedBuffer[BufferSize] = { false }; // Allocation tracker for buffer memory

    std::mutex mtx;

    SM_Matrix_MemoryPool() {} // Private constructor to prevent instantiation

public:
    // Get the singleton instance
    static SM_Matrix_MemoryPool& getInstance() {
        static SM_Matrix_MemoryPool instance;
        return instance;
    }

    // Allocate memory from the pool for matrix instances
    Type* allocate(size_t size, int& i_start)
    {
        int i, j;
        bool available;
        std::lock_guard<std::mutex> lock(mtx);

        for (i = 0; i <= PoolSize - size; i++) {
            // Check if contiguous memory is available
            available = true;
            for (j = 0; j < size; j++) {
                if (allocatedMemory[i + j]) {
                    available = false;
                    break;
                }
            }
            if (available) {
                // Mark as allocated
                for (j = 0; j < size; j++) {
                    allocatedMemory[i + j] = true;
                }
                i_start = i;
                return &memory[i];
            }
        }
        i_start = -1; // indication of invalid memory allocation
        return nullptr; // If no memory is left for allocation, return a nullptr
    }

    // Deallocate memory (for simplicity, just mark it as available) for matrix instances
    void deallocate(Type* ptr, size_t size, const int& i_start)
    {
        int i;
        if (i_start > 0)
        {
            for (i = 0; i < size; i++) {
                memory[i_start + i] = (Type)0;
                allocatedMemory[i_start + i] = false;
            }
        }
    }

    // Allocate memory from the pool for buffer instances
    Type* allocateBuffer(size_t size, int& i_start)
    {
        int i, j;
        bool available = true;
        std::lock_guard<std::mutex> lock(mtx);

        for (i = 0; i <= BufferSize - size; i++) {
            // Check if contiguous buffer is available
            available = true;
            for (j = 0; j < size; j++) {
                if (allocatedBuffer[i + j]) {
                    available = false;
                    break;
                }
            }
            if (available) {
                // Mark as allocated
                for (j = 0; j < size; j++) {
                    allocatedBuffer[i + j] = true;
                }
                i_start = i;
                return &buffer[i];
            }
        }
        i_start = -1; // indication of invalid memory allocation
        return nullptr; // If no buffer memory is left for allocation, return a nullptr
    }

    // Deallocate memory (for simplicity, just mark it as available) for buffer instances
    void deallocateBuffer(Type* ptr, size_t size, const int& i_start)
    {
        int i;
        if (i_start > 0)
        {
            for (i = 0; i < size; i++) {
                buffer[i_start + i] = (Type)0;
                allocatedBuffer[i_start + i] = false;
            }
        }
    }
};

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


template <class Type = double>
class SM_Matrix
{
private:
    /************************************************************************/
    /****************************** Assertions ******************************/
    /************************************************************************/
    // TBD... maybe...

    /************************************************************************/
    /**************************** Private members ***************************/
    /************************************************************************/
    int	        It = 0; /* Iterator member */
    int         MemoryIdx = 0;
    bool        bufferUsed = false, autoAllocated = false; // Indicator that implies the origin of the matrix memory
    SM_RowProxy<Type>  Prxy;

    // Private buffer constructor
    SM_Matrix(size_t Num_Rows, size_t Num_Columns, bool FromBuffer) : Nrows(Num_Rows), Ncolumns(Num_Columns), NumEl(Num_Rows* Num_Columns), bufferUsed(FromBuffer), autoAllocated(true)
    {
        Mat = SM_Matrix_MemoryPool<>::getInstance().allocateBuffer(NumEl, MemoryIdx);
    }

    /************************************************************************/
    /************************ Utility private methods ***********************/
    /************************************************************************/

    /* Copies elements to matrix from a given SM_Matrix object input */
    void ValueCopy(const SM_Matrix& other)
    {
        for (It = 0; It < NumEl; It++) {
            Mat[It] = other.Mat[It];
        }
    }
    /* Copies elements to matrix from a given pointer to an array */
    void ValueCopy(const Type* otherMat)
    {
        for (It = 0; It < NumEl; It++) {
            Mat[It] = otherMat[It];
        }
    }

    // Converts 2 dimensional indices to 1 dimensional
    int _2D_to_1D_indexing(int i, int j) const
    {
        return (i * Ncolumns + j);
    }

    bool CheckBounds(int row, int col) const
    {
        return (row >= 0 && row < Nrows && col >= 0 && col < Ncolumns);
    }
    bool CompareDims(const SM_Matrix& other) const
    {
        return (Nrows == other.Nrows && Ncolumns == other.Ncolumns);
    }
    bool CheckDims(const int num_rows, const int num_cols) const
    {
        return (num_rows == Nrows && num_cols == Ncolumns);
    }
    bool isSquare() const
    {
        return (Nrows == Ncolumns);
    }

    Type RowNorm(int row)
    {
        int j, _1D_idx;
        Type Norm = 0;
        for (j = 0; j < Ncolumns; j++) {
            _1D_idx = _2D_to_1D_indexing(row, j);
            Norm += Mat[_1D_idx] * Mat[_1D_idx];
        }

        return sqrt(Norm);
    }

    Type ColNorm(int col)
    {
        int i, _1D_idx;
        Type Norm = 0;
        for (i = 0; i < Nrows; i++) {
            _1D_idx = _2D_to_1D_indexing(i, col);
            Norm += Mat[_1D_idx] * Mat[_1D_idx];
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
    SM_Matrix() : Nrows(1), Ncolumns(1), NumEl(1), autoAllocated(true)
    {
        Mat = SM_Matrix_MemoryPool<Type>::getInstance().allocate(NumEl, MemoryIdx);

        if (Mat == nullptr)
            std::runtime_error("Invalid memory address");
    }

    /* Regular pointer constructor */
    SM_Matrix(size_t Num_Rows, size_t Num_Columns, Type* ref) : Nrows(Num_Rows), Ncolumns(Num_Columns), NumEl(Num_Rows* Num_Columns)
    {
        if (Num_Rows * Num_Columns > _MATRIX_MAX_SIZE)
        {
            std::cerr << "Matrix number of elements must not exceed " << _MATRIX_MAX_SIZE << std::endl;
            std::exit(EXIT_FAILURE);
        }

        Mat = ref;
    }

    /* Memory pool constructor */
    SM_Matrix(size_t Num_Rows, size_t Num_Columns) : Nrows(Num_Rows), Ncolumns(Num_Columns), NumEl(Num_Rows* Num_Columns), autoAllocated(true)
    {
        Mat = SM_Matrix_MemoryPool<Type>::getInstance().allocate(NumEl, MemoryIdx);

        if (Mat == nullptr)
            std::runtime_error("Invalid memory address");
    }

    /* Pointer to 2D array constructor */
    template<size_t N>
    SM_Matrix(size_t Num_Rows, size_t Num_Columns, Type(*ref)[N]) : Nrows(Num_Rows), Ncolumns(Num_Columns), NumEl(Num_Rows* Num_Columns)
    {
        if (Num_Rows * Num_Columns > _MATRIX_MAX_SIZE)
        {
            std::cerr << "Matrix number of elements must not exceed " << _MATRIX_MAX_SIZE << std::endl;
            std::exit(EXIT_FAILURE);
        }

        Mat = &ref[0][0];
    }

    /* Copy constructor */
    SM_Matrix(const SM_Matrix& other) noexcept
    {
        Nrows           = other.Nrows;
        Ncolumns        = other.Ncolumns;
        NumEl           = other.NumEl;
        autoAllocated   = false; // This constructor creates a matrix instance from an already allocated memory, no memory allocated in this scope!
        bufferUsed      = other.bufferUsed;
        Mat             = other.Mat;

        //other.Mat = nullptr; // Reference matrix should not be cleared!
        MemoryIdx           = -1; // Indication of memory that should not be cleared!
    }

    // Move constructor
    SM_Matrix(SM_Matrix&& other) noexcept
    {
        Nrows = other.Nrows;
        Ncolumns = other.Ncolumns;
        NumEl = other.NumEl;
        autoAllocated = other.autoAllocated;
        bufferUsed = other.bufferUsed;
        Mat = other.Mat;

        // Disconnect memory from the old SM_Matrix instance
        other.Mat = nullptr;
        other.MemoryIdx = -1; // Indication of invalid memory in instance
    }

    ~SM_Matrix()
    {
        if (autoAllocated)
        {
            if (bufferUsed)
                SM_Matrix_MemoryPool<Type>::getInstance().deallocateBuffer(Mat, NumEl, MemoryIdx);
            else
                SM_Matrix_MemoryPool<Type>::getInstance().deallocate(Mat, NumEl, MemoryIdx);
        }
    }

    void ReInit(const SM_Matrix& other)
    {
        this->~SM_Matrix();

        Nrows           = other.Nrows;
        Ncolumns        = other.Ncolumns;
        NumEl           = other.NumEl;
        autoAllocated   = false; // This constructor creates a matrix instance from an already allocated memory, no memory allocated in this scope!
        bufferUsed      = other.bufferUsed;
        Mat             = other.Mat;

        MemoryIdx = -2; // Indication that this SM_Matrix instace was referenced from another preallocated SM_Matrix
    }

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
    Type operator()(const int i, const int j) const { return this->Mat[_2D_to_1D_indexing(i, j)]; }
    /* 2D setter operator */
    Type& operator()(const int i, const int j) { return this->Mat[_2D_to_1D_indexing(i, j)]; }
    /* Proxy getter operator */
    SM_RowProxy<Type> operator[](const int i) const
    {
        Prxy.rowData = &Mat[i * Ncolumns];
        Prxy.Ncolumns = Ncolumns;

        return Prxy;
    }
    /* Proxy setter operator */
    SM_RowProxy<Type>& operator[](const int i)
    {
        Prxy.rowData = &Mat[i * Ncolumns];
        Prxy.Ncolumns = Ncolumns;

        return Prxy;
    }

    // Matrix copy assignment operator (copy by value)
    void operator=(const SM_Matrix& other)
    {
        ValueCopy(other);
    }

    // 1D Array pointer copy to matrix operator (copy by value)
    void operator=(const Type* other)
    {
        ValueCopy(other);
    }

    // Scalar assignment (applies to all elements)
    void operator=(const Type& k)
    {
        for (It = 0; It < NumEl; It++) {
            Mat[It] = k;
        }
    }

    // Move assignment
    //SM_Matrix& operator=(SM_Matrix&& other) noexcept
    //{
    //    if (Mat != other.Mat)
    //    {
    //        Mat = other.Mat;

    //        // Disconnect memory from the old SM_Matrix instance
    //        other.Mat = nullptr;
    //    }
    //    return *this;
    //}

    // Equality operators

    // '==' operator overload
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

    // '!=' operator overload
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
            SM_Matrix MatSum(Nrows, Ncolumns, true);

            for (It = 0; It < NumEl; It++)
            {
                MatSum.Mat[It] = Mat[It] + other.Mat[It];
            }

            return MatSum;
        }
    }

    // Addition by scalar (constant matrix of the same size, where Mat[i] = k)
    SM_Matrix operator+(const Type& k)
    {
        SM_Matrix MatSum(Nrows, Ncolumns, true);

        for (It = 0; It < NumEl; It++)
        {
            MatSum.Mat[It] = Mat[It] + k;
        }

        return MatSum;
    }

    // Addition assignment operator
    void operator+=(const SM_Matrix& other)
    {
        if (CompareDims(other))
        {
            for (It = 0; It < NumEl; It++)
            {
                Mat[It] += other.Mat[It];
            }
        }
    }

    // Scalar addition assignment operator
    void operator+=(const Type& k)
    {
        for (It = 0; It < NumEl; It++)
        {
            Mat[It] += k;
        }
    }

    // Subtraction operators

    // Matrix subtraction
    SM_Matrix operator-(const SM_Matrix& other)
    {
        if (CompareDims(other))
        {
            SM_Matrix MatSub(Nrows, Ncolumns, true);

            for (It = 0; It < NumEl; It++)
            {
                MatSub.Mat[It] = Mat[It] - other.Mat[It];
            }

            return MatSub;
        }
    }

    // Subtraction by scalar (constant matrix of the same size, where Mat[i] = k)
    SM_Matrix operator-(const Type& k)
    {
        SM_Matrix MatSub(Nrows, Ncolumns, true);

        for (It = 0; It < NumEl; It++)
        {
            MatSub.Mat[It] = Mat[It] - k;
        }

        return MatSub;
    }

    // Self negation operator
    SM_Matrix operator-()
    {
        SM_Matrix Neg(Nrows, Ncolumns, true);

        for (It = 0; It < NumEl; It++)
        {
            Neg.Mat[It] = -Mat[It];
        }
        return Neg;
    }

    // Subtraction assignment operator
    void operator-=(const SM_Matrix& other)
    {
        if (CompareDims(other))
        {
            for (It = 0; It < NumEl; It++)
            {
                Mat[It] -= other.Mat[It];
            }
        }
    }

    // Scalar subtraction assignment operator
    void operator-=(const Type& k)
    {
        for (It = 0; It < NumEl; It++)
        {
            Mat[It] -= k;
        }
    }

    // Multiplication operators

    // Matrix multiplication by matrix (for now only supports multiplications of matrices of the same size)
    SM_Matrix operator*(const SM_Matrix& other)
    {
        if (Ncolumns == other.Nrows)
        {
            int i, j, k;
            SM_Matrix MatMul(Nrows, other.Ncolumns, true);

            MatMul.Zeroize();

            for (i = 0; i < Nrows; i++) {
                for (j = 0; j < other.Ncolumns; j++) {
                    for (k = 0; k < Ncolumns; k++) {
                        MatMul.Mat[other._2D_to_1D_indexing(i, j)] += Mat[_2D_to_1D_indexing(i, k)] * other.Mat[other._2D_to_1D_indexing(k, j)];
                    }
                }
            }
            return MatMul;
        }
    }

    // Matrix multiplication by vector

    void MatxVec(Type VecIn[], Type VecOut[])
    {
        int i, j;

        for (i = 0; i < Nrows; i++)
        {
            VecOut[i] = (Type)0;
            for (j = 0; j < Ncolumns; j++)
            {
                VecOut[i] += Mat[_2D_to_1D_indexing(i, j)] * VecIn[j];
            }
        }
    }

    // Matrix multiplication by scalar k
    SM_Matrix operator*(const Type& k)
    {
        SM_Matrix MatMul(Nrows, Ncolumns, true);

        for (It = 0; It < NumEl; It++) {
            MatMul.Mat[It] = Mat[It] * k;
        }
        return MatMul;
    }

    // Matrix multiplication assignment by matrix (applies only to square matrices)
    void operator*=(const SM_Matrix& other)
    {
        if (isSquare())
        {
            int i, j, k;

            SM_Matrix MatMul(Nrows, other.Ncolumns, true);

            MatMul.Zeroize();

            for (i = 0; i < Nrows; i++) {
                for (j = 0; j < other.Ncolumns; j++) {
                    for (k = 0; k < Ncolumns; k++) {
                        MatMul.Mat[other._2D_to_1D_indexing(i, j)] += Mat[_2D_to_1D_indexing(i, k)] * other.Mat[other._2D_to_1D_indexing(k, j)];
                    }
                }
            }
            *this = MatMul;
        }
    }

    // Matrix multiplication assignment by scalar
    void operator*=(const Type& k)
    {
        for (It = 0; It < NumEl; It++) {
            Mat[It] *= k;
        }
    }

    // Division operators

    // Matrix division by scalar
    SM_Matrix operator/(const Type& k)
    {
        SM_Matrix MatDiv(Nrows, Ncolumns, true);

        for (It = 0; It < NumEl; It++) {
            MatDiv.Mat[It] = Mat[It] / k;
        }
        return MatDiv;
    }

    // Matrix division assignment by scalar
    void operator/=(const Type& k)
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

    // Matrix division assignment by matrix (multiply assign with inverse)
    void operator/=(const SM_Matrix& other)
    {
        *this *= other.Invert();
    }

    // Matrix exponentiation (takes only integer exponents)
    SM_Matrix operator^(const int& exponent)
    {
        if (isSquare())
        {
            if (abs(exponent) == 0) // 0 exponent
            {
                SM_Matrix Result(Nrows, Ncolumns, true);
                Result.Identity();

                return std::move(Result);
            }
            else if (exponent > 0) // Positive exponent
            {
                SM_Matrix Result(Nrows, Ncolumns, true);

                Result = *this; // Copy by value

                for (It = 1; It < exponent; It++) {
                    Result *= *this;
                }
                return std::move(Result);
            }
            else // Negative exponent
            {
                SM_Matrix Result(Nrows, Ncolumns, true);

                Result = Invert();
                Result = Result ^ (-exponent);

                return std::move(Result);
            }
        }
    }

    void operator^=(const int& exponent)
    {
        if (isSquare())
        {
            if (abs(exponent) == 0) // 0 exponent
            {
                Identity();
            }
            else if (exponent > 0) // Positive exponent
            {
                SM_Matrix Result(Nrows, Ncolumns, true);

                Result = *this; // Copy by value

                for (It = 1; It < exponent; It++) {
                    Result *= *this;
                }
                *this = Result;
            }
            else // Negative exponent
            {
                SM_Matrix Result(Nrows, Ncolumns, true);

                Result = Invert();
                Result = Result ^ (-exponent);

                *this = Result;
            }
        }
    }

    ///************************************************************************/
    ///************************ Utility public methods ************************/
    ///************************************************************************/

    /* Zeroize matrix elements */
    void Zeroize()
    {
        for (It = 0; It < NumEl; It++)
        {
            Mat[It] = (Type)0;
        }
    }

    ///* Identity matrix operation                                                        */
    ///* it returns a matrix for which the elements are either 1 or 0 based on i == j     */
    ///* where i is the row index & j is the column index                                 */
    void Identity()
    {
        int i, j;
        for (i = 0; i < Nrows; i++) {
            for (j = 0; j < Ncolumns; j++) {
                Mat[_2D_to_1D_indexing(i, j)] = (Type)(i == j);
            }
        }
    }

    /* Application of a single argument function to the object */
    SM_Matrix ApplyEach(Type(*func)(Type))
    {
        SM_Matrix res(Nrows, Ncolumns, true);

        for (It = 0; It < NumEl; It++)
        {
            res.Mat[It] = func(Mat[It]);
        }
        return res;
    }
    SM_Matrix ApplyEach(Type(*func)(Type&))
    {
        SM_Matrix res(Nrows, Ncolumns, true);

        for (It = 0; It < NumEl; It++)
        {
            res.Mat[It] = func(Mat[It]);
        }
        return res;
    }

    /* Application of a double argument function to the object */
    SM_Matrix ApplyEach(Type(*func)(Type, Type), Type SecondArg)
    {
        SM_Matrix res(Nrows, Ncolumns, true);

        for (It = 0; It < NumEl; It++)
        {
            res.Mat[It] = func(Mat[It], SecondArg);
        }
        return res;
    }
    SM_Matrix ApplyEach(Type(*func)(Type&, Type&), Type& SecondArg)
    {
        SM_Matrix res(Nrows, Ncolumns, true);

        for (It = 0; It < NumEl; It++)
        {
            res.Mat[It] = func(Mat[It], SecondArg);
        }
        return res;
    }

    /* Element-wise multiplication */
    SM_Matrix EMultiply(const SM_Matrix& other)
    {
        SM_Matrix res(Nrows, Ncolumns, true);

        if (NumEl == other.NumEl)
        {
            for (It = 0; It < NumEl; It++)
            {
                res.Mat[It] = Mat[It] * other.Mat[It];
            }

            return res;
        }
        else
        {
            res.Zeroize();
            return res;
        }
    }

    /* Element-wise division */
    SM_Matrix EDivide(const SM_Matrix& other)
    {
        SM_Matrix res(Nrows, Ncolumns, true);

        if (NumEl == other.NumEl)
        {
            for (It = 0; It < NumEl; It++)
            {
                res.Mat[It] = _MATRIX_DIVPROTECT(Mat[It], other.Mat[It]);
            }

            return res;
        }
        else
        {
            res.Zeroize();
            return res;
        }
    }

    ///* Multiply instance with vector-like object (make sure the multiplications is mathematically legal!). */
    ///* as input & output, put the addresses of the first elements in the Vin/Vout data structures. */
    //void MultiplyVector(Type* Vin, Type* Vout)
    //{
    //    int i, j;
    //    for (i = 0; i < Nrows; i++)
    //    {
    //        *(Vout + i) = Type(0);
    //        for (j = 0; j < Ncolumns; j++)
    //        {
    //            *(Vout + i) += Mat[i * Ncolumns + j] * (*(Vin + j));
    //        }
    //    }
    //}

    ///* Swaps between 2 matrix elements */
    //SM_Matrix Swap(int r1, int c1, int r2, int c2)
    //{
    //    if (CheckBounds(r1, c1) && CheckBounds(r2, c2))
    //    {
    //        Type temp = Mat[r1 * Ncolumns + c1];
    //        Mat[r1 * Ncolumns + c1] = Mat[r2 * Ncolumns + c2];
    //        Mat[r2 * Ncolumns + c2] = temp;
    //        return *this;
    //    }
    //}

    ///* Swap matrix rows */
    //SM_Matrix SwapRows(int row1, int row2)
    //{
    //    for (It = 0; It < Ncolumns; It++)
    //    {
    //        this->Swap(row1, It, row2, It);
    //    }
    //    return *this;
    //}

    ///* Swap matrix columns */
    //SM_Matrix SwapColumns(int col1, int col2)
    //{
    //    for (It = 0; It < Nrows; It++)
    //    {
    //        this->Swap(It, col1, It, col2);
    //    }
    //    return *this;
    //}

    /* Transpose matrix */
    SM_Matrix Transpose()
    {
        SM_Matrix TMat(Ncolumns, Nrows, true);

        int i, j;

        for (i = 0; i < Nrows; i++) {
            for (j = 0; j < Ncolumns; j++) {
                TMat.Mat[j * Nrows + i] = Mat[_2D_to_1D_indexing(i, j)];
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
                Prod *= Mat[It * Ncolumns + It];
            }
        }
        else
        {
            Prod = (Type)0;
        }
        return Prod;
    }

    /* Matrix trace (sum of diagonal elements) */
    Type Trace()
    {
        Type Sum = 0;
        if (isSquare()) {
            for (It = 0; It < Nrows; It++) {
                Sum += Mat[_2D_to_1D_indexing(It, It)];
            }
        }
        return Sum;
    }

    /* Minor of matrix given by (row,column) position */
    SM_Matrix Minor(int row, int col) const
    {
        SM_Matrix Minor(Nrows - 1, Ncolumns - 1, true);

        int i, j, m_tracker = 0;

        if (CheckBounds(row, col))
        {
            for (i = 0; i < Nrows; i++) {
                if (i == row) { continue; }

                for (j = 0; j < Ncolumns; j++) {
                    if (j == col) { continue; }
                    Minor.Mat[m_tracker] = Mat[_2D_to_1D_indexing(i, j)];
                    m_tracker++;
                }
            }
        }
        else
        {
            Minor.Zeroize();
        }

        return Minor;
    }

    /* Matrix determinant */
    Type Det() const
    {
        if (isSquare()) {

            SM_Matrix L(Nrows, Nrows, true);
            SM_Matrix U(Nrows, Ncolumns, true);

            LU_Decompose(L, U);

            return U.DiagProduct(); // Diagonal product of L is 1
        }
        else
            return (Type)0;
    }

    /* Calculates the adjugate (cofactor) matrix */
    SM_Matrix Adjugate() const
    {
        SM_Matrix Adj(Nrows, Ncolumns, true);

        int i, j;
        Type sign;
        bool ODD;

        for (i = 0; i < Nrows; i++) {
            for (j = 0; j < Ncolumns; j++) {
                ODD = ((i + 1) + (j + 1)) % 2;
                sign = ODD ? -1 : 1;

                Adj.Mat[j * Nrows + i] = sign * Minor(i, j).Det();
            }
        }
        return Adj;
    }

    /* Calculates the inverse of the matrix instance */
    SM_Matrix Invert() const
    {
        Type MatDet = Det();

        return (Adjugate() / MatDet);
    }

    ///* Matrix QR decomposition, Q is orthogonal to A & R is upper triangular matrix */
    //void QR_Decompose(SM_Matrix& Q, SM_Matrix& R)
    //{
    //    CyclicalBuffer<>::BufferHandle BufferHandle = CyclicalBuffer<>::getInstance().getNextBuffer();
    //    CyclicalBuffer<>::BufferHandle BufferHandle2 = CyclicalBuffer<>::getInstance().getNextBuffer();
    //    SM_Matrix CurrentA(Nrows, 1, BufferHandle.getBuffer());
    //    SM_Matrix CurrentA(Nrows, Ncolumns, BufferHandle2.getBuffer());
    // 
    //    Type Norm;
    //    int row, row_inloop, col;
    //
    //    if (!Q.CheckDims(Nrows, Ncolumns) || !R.CheckDims(Ncolumns, Ncolumns))
    //    {
    //        return;
    //    }
    //
    //    if (Nrows >= Ncolumns)
    //    {
    //        R.Zeroize();

    //        for (It = 0; It < Ncolumns; It++)
    //        {
    //            if (It == 0) {
    //                Norm = U.ColNorm(It);
    //                for (row = 0; row < Nrows; row++) {
    //                    Q.Mat[row * Ncolumns + It] = U.Mat[row * Ncolumns + It] / Norm;
    //                }
    //            }
    //            else {
    //                /* Initialize current a_i & u_i vectors */
    //                for (row = 0; row < Nrows; row++) {
    //                    CurrentA.Mat[row] = U.Mat[row * Ncolumns + It] = Mat[row * Ncolumns + It];
    //                }

    //                /* Projecting vectors to current direction i */
    //                for (col = 0; col < It; col++) {
    //                    Norm = U.ColNorm(It);

    //                    for (row = 0; row < Nrows; row++) {
    //                        for (row_inloop = 0; row_inloop < Nrows; row_inloop++) {
    //                            U.Mat[row * Ncolumns + It] -= Q.Mat[row_inloop * Ncolumns + col] * CurrentA.Mat[row_inloop] * Q.Mat[row * Ncolumns + col];
    //                        }
    //                    }
    //                }

    //                /* Dividing u_i by its norm to get q_i (if Norm > 0) */
    //                Norm = U.ColNorm(It);
    //                if (Norm < 1e-6) {
    //                    for (row = 0; row < Nrows; row++) {
    //                        Q.Mat[row * Ncolumns + It] = 0;
    //                    }
    //                }
    //                else {
    //                    for (row = 0; row < Nrows; row++) {
    //                        Q.Mat[row * Ncolumns + It] = U.Mat[row * Ncolumns + It] / Norm;
    //                    }
    //                }
    //            }
    //        }

    //        R.ValueCopy(Q.Transpose() * (*this));
    //    }
    //    else
    //    {
    //        this->Transpose().QR_Decompose(Q, R);
    //    }
    //}

    /* Decompose a square matrix A to Lower triangular & Upper triangular matrices such that A = LU */
    void LU_Decompose(SM_Matrix& L, SM_Matrix& U) const
    {
        int i, j, k;
        Type Sum;

        L.Zeroize();
        U.Zeroize();

        if (!L.CheckDims(Nrows, Nrows) || !U.CheckDims(Nrows, Ncolumns))
        {
            return;
        }

        for (i = 0; i < Nrows; i++) {

            /* Upper triangular matrix */
            for (j = i; j < Ncolumns; j++) {
                Sum = 0;
                for (k = 0; k < i; k++) {
                    //Sum += L.Mat[i * Nrows + k] * U.Mat[k * Ncolumns + j];
                    Sum += L.Mat[i * Nrows + k] * U.Mat[_2D_to_1D_indexing(k, j)];
                }
                U.Mat[_2D_to_1D_indexing(i, j)] = Mat[_2D_to_1D_indexing(i, j)] - Sum;
            }

            /* Lower triangular matrix */
            for (j = i; j < Nrows; j++) {
                if (i == j) {
                    L.Mat[i * Nrows + j] = 1;
                }
                else {
                    Sum = 0;
                    for (k = 0; k < i; k++) {
                        Sum += L.Mat[j * Nrows + k] * U.Mat[_2D_to_1D_indexing(k, i)];
                    }
                    L.Mat[j * Nrows + i] = _MATRIX_DIVPROTECT(Mat[_2D_to_1D_indexing(j, i)] - Sum, U.Mat[_2D_to_1D_indexing(i, i)]);
                }
            }
        }
    }
};

#endif