#pragma once

#include <boost/optional.hpp>
#include "Vector2.hpp"

namespace bell { namespace math {
	/**
	 * 3x2行列
	 */
	template <typename T>
	struct Matrix3x2 final {
		using ValueType = T;

		T _11, _12;
		T _21, _22;
		T _31, _32;

		//	コンストラクタ
		constexpr Matrix3x2() noexcept
			: _11(0), _12(0)
			, _21(0), _22(0)
			, _31(0), _32(0) {}

		constexpr Matrix3x2(T _11, T _12, T _21, T _22, T _31, T _32) noexcept
			: _11(_11), _12(_12)
			, _21(_21), _22(_22)
			, _31(_31), _32(_32) {}

		//	演算子
		constexpr explicit operator bool() const noexcept {
			return !isZero();
		}

		constexpr Matrix3x2 operator+() const noexcept {
			return *this;
		}

		constexpr Matrix3x2 operator-() const noexcept {
			return {
				-_11, -_12,
				-_21, -_22,
				-_31, -_32
			};
		}

		template <typename U>
		constexpr Matrix3x2<decltype(T{}+U{})> operator+(const Matrix3x2<U>& m) const noexcept {
			return {
				_11+m._11, _12+m._12,
				_21+m._21, _22+m._22,
				_31+m._31, _32+m._32,
			};
		}

		template <typename U>
		constexpr Matrix3x2<decltype(T{}-U{})> operator-(const Matrix3x2<U>& m) const noexcept {
			return {
				_11-m._11, _12-m._12,
				_21-m._21, _22-m._22,
				_31-m._31, _32-m._32,
			};
		}

		template <typename U>
		constexpr Matrix3x2<decltype(T{}*U{})> operator*(U a) const noexcept {
			return {
				_11*a, _12*a,
				_21*a, _22*a,
				_31*a, _32*a,
			};
		}
		template <typename U>
		friend constexpr Matrix3x2<decltype(U{}*T{})> operator*(U a, const Matrix3x2& m) noexcept {
			return {
				a*m._11, a*m._12,
				a*m._21, a*m._22,
				a*m._31, a*m._32,
			};
		}
		
		template <typename U>
		constexpr Matrix3x2<decltype(T{}/U{})> operator/(U a) const noexcept {
			return BELL_ASSERT(a != 0), Matrix3x2<decltype(T{}/U{})>{
				_11/a, _12/a,
				_21/a, _22/a,
				_31/a, _32/a,
			};
		}

		template <typename U>
		constexpr Matrix3x2<decltype(T{}*U{})> operator*(const Matrix3x2<U>& m) const noexcept {
			return multiply(m);
		}

		template <typename U>
		friend constexpr Vector2<decltype(U{}*T{})> operator*(const Vector2<U>& v, const Matrix3x2& m) noexcept {
			return m.transform(v);
		}

		Matrix3x2& operator+=(const Matrix3x2& m) noexcept {
			return *this = *this + m;
		}

		Matrix3x2& operator-=(const Matrix3x2& m) noexcept {
			return *this = *this - m;
		}

		Matrix3x2& operator*=(const Matrix3x2 m) noexcept {
			return *this = *this * m;
		}

		friend Vector2<T>& operator*=(Vector2<T>& v, const Matrix3x2& m) noexcept {
			return v = m.transform(v);
		}

		Matrix3x2& operator*=(T a) noexcept {
			return *this = *this * a;
		}

		Matrix3x2& operator/=(T a) noexcept {
			return *this = *this / a;
		}

		constexpr bool operator==(const Matrix3x2& m) const noexcept {
			return equals(m);
		}

		constexpr bool operator!=(const Matrix3x2& m) const noexcept {
			return !equals(m);
		}

		template <typename Ch, typename Traits>
		friend std::basic_ostream<Ch, Traits>& operator<<(std::basic_ostream<Ch, Traits>& os, const Matrix3x2& m) {
			return os
				<< Ch{'{'} << Ch{'('} << m._11 << Ch{','} << m._12 << Ch{')'} << std::endl
				<< Ch{' '} << Ch{'('} << m._21 << Ch{','} << m._22 << Ch{')'} << std::endl
				<< Ch{' '} << Ch{'('} << m._31 << Ch{','} << m._32 << Ch{')'} << Ch{'}'};
		}


		/**
		 * 零行列
		 * @return 零行列
		 */
		constexpr static Matrix3x2 zero() noexcept {
			return {};
		}


		/**
		 * 単位行列
		 * @return 単位行列
		 */
		constexpr static Matrix3x2 identity() noexcept {
			return {
				T{1},    0,
				   0, T{1},
				   0,    0
			};
		}


		/**
		 * 平行移動行列
		 * @param  t 移動量
		 * @return   平行移動行列
		 */
		constexpr static Matrix3x2 translation(const Vector2<T>& t) noexcept {
			return {
				T{1},    0,
				   0, T{1},
				 t.x,  t.y
			};
		}


		/**
		 * 拡大縮小行列
		 * @param  scale 拡大率
		 * @return       原点中心の拡大縮小行列
		 */
		constexpr static Matrix3x2 scaling(const Vector2<T>& scale) noexcept {
			return {
				scale.x,       0,
				      0, scale.y,
				      0,       0
			};
		}


		/**
		 * 任意座標中心拡大縮小行列
		 * @param  scale  拡大率
		 * @param  center 拡大の中心点
		 * @return        center中心の拡大縮小行列
		 */
		constexpr static Matrix3x2 scaling(const Vector2<T>& scale, const Vector2<T>& center) noexcept {
			return {
				                    scale.x,                           0,
				                          0,                     scale.y,
				center.x - scale.x*center.x, center.y - scale.y*center.y
			};
		}


