#pragma once

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cmath>
#include <corecrt_math_defines.h>
#include <iostream>
#include "vector.h"

namespace sdk
{
    class matrix
    {
    public:
        matrix();
        matrix(vec_t, vec_t, vec_t, vec_t, vec_t, vec_t, vec_t, vec_t, vec_t, vec_t, vec_t, vec_t, vec_t, vec_t, vec_t,
               vec_t);
        explicit matrix(vec_t m[16]);
        matrix(const vector_4d& v1, const vector_4d& v2, const vector_4d& v3, const vector_4d& v4);
        ~matrix()
        = default;

        matrix operator*(const matrix& m) const;

        vec_t& operator()(unsigned row, unsigned col);
        vec_t operator()(unsigned row, unsigned col) const;
        vector_4d operator()(unsigned row);
        vector_4d operator()(unsigned row) const;

        void translate(vec_t x, vec_t y, vec_t z);
        void translate(const vector& v);
        void rotate(vec_t angle, const vector& v);
        void transpose();

        const static matrix identity;

        static matrix create_translation(const vector& v);
        static matrix create_translation(vec_t x, vec_t y, vec_t z);
        static matrix create_scale(const vector& v);
        static matrix create_scale(vec_t x, vec_t y, vec_t z);
        static matrix create_rotation_x(vec_t a);
        static matrix create_rotation_y(vec_t a);
        static matrix create_rotation_z(vec_t a);
        static matrix create_rotation(vec_t angle, const vector& v);
        static matrix create_look_at(const vector& eye, const vector& center, const vector& up);
        static matrix create_perspective(vec_t fovy, vec_t aspect, vec_t near, vec_t far);

        // Euler angles //
        vec_t get_roll() { return atan2(-(*this)(2, 0), (*this)(0, 0)); } // X //
        vec_t get_pitch() { return asin((*this)(1, 0)); } // Y //
        vec_t get_yaw() { return atan2(-(*this)(1, 2), (*this)(1, 1)); } // Z //

        void show() const;

    private:
        vec_t mat_[4][4]{};
    };
}

#endif
