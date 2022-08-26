#include "quaternion.hpp"
#include <cmath>
#include <numbers>

// @credits: https://docs.unity3d.com/ScriptReference/Vector3.OrthoNormalize.html
// @credits: http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation
// @credits: http://www.flipcode.com/documents/matrfaq.html
// @credits: http://db-in.com/blog/2011/04/cameras-on-opengl-es-2-x/
// @credits: http://wiki.beyondunreal.com/Legacy:Quaternion
// @credits: http://clb.demon.fi/MathGeoLib/docs/float3x3.cpp_code.html#612
// @credits: http://clb.demon.fi/MathGeoLib/docs/Quat_summary.php
// @credits: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
// @credits: http://www.koders.com/cpp/fid6E231B19C37F95D54405AEADD2C7CE1E84C5CEF1.aspx
// @credits: http://forums.create.msdn.com/forums/t/4574.aspx

constexpr sdk::quaternion sdk::quaternion::identity(0.f, 0.f, 0.f, 1.f);

sdk::quaternion sdk::quaternion::normalized() const
{
    const float mag = std::sqrtf(w * w + x * x + y * y + z * z);
    return { x / mag, y / mag, z / mag, w / mag };
}

void sdk::quaternion::normalize()
{
    const float mag = std::sqrtf(w * w + x * x + y * y + z * z);

    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;
}

sdk::quaternion sdk::quaternion::angle_axis(float angle, const vector& axis)
{
    const vector vn = axis.normalized();

    angle *= 0.0174532925f; // to radians!
    angle *= 0.5f;
    const float sin_angle = sin(angle);

    return { vn.x * sin_angle, vn.y * sin_angle, vn.z * sin_angle, std::cos(angle) };
}

sdk::quaternion sdk::quaternion::from_eulerangles(vector v)
{
    v.x *= 0.0174532925f; // to radians!
    v.y *= 0.0174532925f; // to radians!
    v.z *= 0.0174532925f; // to radians!

    v.x *= 0.5f;
    v.y *= 0.5f;
    v.z *= 0.5f;

    const float sinx = std::sinf(v.x);
    const float siny = std::sinf(v.y);
    const float sinz = std::sinf(v.z);
    const float cosx = std::cosf(v.x);
    const float cosy = std::cosf(v.y);
    const float cosz = std::cosf(v.z);

    quaternion q;

    q.x = sinx * cosy * cosz + cosx * siny * sinz;
    q.y = cosx * siny * cosz - sinx * cosy * sinz;
    q.z = cosx * cosy * sinz - sinx * siny * cosz;
    q.w = cosx * cosy * cosz + sinx * siny * sinz;

    return q;
}

void sdk::quaternion::set_eulerangles(vector v)
{
    v.x *= 0.0174532925f; // To radians!
    v.y *= 0.0174532925f; // To radians!
    v.z *= 0.0174532925f; // To radians!

    v.x *= 0.5f;
    v.y *= 0.5f;
    v.z *= 0.5f;

    const float sinx = std::sinf(v.x);
    const float siny = std::sinf(v.y);
    const float sinz = std::sinf(v.z);
    const float cosx = std::cosf(v.x);
    const float cosy = std::cosf(v.y);
    const float cosz = std::cosf(v.z);

    x = sinx * cosy * cosz + cosx * siny * sinz;
    y = cosx * siny * cosz - sinx * cosy * sinz;
    z = cosx * cosy * sinz - sinx * siny * cosz;
    w = cosx * cosy * cosz + sinx * siny * sinz;
}

sdk::vector sdk::quaternion::to_eulerangles() const
{
	const float check = 2.0f * (-y * z + w * x);

    if (check < -0.995f)
    {
        return vector(
            -90.0f,
            0.0f,
            -atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * radtodeg
        );
    }

	if (check > 0.995f)
    {
        return vector(
            90.0f,
            0.0f,
            atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * radtodeg
        );
    }

	return vector(
		asinf(check) * radtodeg,
		atan2f(2.0f * (x * z + w * y), 1.0f - 2.0f * (x * x + y * y)) * radtodeg,
		atan2f(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z)) * radtodeg
    );
}

