#pragma once

#include <ostream>
#include <cmath>
#include "../Assert.hpp"

namespace bell { namespace math {
	/**
	 * 2次元ベクトル
	 */
	template <typename T>
	struct Vector2 final {
		using ValueType = T;

		T x;
		T y;

		//	コンストラクタ
		constexpr Vector2() noexcept
			: x(0), y(0) {}

		constexpr Vector2(T x, T y) noexcept
			: x(x), y(y) {}

		//	演算子
		constexpr explicit operator bool() const noexcept {
			return !isZero();
		}

		template <typename U>
		constexpr operator Vector2<U>() const noexcept {
			return { static_cast<U>(x), static_cast<U>(y) };
		}

		constexpr Vector2 operator+() const noexcept {
			return { +x, +y };
		}

		constexpr Vector2 operator-() const noexcept {
			return { -x, -y };
		}

		template <typename U>
		constexpr Vector2<decltype(T{}+U{})> operator+(const Vector2<U>& v) const noexcept {
			return { x+v.x, y+v.y };
		}

		template <typename U>
		constexpr Vector2<decltype(T{}-U{})> operator-(const Vector2<U>& v) const noexcept {
			return { x-v.x, y-v.y };
		}
		
		template <typename U>
		constexpr Vector2<decltype(T{}*U{})> operator*(U a) const noexcept {
			return { x*a, y*a };
		}

		template <typename U>
		friend constexpr Vector2<decltype(U{}*T{})> operator*(U a, const Vector2& v) noexcept {
			return { a*v.x, a*v.y };
		}
		
		template <typename U>
		constexpr Vector2<decltype(T{}/U{})> operator/(U a) const noexcept {
			return BELL_ASSERT(a != 0), Vector2<decltype(T{}/U{})>{ x/a, y/a };
		}

		Vector2& operator+=(const Vector2& v) noexcept {
			return *this = *this+v;
		}

		Vector2& operator-=(const Vector2& v) noexcept {
			return *this = *this-v;
		}

		Vector2& operator*=(T a) noexcept {
			return *this = *this*a;
		}

		Vector2& operator/=(T a) noexcept {
			return *this = *this/a;
		}

		constexpr bool operator==(const Vector2& v) const noexcept {
			return equals(v);
		}

		constexpr bool operator!=(const Vector2& v) const noexcept {
			return !equals(v);
		}

		template <typename Ch, typename Traits>
		friend std::basic_ostream<Ch, Traits>& operator<<(std::basic_ostream<Ch, Traits>& os, const Vector2& v) {
			return os << Ch{'('} << v.x << Ch{','} << v.y << Ch{')'};
		}


		/**
		 * 零ベクトルの取得
		 * @return (0, 0)
		 */
		constexpr static Vector2 zero() noexcept {
			return {};
		}


		/**
		 * x単位ベクトル
		 * @return (1, 0)
		 */
		constexpr static Vector2 unitX() noexcept {
			return { T{1}, T{0} };
		}


		/**
		 * y単位ベクトル
		 * @return (0, 1)
		 */
		constexpr static Vector2 unitY() noexcept {
			return { T{0}, T{1} };
		}


		/**
		 * 角度を指定して単位ベクトルを算出する
		 * @param  angle_rad 求める単位ベクトルの角度[rad]
		 * @return           (cos, sin)
		 */
		/*constexpr*/ static Vector2 unit(T angle_rad) noexcept {
			return { std::cos(angle_rad), std::sin(angle_rad) };
		}


		/**
		 * 値の設定
		 * @param  x
		 * @param  y
		 * @return   this参照
		 */
		Vector2& set(T x, T y) noexcept {
			this->x = x;
			this->y = y;
			return *this;
		}


		/**
		 * 零ベクトルであるか
		 * @return x,yがともに0であればtrue
		 */
		constexpr bool isZero() const noexcept {
			return x == 0 && y == 0;
		}


		/**
		 * 2つのベクトルの等値比較
		 * @param  v 比較対象のベクトル
		 * @return   x,y成分が共に等しければtrue
		 */
		constexpr bool equals(const Vector2& v) const noexcept {
			return x == v.x && y == v.y;
		}


		/**
		 * 内積の算出
		 * @param  v
		 * @return   内積
		 */
		template <typename U>
		constexpr auto dot(const Vector2<U>& v) const noexcept
			-> decltype(x*v.x + y*v.y) {
			return x*v.x + y*v.y;
		}


		/**
		 * 外積の算出
		 * @param  v
		 * @return   外積
		 */
		template <typename U>
		constexpr auto cross(const Vector2<U>& v) const noexcept
			-> decltype(x*v.y - y*v.x) {
			return x*v.y - y*v.x;
		}


		/**
		 * ベクトルの大きさの2乗の算出
		 * @return ベクトルの大きさの2乗
		 */
		constexpr T lengthSq() const noexcept {
			return x*x + y*y;
		}


		/**
		 * ベクトルの大きさの算出
		 * @return ベクトルの大きさ
		 */
		/*constexpr*/ T length() const noexcept {
			return std::sqrt(lengthSq());
		}


		/**
		 * x軸に対して成す角度の取得
		 * @return このベクトルがx軸に対して成す角度
		 */
		/*constexpr*/ T angle() const noexcept {
			return std::atan2(y, x);
		}


		/**
		 * 2位置ベクトル間の距離の2乗を求める
		 * @param  v 距離を求める位置ベクトル
		 * @return   this-v間の距離の2乗
		 */
		template <typename U>
		constexpr decltype(U{}-T{}) distanceSq(const Vector2<U>& v) const noexcept {
			return (v - *this).lengthSq();
		}


		/**
		 * 2位置ベクトル間の距離を求める
		 * @param  v 距離を求める位置ベクトル
		 * @return   this-v間の距離
		 */
		template <typename U>
		/*constexpr*/ decltype(U{}-T{}) distance(const Vector2<U>& v) const noexcept {
			return (v - *this).length();
		}


		/**
		 * 正規化されたベクトルの算出
		 * @return 正規化されたベクトル
		 */
		/*constexpr*/ Vector2 normalized() const noexcept {
			return *this / length();
		}


		/**
		 * 原点に対して指定角回転されたベクトルの算出
		 * @param  rotation_rad 回転量[rad]
		 * @return              回転されたベクトル
		 */
		/*constexpr*/ Vector2 rotated(T rotation_rad) const noexcept {
			T c = std::cos(rotation_rad);
			T s = std::sin(rotation_rad);
			return { x*c - y*s, x*s + y*c };
		}
	};

	using Vec2i	= Vector2<int>;
	using Vec2f	= Vector2<float>;
	using Vec2d	= Vector2<double>;
	using Vec2	= Vec2f;
}}
