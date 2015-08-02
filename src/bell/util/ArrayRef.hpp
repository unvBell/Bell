#pragma once

#include <algorithm>
#include <array>
#include <vector>
#include <cstdint>

#include "../Assert.hpp"

namespace bell {
	/**
	 * 配列への参照を保持するクラス
	 */
	template <typename Type>
	class ArrayRef final {
	public:
		using ValueType			= Type;
		using SizeType			= uint64_t;
		using PosType			= int64_t;
		using Pointer			= const Type*;
		using Reference			= const Type&;
		using Iterator			= Pointer;
		using ReverseIterator	= std::reverse_iterator<Iterator>;

	private:
		Pointer		ptr_;
		SizeType	len_;


		constexpr ArrayRef slice_impl(SizeType begin, SizeType end) const noexcept {
			return (ptr_ && begin < len_ && begin < end)
				? ArrayRef{ ptr_+begin, std::min(end, len_)-begin }
				: ArrayRef{};
		}

	public:
		//	コンストラクタ
		constexpr ArrayRef() noexcept
			: ptr_(nullptr), len_(0) {}

		constexpr ArrayRef(Pointer ptr, SizeType size) noexcept
			: ptr_(ptr), len_(size) {}

		template <SizeType N>
		constexpr ArrayRef(const Type (&a)[N]) noexcept
			: ptr_(a), len_(N) {}

		template <SizeType N>
		ArrayRef(const std::array<Type, N>& a) noexcept
			: ptr_(a.data()), len_(N) {}

		template <typename Allocator>
		ArrayRef(const std::vector<Type, Allocator>& v) noexcept
			: ptr_(v.data()), len_(v.size()) {}

		ArrayRef(const ArrayRef&) =default;

		//	デストラクタ
		~ArrayRef() =default;

		//	演算子
		ArrayRef& operator=(const ArrayRef&) =default;

		constexpr explicit operator bool() const noexcept {
			return !empty();
		}

		bool operator==(const ArrayRef& a) const noexcept {
			return equals(a);
		}

		bool operator!=(const ArrayRef& a) const noexcept {
			return !equals(a);
		}

		constexpr Reference operator[](SizeType a) const noexcept {
			return BELL_ASSERT(ptr_ && a < len_), ptr_[a];
		}

		template <typename Ch, typename Traits>
		friend std::basic_ostream<Ch, Traits>& operator<<(std::basic_ostream<Ch, Traits>& os, const ArrayRef& a) {
			os << Ch{'['};
			for(int i=0; i<a.size(); i++) {
				if(i) os << Ch{','};
				os << a[i];
			}
			return os << Ch{']'};
		}

		//	イテレータ
		constexpr Iterator	begin	() const noexcept { return ptr_;						}
		constexpr Iterator	cbegin	() const noexcept { return begin();						}
		constexpr Iterator	end		() const noexcept { return ptr_+len_;					}
		constexpr Iterator	cend	() const noexcept { return end();						}
		ReverseIterator		rbegin	() const noexcept { return ReverseIterator{ end() };	}
		ReverseIterator		crbegin	() const noexcept { return rbegin();					}
		ReverseIterator		rend	() const noexcept { return ReverseIterator{ begin() };	}
		ReverseIterator		crend	() const noexcept { return rend();						}


		/**
		 * 要素数の取得
		 * @return 配列の要素数
		 */
		constexpr SizeType size() const noexcept {
			return len_;
		}


		/**
		 * 配列の先頭要素へのポインタ
		 * @return 先頭ポインタ
		 */
		constexpr Pointer data() const noexcept {
			return ptr_;
		}


		/**
		 * 配列が空か
		 * @return 要素数が0ならばtrueを返す
		 */
		constexpr bool empty() const noexcept {
			return len_ == 0;
		}


		/**
		 * 配列の等値比較
		 * @param  a 比較対象の配列
		 * @return   全要素が等しければtrueを返す
		 */
		bool equals(const ArrayRef& a) const noexcept {
			return std::equal(begin(), end(), a.begin(), a.end());
		}


		/**
		 * 参照のクリア
		 */
		void clear() noexcept {
			ptr_ = nullptr;
			len_ = 0;
		}


		/**
		 * 安全なアクセサ
		 * @param  pos               アクセスする要素
		 * @return                   要素
		 * @throws std::out_of_range 範囲外にアクセスした時
		 */
		constexpr Reference at(SizeType pos) const {
			return (ptr_ && pos < len_)
				? std::cref(ptr_[pos])	//	警告封じ
				: throw std::out_of_range{ "bell::util::ArrayRef<>::at OutOfRange" };
		}


		/**
		 * 先頭要素の取得
		 * @return 先頭要素への参照
		 */
		constexpr Reference front() const noexcept {
			return BELL_ASSERT(ptr_ && len_ > 0), ptr_[0];
		}


		/**
		 * 末尾要素の取得
		 * @return 末尾要素への参照
		 */
		constexpr Reference back() const noexcept {
			return BELL_ASSERT(ptr_ && len_ > 0), ptr_[len_-1];
		}


		/**
		 * 先頭から指定要素数取り除く
		 * @param n 取り除く要素数
		 */
		void removePrefix(SizeType n) noexcept {
			ptr_ += n;
			len_ = len_ > n ? len_-n : 0;
		}


		/**
		 * 末尾から指定要素数取り除く
		 * @param n 取り除く要素数
		 */
		void removeSuffix(SizeType n) noexcept {
			len_ = len_ > n ? len_-n : 0;
		}


		/**
		 * 先頭要素を取り除く
		 */
		void popFront() noexcept {
			removePrefix(1);
		}


		/**
		 * 末尾要素を取り除く
		 */
		void popBack() noexcept {
			removeSuffix(1);
		}


		/**
		 * 配列のスライス
		 * @param  begin スライス開始位置
		 * @param  end   スライス終了位置 (スライス後の配列にendは含まない)
		 * @return       スライスされた配列
		 *
		 * [0, 1, 2, 3, 4].slice( 1,  3) => [1, 2]
		 * [0, 1, 2, 3, 4].slice( 3,  3) => []
		 * [0, 1, 2, 3, 4].slice( 3,  8) => [3, 4]
		 * [0, 1, 2, 3, 4].slice(-3, -1) => [2, 3]
		 * [0, 1, 2, 3, 4].slice(-8,  2) => [0, 1]
		 */
		constexpr ArrayRef slice(PosType begin, PosType end) const noexcept {
			return slice_impl(
				begin < 0 ? (len_ > static_cast<SizeType>(-begin) ? len_+begin : 0) : begin,
				end   < 0 ? (len_ > static_cast<SizeType>(-end  ) ? len_+end   : 0) : end  );
		}


		/**
		 * vectorの生成
		 * @return 生成されたvector
		 */
		template <typename Allocator = std::allocator<Type>>
		std::vector<Type, Allocator> toVector() const {
			return { begin(), end() };
		}
	};
}
