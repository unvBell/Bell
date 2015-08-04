#ifdef _DEBUG

#include <gtest/gtest.h>
#include "Vector2.hpp"
#include "Constants.hpp"

using namespace std;
using namespace bell::math;

template <typename T>
class Bell_Math_Vector2 : public testing::Test {};
template <typename T>
class Bell_Math_Vector2_F : public testing::Test {};

using TypeParams = testing::Types<int, float, double, long double>;
using TypeFloats = testing::Types<float, double, long double>;

TYPED_TEST_CASE(Bell_Math_Vector2, TypeParams);
TYPED_TEST_CASE(Bell_Math_Vector2_F, TypeFloats);

TYPED_TEST(Bell_Math_Vector2, CtorCompileTime) {
	using T = TypeParam;
	using V = Vector2<T>;

	constexpr V a;
	constexpr V b = { T{10}, T{20} };
	constexpr V c = b;

	static_assert(a.x == T{ 0}, "");
	static_assert(a.y == T{ 0}, "");
	static_assert(b.x == T{10}, "");
	static_assert(b.y == T{20}, "");
	static_assert(c.x == T{10}, "");
	static_assert(c.y == T{20}, "");
}

//TEST(Bell_Math_Vector2, OpType) {
	static_assert(is_same<Vec2i, Vector2<int>   >::value, "");
	static_assert(is_same<Vec2f, Vector2<float> >::value, "");
	static_assert(is_same<Vec2d, Vector2<double>>::value, "");
	static_assert(is_same<Vec2 , Vector2<float> >::value, "");

	static_assert(is_same<decltype(Vec2i{} + Vec2i{}), Vec2i>::value, "");
	static_assert(is_same<decltype(Vec2i{} + Vec2f{}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2i{} + Vec2d{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2f{} + Vec2i{}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2f{} + Vec2f{}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2f{} + Vec2d{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} + Vec2i{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} + Vec2f{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} + Vec2d{}), Vec2d>::value, "");

	static_assert(is_same<decltype(Vec2i{} - Vec2i{}), Vec2i>::value, "");
	static_assert(is_same<decltype(Vec2i{} - Vec2f{}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2i{} - Vec2d{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2f{} - Vec2i{}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2f{} - Vec2f{}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2f{} - Vec2d{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} - Vec2i{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} - Vec2f{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} - Vec2d{}), Vec2d>::value, "");

	static_assert(is_same<decltype(Vec2i{} * int   {}), Vec2i>::value, "");
	static_assert(is_same<decltype(Vec2i{} * float {}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2i{} * double{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2f{} * int   {}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2f{} * float {}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2f{} * double{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} * int   {}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} * float {}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} * double{}), Vec2d>::value, "");

	static_assert(is_same<decltype(int   {} * Vec2i{}), Vec2i>::value, "");
	static_assert(is_same<decltype(int   {} * Vec2f{}), Vec2f>::value, "");
	static_assert(is_same<decltype(int   {} * Vec2d{}), Vec2d>::value, "");
	static_assert(is_same<decltype(float {} * Vec2i{}), Vec2f>::value, "");
	static_assert(is_same<decltype(float {} * Vec2f{}), Vec2f>::value, "");
	static_assert(is_same<decltype(float {} * Vec2d{}), Vec2d>::value, "");
	static_assert(is_same<decltype(double{} * Vec2i{}), Vec2d>::value, "");
	static_assert(is_same<decltype(double{} * Vec2f{}), Vec2d>::value, "");
	static_assert(is_same<decltype(double{} * Vec2d{}), Vec2d>::value, "");

	static_assert(is_same<decltype(Vec2i{} / int   {}), Vec2i>::value, "");
	static_assert(is_same<decltype(Vec2i{} / float {}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2i{} / double{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2f{} / int   {}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2f{} / float {}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2f{} / double{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} / int   {}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} / float {}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} / double{}), Vec2d>::value, "");
//}

