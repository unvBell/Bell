#pragma once

#ifdef WIN32

namespace bell { namespace timer {
	/**
	 * タイマー
	 */
	class HiPerformanceTimer final {
		long long	begin_;
		double		freq_;

	public:
		HiPerformanceTimer() noexcept;

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

#else

#include "Timer.hpp"

namespace bell { namespace timer {
	using HiPerformanceTimer = Timer;
}}

#endif
