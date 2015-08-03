#pragma once

#include "../Exception.hpp"

namespace bell { namespace deflate {
	/**
	 * Deflate圧縮, 伸長に関する例外
	 */
	class DeflateError : public Exception<std::runtime_error> {
	public:
		/**
		 * コンストラクタ
		 * @param msg エラーメッセージ
		 */
		explicit DeflateError(boost::string_ref msg)
			: Exception(msg, nullptr) {}

		virtual ~DeflateError() =default;
	};
}}
