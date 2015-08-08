#pragma once

#include "../Format.hpp"
#include "../encoding/Encoding.hpp"

namespace bell { namespace detail {
	//	文字列のログ出力
	void outputLogText(logger::OutputLevel level, boost::string_ref text);
}}

namespace bell { namespace logger {
	template <typename... Args>
	void write(OutputLevel level, boost::string_ref fmt, Args&&... args) {
		detail::outputLogText(level, format(fmt, args...));
	}
	
	template <typename... Args>
	void write(OutputLevel level, boost::wstring_ref fmt, Args&&... args) {
		detail::outputLogText(level, encoding::wideToUtf8(wformat(fmt, args...)));
	}

	template <typename... Args>
	void write(boost::string_ref fmt, Args&&... args) {
		write(OutputLevel::info, fmt, args...);
	}

	template <typename... Args>
	void write(boost::wstring_ref fmt, Args&&... args) {
		write(OutputLevel::info, fmt, args...);
	}

	template <typename... Args>
	void writeDebugTrace(boost::string_ref fmt, Args&&... args) {
		write(OutputLevel::trace, fmt, args...);
	}

	template <typename... Args>
	void writeDebugTrace(boost::wstring_ref fmt, Args&&... args) {
		write(OutputLevel::trace, fmt, args...);
	}

	template <typename... Args>
	void writeDebug(boost::string_ref fmt, Args&&... args) {
		write(OutputLevel::debug, fmt, args...);
	}

	template <typename... Args>
	void writeDebug(boost::wstring_ref fmt, Args&&... args) {
		write(OutputLevel::debug, fmt, args...);
	}

	template <typename... Args>
	void writeWarn(boost::string_ref fmt, Args&&... args) {
		write(OutputLevel::warn, fmt, args...);
	}

	template <typename... Args>
	void writeWarn(boost::wstring_ref fmt, Args&&... args) {
		write(OutputLevel::warn, fmt, args...);
	}

	template <typename... Args>
	void writeError(boost::string_ref fmt, Args&&... args) {
		write(OutputLevel::error, fmt, args...);
	}

	template <typename... Args>
	void writeError(boost::wstring_ref fmt, Args&&... args) {
		write(OutputLevel::error, fmt, args...);
	}

	template <typename... Args>
	void writeFatalError(boost::string_ref fmt, Args&&... args) {
		write(OutputLevel::fatal, fmt, args...);
	}

	template <typename... Args>
	void writeFatalError(boost::wstring_ref fmt, Args&&... args) {
		write(OutputLevel::fatal, fmt, args...);
	}
}}
