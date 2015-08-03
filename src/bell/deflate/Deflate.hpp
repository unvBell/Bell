#pragma once

#include "../Alias.hpp"
#include "../util/ArrayRef.hpp"

namespace bell { namespace deflate {
	constexpr int defaultCompressionLevel = 5;

	/**
	 * 圧縮
	 * @param  src          圧縮元のバイト列
	 * @param  level        圧縮レベル[1,9] (default:defaultCompressionLevel)
	 * @return              圧縮されたバイト列
	 * @throws DeflateError 圧縮に失敗した時
	 */
	std::vector<byte> compress(ArrayRef<byte> src, int level = defaultCompressionLevel);
	

	/**
	 * 伸長
	 * @param  src          圧縮されたバイト列
	 * @param  uncompSize   伸長後の大きさ
	 * @return              伸長されたバイト列
	 * @throws DeflateError 伸長に失敗した時
	 */
	std::vector<byte> uncompress(ArrayRef<byte> src, size_t uncompSize);
}}
