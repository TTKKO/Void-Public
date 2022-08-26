#include "matrix.hpp"

const sdk::matrix sdk::matrix::identity = matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

sdk::matrix::matrix()
{
    *this = identity;
}

sdk::matrix::matrix(const vec_t _00, const vec_t _01, const vec_t _02, const vec_t _03, const vec_t _10,
                    const vec_t _11, const vec_t _12, const vec_t _13, const vec_t _20, const vec_t _21,
                    const vec_t _22, const vec_t _23, const vec_t _30, const vec_t _31, const vec_t _32,
                    const vec_t _33)
{
    (*this)(0, 0) = _00;
    (*this)(0, 1) = _01;
    (*this)(0, 2) = _02;
    (*this)(0, 3) = _03;

    (*this)(1, 0) = _10;
    (*this)(1, 1) = _11;
    (*this)(1, 2) = _12;
    (*this)(1, 3) = _13;

    (*this)(2, 0) = _20;
    (*this)(2, 1) = _21;
    (*this)(2, 2) = _22;
    (*this)(2, 3) = _23;

    (*this)(3, 0) = _30;
    (*this)(3, 1) = _31;
    (*this)(3, 2) = _32;
    (*this)(3, 3) = _33;
}

sdk::matrix::matrix(vec_t m[16])
{
    int index = 0;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            (*this)(i, j) = m[index++];
        }
}

sdk::matrix::matrix(const vector_4d& v1, const vector_4d& v2, const vector_4d& v3, const vector_4d& v4)
{
    (*this)(0) = v1;
    (*this)(1) = v2;
    (*this)(2) = v3;
    (*this)(3) = v4;
}

vec_t& sdk::matrix::operator()(const unsigned row, const unsigned col)
{
    return mat_[row][col];
}

vec_t sdk::matrix::operator()(const unsigned row, const unsigned col) const
{
    return mat_[row][col];
}

// this one only needed for something like this: m(0) = Vector4(1,1,1,1) //
sdk::vector_4d sdk::matrix::operator()(const unsigned row)
{
    return vector_4d{mat_[row][0], mat_[row][1], mat_[row][2], mat_[row][3]};
}

sdk::vector_4d sdk::matrix::operator()(const unsigned row) const
{
    return vector_4d{mat_[row][0], mat_[row][1], mat_[row][2], mat_[row][3]};
}

sdk::matrix sdk::matrix::operator*(const matrix& m) const
{
    matrix a;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            vec_t sum = 0;

            for (int k = 0; k < 4; ++k)
                sum += (*this)(k, i) * m(j, k);

            a(j, i) = sum;
        }

    return a;
}

void sdk::matrix::translate(const vec_t x, const vec_t y, const vec_t z)
{
    const vec_t xx = (x * (*this)(0, 0) + y * (*this)(1, 0) + z * (*this)(2, 0));
    const vec_t yy = (x * (*this)(0, 1) + y * (*this)(1, 1) + z * (*this)(2, 1));
    const vec_t zz = (x * (*this)(0, 2) + y * (*this)(1, 2) + z * (*this)(2, 2));
    const vec_t ww = (x * (*this)(0, 3) + y * (*this)(1, 3) + z * (*this)(2, 3));

    (*this)(3, 0) += xx;
    (*this)(3, 1) += yy;
    (*this)(3, 2) += zz;
    (*this)(3, 3) += ww;
}

void sdk::matrix::translate(const vector& v)
{
    this->translate(v.x, v.y, v.z);
}

void sdk::matrix::transpose()
{
    matrix trans;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            trans.mat_[i][j] = this->mat_[j][i];

    (*this) = trans;
}

void sdk::matrix::show() const
{
    std::cout << std::endl;
    for (const auto i : this->mat_)
    {
        for (int j = 0; j < 4; ++j)
            std::cout << i[j] << " ";

        std::cout << std::endl;
    }
}

sdk::matrix sdk::matrix::create_translation(const vector& v)
{
    return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        v.x, v.y, v.z, 1
    };
}

sdk::matrix sdk::matrix::create_translation(const vec_t x, const vec_t y, const vec_t z)
{
    return create_translation(vector(x, y, z));
}

sdk::matrix sdk::matrix::create_scale(const vector& v)
{
    return {
        v.x, 0, 0, 0,
        0, v.y, 0, 0,
        0, 0, v.z, 0,
        0, 0, 0, 1
    };
}

sdk::matrix sdk::matrix::create_scale(const vec_t x, const vec_t y, const vec_t z)
{
    return create_scale(vector(x, y, z));
}

sdk::matrix sdk::matrix::create_rotation_x(const vec_t a)
{
    return {
        1, 0, 0, 0,
        0, cos(a), sin(a), 0,
        0, -sin(a), cos(a), 0,
        0, 0, 0, 1
    };
}

