#ifdef _DEBUG

#include <gtest/gtest.h>
#include "ArrayRef.hpp"

using namespace std;
using bell::ArrayRef;

TEST(Bell_Util_ArrayRef, ConstMethod) {
	int				raw[4]	=  { 0, 1, 2, 3 };
	array<int, 5>	arr		= {{ 0, 1, 2, 3, 4 }};
	vector<int>		vec		=  { 0, 1, 2, 3, 4, 5 };

	//	ctor
	ArrayRef<int>	a = raw;
	ArrayRef<int>	b = arr;
	ArrayRef<int>	c = vec;
	ArrayRef<int>	d = { raw, 2 };
	ArrayRef<int>	e;
	ArrayRef<int>	f = a;
	ArrayRef<int>	g = { raw + 2, 0 };

	//	op bool
	EXPECT_TRUE (!!a);
	EXPECT_TRUE (!!b);
	EXPECT_TRUE (!!c);
	EXPECT_TRUE (!!d);
	EXPECT_FALSE(!!e);
	EXPECT_TRUE (!!f);
	EXPECT_FALSE(!!g);

	//	op==, !=
	EXPECT_TRUE (a == a);
	EXPECT_FALSE(a == b);
	EXPECT_FALSE(a == d);
	EXPECT_TRUE (a == f);
	EXPECT_FALSE(a != a);
	EXPECT_TRUE (a != b);
	EXPECT_TRUE (a != d);
	EXPECT_FALSE(a != f);

	//	op[]
	EXPECT_EQ(0, a[0]);
	EXPECT_EQ(1, a[1]);
	EXPECT_EQ(2, a[2]);
	EXPECT_DEATH(a[5], ".*");

	//	iter
	EXPECT_EQ(a.data()         , a. begin());
	EXPECT_EQ(a.data()         , a.cbegin());
	EXPECT_EQ(a.data()+a.size(), a.   end());
	EXPECT_EQ(a.data()+a.size(), a.  cend());
	
	EXPECT_EQ(reverse_iterator<const int*>{ a.   end() }, a. rbegin());
	EXPECT_EQ(reverse_iterator<const int*>{ a.  cend() }, a.crbegin());
	EXPECT_EQ(reverse_iterator<const int*>{ a. begin() }, a.   rend());
	EXPECT_EQ(reverse_iterator<const int*>{ a.cbegin() }, a.  crend());
	
	//	data
	EXPECT_EQ(raw       , a.data());
	EXPECT_EQ(arr.data(), b.data());
	EXPECT_EQ(vec.data(), c.data());
	EXPECT_EQ(raw       , d.data());
	EXPECT_EQ(nullptr   , e.data());
	EXPECT_EQ(raw       , f.data());
	EXPECT_EQ(raw + 2   , g.data());

	//	size
	EXPECT_EQ(4, a.size());
	EXPECT_EQ(5, b.size());
	EXPECT_EQ(6, c.size());
	EXPECT_EQ(2, d.size());
	EXPECT_EQ(0, e.size());
	EXPECT_EQ(4, f.size());
	EXPECT_EQ(0, g.size());

	//	empty
	EXPECT_FALSE(a.empty());
	EXPECT_FALSE(b.empty());
	EXPECT_TRUE (e.empty());
	EXPECT_TRUE (g.empty());

	//	equals
	EXPECT_TRUE (a.equals(a));
	EXPECT_FALSE(a.equals(b));
	EXPECT_FALSE(a.equals(d));
	EXPECT_TRUE (a.equals(f));

	//	at
	EXPECT_EQ(0, a.at(0));
	EXPECT_EQ(1, a.at(1));
	EXPECT_EQ(2, a.at(2));
	EXPECT_THROW(a.at(5), out_of_range);

	//	front/back
	EXPECT_EQ(0, a.front());
	EXPECT_EQ(3, a. back());

	//	toVector
	auto v = a.toVector();
	EXPECT_EQ(4, v.size());
	EXPECT_EQ(a, v);
}

TEST(Bell_Util_ArrayRef, Slice) {
	vector<int> arr = { 0, 1, 2, 3, 4 };

	vector<int> a1  = { 1, 2 };
	vector<int> a2  = {};
	vector<int> a3  = { 3, 4 };
	vector<int> a4  = { 2, 3 };
	vector<int> a5  = { 0, 1 };

	ArrayRef<int> ref = arr;

	EXPECT_EQ(ArrayRef<int>{ a1 }, ref.slice( 1,  3));
	EXPECT_EQ(ArrayRef<int>{ a2 }, ref.slice( 3,  3));
	EXPECT_EQ(ArrayRef<int>{ a3 }, ref.slice( 3,  8));
	EXPECT_EQ(ArrayRef<int>{ a4 }, ref.slice(-3, -1));
	EXPECT_EQ(ArrayRef<int>{ a5 }, ref.slice(-8,  2));
}

