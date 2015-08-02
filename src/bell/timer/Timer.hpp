#pragma once

#include <chrono>

namespace bell { namespace timer {
	/**
	 * タイマー
	 */
	class Timer final {
		std::chrono::system_clock::time_point begin_;

	public:
		Timer() noexcept;

		/**
		 * 計測の開始
		 */
		void restart() noexcept;


		/**
		 * 経過時間の取得
		 * @return 計測開始からの経過時間[秒]
		 */
		double elapsed() const noexcept;
	};
}}

#include "Timer.inl"
