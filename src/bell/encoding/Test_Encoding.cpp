#ifdef _DEBUG

#include <gtest/gtest.h>
#include "Encoding.hpp"

using namespace bell::encoding;

namespace {
	constexpr char		utf8[] = u8"123abcいろは春眠暁";
	constexpr char		sjis[] = "\x31\x32\x33\x61\x62\x63\x82\xA2\x82\xeb\x82\xcd\x8f\x74\x96\xb0\x8b\xc5";	//	sjis"123abcいろは春眠暁"
	constexpr wchar_t	wide[] = L"123abcいろは春眠暁";
}

TEST(Bell_Encoding, ToUTF8) {
	EXPECT_EQ(utf8, sjisToUtf8(sjis));
	EXPECT_EQ(utf8, wideToUtf8(wide));
}

TEST(Bell_Encoding, ToSJis) {
	EXPECT_EQ(sjis, utf8ToSJis(utf8));
	EXPECT_EQ(sjis, wideToSJis(wide));
}

TEST(Bell_Encoding, ToWide) {
	EXPECT_EQ(wide, utf8ToWide(utf8));
	EXPECT_EQ(wide, sjisToWide(sjis));
}

#endif
