/**
 * \file vector.cpp
 * \author Pompei2
 * \date 1 February 2010
 * \brief This file contains the implementation of the vector class. This class defines a 3-component vector.
 **/

#include "vector.h"

#include "math.h"
#include "stdlib.h"

static const float epsilon = 2e-7;

static int nearZero(float val) {
    return ((val > 0.0f && val < epsilon)
         || (val < 0.0f && val > -epsilon)
         || (val == 0.0f));
}

////////////////////////////////////////////
// Constructors and assignment operators. //
////////////////////////////////////////////

vector_t vector0()
{
    vector_t ret;
    ret.v = (float*)malloc(sizeof(float)*4);
    ret.v[0] = 0.0f;
    ret.v[1] = 0.0f;
    ret.v[2] = 0.0f;
    ret.v[3] = 1.0f;
    return ret;
}

vector_t vectorp(float in_v[3])
{
    vector_t ret;
    ret.v = (float*)malloc(sizeof(float)*4);
    ret.v[0] = in_v[0];
    ret.v[1] = in_v[1];
    ret.v[2] = in_v[2];
    ret.v[3] = 1.0f;
    return ret;
}

vector_t vector(float x, float y, float z)
{
    vector_t ret;
    ret.v = (float*)malloc(sizeof(float)*4);
    ret.v[0] = x;
    ret.v[1] = y;
    ret.v[2] = z;
    ret.v[3] = 1.0f;
    return ret;
}

vector_t vectorw(float x, float y, float z, float w)
{
    vector_t ret;
    ret.v = (float*)malloc(sizeof(float)*4);
    if(nearZero(w)) {
        ret.v[0] = x;
        ret.v[1] = y;
        ret.v[2] = z;
        ret.v[3] = 0.0f;
    } else {
        ret.v[0] = x/w;
        ret.v[1] = y/w;
        ret.v[2] = z/w;
        ret.v[3] = 1.0f;
    }
    return ret;
}

vector_t vectorvw(const vector_t v, float w)
{
    vector_t ret;
    ret.v = (float*)malloc(sizeof(float)*4);
    if(nearZero(w)) {
        ret.v[0] = vector_x(v);
        ret.v[1] = vector_y(v);
        ret.v[2] = vector_z(v);
        ret.v[3] = 0.0f;
    } else {
        ret.v[0] = vector_x(v)/w;
        ret.v[1] = vector_y(v)/w;
        ret.v[2] = vector_z(v)/w;
        ret.v[3] = 1.0f;
    }
    return ret;
}

vector_t vector_copy(const vector_t in_v)
{
    vector_t ret;
    ret.v = (float*)malloc(sizeof(float)*4);
    ret.v[0] = vector_x(in_v);
    ret.v[1] = vector_y(in_v);
    ret.v[2] = vector_z(in_v);
    ret.v[3] = 1.0f;
    return ret;
}

void vector_free(vector_t self)
{
    if(self.v) free(self.v);
}

///////////////////////////////////////
// Conversion methods and operators. //
///////////////////////////////////////

char *vector_to_s(const vector_t self, unsigned int in_iDecimalPlaces)
{
    /// TODO
    return NULL;
}

////////////////////////////////
// Basic vector calculations. //
////////////////////////////////

vector_t vector_neg(const vector_t self)
{
    return vector(-vector_x(self),
                  -vector_y(self),
                  -vector_z(self));
}

vector_t vector_add(const vector_t self, const vector_t other)
{
    return vector(vector_x(self) + vector_x(other),
                  vector_y(self) + vector_y(other),
                  vector_z(self) + vector_z(other));
}

vector_t vector_sub(const vector_t self, const vector_t other)
{
    return vector(vector_x(self) - vector_x(other),
                  vector_y(self) - vector_y(other),
                  vector_z(self) - vector_z(other));
}

vector_t vector_scaled(const vector_t self, float s)
{
    return vector(vector_x(self) * s,
                  vector_y(self) * s,
                  vector_z(self) * s);
}

void vector_inc(vector_t self, const vector_t other)
{
    vector_setx(self, vector_x(self) + vector_x(other));
    vector_sety(self, vector_y(self) + vector_y(other));
    vector_setz(self, vector_z(self) + vector_z(other));
}

