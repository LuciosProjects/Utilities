#ifndef TYPEDEFINITIONS_H
#define TYPEDEFINITIONS_H

// Boolean (logical)
typedef bool				BOOLEAN;
constexpr BOOLEAN TRUE		= true;
constexpr BOOLEAN FALSE		= false;

// Integers
typedef short			int SInt16;
typedef					int SInt32;		// Regular size of signed integer
typedef long			int SInt64;
typedef long long		int SInt64x2;	// super long integer type (for very large integers), signed
typedef unsigned short	int UInt16;
typedef unsigned		int UInt32;		// Regular size of unsigned integer
typedef unsigned long	int UInt64;
typedef unsigned long long  UInt64x2;	// super long integer type (for very large integers), unsigned

// Floating point variable types
typedef float				Real32;
typedef double				Real64;
typedef long double			LReal64;	// long double (3x the size of float)
using Real128 = double[2];				// super long double (4x the size of float)

// Characters
typedef char				Char;
typedef signed char			SChar;
typedef unsigned char		UChar;
typedef wchar_t				WChar;

#endif
