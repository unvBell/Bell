#pragma once

namespace bell { namespace timer {
	//	ctor
	Timer::Timer() noexcept
		: begin_(std::chrono::system_clock::now()) {}


	//	計測開始
	void Timer::restart() noexcept {
		begin_ = std::chrono::system_clock::now();
	}


	//	経過時間
	double Timer::elapsed() const noexcept {
		using namespace std::chrono;

		auto now = system_clock::now();
		auto dur = now - begin_;

		return duration_cast<microseconds>(dur).count() * 1e-6;
	}
}}
