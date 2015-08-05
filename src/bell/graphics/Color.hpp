#pragma once

#include <cstdint>

namespace bell { namespace graphics {
	/**
	 * 色
	 */
	struct Color final {
		float r, g, b, a;

		//	コンストラクタ
		constexpr Color() noexcept
			: r(0), g(0), b(0), a(1.f) {}

		constexpr Color(float r, float g, float b, float a = 1.f) noexcept
			: r(r), g(g), b(b), a(a) {}

		constexpr Color(uint32_t argb) noexcept
			: r(((argb >> 16) & 0xff) / 255.f)
			, g(((argb >>  8) & 0xff) / 255.f)
			, b(((argb >>  0) & 0xff) / 255.f)
			, a(((argb >> 24) & 0xff) / 255.f) {}


		/**
		 * RGBA値から色の算出
		 * @param  r [0,1]
		 * @param  g [0,1]
		 * @param  b [0,1]
		 * @param  a [0,1] (default:1.f)
		 * @return   色
		 */
		constexpr static Color rgb(float r, float g, float b, float a = 1.f) noexcept;


		/**
		 * HSVA値から色の算出
		 * @param  h 色相[0,2π]
		 * @param  s 彩度[0,1]
		 * @param  v 明度[0,1]
		 * @param  a アルファ[0,1] (default:1.f)
		 * @return   色
		 */
		/*constexpr*/ static Color hsv(float h, float s, float v, float a = 1.f) noexcept;


		/**
		 * 2つの色の等値比較
		 * @param  c 比較対象の色
		 * @return   全ての要素が等しければtrue
		 */
		constexpr bool equals(const Color& c) const noexcept {
			return r == c.r && g == c.g && b == c.b && a == c.a;
		}


		//	演算子
		constexpr bool operator==(const Color& c) const noexcept {
			return equals(c);
		}

		constexpr bool operator!=(const Color& c) const noexcept {
			return !equals(c);
		}
	};
}}

#include "Color.inl"
