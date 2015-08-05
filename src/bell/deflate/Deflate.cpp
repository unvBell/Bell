#include <zlib/zlib.h>
#include "Deflate.hpp"
#include "DeflateError.hpp"
#include "../util/Clamp.hpp"

#ifdef _DEBUG
# pragma comment(lib, "zlib/zlib_d.lib")
#else
# pragma comment(lib, "zlib/zlib.lib")
#endif

namespace bell { namespace deflate {
	//	圧縮
	std::vector<byte> compress(ArrayRef<byte> src, int level) {
		//	レベルを[1, 9]にクリップ
		level = clamp(level, 1, 9);

		//	データを格納するバッファの確保
		std::vector<byte> data;
		data.resize(compressBound(static_cast<uLong>(src.size())));

		//	初期化
		z_stream zs		= {};
		zs.next_in		= const_cast<byte*>(src.data());	//	データは書き換えられない
		zs.avail_in		= static_cast<uInt>(src.size());
		zs.next_out		= &data[0];
		zs.avail_out	= data.size();

		if(deflateInit2(&zs, level, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY))
			BELL_THROW(DeflateError, "Failed to initialize compress stream.");

		//	圧縮
		int res = ::deflate(&zs, Z_FINISH);

		data.resize(zs.total_out);

		//	片付け
		deflateEnd(&zs);
		if(res != Z_STREAM_END)
			BELL_THROW(DeflateError, "Failed to compress.");

		return data;
	}


	//	伸長
	std::vector<byte> uncompress(ArrayRef<byte> src, size_t uncompSize) {
		//	データを格納するバッファの確保
		std::vector<byte> data;
		data.resize(uncompSize);

		//	初期化
		z_stream zs		= {};
		zs.next_in		= const_cast<byte*>(src.data());	//	データは書き換えられない
		zs.avail_in		= static_cast<uInt>(src.size());
		zs.next_out		= &data[0];
		zs.avail_out	= data.size();

		if(inflateInit2(&zs, -MAX_WBITS))
			BELL_THROW(DeflateError, "Failed to initialize uncompress stream.");

		//	伸長
		int res = inflate(&zs, Z_FINISH);

		data.resize(zs.total_out);
		inflateEnd(&zs);
		
		if(res != Z_STREAM_END)
			BELL_THROW(DeflateError, "Failed to uncompress.");

		return data;
	}
}}