sdk::matrix sdk::matrix::create_rotation_y(const vec_t a)
{
    return {
        cos(a), 0, -sin(a), 0,
        0, 1, 0, 0,
        sin(a), 0, cos(a), 0,
        0, 0, 0, 1
    };
}

sdk::matrix sdk::matrix::create_rotation_z(const vec_t a)
{
    return {
        cos(a), sin(a), 0, 0,
        -sin(a), cos(a), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

sdk::matrix sdk::matrix::create_rotation(const vec_t angle, const vector& v)
{
    const vec_t a = angle;
    const vec_t c = cos(a);
    const vec_t s = sin(a);

    vector axis = v;
    axis = axis.normalized();

    const vector temp = axis * (1.0f - c);

    matrix rotate;
    rotate(0, 0) = c + temp.x * axis.x;
    rotate(0, 1) = 0 + temp.x * axis.y + s * axis.z;
    rotate(0, 2) = 0 + temp.x * axis.z - s * axis.y;

    rotate(1, 0) = 0 + temp.y * axis.x - s * axis.z;
    rotate(1, 1) = c + temp.y * axis.y;
    rotate(1, 2) = 0 + temp.y * axis.z + s * axis.x;

    rotate(2, 0) = 0 + temp.z * axis.x + s * axis.y;
    rotate(2, 1) = 0 + temp.z * axis.y - s * axis.x;
    rotate(2, 2) = c + temp.z * axis.z;

    matrix identity;

    matrix m;
    m(0) = (identity)(0) * rotate(0, 0) + (identity)(1) * rotate(0, 1) + (identity)(2) * rotate(0, 2);
    m(1) = (identity)(0) * rotate(1, 0) + (identity)(1) * rotate(1, 1) + (identity)(2) * rotate(1, 2);
    m(2) = (identity)(0) * rotate(2, 0) + (identity)(1) * rotate(2, 1) + (identity)(2) * rotate(2, 2);
    m(3) = (identity)(3);

    return m;
}

void sdk::matrix::rotate(const vec_t angle, const vector& v)
{
    const vec_t a = angle;
    const vec_t c = cos(a);
    const vec_t s = sin(a);

    const auto axis = v.normalized();

    const vector temp = axis * (1.0f - c);

    matrix rotate;
    rotate(0, 0) = c + temp.x * axis.x;
    rotate(0, 1) = 0 + temp.x * axis.y + s * axis.z;
    rotate(0, 2) = 0 + temp.x * axis.z - s * axis.y;

    rotate(1, 0) = 0 + temp.y * axis.x - s * axis.z;
    rotate(1, 1) = c + temp.y * axis.y;
    rotate(1, 2) = 0 + temp.y * axis.z + s * axis.x;

    rotate(2, 0) = 0 + temp.z * axis.x + s * axis.y;
    rotate(2, 1) = 0 + temp.z * axis.y - s * axis.x;
    rotate(2, 2) = c + temp.z * axis.z;

    matrix m;
    m(0) = (*this)(0) * rotate(0, 0) + (*this)(1) * rotate(0, 1) + (*this)(2) * rotate(0, 2);
    m(1) = (*this)(0) * rotate(1, 0) + (*this)(1) * rotate(1, 1) + (*this)(2) * rotate(1, 2);
    m(2) = (*this)(0) * rotate(2, 0) + (*this)(1) * rotate(2, 1) + (*this)(2) * rotate(2, 2);
    m(3) = (*this)(3);

    *this = m;
}

sdk::matrix sdk::matrix::create_look_at(const vector& eye, const vector& center, const vector& up)
{
    auto f = center - eye;
    f = f.normalized();
    auto u = up.normalized();
    auto s = f.cross_product(u);
    s = s.normalized();
    u = s.cross_product(f);

    matrix result;

    result(0, 0) = s.x;
    result(1, 0) = s.y;
    result(2, 0) = s.z;
    result(0, 1) = u.x;
    result(1, 1) = u.y;
    result(2, 1) = u.z;
    result(0, 2) = -f.x;
    result(1, 2) = -f.y;
    result(2, 2) = -f.z;
    result(3, 0) = -s.dot_product(eye);
    result(3, 1) = -s.dot_product(eye);
    result(3, 2) = s.dot_product(eye);

    result(3, 3) = 1.0f;

    return result;
}

sdk::matrix sdk::matrix::create_perspective(const vec_t fovy, const vec_t aspect, const vec_t near, const vec_t far)
{
    const vec_t angle = (fovy / 180.0f) * M_PI;
    vec_t f = 1.0f / tan(angle * 0.5f);

    return {
        f / aspect, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (far + near) / (near - far), -1,
        0, 0, 2 * far * near / (near - far), 0
    };
}
