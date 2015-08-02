#pragma once

#include <vector>
#include <boost/utility/string_ref.hpp>
#include "../util/ArrayRef.hpp"

namespace bell { namespace exception {
	/**
	 * トレース情報
	 */
	struct TraceInfo final {
		const char*	file;
		const long	line;
		const char*	function;
	};


	/**
	 * スタックトレースレコーダ
	 */
	class TraceRecorder {
		std::vector<TraceInfo> trace_;

	public:
		explicit TraceRecorder() {}
		virtual ~TraceRecorder() =default;


		/**
		 * スタックトレースの記録
		 * @param file 例外が投げられたファイル名
		 * @param line 例外が投げられた行番号
		 * @param func 例外が投げられた関数名
		 */
		virtual void recordTrace(const char* file, long line, const char* func) {
			trace_.emplace_back(TraceInfo{ file, line, func });
		}


		/**
		 * スタックトレースの取得
		 * @return スタックトレース
		 */
		ArrayRef<TraceInfo> stackTrace() const noexcept {
			return trace_;
		}
	};
}}
