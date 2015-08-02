#pragma once

#ifndef BELL_ENABLE_ASSERTION_HANDLER
# include <iostream>
# include "../preprocessor/Stringize.hpp"
#endif


/**
 * アサーション文字列のフォーマッティング
 * @param expr 式文字列
 * @param msg  エラーメッセージ
 * @param file ファイル名
 * @param line 行数
 * @param func 関数名
 */
#define BELL_ASSERTION_FORMAT(expr, msg, file, line, func)	\
	"Assertion Failed! " msg "\n"							\
	"assert (" #expr ")\n"									\
	"assert at " file " (" BELL_PP_STRINGIZE(line) ") " func


namespace bell { namespace assertion {
	/**
	 * アサーション情報
	 */
	struct AssertionInfo {
		const char*	expr;
		const char*	msg;
		const char*	file;
		const long	line;
		const char*	function;
	};


	/**
	 * アサーションの失敗
	 * @param info アサーション情報
	 */
	void assertionFailed(AssertionInfo info);

#ifndef BELL_ENABLE_ASSERTION_HANDLER
	//	デフォルトアサートハンドラ
	inline void assertionFailed(AssertionInfo info) {
		std::cerr << info.msg << std::endl;
		std::abort();
	}
#endif
}}


namespace bell { namespace detail {
	/**
	 * 条件のチェック
	 * @param cond 条件
	 * @param msg  エラーメッセージ
	 * @param expr 式文字列
	 * @param file ファイル名
	 * @param line 行数
	 * @param func 関数名
	 */
	constexpr inline bool assertionCheck(bool cond, const char* msg, const char* expr, const char* file, long line, const char* func) {
		return cond ? true : (assertion::assertionFailed({ expr, msg, file, line, func }), false);
	}
}}
