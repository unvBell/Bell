#ifdef _DEBUG

#include <gtest/gtest.h>
#include "Color.hpp"

using bell::graphics::Color;

TEST(Bell_Graphics_Color, Ctor) {
	constexpr Color c;
	constexpr Color d = { 0.1f, 0.2f, 0.3f };
	constexpr Color e = { 0.1f, 0.2f, 0.3f, 0.4f };
	constexpr Color f = 0xff804020;

	static_assert(c.r == 0.0f		&& c.g == 0.0f		&& c.b == 0.0f		&& c.a == 1.0f, "");
	static_assert(d.r == 0.1f		&& d.g == 0.2f		&& d.b == 0.3f		&& d.a == 1.0f, "");
	static_assert(e.r == 0.1f		&& e.g == 0.2f		&& e.b == 0.3f		&& e.a == 0.4f, "");
	static_assert(f.r == 128/255.f	&& f.g == 64/255.f	&& f.b == 32/255.f	&& f.a == 1.0f, "");
}

//	TODO 色テスト

#endif