//TEST(Bell_Math_Vector2, MethodType) {
	static_assert(is_same<decltype(Vec2i{}.dot(Vec2i{})), int   >::value, "");
	static_assert(is_same<decltype(Vec2i{}.dot(Vec2f{})), float >::value, "");
	static_assert(is_same<decltype(Vec2i{}.dot(Vec2d{})), double>::value, "");
	static_assert(is_same<decltype(Vec2f{}.dot(Vec2i{})), float >::value, "");
	static_assert(is_same<decltype(Vec2f{}.dot(Vec2f{})), float >::value, "");
	static_assert(is_same<decltype(Vec2f{}.dot(Vec2d{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.dot(Vec2i{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.dot(Vec2f{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.dot(Vec2d{})), double>::value, "");
	
	static_assert(is_same<decltype(Vec2i{}.cross(Vec2i{})), int   >::value, "");
	static_assert(is_same<decltype(Vec2i{}.cross(Vec2f{})), float >::value, "");
	static_assert(is_same<decltype(Vec2i{}.cross(Vec2d{})), double>::value, "");
	static_assert(is_same<decltype(Vec2f{}.cross(Vec2i{})), float >::value, "");
	static_assert(is_same<decltype(Vec2f{}.cross(Vec2f{})), float >::value, "");
	static_assert(is_same<decltype(Vec2f{}.cross(Vec2d{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.cross(Vec2i{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.cross(Vec2f{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.cross(Vec2d{})), double>::value, "");
	
	static_assert(is_same<decltype(Vec2i{}.distanceSq(Vec2i{})), int   >::value, "");
	static_assert(is_same<decltype(Vec2i{}.distanceSq(Vec2f{})), float >::value, "");
	static_assert(is_same<decltype(Vec2i{}.distanceSq(Vec2d{})), double>::value, "");
	static_assert(is_same<decltype(Vec2f{}.distanceSq(Vec2i{})), float >::value, "");
	static_assert(is_same<decltype(Vec2f{}.distanceSq(Vec2f{})), float >::value, "");
	static_assert(is_same<decltype(Vec2f{}.distanceSq(Vec2d{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.distanceSq(Vec2i{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.distanceSq(Vec2f{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.distanceSq(Vec2d{})), double>::value, "");
	
	static_assert(is_same<decltype(Vec2i{}.distance(Vec2i{})), int   >::value, "");
	static_assert(is_same<decltype(Vec2i{}.distance(Vec2f{})), float >::value, "");
	static_assert(is_same<decltype(Vec2i{}.distance(Vec2d{})), double>::value, "");
	static_assert(is_same<decltype(Vec2f{}.distance(Vec2i{})), float >::value, "");
	static_assert(is_same<decltype(Vec2f{}.distance(Vec2f{})), float >::value, "");
	static_assert(is_same<decltype(Vec2f{}.distance(Vec2d{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.distance(Vec2i{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.distance(Vec2f{})), double>::value, "");
	static_assert(is_same<decltype(Vec2d{}.distance(Vec2d{})), double>::value, "");
//}

TYPED_TEST(Bell_Math_Vector2, Op) {
	using T = TypeParam;
	using V = Vector2<T>;

	constexpr V a = { T{ 2}, T{ 5} };
	constexpr V b = { T{10}, T{20} };
	constexpr V c = { T{10}, T{20} };
	constexpr V d;

	//	op Vector2<U>
	Vec2i vi = a;
	Vec2f vf = a;
	Vec2d vd = a;

	//	op bool
	static_assert( a, "");
	static_assert( b, "");
	static_assert( c, "");
	static_assert(!d, "");

	//	op unary
	static_assert(+a == V(T{ 2},T{  5}), "");
	static_assert(-a == V(T{-2},T{ -5}), "");

	//	op binary
	static_assert(a+b == V(T{12},T{ 25}), "");
	static_assert(a-b == V(T{-8},T{-15}), "");
	static_assert(a*3 == V(T{ 6},T{ 15}), "");
	static_assert(5*a == V(T{10},T{ 25}), "");
	static_assert(b/5 == V(T{ 2},T{  4}), "");
	//static_assert(a/0, "");
	EXPECT_DEATH(a/0, ".*");

	//	op binary assign
	V e = { T{ 2}, T{ 5} };
	V f = { T{10}, T{20} };
	V g = { T{ 2}, T{ 5} };
	V h = { T{10}, T{20} };

	e += a;
	f -= a;
	g *= 3;
	h /= 2;

	EXPECT_EQ(V(T{ 4},T{10}), e);
	EXPECT_EQ(V(T{ 8},T{15}), f);
	EXPECT_EQ(V(T{ 6},T{15}), g);
	EXPECT_EQ(V(T{ 5},T{10}), h);

	//	op equal
	static_assert(  a == a , "");
	static_assert(!(a == b), "");
	static_assert(  b == c , "");

	static_assert(!(a != a), "");
	static_assert(  a != b , "");
	static_assert(!(b != c), "");
}

TYPED_TEST(Bell_Math_Vector2, StaticMethodCompileTime) {
	using T = TypeParam;
	using V = Vector2<T>;

	static_assert(V::zero () == V{T{0},T{0}}, "");
	static_assert(V::unitX() == V{T{1},T{0}}, "");
	static_assert(V::unitY() == V{T{0},T{1}}, "");
}

TYPED_TEST(Bell_Math_Vector2_F, StaticMethod) {
	using T = TypeParam;
	using V = Vector2<T>;

	T c = static_cast<T>(cos(0.3));
	T s = static_cast<T>(sin(0.3));

	EXPECT_EQ(V(c,s), V::unit(static_cast<T>(0.3)));
}

TYPED_TEST(Bell_Math_Vector2, ConstMethodCompileTime) {
	using T = TypeParam;
	using V = Vector2<T>;

	constexpr V a = { T{1}, 0};
	constexpr V b = { T{10}, T{13} };
	constexpr V c = { T{-5}, T{ 8} };

	static_assert( V::zero ().isZero(), "");
	static_assert(!V::unitX().isZero(), "");
	static_assert(!V::unitY().isZero(), "");

	static_assert(!V::zero ().equals(a), "");
	static_assert( V::unitX().equals(a), "");
	static_assert(!V::unitY().equals(a), "");

	static_assert(b.dot(c) == 54, "");
	static_assert(c.dot(b) == 54, "");

	static_assert(b.cross(c) ==  145, "");
	static_assert(c.cross(b) == -145, "");

	static_assert(b.lengthSq() == 269, "");
	static_assert(c.lengthSq() ==  89, "");

	static_assert(b.distanceSq(c) == 250, "");
	static_assert(c.distanceSq(b) == 250, "");
}

TYPED_TEST(Bell_Math_Vector2_F, ConstMethod) {
	using T = TypeParam;
	using V = Vector2<T>;

	constexpr V a = { T{ 4}, T{3} };
	constexpr V b = { T{12}, T{5} };

	EXPECT_EQ( 5, a.length());
	EXPECT_EQ(13, b.length());

	EXPECT_EQ(         0,   V::unitX() .angle());
	EXPECT_EQ( pi<T>()/2,   V::unitY() .angle());
	EXPECT_EQ(-pi<T>()  , (-V::unitX()).angle());
	EXPECT_EQ(-pi<T>()/2, (-V::unitY()).angle());

	EXPECT_EQ(sqrt(T{68}), a.distance(b));
	EXPECT_EQ(sqrt(T{68}), b.distance(a));

	EXPECT_EQ(V(static_cast<T>( 4./ 5), static_cast<T>(3./ 5)), a.normalized());
	EXPECT_EQ(V(static_cast<T>(12./13), static_cast<T>(5./13)), b.normalized());
	
	EXPECT_NEAR( V::unitX().x, V::unitX().rotated(        0).x, 1e-6);
	EXPECT_NEAR( V::unitX().y, V::unitX().rotated(        0).y, 1e-6);
	EXPECT_NEAR( V::unitY().x, V::unitX().rotated(pi<T>()/2).x, 1e-6);
	EXPECT_NEAR( V::unitY().y, V::unitX().rotated(pi<T>()/2).y, 1e-6);
	EXPECT_NEAR(-V::unitX().x, V::unitX().rotated(pi<T>()  ).x, 1e-6);
	EXPECT_NEAR(-V::unitX().y, V::unitX().rotated(pi<T>()  ).y, 1e-6);
}

TYPED_TEST(Bell_Math_Vector2, NonConstMethod) {
	using T = TypeParam;
	using V = Vector2<T>;

	V a;
	a.set(T{5}, T{6});

	EXPECT_EQ(V(T{5}, T{6}), a);
}

#endif
