#pragma once

#include <vector>
#include <boost/utility/string_ref.hpp>
#include "../util/ArrayRef.hpp"

namespace bell { namespace exception {
	/**
	 * エラー情報を記録するクラス
	 */
	class ErrorInfoRecorder {
		std::string info_;

	public:
		explicit ErrorInfoRecorder() noexcept {}

		explicit ErrorInfoRecorder(boost::string_ref msg)
			: info_(msg.to_string() + '\n') {}

		virtual ~ErrorInfoRecorder() =default;


		/**
		 * エラー情報の追加
		 * @param info 追加する情報
		 */
		virtual void addInfo(boost::string_ref info) {
			info_ += info.to_string() + '\n';
		}


		/**
		 * エラー情報の取得
		 * @return エラー情報
		 */
		const char* errorInfo() const noexcept {
			return info_.c_str();
		}
	};
}}