void vector_dec(vector_t self, const vector_t other)
{
    vector_setx(self, vector_x(self) - vector_x(other));
    vector_sety(self, vector_y(self) - vector_y(other));
    vector_setz(self, vector_z(self) - vector_z(other));
}

void vector_scale(vector_t self, float s)
{
    vector_setx(self, vector_x(self) * s);
    vector_sety(self, vector_y(self) * s);
    vector_setz(self, vector_z(self) * s);
}

vector_t vector_cross(const vector_t self, const vector_t other)
{
    return vector(vector_y(self)*vector_z(other) - vector_z(self)*vector_y(other),
                  vector_z(self)*vector_x(other) - vector_x(self)*vector_z(other),
                  vector_x(self)*vector_y(other) - vector_y(self)*vector_x(other));
}

float vector_dot(const vector_t self, const vector_t other)
{
    return vector_x(self)*vector_x(other)
         + vector_y(self)*vector_y(other)
         + vector_z(self)*vector_z(other);
}

///////////////////////////////////////
// vector length related operations. //
///////////////////////////////////////

float vector_len(const vector_t self)
{
    return sqrt(vector_x(self)*vector_x(self)
              + vector_y(self)*vector_y(self)
              + vector_z(self)*vector_z(self));
}

void vector_normalize(vector_t self)
{
    float x = vector_x(self);
    float y = vector_y(self);
    float z = vector_z(self);

    // The zero-vector stays the zero-vector.
    if(nearZero(x) &&
       nearZero(y) &&
       nearZero(z) ) {
        vector_setx(self, 0.0f);
        vector_sety(self, 0.0f);
        vector_setz(self, 0.0f);
        return;
    }

    float l = vector_len(self);

    // Very little vectors will be stretched to a unit vector in one direction.
    if(nearZero(l)) {
        if((x >= y)
        && (x >= z)
        && (x >= 0.0f)) {
            vector_setx(self, 1.0f);
            vector_sety(self, 0.0f);
            vector_setz(self, 0.0f);
        } else if((x <= y)
               && (x <= z)
               && (x <= 0.0f)) {
            vector_setx(self, -1.0f);
            vector_sety(self,  0.0f);
            vector_setz(self,  0.0f);
        } else {
            if(y >= z
            && y >= 0.0f) {
                vector_setx(self, 0.0f);
                vector_sety(self, 1.0f);
                vector_setz(self, 0.0f);
            } else if(y <= z
                   && y <= 0.0f) {
                vector_setx(self,  0.0f);
                vector_sety(self, -1.0f);
                vector_setz(self,  0.0f);
            } else {
                vector_setx(self, 0.0f);
                vector_sety(self, 0.0f);
                if(z >= 0.0) {
                    vector_setz(self, 1.0f);
                } else {
                    vector_setz(self, -1.0f);
                }
            }
        }
    } else {
        // Follows the usual normalization rule.
        vector_scale(self, 1.0f/l);
    }
}

vector_t vector_normalized(const vector_t self)
{
    vector_t copy = vector_copy(self);
    vector_normalize(copy);
    return copy;
}

//////////////////////////////////////
// vector interpolation operations. //
//////////////////////////////////////

vector_t vector_lerp(const vector_t self, const vector_t other, float between)
{
    return vector_add(self, vector_scaled(vector_sub(other, self), between));
}

///////////////////////////////////
// Vector comparison operations. //
///////////////////////////////////
int vector_eq(const vector_t self, const vector_t other)
{
    vector_t diff = vector_sub(self, other);
    return nearZero(vector_x(diff)) && nearZero(vector_y(diff)) && nearZero(vector_z(diff));
};

////////////////////////////
// vector transformation. //
////////////////////////////
/*
vector_t operator*(const Base4x4Matrix& m, const Vector& v)
{
    return vector_t(m[0]*v[0] + m[4]*v[1] + m[8] *v[2] + m[12]*v[3],
                  m[1]*v[0] + m[5]*v[1] + m[9] *v[2] + m[13]*v[3],
                  m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]*v[3],
                  m[3]*v[0] + m[7]*v[1] + m[11]*v[2] + m[15]*v[3]);
}
*/
