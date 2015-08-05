#pragma once

#include <algorithm>

namespace bell {
	/**
	 * 値を, minval ~ maxvalの間に制限する
	 * @param  val    制限する値
	 * @param  minval 制限の下限
	 * @param  maxval 制限の上限
	 * @param  [less] 比較関数オブジェクト
	 * @return        valがminvalより小さければminval maxvalより大きければmaxval そうでなければvalを返す
	 */
	template <typename Val, typename Less>
	constexpr Val clamp(const Val& val, const Val& minval, const Val& maxval, const Less& less) noexcept {
		return std::min(std::max(val, minval, less), maxval, less);
	}
	
	template <typename Val>
	constexpr Val clamp(const Val& val, const Val& minval, const Val& maxval) noexcept {
		return clamp(val, minval, maxval, std::less<Val>{});
	}
}
