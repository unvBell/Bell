#pragma once

#include "../Exception.hpp"

namespace bell { namespace file {
	/**
	 * ファイル入出力に関する例外
	 */
	class FileException : public Exception<std::runtime_error> {
	public:
		/**
		 * コンストラクタ
		 * @param name ファイル名
		 * @param msg  エラーメッセージ
		 */
		explicit FileException(boost::string_ref name, boost::string_ref msg)
			: Exception(name.to_string() + '\n' + msg.to_string(), nullptr) {}

		virtual ~FileException() {}
	};
}}
