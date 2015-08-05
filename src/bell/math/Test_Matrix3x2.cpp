#ifdef _DEBUG

#include <gtest/gtest.h>
#include "Matrix3x2.hpp"

using namespace std;
using namespace bell::math;

namespace {
	template <typename Ch, typename Traits, typename T>
	std::basic_ostream<Ch, Traits>& operator<<(std::basic_ostream<Ch, Traits>& os, const boost::optional<Matrix3x2<T>>& m) {
		return m ? (os << m.get()) : (os << Ch{'('} << Ch{'n'} << Ch{'o'} << Ch{'n'} << Ch{'e'} << Ch{')'});
	}
}

template <typename T>
class Bell_Math_Matrix3x2 : public testing::Test {};
template <typename T>
class Bell_Math_Matrix3x2_F : public testing::Test {};

using TypeParams = testing::Types<int, float, double, long double>;
using TypeFloats = testing::Types<float, double, long double>;

TYPED_TEST_CASE(Bell_Math_Matrix3x2, TypeParams);
TYPED_TEST_CASE(Bell_Math_Matrix3x2_F, TypeFloats);

TYPED_TEST(Bell_Math_Matrix3x2, Ctor) {
	using T = TypeParam;
	using M = Matrix3x2<T>;

	constexpr M a;
	constexpr M b = { 11, 12, 21, 22, 31, 32 };
	constexpr M c = b;

	static_assert(a._11 == 0, "");
	static_assert(a._12 == 0, "");
	static_assert(a._21 == 0, "");
	static_assert(a._22 == 0, "");
	static_assert(a._31 == 0, "");
	static_assert(a._32 == 0, "");

	static_assert(b._11 == 11, "");
	static_assert(b._12 == 12, "");
	static_assert(b._21 == 21, "");
	static_assert(b._22 == 22, "");
	static_assert(b._31 == 31, "");
	static_assert(b._32 == 32, "");

	static_assert(c._11 == 11, "");
	static_assert(c._12 == 12, "");
	static_assert(c._21 == 21, "");
	static_assert(c._22 == 22, "");
	static_assert(c._31 == 31, "");
	static_assert(c._32 == 32, "");
}

