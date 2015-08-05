#pragma once

#include <type_traits>

namespace bell { namespace math {
	/**
	 * 床関数
	 * @param  x
	 * @return   [x]
	 */
	template <typename Float>
	constexpr Float floor(Float x) noexcept {
		static_assert(
			std::is_floating_point<Float>::value,
			"bell::math::floor<Float> Float must be floating point.");

		return
			static_cast<long>(x) == x
				? x
				: x < 0
					? static_cast<long>(x)-1
					: static_cast<long>(x);
	}
}}

namespace bell {
	using bell::math::floor;
}
