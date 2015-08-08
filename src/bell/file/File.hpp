#pragma once

#include <memory>
#include <boost/utility/string_ref.hpp>
#include "../Alias.hpp"
#include "../util/ArrayRef.hpp"

namespace bell { namespace file {
	/**
	 * ファイル
	 */
	class File final {
		struct Impl;
		std::shared_ptr<Impl> impl_;

		explicit File(std::shared_ptr<Impl> impl) noexcept;

	public:
		/**
		 * ファイルを開く
		 * @param  path          開くファイルのパス
		 * @throws FileException ファイルを開くのに失敗した時
		 */
		static File open(boost::string_ref path);


		/**
		 * メモリー上の配列をファイルとして扱う
		 * @param name ファイル名
		 * @param data ファイルとして扱うデータ
		 */
		static File openFromMemory(boost::string_ref name, ArrayRef<byte> data);


		/**
		 * ファイル名の取得
		 * @return name
		 */
		boost::string_ref name() const noexcept;


		/**
		 * ファイルデータの取得
		 * @return ファイル内容のバイト列
		 */
		ArrayRef<byte> data() const noexcept;
	};
}}

namespace bell {
	using file::File;
}