//TEST(Bell_Math_Matrix3x2, OpType) {
	static_assert(is_same<Mat3x2i, Matrix3x2<int>   >::value, "");
	static_assert(is_same<Mat3x2f, Matrix3x2<float> >::value, "");
	static_assert(is_same<Mat3x2d, Matrix3x2<double>>::value, "");
	static_assert(is_same<Mat3x2 , Matrix3x2<float> >::value, "");

	static_assert(is_same<decltype(Mat3x2i{} + Mat3x2i{}), Mat3x2i>::value, "");
	static_assert(is_same<decltype(Mat3x2i{} + Mat3x2f{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2i{} + Mat3x2d{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} + Mat3x2i{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} + Mat3x2f{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} + Mat3x2d{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} + Mat3x2i{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} + Mat3x2f{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} + Mat3x2d{}), Mat3x2d>::value, "");

	static_assert(is_same<decltype(Mat3x2i{} - Mat3x2i{}), Mat3x2i>::value, "");
	static_assert(is_same<decltype(Mat3x2i{} - Mat3x2f{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2i{} - Mat3x2d{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} - Mat3x2i{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} - Mat3x2f{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} - Mat3x2d{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} - Mat3x2i{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} - Mat3x2f{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} - Mat3x2d{}), Mat3x2d>::value, "");

	static_assert(is_same<decltype(Mat3x2i{} * int   {}), Mat3x2i>::value, "");
	static_assert(is_same<decltype(Mat3x2i{} * float {}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2i{} * double{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} * int   {}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} * float {}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} * double{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} * int   {}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} * float {}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} * double{}), Mat3x2d>::value, "");

	static_assert(is_same<decltype(int   {} * Mat3x2i{}), Mat3x2i>::value, "");
	static_assert(is_same<decltype(int   {} * Mat3x2f{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(int   {} * Mat3x2d{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(float {} * Mat3x2i{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(float {} * Mat3x2f{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(float {} * Mat3x2d{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(double{} * Mat3x2i{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(double{} * Mat3x2f{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(double{} * Mat3x2d{}), Mat3x2d>::value, "");

	static_assert(is_same<decltype(Mat3x2i{} / int   {}), Mat3x2i>::value, "");
	static_assert(is_same<decltype(Mat3x2i{} / float {}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2i{} / double{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} / int   {}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} / float {}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} / double{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} / int   {}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} / float {}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} / double{}), Mat3x2d>::value, "");

	static_assert(is_same<decltype(Mat3x2i{} * Mat3x2i{}), Mat3x2i>::value, "");
	static_assert(is_same<decltype(Mat3x2i{} * Mat3x2f{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2i{} * Mat3x2d{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} * Mat3x2i{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} * Mat3x2f{}), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{} * Mat3x2d{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} * Mat3x2i{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} * Mat3x2f{}), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{} * Mat3x2d{}), Mat3x2d>::value, "");

	static_assert(is_same<decltype(Vec2i{} * Mat3x2i{}), Vec2i>::value, "");
	static_assert(is_same<decltype(Vec2i{} * Mat3x2f{}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2i{} * Mat3x2d{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2f{} * Mat3x2i{}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2f{} * Mat3x2f{}), Vec2f>::value, "");
	static_assert(is_same<decltype(Vec2f{} * Mat3x2d{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} * Mat3x2i{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} * Mat3x2f{}), Vec2d>::value, "");
	static_assert(is_same<decltype(Vec2d{} * Mat3x2d{}), Vec2d>::value, "");
//}

//TEST(Bell_Math_Matrix3x2, MethodType) {
	static_assert(is_same<decltype(Mat3x2i{}.multiply(Mat3x2i{})), Mat3x2i>::value, "");
	static_assert(is_same<decltype(Mat3x2i{}.multiply(Mat3x2f{})), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2i{}.multiply(Mat3x2d{})), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2f{}.multiply(Mat3x2i{})), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{}.multiply(Mat3x2f{})), Mat3x2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{}.multiply(Mat3x2d{})), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{}.multiply(Mat3x2i{})), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{}.multiply(Mat3x2f{})), Mat3x2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{}.multiply(Mat3x2d{})), Mat3x2d>::value, "");

	static_assert(is_same<decltype(Mat3x2i{}.transform(Vec2i{})), Vec2i>::value, "");
	static_assert(is_same<decltype(Mat3x2i{}.transform(Vec2f{})), Vec2f>::value, "");
	static_assert(is_same<decltype(Mat3x2i{}.transform(Vec2d{})), Vec2d>::value, "");
	static_assert(is_same<decltype(Mat3x2f{}.transform(Vec2i{})), Vec2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{}.transform(Vec2f{})), Vec2f>::value, "");
	static_assert(is_same<decltype(Mat3x2f{}.transform(Vec2d{})), Vec2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{}.transform(Vec2i{})), Vec2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{}.transform(Vec2f{})), Vec2d>::value, "");
	static_assert(is_same<decltype(Mat3x2d{}.transform(Vec2d{})), Vec2d>::value, "");
//}

TYPED_TEST(Bell_Math_Matrix3x2, Op) {
	using T = TypeParam;
	using M = Matrix3x2<T>;
	using V = Vector2<T>;

	//	op bool
	static_assert(!M::zero()    , "");
	static_assert( M::identity(), "");

	//	op unary
	static_assert(+M(1, 2, 3, 4, 5, 6) == M( 1, 2, 3, 4, 5, 6), "");
	static_assert(-M(1, 2, 3, 4, 5, 6) == M(-1,-2,-3,-4,-5,-6), "");

	//	op binary
	static_assert(M(10,20,30,40,50,60)+M(1,2,3,4,5,6) == M(11,22,33,44,55,66), "");
	static_assert(M(10,20,30,40,50,60)-M(1,2,3,4,5,6) == M( 9,18,27,36,45,54), "");
	static_assert(M( 1, 2, 3, 4, 5, 6)*3              == M( 3, 6, 9,12,15,18), "");
	static_assert(M( 5,10,15,20,25,30)/5              == M( 1, 2, 3, 4, 5, 6), "");
	static_assert(M( 3, 2, 1, 6, 5, 4)*M(1,2,3,4,5,6) == M( 9,14,19,26,22,32), "");
	static_assert(V(1, 3)             *M(2,3,4,6,5,1) == V(19,22)            , "");
	//static_assert(M( 5,10,15,20,25,30)/0              == M( 1, 2, 3, 4, 5, 6), "");
	EXPECT_DEATH(M{}/0, ".*");

	//	op binary assign
	M a = {1,2,3,4,5,6};
	M b = {9,8,7,6,5,4};
	M c = {1,1,1,2,3,4};
	M d = {2,4,6,8,2,4};
	M e = {1,2,3,4,5,6};
	V v = {5,2};

	a += M{6,5,4,3,2,1};
	b -= M{6,5,4,3,2,1};
	c *= 2;
	d /= 2;
	e *= M{1,1,2,2,3,3};
	v *= M{2,1,4,3,6,5};

	EXPECT_EQ(M(7,7,7,7,7,7), a);
	EXPECT_EQ(M(3,3,3,3,3,3), b);
	EXPECT_EQ(M(2,2,2,4,6,8), c);
	EXPECT_EQ(M(1,2,3,4,1,2), d);
	EXPECT_EQ(M(1,2,3,4,5,6)*M(1,1,2,2,3,3), e);
	EXPECT_EQ(V(24, 16)     , v);

	//	op equal
	static_assert(!(M(1,0,0,0,0,0) == M(0,0,0,0,0,0)), "");
	static_assert(  M(1,0,0,0,0,0) == M(1,0,0,0,0,0) , "");
	static_assert(  M(1,0,0,0,0,0) != M(0,0,0,0,0,0) , "");
	static_assert(!(M(1,0,0,0,0,0) != M(1,0,0,0,0,0)), "");
}