		/**
		 * 回転行列
		 * @param  rotation_rad 回転量[rad]
		 * @return              原点中心の回転行列
		 */
		/*constexpr*/ static Matrix3x2 rotation(T rotation_rad) noexcept {
			T c = std::cos(rotation_rad);
			T s = std::sin(rotation_rad);
			
			return {
				 c, s,
				-s, c,
				 0, 0
			};
		}


		/**
		 * 任意座標中心の回転行列
		 * @param  rotation_rad 回転量[rad]
		 * @param  center       回転の中心点
		 * @return              center中心の回転行列
		 */
		/*constexpr*/ static Matrix3x2 rotation(T rotation_rad, const Vector2<T>& center) noexcept {
			T c = std::cos(rotation_rad);
			T s = std::sin(rotation_rad);

			T _31 = center.x - c*center.x + s*center.y;
			T _32 = center.y - s*center.x - c*center.y;
			
			return {
				  c,   s,
				 -s,   c,
				_31, _32
			};
		}


		/**
		 * 傾斜行列
		 * @param  angleX_rad x軸に対してなす傾斜角[rad]
		 * @param  angleY_rad y軸に対してなす傾斜角[rad]
		 * @return            原点基準の傾斜行列
		 */
		/*constexpr*/ static Matrix3x2 skew(T angleX_rad, T angleY_rad) noexcept {
			T _12 = std::tan(angleY_rad);
			T _21 = std::tan(angleX_rad);

			return {
				T{1},  _12,
				 _21, T{1},
				   0,    0
			};
		}


		/**
		 * 任意座標基準の傾斜行列
		 * @param  angleX_rad x軸に対してなす傾斜角[rad]
		 * @param  angleY_rad y軸に対してなす傾斜角[rad]
		 * @param  center     傾斜の基準点
		 * @return            center基準の傾斜行列
		 */
		/*constexpr*/ static Matrix3x2 skew(T angleX_rad, T angleY_rad, const Vector2<T>& center) noexcept {
			T _12 = std::tan(angleY_rad);
			T _21 = std::tan(angleX_rad);
			T _31 = -center.y * _21;
			T _32 = -center.x * _12;

			return {
				T{1},  _12,
				 _21, T{1},
				 _31,  _32
			};
		}


		/**
		 * 値の設定
		 * @param  _11
		 * @param  _12
		 * @param  _21
		 * @param  _22
		 * @param  _31
		 * @param  _32
		 * @return     this参照
		 */
		Matrix3x2& set(T _11, T _12, T _21, T _22, T _31, T _32) noexcept {
			this->_11 = _11;
			this->_12 = _12;
			this->_21 = _21;
			this->_22 = _22;
			this->_31 = _31;
			this->_32 = _32;
			return *this;
		}


		/**
		 * 零行列であるか
		 * @return 全ての要素が0であればtrue
		 */
		constexpr bool isZero() const noexcept {
			return
				_11 == 0 && _12 == 0 &&
				_21 == 0 && _22 == 0 &&
				_31 == 0 && _32 == 0;
		}


		/**
		 * 単位行列であるか
		 * @return 単位行列であればtrue
		 */
		constexpr bool isIdentity() const noexcept {
			return
				_11 == T{1} && _12 ==    0 &&
				_21 ==    0 && _22 == T{1} &&
				_31 ==    0 && _32 ==    0;
		}


		/**
		 * 逆行列を持つか
		 * @return 行列式が0であればfalse
		 */
		constexpr bool isInvertible() const noexcept {
			return determinant() != 0;
		}


		/**
		 * 2つの行列の等値比較
		 * @param  m 比較対象の行列
		 * @return   全ての要素が等しければtrue
		 */
		constexpr bool equals(const Matrix3x2& m) const noexcept {
			return
				_11 == m._11 && _12 == m._12 &&
				_21 == m._21 && _22 == m._22 &&
				_31 == m._31 && _32 == m._32;
		}


		/**
		 * 行列式の算出
		 * @return 行列式
		 */
		constexpr T determinant() const noexcept {
			return _11*_22 - _12*_21;
		}


		/**
		 * 逆行列の算出
		 * @return 行列式が0であればnone そうでなければ逆行列
		 */
		/*constexpr*/ boost::optional<Matrix3x2> invert() const noexcept {
			if(T det = determinant())
				return Matrix3x2{
					            _22,              -_12,
					           -_21,               _11,
					_21*_32-_22*_31, _12*_31 - _11*_32
				} / det;

			return boost::none;
		}


		/**
		 * 行列同士の乗算
		 * @param  m
		 * @return   this*m
		 */
		template <typename U>
		constexpr Matrix3x2<decltype(T{}*U{})> multiply(const Matrix3x2<U>& m) const noexcept {
			return {
				_11*m._11+_12*m._21      , _11*m._12+_12*m._22      ,
				_21*m._11+_22*m._21      , _21*m._12+_22*m._22      ,
				_31*m._11+_32*m._21+m._31, _31*m._12+_32*m._22+m._32
			};
		}


		/**
		 * ベクトルの変換
		 * @param  v 変換するベクトル
		 * @return   v*this
		 */
		template <typename U>
		constexpr Vector2<decltype(U{}*T{})> transform(const Vector2<U>& v) const noexcept {
			return {
				v.x*_11 + v.y*_21 + _31,
				v.x*_12 + v.y*_22 + _32,
			};
		}
	};

	using Mat3x2i	= Matrix3x2<int>;
	using Mat3x2f	= Matrix3x2<float>;
	using Mat3x2d	= Matrix3x2<double>;
	using Mat3x2	= Mat3x2f;
}}
