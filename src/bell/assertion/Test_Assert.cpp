#ifdef _DEBUG

#include <gtest/gtest.h>
#include "../Assert.hpp"

TEST(Bell_Assertion, Runtime) {
	int x = 0;

	BELL_ASSERT(true  );
	BELL_ASSERT(x == 0);

	BELL_ASSERT_MSG(true  , "msg");
	BELL_ASSERT_MSG(x == 0, "msg");
	
	EXPECT_DEATH(BELL_ASSERT(false ), "Assertion Failed!.+");
	EXPECT_DEATH(BELL_ASSERT(x != 0), "Assertion Failed!.+");
	
	EXPECT_DEATH(BELL_ASSERT_MSG(false , "msg"), "Assertion Failed!.+");
	EXPECT_DEATH(BELL_ASSERT_MSG(x != 0, "msg"), "Assertion Failed!.+");
}


namespace {
	constexpr bool f(int x) {
		return BELL_ASSERT(x > 0), true;
	}

	constexpr bool g(int x) {
		return BELL_ASSERT_MSG(x > 0, "g"), true;
	}
}

TEST(Bell_Assertion, CompileTime) {
	constexpr bool a = f(10);
	//constexpr bool b = f(-10);

	constexpr bool c = g(42);
	//constexpr bool d = g(-42);
}

#endif