TYPED_TEST(Bell_Math_Matrix3x2, StaticMethodCompileTime) {
	using T = TypeParam;
	using M = Matrix3x2<T>;

	static_assert(M::zero       ()      == M{0,0,0,0,0,0}, "");
	static_assert(M::identity   ()      == M{1,0,0,1,0,0}, "");
	static_assert(M::translation({3,4}) == M{1,0,0,1,3,4}, "");
	static_assert(M::scaling    ({3,4}) == M{3,0,0,4,0,0}, "");

	static_assert(M::scaling({3,4},{5,6}) == M::translation({-5,-6})*M::scaling({3,4})*M::translation({5,6}), "");
}

TYPED_TEST(Bell_Math_Matrix3x2_F, StaticMethod) {
	using T = TypeParam;
	using M = Matrix3x2<T>;

	T rot  = static_cast<T>(0.3);
	T angX = static_cast<T>(0.3);
	T angY = static_cast<T>(1.2);

	T c = cos(rot);
	T s = sin(rot);
	T t = tan(angX);
	T u = tan(angY);

	EXPECT_EQ(M(c,s,-s,c,0,0), M::rotation(rot));
	EXPECT_EQ(M(1,u, t,1,0,0), M::skew(angX, angY));

	EXPECT_EQ(M::translation({-5,-6})*M::rotation(rot)  *M::translation({5,6}), M::rotation(rot, {5,6}));
	EXPECT_EQ(M::translation({-5,-6})*M::skew(angX,angY)*M::translation({5,6}), M::skew(angX,angY, {5,6}));
}

TYPED_TEST(Bell_Math_Matrix3x2, Method) {
	using T = TypeParam;
	using M = Matrix3x2<T>;
	using V = Vector2<T>;

	//	set
	M a;
	a.set(11,12,21,22,31,32);
	EXPECT_EQ(M(11,12,21,22,31,32), a);

	static_assert( M::zero    ().isZero(), "");
	static_assert(!M::identity().isZero(), "");

	static_assert(!M::zero    ().isIdentity(), "");
	static_assert( M::identity().isIdentity(), "");

	static_assert(!M::zero    ().isInvertible(), "");
	static_assert( M::identity().isInvertible(), "");

	static_assert( M{1,2,3,4,5,6}.equals({1,2,3,4,5,6}), "");
	static_assert(!M{1,2,3,4,5,6}.equals({0,2,3,4,5,6}), "");

	static_assert(M{1,2,3,4,5,6}.determinant() == -2, "");
	static_assert(M{1,2,3,4,0,0}.determinant() == -2, "");
	static_assert(M{5,3,1,7,0,0}.determinant() == 32, "");

	EXPECT_EQ(boost::none  , M::zero().invert());
	EXPECT_EQ(M::identity(), M::identity().invert());
	EXPECT_EQ(M::identity(), M::identity().invert().get());

	static_assert(M{3,2,1,6,5,4}.multiply(M{1,2,3,4,5,6}) == M{9,14,19,26,22,32}, "");
	static_assert(M{2,3,4,6,5,1}.transform(V{1, 3})       == V{19,22}           , "");
}

#endif
