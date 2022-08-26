#pragma once
// @note: vector3 implementation modified to use sse instructions
// @credits: https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/mathlib/vector.h
#include <cmath>
#include <smmintrin.h>
#include <limits>

using vec_t = float;

namespace sdk
{
	class vector_2d
	{
	public:
		// Members

		union
		{
			struct
			{
				vec_t x;
				vec_t y;
			};

			__m128 mmvalue;
		};

		// Construction/destruction

		explicit vector_2d(const vec_t x = 0.f, const vec_t y = 0.f) : mmvalue(_mm_set_ps(0.f, 0.f, y, x))
		{
		}

		explicit vector_2d(const vec_t* arr_vector) : mmvalue(_mm_set_ps(0.f, 0.f, arr_vector[0], arr_vector[1]))
		{
		}

		explicit vector_2d(const vector_2d& arr_vector) : mmvalue(arr_vector.mmvalue)
		{
		}

		explicit vector_2d(const __m128 v_mmvalue) : mmvalue(v_mmvalue)
		{
		}

		vector_2d& operator=(const vector_2d& vec_base_2d)
		{
			this->mmvalue = vec_base_2d.mmvalue;
			return *this;
		}

		// Base address...
		vec_t* base()
		{
			return reinterpret_cast<vec_t*>(this);
		}

		_NODISCARD const vec_t* base() const
		{
			return reinterpret_cast<const vec_t*>(this);
		}

		bool operator==(const vector_2d& v) const
		{
			return (_mm_movemask_ps(_mm_cmpeq_ps(mmvalue, v.mmvalue)) & 0x7) == 0x7;
		}

		bool operator!=(const vector_2d& v) const
		{
			return !(*this == v);
		}

		vector_2d& operator+=(const vector_2d& v)
		{
			mmvalue = _mm_add_ps(mmvalue, v.mmvalue);
			return *this;
		}

		vector_2d& operator-=(const vector_2d& v)
		{
			mmvalue = _mm_sub_ps(mmvalue, v.mmvalue);
			return *this;
		}

		vector_2d& operator*=(const vector_2d& v)
		{
			mmvalue = _mm_mul_ps(mmvalue, v.mmvalue);
			return *this;
		}

		vector_2d& operator/=(const vector_2d& v)
		{
			mmvalue = _mm_div_ps(mmvalue, v.mmvalue);
			return *this;
		}

		vector_2d& operator+=(const vec_t s)
		{
			mmvalue = _mm_add_ps(mmvalue, _mm_set1_ps(s));
			return *this;
		}

		vector_2d& operator-=(const vec_t s)
		{
			mmvalue = _mm_sub_ps(mmvalue, _mm_set1_ps(s));
			return *this;
		}

		vector_2d& operator*=(const vec_t s)
		{
			mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(s));
			return *this;
		}

		vector_2d& operator/=(const vec_t s)
		{
			mmvalue = _mm_div_ps(mmvalue, _mm_set1_ps(s));
			return *this;
		}

		vector_2d operator+(const vector_2d& vec_add) const
		{
			return vector_2d(_mm_add_ps(mmvalue, vec_add.mmvalue));
		}

		vector_2d operator-(const vector_2d& vec_subtract) const
		{
			return vector_2d(_mm_sub_ps(mmvalue, vec_subtract.mmvalue));
		}

		vector_2d operator*(const vector_2d& vec_multiply) const
		{
			return vector_2d(_mm_mul_ps(mmvalue, vec_multiply.mmvalue));
		}

		vector_2d operator/(const vector_2d& vec_divide) const
		{
			return vector_2d(_mm_div_ps(mmvalue, vec_divide.mmvalue));
		}

		vector_2d operator+(const vec_t fl_add) const
		{
			return vector_2d(_mm_add_ps(mmvalue, _mm_set1_ps(fl_add)));
		}

		vector_2d operator-(const vec_t fl_subtract) const
		{
			return vector_2d(_mm_sub_ps(mmvalue, _mm_set1_ps(fl_subtract)));
		}

		vector_2d operator*(const vec_t fl_multiply) const
		{
			return vector_2d(_mm_mul_ps(mmvalue, _mm_set1_ps(fl_multiply)));
		}

