#pragma once
#include <cmath>
#include <cfloat>
#include <cstddef>
#include <limits>

namespace Chorus
{
	typedef signed char	int8;
	typedef signed short int16;
	typedef signed int int32;
	typedef unsigned char uint8;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef float float32;


	#define	chMaxFloat		FLT_MAX
	#define	chEpsilon		FLT_EPSILON
	#define chPi			3.14159265359f
}