#ifdef _DEBUG

#include <gtest/gtest.h>
#include "Deflate.hpp"

using namespace std;
using namespace bell;

TEST(Bell_Deflate, Deflate) {
	vector<byte> v;
	v.resize(4096);

	for(int i=0; i<4096; i++)
		v[i] = i%256;

	for(int i=1; i<=9; i++) {
		auto w = deflate::compress(v, i);
		auto x = deflate::uncompress(w, v.size());

		EXPECT_LT(w.size(), v.size());
		EXPECT_EQ(v, x);
	}
}

#endif