		vector_2d operator/(const vec_t fl_divide) const
		{
			return vector_2d(_mm_div_ps(mmvalue, _mm_set1_ps(fl_divide)));
		}
	};

	_MM_ALIGN16 class vector
	{
	public:
		explicit vector(const vec_t x = 0.f, const vec_t y = 0.f, const vec_t z = 0.f) : mmvalue(_mm_set_ps(0.f, z, y, x))
		{
		}

		explicit vector(const vec_t* arr_vector) : mmvalue(_mm_set_ps(0.f, arr_vector[2], arr_vector[1], arr_vector[0]))
		{
		}

		explicit vector(const vector_2d& vec_base_2d) : mmvalue(vec_base_2d.mmvalue)
		{
		}

		explicit vector(const __m128 m) : mmvalue(m)
		{
		}

		static vector up()
		{
			return vector { _mm_set_ps(0.f, 0.f, 1.f, 0.f) };
		}

		static vector forward()
		{
			return vector{ _mm_set_ps(0.f, 1.f, 0.f, 0.f) };
		}

		_NODISCARD bool is_valid() const
		{
			return std::isfinite(this->x) && std::isfinite(this->y) && std::isfinite(this->z);
		}

		void invalidate()
		{
			static constexpr auto inf = std::numeric_limits<vec_t>::infinity();
			mmvalue = _mm_set_ps(0.f, inf, inf, inf);
		}

		_NODISCARD vec_t* data()
		{
			return reinterpret_cast<vec_t*>(this);
		}

		_NODISCARD const vec_t* data() const
		{
			return reinterpret_cast<vec_t*>(const_cast<vector*>(this));
		}

		vec_t& operator[](const std::size_t i)
		{
			return this->data()[i];
		}

		const vec_t& operator[](const std::size_t i) const
		{
			return this->data()[i];
		}

		bool operator==(const vector& vec_base) const
		{
			return this->is_equal(vec_base);
		}

		bool operator!=(const vector& vec_base) const
		{
			return !this->is_equal(vec_base);
		}

		vector& operator=(const vector& vec_base) = default;

		vector& operator=(const vector_2d& vec_base_2d)
		{
			this->mmvalue = vec_base_2d.mmvalue;
			return *this;
		}

		vector& operator+=(const vector& vec_base)
		{
			mmvalue = _mm_add_ps(mmvalue, vec_base.mmvalue);
			return *this;
		}

		vector& operator-=(const vector& vec_base)
		{
			mmvalue = _mm_sub_ps(mmvalue, vec_base.mmvalue);
			return *this;
		}

		vector& operator*=(const vector& vec_base)
		{
			mmvalue = _mm_mul_ps(mmvalue, vec_base.mmvalue);
			return *this;
		}

		vector& operator/=(const vector& vec_base)
		{
			mmvalue = _mm_div_ps(mmvalue, vec_base.mmvalue);
			return *this;
		}

		vector& operator+=(const vec_t fl_add)
		{
			mmvalue = _mm_add_ps(mmvalue, _mm_set1_ps(fl_add));
			return *this;
		}

		vector& operator-=(const vec_t fl_subtract)
		{
			mmvalue = _mm_sub_ps(mmvalue, _mm_set1_ps(fl_subtract));
			return *this;
		}

		vector& operator*=(const vec_t fl_multiply)
		{
			mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(fl_multiply));
			return *this;
		}

		vector& operator/=(const vec_t fl_divide)
		{
			mmvalue = _mm_div_ps(mmvalue, _mm_set1_ps(fl_divide));
			return *this;
		}

		vector operator+(const vector& vec_add) const
		{
			return vector(_mm_add_ps(mmvalue, vec_add.mmvalue));
		}

		vector operator-(const vector& vec_subtract) const
		{
			return vector(_mm_sub_ps(mmvalue, vec_subtract.mmvalue));
		}

		vector operator*(const vector& vec_multiply) const
		{
			return vector(_mm_mul_ps(mmvalue, vec_multiply.mmvalue));
		}

		vector operator/(const vector& vec_divide) const
		{
			return vector(_mm_div_ps(mmvalue, vec_divide.mmvalue));
		}

		vector operator+(const vec_t fl_add) const
		{
			return vector(_mm_add_ps(mmvalue, _mm_set1_ps(fl_add)));
		}

		vector operator-(const vec_t fl_subtract) const
		{
			return vector(_mm_sub_ps(mmvalue, _mm_set1_ps(fl_subtract)));
		}

		vector operator*(const vec_t fl_multiply) const
		{
			return vector(_mm_mul_ps(mmvalue, _mm_set1_ps(fl_multiply)));
		}

		vector operator/(const vec_t fl_divide) const
		{
			return vector(_mm_div_ps(mmvalue, _mm_set1_ps(fl_divide)));
		}

		_NODISCARD bool is_equal(const vector& vec_equal, const vec_t fl_error_margin = std::numeric_limits<vec_t>::epsilon()) const
		{
			return (std::fabsf(this->x - vec_equal.x) < fl_error_margin &&
				std::fabsf(this->y - vec_equal.y) < fl_error_margin &&
				std::fabsf(this->z - vec_equal.z) < fl_error_margin);
		}

		_NODISCARD bool is_zero() const
		{
			return (std::fpclassify(this->x) == FP_ZERO &&
				std::fpclassify(this->y) == FP_ZERO &&
				std::fpclassify(this->z) == FP_ZERO);
		}

		_NODISCARD vector_2d to_vector_2d() const
		{
			return vector_2d(this->x, this->y);
		}

		_NODISCARD vec_t length() const
		{
			return std::sqrtf(this->length_sqr());
		}

		_NODISCARD vec_t length_sqr() const
		{
			return dot_product(*this);
		}

		_NODISCARD vec_t length_2d() const
		{
			return std::sqrtf(this->length_2d_sqr());
		}

		_NODISCARD constexpr vec_t length_2d_sqr() const
		{
			return this->x * this->x + this->y * this->y;
		}

		_NODISCARD vec_t dist_to(const vector& vec_end) const
		{
			return (*this - vec_end).length();
		}

		_NODISCARD vec_t dist_to_sqr(const vector& vec_end) const
		{
			return (*this - vec_end).length_sqr();
		}

		static void ortho_normalize(vector* normal, vector* tangent)
		{
			*normal = normal->normalized();
			*tangent = tangent->normalized();
		}

		_NODISCARD vector normalized() const
		{
			vector vec_out = *this;
			vec_out.normalize_in_place();
			return vec_out;
		}

		vec_t normalize_in_place()
		{
			const vec_t fl_length = this->length();
			const vec_t fl_radius = 1.0f / (fl_length + std::numeric_limits<vec_t>::epsilon());

			mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(fl_radius));

			return fl_length;
		}

		_NODISCARD vec_t dot_product(const vector& vec_dot) const
		{
			return _mm_cvtss_f32(_mm_dp_ps(mmvalue, vec_dot.mmvalue, 0x71));
		}

		_NODISCARD vector cross_product(const vector& vec_cross) const
		{
			return vector(_mm_sub_ps(
				_mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(vec_cross.mmvalue, vec_cross.mmvalue, _MM_SHUFFLE(3, 1, 0, 2))),
				_mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(vec_cross.mmvalue, vec_cross.mmvalue, _MM_SHUFFLE(3, 0, 2, 1)))
			));
		}

		union
		{
			struct
			{
				vec_t x;
				vec_t y;
				vec_t z;
			};

			__m128 mmvalue;
		};

	};

	class vector_4d
	{
	public:
		union
		{
			struct
			{
				vec_t x;
				vec_t y;
				vec_t z;
				vec_t w;
			};

			__m128 mmvalue;
		};

		// Construction/destruction
		explicit vector_4d(const vec_t x = 0.f, const vec_t y = 0.f, const vec_t z = 0.f, const vec_t w = 0.f) : mmvalue(_mm_set_ps(w, z, y, x))
		{
		}

		explicit vector_4d(const vec_t* arr_vector) : mmvalue(_mm_set_ps(arr_vector[0], arr_vector[1], arr_vector[2], arr_vector[3]))
		{
		}

		explicit vector_4d(const vector& vec_base) : mmvalue(vec_base.mmvalue)
		{
		}

		explicit vector_4d(const __m128 m) : mmvalue(m)
		{
		}

		vec_t* base()
		{
			return reinterpret_cast<vec_t*>(this);
		}

		_NODISCARD const vec_t* base() const
		{
			return reinterpret_cast<const vec_t*>(this);
		}

		// Cast to Vector and Vector2D...
		vector& as_vector_3d()
		{
			return *reinterpret_cast<vector*>(this);
		}

		_NODISCARD const vector& as_vector_3d() const
		{
			return *reinterpret_cast<const vector*>(this);
		}

		vector_2d& as_vector_2d()
		{
			return *reinterpret_cast<vector_2d*>(this);
		}

		_NODISCARD const vector_2d& as_vector_2d() const
		{
			return *reinterpret_cast<const vector_2d*>(this);
		}

		vector_4d& operator=(const vector_4d& v_other) = default;

		// equality
		bool operator==(const vector_4d& v) const
		{
			return (_mm_movemask_ps(_mm_cmpeq_ps(mmvalue, v.mmvalue)) & 0x7) == 0x7;
		}

		bool operator!=(const vector_4d& v) const
		{
			return !(*this == v);
		}

		// arithmetic operations
		vector_4d& operator+=(const vector_4d& vec_base)
		{
			mmvalue = _mm_add_ps(mmvalue, vec_base.mmvalue);
			return *this;
		}

		vector_4d& operator-=(const vector_4d& vec_base)
		{
			mmvalue = _mm_sub_ps(mmvalue, vec_base.mmvalue);
			return *this;
		}

		vector_4d& operator*=(const vector_4d& vec_base)
		{
			mmvalue = _mm_mul_ps(mmvalue, vec_base.mmvalue);
			return *this;
		}

		vector_4d& operator/=(const vector_4d& vec_base)
		{
			mmvalue = _mm_div_ps(mmvalue, vec_base.mmvalue);
			return *this;
		}

		vector_4d& operator+=(const vec_t fl_add)
		{
			mmvalue = _mm_add_ps(mmvalue, _mm_set1_ps(fl_add));
			return *this;
		}

		vector_4d& operator-=(const vec_t fl_subtract)
		{
			mmvalue = _mm_sub_ps(mmvalue, _mm_set1_ps(fl_subtract));
			return *this;
		}

		vector_4d& operator*=(const vec_t fl_multiply)
		{
			mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(fl_multiply));
			return *this;
		}

		vector_4d& operator/=(const vec_t fl_divide)
		{
			mmvalue = _mm_div_ps(mmvalue, _mm_set1_ps(fl_divide));
			return *this;
		}

		vector_4d operator+(const vector_4d& vec_add) const
		{
			return vector_4d(_mm_add_ps(mmvalue, vec_add.mmvalue));
		}

		vector_4d operator-(const vector_4d& vec_subtract) const
		{
			return vector_4d(_mm_sub_ps(mmvalue, vec_subtract.mmvalue));
		}

		vector_4d operator*(const vector_4d& vec_multiply) const
		{
			return vector_4d(_mm_mul_ps(mmvalue, vec_multiply.mmvalue));
		}

		vector_4d operator/(const vector_4d& vec_divide) const
		{
			return vector_4d(_mm_div_ps(mmvalue, vec_divide.mmvalue));
		}

		vector_4d operator+(const vec_t fl_add) const
		{
			return vector_4d(_mm_add_ps(mmvalue, _mm_set1_ps(fl_add)));
		}

		vector_4d operator-(const vec_t fl_subtract) const
		{
			return vector_4d(_mm_sub_ps(mmvalue, _mm_set1_ps(fl_subtract)));
		}

		vector_4d operator*(const vec_t fl_multiply) const
		{
			return vector_4d(_mm_mul_ps(mmvalue, _mm_set1_ps(fl_multiply)));
		}

		vector_4d operator/(const vec_t fl_divide) const
		{
			return vector_4d(_mm_div_ps(mmvalue, _mm_set1_ps(fl_divide)));
		}

		_NODISCARD vec_t dot(const vector_4d& v_other) const
		{
			return _mm_cvtss_f32(_mm_dp_ps(mmvalue, v_other.mmvalue, 0x71));
		}
	};
}
