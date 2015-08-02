#ifdef _DEBUG

#include <numeric>
#include <gtest/gtest.h>
#include "Crc32.hpp"

TEST(Bell_Hash, Crc32) {
	using namespace std;
	using namespace bell;
	using namespace bell::hash;

	vector<byte> a;	//	[0, 1, ... 255]
	vector<byte> b;	//	[255, ... 1, 0]
	vector<byte> c;	//	a + b

	a.resize(256);
	b.resize(256);

	iota(a. begin(), a. end(), 0);
	iota(b.rbegin(), b.rend(), 0);

	c.insert(c.end(), a.begin(), a.end());
	c.insert(c.end(), b.begin(), b.end());

	EXPECT_EQ(0x29058c73, crc32(a));
	EXPECT_EQ(0xda3ba10a, crc32(b));
	EXPECT_EQ(0xef5f180f, crc32(c));
	EXPECT_EQ(0xef5f180f, crc32(b, crc32(a)));
	
}

#endif
