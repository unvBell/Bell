#ifdef _DEBUG

#include <gtest/gtest.h>
#include "ErrorInfoRecorder.hpp"

using namespace bell;
using namespace bell::exception;

TEST(Bell_Exception_ErrorInfoRecorder, StackTrace) {
	ErrorInfoRecorder r1;
	r1.addInfo("a");
	r1.addInfo("b");
	r1.addInfo("c");

	EXPECT_STREQ("a\nb\nc\n", r1.errorInfo());
	
	ErrorInfoRecorder r2{ "xyz" };
	r2.addInfo("a");
	r2.addInfo("b");
	r2.addInfo("c");

	EXPECT_STREQ("xyz\na\nb\nc\n", r2.errorInfo());
}

#endif
