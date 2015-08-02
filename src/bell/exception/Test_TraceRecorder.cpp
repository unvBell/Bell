#ifdef _DEBUG

#include <gtest/gtest.h>
#include "TraceRecorder.hpp"

using namespace bell;
using namespace bell::exception;

TEST(Bell_Exception_TraceRecorder, StackTrace) {
	TraceRecorder rec;

	rec.recordTrace("a", 42, "f");
	rec.recordTrace("b", 43, "g");
	rec.recordTrace("c", 64, "h");

	ArrayRef<TraceInfo> trace = rec.stackTrace();

	EXPECT_STREQ("a", trace[0].file		);
	EXPECT_EQ	( 42, trace[0].line		);
	EXPECT_STREQ("f", trace[0].function	);
	
	EXPECT_STREQ("b", trace[1].file		);
	EXPECT_EQ	( 43, trace[1].line		);
	EXPECT_STREQ("g", trace[1].function	);
	
	EXPECT_STREQ("c", trace[2].file		);
	EXPECT_EQ	( 64, trace[2].line		);
	EXPECT_STREQ("h", trace[2].function	);
}

#endif
