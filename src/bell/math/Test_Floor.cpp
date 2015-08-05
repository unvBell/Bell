#ifdef _DEBUG

//#include <gtest/gtest.h>
#include "Floor.hpp"

using bell::math::floor;

//TEST(Bell_Math_Floor, Floor) {
	static_assert(floor( 5.0f) ==  5.f, "");
	static_assert(floor(-5.0f) == -5.f, "");
	static_assert(floor( 2.5f) ==  2.f, "");
	static_assert(floor(-2.5f) == -3.f, "");
	
	static_assert(floor( 5.0) ==  5., "");
	static_assert(floor(-5.0) == -5., "");
	static_assert(floor( 2.5) ==  2., "");
	static_assert(floor(-2.5) == -3., "");
	
	static_assert(floor( 5.0L) ==  5.L, "");
	static_assert(floor(-5.0L) == -5.L, "");
	static_assert(floor( 2.5L) ==  2.L, "");
	static_assert(floor(-2.5L) == -3.L, "");
//}

#endif
