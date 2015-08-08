#ifdef _DEBUG

#include <gtest/gtest.h>
#include "File.hpp"
#include "FileException.hpp"

using namespace boost;
using namespace bell;

TEST(Bell_File, File) {
	EXPECT_THROW(File::open("<no such file>"), file::FileException);

	constexpr byte data[] = { 0xef, 0xbb, 0xbf, '1', '2', '3' };

	auto f = File::open("test/file.dat");
	auto g = File::openFromMemory("virtual", data);

	EXPECT_EQ(string_ref{ "test/file.dat" }	, f.name());
	EXPECT_EQ(ArrayRef<byte>{ data }		, f.data());

	EXPECT_EQ(string_ref{ "virtual" }		, g.name());
	EXPECT_EQ(ArrayRef<byte>{ data }		, g.data());
}

#endif
