#ifdef _DEBUG

#include <gtest/gtest.h>
#include "Logger.hpp"

using namespace bell;

TEST(Bell_Logger, Initialize) {
	EXPECT_FALSE(logger::isInitialized()			);

	EXPECT_FALSE(logger::initialize("<>")			);	//	ファイル名には使えない文字
	EXPECT_FALSE(logger::isInitialized()			);
	
	EXPECT_TRUE (logger::initialize("test/Log.txt")	);
	EXPECT_TRUE (logger::isInitialized()			);
	
	EXPECT_FALSE(logger::initialize("test/Log2.txt"));	//	もう開いてる
	EXPECT_TRUE (logger::isInitialized()			);
}

TEST(Bell_Logger, Level) {
	EXPECT_EQ(logger::OutputLevel::debug, logger::outputLevel());

	logger::outputLevel(logger::OutputLevel::all);
	EXPECT_EQ(logger::OutputLevel::all, logger::outputLevel());
}

TEST(Bell_Logger, Write) {
	logger::outputLevel(logger::OutputLevel::debug);
	logger::writeDebugTrace	("trace"	);
	logger::writeDebug		("debug"	);
	logger::write			("info"		);
	logger::writeWarn		("warn"		);
	logger::writeError		("error"	);
	logger::writeFatalError	("fatal"	);
	
	logger::writeDebugTrace	(L"w_trace"	);
	logger::writeDebug		(L"w_debug"	);
	logger::write			(L"w_info"	);
	logger::writeWarn		(L"w_warn"	);
	logger::writeError		(L"w_error"	);
	logger::writeFatalError	(L"w_fatal"	);

	logger::outputLevel(logger::OutputLevel::warn);
	logger::writeDebugTrace	("trace"	);
	logger::writeDebug		("debug"	);
	logger::write			("info"		);
	logger::writeWarn		("warn"		);
	logger::writeError		("error"	);
	logger::writeFatalError	("fatal"	);
	
	logger::writeDebugTrace	(L"w_trace"	);
	logger::writeDebug		(L"w_debug"	);
	logger::write			(L"w_info"	);
	logger::writeWarn		(L"w_warn"	);
	logger::writeError		(L"w_error"	);
	logger::writeFatalError	(L"w_fatal"	);
}

#endif
