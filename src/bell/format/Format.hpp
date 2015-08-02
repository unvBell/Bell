#pragma once

#include <boost/utility/string_ref.hpp>

namespace bell {
	/**
	 * ������̃t�H�[�}�b�e�B���O
	 * @param  fmt  �����w�蕶����
	 * @param  args
	 * @return      �t�H�[�}�b�e�B���O���ꂽ������
	 * @throws boost::io::format_error �������ɃG���[���L�����ꍇ
	 * @see    boost::format
	 *
	 * format("%1% %2$.4f", 42, 3.14)		=> "42 3.1400"
	 * format("%2% %1%", "hoge", "piyo")	=> "piyo hoge"
	 * format("%1% %1%", true)				=> "true true"
	 */
	template <typename... Args>
	std::string format(boost::string_ref _format, Args&&... args);


	/**
	 * ������̃t�H�[�}�b�e�B���O
	 * @param  fmt  �����w�蕶����
	 * @param  args
	 * @return      �t�H�[�}�b�e�B���O���ꂽ������
	 * @throws boost::io::format_error �������ɃG���[���L�����ꍇ
	 * @see    boost::wformat
	 *
	 * wformat(L"%1% %2$.4f", 42, 3.14)		=> L"42 3.1400"
	 * wformat(L"%2% %1%", L"hoge", L"piyo")=> L"piyo hoge"
	 * wformat(L"%1% %1%", true)			=> L"true true"
	 */
	template <typename... Args>
	std::wstring wformat(boost::wstring_ref format, Args&&... args);
}

#include "Format.inl"
