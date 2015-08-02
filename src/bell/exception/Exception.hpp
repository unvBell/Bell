#pragma once

#include <boost/current_function.hpp>
#include "ErrorInfoRecorder.hpp"
#include "../preprocessor/Stringize.hpp"

/**
 * ファイル, 行数, 関数名のフォーマッティング
 * @param file ファイル名
 * @param line 行数
 * @param func 関数名
 */
#define BELL_EXCEPTION_FORMAT(file, line, func)\
	file " (" BELL_PP_STRINGIZE(line) ") " func


/**
 * 例外を投げるマクロ
 * @param ExceptType 投げる例外の型
 * @param ...        ExceptTypeの初期化パラメータ
 */
#define BELL_THROW(ExceptType, ...)														\
	do {																				\
		ExceptType e{ __VA_ARGS__ };													\
		e.addInfo(BELL_EXCEPTION_FORMAT(__FILE__, __LINE__, BOOST_CURRENT_FUNCTION));	\
		throw e;																		\
	} while(false)


/**
 * 例外の再送出
 * @param except 投げられた例外
 */
#define BELL_RETHROW(e)																	\
	do {																				\
		e.addInfo(BELL_EXCEPTION_FORMAT(__FILE__, __LINE__, BOOST_CURRENT_FUNCTION));	\
		throw;																			\
	} while(false)


namespace bell { namespace exception {
	/**
	 * 例外
	 */
	template <typename BaseExcept>
	class Exception : public BaseExcept, public ErrorInfoRecorder {
	public:
		/**
		 * コンストラクタ
		 * @param msg  エラーメッセージ
		 * @param args BaseExceptのコンストラクタに渡す値
		 */
		template <typename... Args>
		explicit Exception(boost::string_ref msg, Args&&... args)
			: BaseExcept(args...), ErrorInfoRecorder(msg) {}

		virtual ~Exception() =default;


		/**
		 * エラーメッセージの取得
		 * @return エラーメッセージ
		 */
		virtual const char* what() const override {
			return errorInfo();
		}
	};
}}
