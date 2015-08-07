#pragma once

#include <boost/utility/string_ref.hpp>

namespace bell {
	/**
	 * 文字列のフォーマッティング
	 * @param  fmt  書式指定文字列
	 * @param  args
	 * @return      フォーマッティングされた文字列
	 * @throws boost::io::format_error 書式等にエラーが有った場合
	 * @see    boost::format
	 *
	 * format("%1% %2$.4f", 42, 3.14)		=> "42 3.1400"
	 * format("%2% %1%", "hoge", "piyo")	=> "piyo hoge"
	 * format("%1% %1%", true)				=> "true true"
	 */
	template <typename... Args>
	std::string format(boost::string_ref fmt, Args&&... args);


	/**
	 * 文字列のフォーマッティング
	 * @param  fmt  書式指定文字列
	 * @param  args
	 * @return      フォーマッティングされた文字列
	 * @throws boost::io::format_error 書式等にエラーが有った場合
	 * @see    boost::wformat
	 *
	 * wformat(L"%1% %2$.4f", 42, 3.14)		=> L"42 3.1400"
	 * wformat(L"%2% %1%", L"hoge", L"piyo")=> L"piyo hoge"
	 * wformat(L"%1% %1%", true)			=> L"true true"
	 */
	template <typename... Args>
	std::wstring wformat(boost::wstring_ref fmt, Args&&... args);
}

#include "Format.inl"
