#pragma once

#include <assert.h>


typedef signed char			int8;
typedef short				int16;
typedef int			    	int32;
typedef long long			int64;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

typedef float               float32;
typedef double              float64;


static_assert(sizeof(uint32) == 4 && sizeof(int64) == 8);