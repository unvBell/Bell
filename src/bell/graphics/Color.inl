#pragma once

#include "../Assert.hpp"
#include "../math/Constants.hpp"
#include "../math/Floor.hpp"

namespace bell { namespace graphics {
	//	RGBA
	inline constexpr Color Color::rgb(float r, float g, float b, float a) noexcept {
		return
			BELL_ASSERT(0 <= r && r <= 1.f),
			BELL_ASSERT(0 <= g && g <= 1.f),
			BELL_ASSERT(0 <= b && b <= 1.f),
			BELL_ASSERT(0 <= a && a <= 1.f),
			Color{ r, g, b, a };
	}


	//	HSVA
	inline /*constexpr*/ Color Color::hsv(float h, float s, float v, float a) noexcept {
		BELL_ASSERT(0 <= s && s <= 1.f);
		BELL_ASSERT(0 <= v && v <= 1.f);
		BELL_ASSERT(0 <= a && a <= 1.f);
		
		h /= 2*pi<float>() / 6;

		int   i = static_cast<int>(floor(h));
		float f = h - i;
		float p = v * (1 - s);
		float q = v * (1 - s*f);
		float r = v * (1 - s*(1-f));

		switch((i%6+6)%6) {
		case 0 : return { v, r, p, a };
		case 1 : return { q, v, p, a };
		case 2 : return { p, v, r, a };
		case 3 : return { p, q, v, a };
		case 4 : return { r, p, v, a };
		default: return { v, p, q, a };
		}
	}
}}
