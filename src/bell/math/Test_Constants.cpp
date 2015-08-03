#ifdef _DEBUG

#include <gtest/gtest.h>
#include "Constants.hpp"

using namespace bell::math;

TEST(Bell_Math_Constants, PI) {
	EXPECT_EQ(3.14159265358979323846L, pi<long double>());
	EXPECT_EQ(3.14159265358979323846 , pi<double>()		);
	EXPECT_EQ(3.14159265358979323846f, pi<float>()		);
}

#endif