void sdk::quaternion::to_angle_axis(float* angle, vector* axis) const
{
    *angle = std::acosf(w);

    if (float sinz = std::sinf(*angle); std::fabsf(sinz) > 1e-4f)
    {
        sinz = 1.0f / sinz;

        axis->x = x * sinz;
        axis->y = y * sinz;
        axis->z = z * sinz;

        *angle *= 2.0f * 57.2957795f;
        if (*angle > 180.0f)
            *angle = 360.0f - *angle;
    }
    else
    {
        *angle = 0.0f;
        axis->x = 1.0f;
        axis->y = 0.0f;
        axis->z = 0.0f;
    }
}

float sdk::quaternion::angle(const quaternion& a, const quaternion& b)
{
    const float degrees = std::acosf((b * inverse(a)).w) * 2.0f * 57.2957795f;
    if (degrees > 180.0f)
        return 360.0f - degrees;
    return degrees;
}

sdk::quaternion operator*(const float f, sdk::quaternion& m)
{
    return {m.x * f, m.y * f, m.z * f, m.w * f };
}

sdk::quaternion operator*(const float f, const sdk::quaternion& m)
{
    return {m.x * f, m.y * f, m.z * f, m.w * f };
}

sdk::quaternion sdk::quaternion::slerp(const quaternion& from, const quaternion& to, const float t)
{
    float cos_theta = dot(from, to);
    quaternion temp(to);

    if (cos_theta < 0.0f)
    {
        cos_theta *= -1.0f;
        temp = temp * -1.0f;
    }

    const float theta = std::acosf(cos_theta);
    float sin_theta = 1.0f / std::sinf(theta);

    return sin_theta * (
        from * std::sinf(theta * (1.0f - t)) +
        temp * std::sinf(t * theta)
    );
}

sdk::quaternion sdk::quaternion::rotate_towards(const quaternion& from, const quaternion& to, const float max_delta)
{
	const float a = angle(from, to);

    if (a == 0.f)
        return to;

    return slerp(from, to, max_delta / a);
}

#define M00 right.x
#define M01 up.x
#define M02 forward.x
#define M10 right.y
#define M11 up.y
#define M12 forward.y
#define M20 right.z
#define M21 up.z
#define M22 forward.z

sdk::quaternion sdk::quaternion::look_rotation(const vector& look_at, const vector& up_direction)
{
    vector forward = look_at;
    vector up = up_direction;
    vector::ortho_normalize(&forward, &up);
    const vector right = up.cross_product(forward);

    quaternion ret;
    ret.w = std::sqrtf(1.0f + M00 + M11 + M22) * 0.5f;
    const float w4_recip = 1.0f / (4.0f * ret.w);
    ret.x = (M21 - M12) * w4_recip;
    ret.y = (M02 - M20) * w4_recip;
    ret.z = (M10 - M01) * w4_recip;

    return ret;
}

sdk::quaternion sdk::quaternion::look_rotation(const vector& look_at)
{
    vector up = vector::up();
    vector forward = look_at;
    vector::ortho_normalize(&forward, &up);
    const vector right = up.cross_product(forward);

    quaternion ret;
    ret.w = std::sqrtf(1.0f + M00 + M11 + M22) * 0.5f;
    const float w4_recip = 1.0f / (4.0f * ret.w);
    ret.x = (M21 - M12) * w4_recip;
    ret.y = (M02 - M20) * w4_recip;
    ret.z = (M10 - M01) * w4_recip;

    return ret;
}

void sdk::quaternion::set_look_rotation(const vector& look_at)
{
    vector up = vector::up();
    vector forward = look_at;
    vector::ortho_normalize(&forward, &up);
    const vector right = up.cross_product(forward);

    w = std::sqrtf(1.0f + M00 + M11 + M22) * 0.5f;
    const float w4_recip = 1.0f / (4.0f * w);
    x = (M21 - M12) * w4_recip;
    y = (M02 - M20) * w4_recip;
    z = (M10 - M01) * w4_recip;
}

void sdk::quaternion::set_look_rotation(const vector& look_at, const vector& up_direction)
{
    vector forward = look_at;
    vector up = up_direction;
    vector::ortho_normalize(&forward, &up);
    const vector right = up.cross_product(forward);

    w = sqrtf(1.0f + M00 + M11 + M22) * 0.5f;
    const float w4_recip = 1.0f / (4.0f * w);
    x = (M21 - M12) * w4_recip;
    y = (M02 - M20) * w4_recip;
    z = (M10 - M01) * w4_recip;
}

#undef M00
#undef M01
#undef M02
#undef M10
#undef M11
#undef M12
#undef M20
#undef M21
#undef M22