TEST(Bell_Util_ArrayRef, NonConstMethod) {
	vector<int> v = { 0, 1, 2, 3, 4 };

	{
		ArrayRef<int> a = v;
		a.clear();
		EXPECT_EQ(nullptr, a.data());
		EXPECT_EQ(      0, a.size());
	}

	{
		ArrayRef<int> a = v;
		a.removePrefix(3);
		EXPECT_EQ(v.data()+3, a.data());
		EXPECT_EQ(         2, a.size());

		a.removePrefix(3);
		EXPECT_FALSE(!!a);
	}

	{
		ArrayRef<int> a = v;
		a.removeSuffix(3);
		EXPECT_EQ(v.data(), a.data());
		EXPECT_EQ(       2, a.size());

		a.removePrefix(3);
		EXPECT_FALSE(!!a);
	}

	{
		ArrayRef<int> a = v;
		a.popFront();

		EXPECT_EQ(v.data()+1, a.data());
		EXPECT_EQ(         4, a.size());
	}

	{
		ArrayRef<int> a = v;
		a.popBack();

		EXPECT_EQ(v.data(), a.data());
		EXPECT_EQ(       4, a.size());
	}
}

TEST(Bell_Util_ArrayRef, Op_CompileTime) {
	constexpr int			raw[5]	= { 0, 1, 2, 3, 4 };
//	constexpr ArrayRef<int>	a		= raw;
//	constexpr ArrayRef<int>	b		= { raw+1, 3 };
	constexpr ArrayRef<int> c;

//	static_assert( a, "a.op bool");
//	static_assert( b, "b.op bool");
	static_assert(!c, "c.op bool");

//	static_assert(a[2] == 2, "a.op[]");
//	static_assert(b[0] == 1, "b.op[]");
	//static_assert(c[0]     , "c.op[]");
}

TEST(Bell_Util_ArrayRef, Method_CompileTime) {
	constexpr int			raw[5]	= { 0, 1, 2, 3, 4 };
//	constexpr ArrayRef<int>	a		= raw;
//	constexpr ArrayRef<int>	b		= { raw+1, 3 };
	constexpr ArrayRef<int> c;

//	static_assert(a. begin() == a.data()         , "a.begin" );
//	static_assert(a.cbegin() == a.data()         , "a.cbegin");
//	static_assert(a.   end() == a.data()+a.size(), "a.end"   );
//	static_assert(a.  cend() == a.data()+a.size(), "a.cend"  );
//	static_assert(b. begin() == b.data()         , "b.begin" );
//	static_assert(b.cbegin() == b.data()         , "b.cbegin");
//	static_assert(b.   end() == b.data()+b.size(), "b.end"   );
//	static_assert(b.  cend() == b.data()+b.size(), "b.cend"  );
	static_assert(c. begin() == c.data()         , "c.begin" );
	static_assert(c.cbegin() == c.data()         , "c.cbegin");
	static_assert(c.   end() == c.data()+c.size(), "c.end"   );
	static_assert(c.  cend() == c.data()+c.size(), "c.cend"  );

//	static_assert(a.data() == raw + 0, "a.data");
//	static_assert(b.data() == raw + 1, "b.data");
	static_assert(c.data() == nullptr, "c.date");

//	static_assert(a.size() == 5, "a.size");
//	static_assert(b.size() == 3, "b.size");
	static_assert(c.size() == 0, "c.size");

//	static_assert(!a.empty(), "a.empty");
//	static_assert(!b.empty(), "b.empty");
	static_assert( c.empty(), "c.empty");

//	static_assert(a.at(2) == 2, "a.at");
//	static_assert(b.at(2) == 3, "b.at");
	//static_assert(c.at(0)     , "c.at");

//	static_assert(a.front() == 0, "a.front");
//	static_assert(b.front() == 1, "b.front");
	//static_assert(c.front()     , "c.front");

//	static_assert(a.back() == 4, "a.back");
//	static_assert(b.back() == 3, "b.back");
	//static_assert(c.back()     , "c.back");
	
//	static_assert( a.slice(0, 2), "a.slice");
//	static_assert(!a.slice(2, 1), "a.slice");
//	static_assert( a.slice(-2, -1), "c.slice");
//	static_assert( b.slice(0, 2), "b.slice");
//	static_assert(!b.slice(2, 1), "b.slice");
//	static_assert( b.slice(-2, -1), "c.slice");
	static_assert(!c.slice( 0,  2), "c.slice");
	static_assert(!c.slice( 2,  1), "c.slice");
	static_assert(!c.slice(-2, -1), "c.slice");
}

#endif
