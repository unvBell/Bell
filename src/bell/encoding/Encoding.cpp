#include <Windows.h>	//	TODO WinAPIに依存しない
#include "Encoding.hpp"

namespace {
	std::string wcsToMbcs(UINT codePage, boost::wstring_ref wcs) {
		//	変換後のサイズを取得
		int len = WideCharToMultiByte(codePage, 0, wcs.data(), wcs.size(), nullptr, 0, nullptr, nullptr);

		std::string buffer;
		buffer.resize(len);

		WideCharToMultiByte(codePage, 0, wcs.data(), wcs.size(), &buffer[0], len, nullptr, nullptr);
		return buffer;
	}

	std::wstring mbcsToWcs(UINT codePage, boost::string_ref mbcs) {
		//	変換後のサイズを取得
		int len = MultiByteToWideChar(codePage, 0, mbcs.data(), mbcs.size(), nullptr, 0);

		std::wstring buffer;
		buffer.resize(len);

		MultiByteToWideChar(codePage, 0, mbcs.data(), mbcs.size(), &buffer[0], len);
		return buffer;
	}
}

namespace bell { namespace encoding {
	//	UTF-8 => Shift-JIS
	std::string utf8ToSJis(boost::string_ref u8) {
		return wideToSJis(utf8ToWide(u8));
	}

	//	UTF-8 => WideChar
	std::wstring utf8ToWide(boost::string_ref u8) {
		return mbcsToWcs(CP_UTF8, u8);
	}

	//	WideChar => UTF-8
	std::string wideToSJis(boost::wstring_ref wide) {
		return wcsToMbcs(CP_ACP, wide);
	}

	//	WideChar => Shift-JIS
	std::string wideToUtf8(boost::wstring_ref wide) {
		return wcsToMbcs(CP_UTF8, wide);
	}

	//	Shift-JIS => UTF-8
	std::string sjisToUtf8(boost::string_ref sjis) {
		return wideToUtf8(sjisToWide(sjis));
	}

	//	Shift-JIS => WideChar
	std::wstring sjisToWide(boost::string_ref sjis) {
		return mbcsToWcs(CP_ACP, sjis);
	}
}}
