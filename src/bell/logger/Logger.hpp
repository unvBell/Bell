#pragma once

#include <limits>
#include <boost/utility/string_ref.hpp>

namespace bell { namespace logger {
	/**
	 * ログ出力レベル
	 */
	enum class OutputLevel {
		trace,
		debug,
		info,
		warn,
		error,
		fatal,

		off = std::numeric_limits<int>::max(),
		all = std::numeric_limits<int>::min(),
	};


	/**
	 * ログファイルの生成
	 * @param  name 生成するファイル名
	 * @return      既に生成されているか, 生成に失敗した時はfalse
	 */
	bool initialize(boost::string_ref name) noexcept;


	/**
	 * ログファイルが既に生成されているか
	 * @return 既に生成されていた場合true
	 */
	bool isInitialized() noexcept;


	/**
	 * ログ出力
	 * @param level 出力レベル
	 * @param fmt   出力する文字列フォーマット
	 * @param args  パラメータ
	 *
	 * levelが現在の出力レベルより低い場合は出力されない
	 */
	template <typename... Args>
	void write(OutputLevel level, boost::string_ref str, Args&&... args);
	template <typename... Args>
	void write(OutputLevel level, boost::wstring_ref str, Args&&... args);


	/**
	 * ログ出力
	 * @param fmt  出力する文字列フォーマット
	 * @param args パラメータ
	 *
	 * 出力レベル info
	 */
	template <typename... Args>
	void write(boost::string_ref str, Args&&... args);
	template <typename... Args>
	void write(boost::wstring_ref str, Args&&... args);


	/**
	 * ログデバッグトレース出力
	 * @param fmt  出力する文字列フォーマット
	 * @param args パラメータ
	 *
	 * 出力レベル trace
	 */
	template <typename... Args>
	void writeDebugTrace(boost::string_ref str, Args&&... args);
	template <typename... Args>
	void writeDebugTrace(boost::wstring_ref str, Args&&... args);


	/**
	 * ログデバッグ出力
	 * @param fmt  出力する文字列フォーマット
	 * @param args パラメータ
	 *
	 * 出力レベル debug
	 */
	template <typename... Args>
	void writeDebug(boost::string_ref str, Args&&... args);
	template <typename... Args>
	void writeDebug(boost::wstring_ref str, Args&&... args);


	/**
	 * ログ警告出力
	 * @param fmt  出力する文字列フォーマット
	 * @param args パラメータ
	 *
	 * 出力レベル warn
	 */
	template <typename... Args>
	void writeWarn(boost::string_ref str, Args&&... args);
	template <typename... Args>
	void writeWarn(boost::wstring_ref str, Args&&... args);


	/**
	 * ログエラー出力
	 * @param fmt  出力する文字列フォーマット
	 * @param args パラメータ
	 *
	 * 出力レベル error
	 */
	template <typename... Args>
	void writeError(boost::string_ref str, Args&&... args);
	template <typename... Args>
	void writeError(boost::wstring_ref str, Args&&... args);


	/**
	 * ログ致命的エラー出力
	 * @param fmt  出力する文字列フォーマット
	 * @param args パラメータ
	 *
	 * 出力レベル fatal
	 */
	template <typename... Args>
	void writeFatalError(boost::string_ref str, Args&&... args);
	template <typename... Args>
	void writeFatalError(boost::wstring_ref str, Args&&... args);


	/**
	 * ログ出力レベルの設定
	 * @param level 設定するレベル
	 *
	 * levelより低いレベルのログは出力されなくなる
	 */
	void outputLevel(OutputLevel level) noexcept;


	/**
	 * 現在の出力レベルの取得
	 * @return 現在の出力レベル
	 */
	OutputLevel outputLevel() noexcept;
}}

#include "Logger.inl"
