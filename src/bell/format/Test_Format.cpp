#ifdef _DEBUG

#include <gtest/gtest.h>
#include "Format.hpp"

using namespace bell;

TEST(Bell_Format, Format) {
	EXPECT_EQ("42 3.1400"		, format("%1% %2$.4f"	, 42, 3.14						));
	EXPECT_EQ("piyo hoge"		, format("%2% %1%"		, "hoge", "piyo"				));
	EXPECT_EQ("true true"		, format("%1% %1%"		, true							));
	EXPECT_EQ("(nullptr) false"	, format("%1% %2%"		, (const char*)nullptr, false	));
}

TEST(Bell_Format, WFormat) {
	EXPECT_EQ(L"42 3.1400"		, wformat(L"%1% %2$.4f"	, 42, 3.14						));
	EXPECT_EQ(L"piyo hoge"		, wformat(L"%2% %1%"	, L"hoge", L"piyo"				));
	EXPECT_EQ(L"true true"		, wformat(L"%1% %1%"	, true							));
	EXPECT_EQ(L"(nullptr) false", wformat(L"%1% %2%"	, (const wchar_t*)nullptr, false));
}

#endif
