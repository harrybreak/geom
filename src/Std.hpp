#pragma once

#include "Types.hpp"

#define pure = 0

#if defined(__GNUC__) || defined(__clang__)
#define force_inline inline __attribute__((always_inline))
#else
	#define force_inline inline
#endif