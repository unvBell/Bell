#pragma once

#include <boost/utility/string_ref.hpp>

namespace bell { namespace encoding {
	/**
	 * UTF-8 => Shift-JIS
	 * @param  u8 UTF-8
	 * @return    SJis
	 */
	std::string utf8ToSJis(boost::string_ref u8);


	/**
	 * UTF-8 => WideChar
	 * @param  u8 UTF-8
	 * @return    WideChar
	 */
	std::wstring utf8ToWide(boost::string_ref u8);


	/**
	 * WideChar => UTF-8
	 * @param  wcs WideChar
	 * @return     UTF-8
	 */
	std::string wideToUtf8(boost::wstring_ref wcs);


	/**
	 * WideChar => Shift-JIS
	 * @param  wcs WideChar
	 * @return     SJis
	 */
	std::string wideToSJis(boost::wstring_ref wcs);


	/**
	 * Shift-JIS => UTF-8
	 * @param  sjis SJis
	 * @return      UTF-8
	 */
	std::string sjisToUtf8(boost::string_ref u8);


	/**
	 * Shift-JIS => WideChar
	 * @param  sjis SJis
	 * @return      WideChar
	 */
	std::wstring sjisToWide(boost::string_ref u8);
}}
