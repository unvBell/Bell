#ifdef WIN32

#include <Windows.h>
#include "HiPerformanceTimer.hpp"

namespace {
	//	分解能
	double frequency() noexcept {
		LARGE_INTEGER f;
		QueryPerformanceFrequency(&f);
		return static_cast<double>(f.QuadPart);
	}


	//	現在時刻
	long long now() noexcept {
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		return t.QuadPart;
	}
}

namespace bell { namespace timer {
	//	ctor
	HiPerformanceTimer::HiPerformanceTimer() noexcept
		: begin_(now()), freq_(frequency()) {}


	//	計測開始
	void HiPerformanceTimer::restart() noexcept {
		begin_ = now();
	}


	//	経過時間
	double HiPerformanceTimer::elapsed() const noexcept {
		return (now() - begin_) / freq_;
	}
}}

#endif
