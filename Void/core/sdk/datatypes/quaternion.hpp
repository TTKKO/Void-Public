#ifndef _H_QUATERNION_
#define _H_QUATERNION_

#ifndef _H_MATRIX_
#include "matrix.hpp"
#endif

// @note: quaternion implementation modified to use sse instructions

namespace sdk
{
    class quaternion
    {
    public:
        float x;
    	float y;
    	float z;
    	float w;
    
        constexpr quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
        {
        }

        constexpr quaternion(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w)
        {
        }

        constexpr quaternion(const quaternion& q) = default;

        constexpr ~quaternion() = default;

        constexpr quaternion& operator=(const quaternion& q)
        {
            if (this == &q) 
                return *this;

            x = q.x;
            y = q.y;
            z = q.z;
            w = q.w;

            return *this;
        }

        constexpr bool operator==(const quaternion& rhs) const
        {
            return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
        }

        constexpr bool operator!=(const quaternion& rhs) const
        {
            return !(x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
        }

        constexpr quaternion& operator*=(const quaternion& rhs)
        {
            quaternion q;

            q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
            q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
            q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
            q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;

            *this = q;
            return *this;
        }

        constexpr quaternion operator*(const quaternion& rhs) const
        {
            quaternion q;

            q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
            q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
            q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
            q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;

            return q;
        }

		constexpr quaternion operator*(const float& rhs) const
        {
            return { x * rhs, y * rhs, z * rhs, w * rhs };
        }

        constexpr quaternion operator+(const quaternion& rhs) const
        {
            return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
        }

        _NODISCARD quaternion normalized() const;
    	void normalize();
        constexpr quaternion conjugate() // @note: inverse
        {
            return { -x, -y, -z, w };
        }

        void to_angle_axis(float* angle, vector* axis) const;
        void set_eulerangles(vector v);
        _NODISCARD vector to_eulerangles() const;

        _NODISCARD constexpr float dot(const quaternion& b) const
        {
            return (w * b.w + x * b.x * y * b.y + z * b.z);
        }

        static constexpr float dot(const quaternion& a, const quaternion& b)
        {
            return (a.w * b.w + a.x * b.x * a.y * b.y + a.z * b.z);
        }

        void set_look_rotation(const vector& look_at);
        void set_look_rotation(const vector& look_at, const vector& up_direction);

        static quaternion look_rotation(const vector& look_at);
        static quaternion look_rotation(const vector& look_at, const vector& up_direction);
        static quaternion slerp(const quaternion& from, const quaternion& to, float t);
        static quaternion rotate_towards(const quaternion& from, const quaternion& to, float max_delta);

        constexpr static quaternion lerp(const quaternion& from, const quaternion& to, const float t)
        {
	        const quaternion src = from * (1.0f - t);
            const quaternion dst = to * t;

            quaternion q = src + dst;
            return q;
        }

        static float angle(const quaternion& a, const quaternion& b);

        static quaternion angle_axis(float angle, const vector& axis);

        constexpr static quaternion inverse(const quaternion& rotation)
        {
            return { -1.0f * rotation.x, -1.0f * rotation.y, -1.0f * rotation.z, rotation.w };
        }

        static quaternion from_eulerangles(vector v);

    private:
    	static const quaternion identity;

        static constexpr float pi = 3.14159265358979323846264338327950288f;
        static constexpr float degtorad = pi / 180.0f;
        static constexpr float degtorad2 = pi / 360.0f;
        static constexpr float radtodeg = 1.0f / degtorad;
    };
}

#endif
