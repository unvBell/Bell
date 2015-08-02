#pragma once

#include "../Alias.hpp"
#include "../util/ArrayRef.hpp"

namespace bell { namespace hash {
	using Crc32 = uint32_t;

	/**
	 * CRC-32
	 * @param  src ハッシュ元の値
	 * @param  crc CRC-32初期値 (default:0)
	 * @return     CRC-32
	 */
	Crc32 crc32(ArrayRef<byte> src, Crc32 crc = 0) noexcept;
}}
