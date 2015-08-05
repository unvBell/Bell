#pragma once

namespace bell { namespace math {
	/**
	 * 円周率
	 * @return π
	 */
	template <typename T>
	inline constexpr T pi() noexcept {
		return static_cast<T>(3.1415926535897932384626433832795028841971693993L);
	}
}}

namespace bell {
	using math::pi;
}
