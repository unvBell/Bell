#include <fstream>
#include <iomanip>
#include <shared_mutex>
#include "Logger.hpp"
#include "../timer/HiPerformanceTimer.hpp"

namespace {
	using bell::logger::OutputLevel;
	using bell::timer::HiPerformanceTimer;

	using Lock			= std::lock_guard<std::shared_timed_mutex>;
	using SharedLock	= std::shared_lock<std::shared_timed_mutex>;

#ifdef _DEBUG
	constexpr OutputLevel defaultLevel = OutputLevel::debug;
#else
	constexpr OutputLevel defaultLevel = OutputLevel::info;
#endif

	std::shared_timed_mutex	mutex;
	std::ofstream			file;
	OutputLevel				currentLevel	= defaultLevel;
	HiPerformanceTimer		timer;
}

namespace bell { namespace detail {
	//	出力
	void outputLogText(logger::OutputLevel level, boost::string_ref text) {
		Lock lock{ mutex };

		if(level < currentLevel || !file.is_open())
			return;

		//	時刻の表示
		file << format("%1$12.3f", ::timer.elapsed()*1000);

		switch(level) {
		case OutputLevel::trace: file << "[TRACE]"; break;
		case OutputLevel::debug: file << "[DEBUG]"; break;
		case OutputLevel::info : file << "[INFO ]"; break;
		case OutputLevel::warn : file << "[WARN ]"; break;
		case OutputLevel::error: file << "[ERROR]"; break;
		case OutputLevel::fatal: file << "[FATAL]"; break;
		}

		file << text << std::endl;
	}
}}

namespace bell { namespace logger {
	//	ログの生成
	bool initialize(boost::string_ref name) noexcept {
		Lock lock{ mutex };

		if(file.is_open())
			return false;

		//	開く
		file.open(name.to_string());
		if(!file)
			return false;

		file << "";	//	TODO

		//	計測開始
		::timer.restart();

		return true;
	}


	//	生成されてるか
	bool isInitialized() noexcept {
		SharedLock lock{ mutex };
		return file.is_open();
	}


	//	出力レベルの設定
	void outputLevel(OutputLevel level) noexcept {
		Lock lock{ mutex };
		currentLevel = level;
	}


	//	出力レベルの取得
	OutputLevel outputLevel() noexcept {
		SharedLock lock{ mutex };
		return currentLevel;
	}
}}
