#ifdef _DEBUG

//#include <gtest/gtest.h>
#include <functional>
#include "Clamp.hpp"

using std::greater;
using bell::clamp;

//TEST(Bell_Util_Clamp, Clamp) {
	static_assert(clamp(-1, 0, 1) == 0, "");
	static_assert(clamp( 2, 0, 1) == 1, "");

	static_assert(clamp(0.5, 0., 1.) == 0.5, "");
	static_assert(clamp(-1., 0., 1.) == 0. , "");

	static_assert(clamp(-1, 1, 0, greater<int>{}) == 0, "");
	static_assert(clamp( 2, 1, 0, greater<int>{}) == 1, "");

	static_assert(clamp(0.5, 1., 0., greater<double>{}) == 0.5, "");
	static_assert(clamp(-1., 1., 0., greater<double>{}) == 0. , "");
//}

#endif
