#ifdef _DEBUG

#include <thread>
#include <gtest/gtest.h>
#include "Timer.hpp"
#include "HiPerformanceTimer.hpp"

using namespace bell::timer;

TEST(Bell_Timer, Timer) {
	Timer				t;
	HiPerformanceTimer	u;

	std::this_thread::sleep_for(std::chrono::milliseconds{ 10 });
	EXPECT_NEAR(0.01, t.elapsed(), 0.001);
	EXPECT_NEAR(0.01, u.elapsed(), 0.001);
}

#endif
