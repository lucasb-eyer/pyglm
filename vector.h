/**
 * \file Vector.h
 * \author Pompei2
 * \date 1 February 2010
 * \brief This file contains the vector class definition. This class defines a 3-component vector.
 **/

#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float* v;
} vector_t;

vector_t vector0();
/// Creates a vector based on the contents of a float array.
/// \param in_v The three coordinates of the vector.
vector_t vectorp(float in_v[3]);
/// Creates a vector.
/// \param in_fX The value of the first component of the vector.
/// \param in_fY The value of the second component of the vector.
/// \param in_fZ The value of the third component of the vector.
vector_t vector(float in_fX, float in_fY, float in_fZ);
/// Creates a \e dehomogenized vector or a vector with the homogeneous
/// component (w) set to 0 using the arguments.
/// \param in_fX The value of the first component of the vector.
/// \param in_fY The value of the second component of the vector.
/// \param in_fZ The value of the third component of the vector.
/// \param in_fW The value of the homogeneous component of the vector.
/// \warning the value of the homogeneous component of the vector will
///          \e not be stored. Rather, the coordinate will be dehomogenized.
/// \note \e IF \a in_fW is nearly zero, it will be stored as 0.
vector_t vectorw(float in_fX, float in_fY, float in_fZ, float in_fW);
/// Creates a \e dehomogenized vector or a vector with the homogeneous
/// component (w) set to 0 using the arguments.
/// \param in_v The first three components to be copied.
/// \param in_fW The value of the homogeneous component of the vector.
/// \warning the value of the homogeneous component of the vector will
///          \e not be stored. Rather, the coordinate will be dehomogenized.
/// \note \e IF \a in_fW is nearly zero, it will be stored as 0.
vector_t vectorvw(const vector_t in_v, float in_fW);
/// Copies a vector.
/// \param in_v The vector to be copied.
vector_t vector_copy(const vector_t self);
/// Cleans up the vector's memory
void vector_free(vector_t self);

///////////////////////////////////////
// Conversion methods and operators. //
///////////////////////////////////////

/// \return A read-only array of three floats holding the values of the
///         three components of this vector.
inline const float *vector_array3f(const vector_t self) {return self.v;};
/// \return A read-only array of four floats holding the values of the
///         three components of this vector and the w component set to 1.0f.
inline const float *vector_array4f(const vector_t self) {return self.v;};

/// \return A string-representation of the vector.
/// \param in_iDecimalPlaces The amount of numbers to print behind the dot.
char* vector_to_s(const vector_t self, unsigned int in_iDecimalPlaces);

/////////////////////////////////////
// Accessors, getters and setters. //
/////////////////////////////////////

/// \return The X coordinate of the vector.
inline float vector_x(const vector_t self) { return self.v[0]; };
/// \return The Y coordinate of the vector.
inline float vector_y(const vector_t self) { return self.v[1]; };
/// \return The Z coordinate of the vector.
inline float vector_z(const vector_t self) { return self.v[2]; };
/// \param in_fX The new X coordinate of the vector.
inline void vector_setx(vector_t self, float in_fX) { self.v[0] = in_fX; };
/// \param in_fY The new Y coordinate of the vector.
inline void vector_sety(vector_t self, float in_fY) { self.v[1] = in_fY; };
/// \param in_fZ The new Z coordinate of the vector.
inline void vector_setz(vector_t self, float in_fZ) { self.v[2] = in_fZ; };

////////////////////////////////
// Basic Vector calculations. //
////////////////////////////////

/// \return A negated copy of this vector.
vector_t vector_neg(const vector_t self);
/// Adds two vectors.
/// \param other The vector to add to this vector.
/// \returns the vector resulting from this + \a other
vector_t vector_add(const vector_t self, const vector_t other);
/// Subtracts two vectors.
/// \param other The vector to subtract from this vector.
/// \returns the vector resulting from this - \a other
vector_t vector_sub(const vector_t self, const vector_t other);

/// Creates a scaled vector.
/// \param in_f The scaling factor.
/// \returns the vector resulting from self * \a in_f (this multiplied component-wise by f).
vector_t vector_scaled(const vector_t self, float in_f);

/// \param in_v The vector to add to this vector. The result is stored in this vector.
void vector_inc(vector_t self, const vector_t other);
/// \param in_v The vector to subtract from this vector. The result is stored in this vector.
void vector_dec(vector_t self, const vector_t other);
/// \param in_f The factor to scale this vector. The result is stored in this vector.
void vector_scale(vector_t self, float in_f);

/// Calculate the cross product of two vectors. Returns a vector perpendicular to both other vectors.
/// \param in_v The second vector of the cross product
/// \return The resulting vector from self CROSS \a other
vector_t vector_cross(const vector_t self, const vector_t other);
/// Calculate the dot product of two vectors. Returns a number related to the cosine of the angle of both vectors.
/// \param in_v The second vector of the dot product
/// \return The resulting vector from self DOT \a other
/// \note If both vectors are noralized, the return value is the cosine of their angle.
float vector_dot(const vector_t self, const vector_t other);

///////////////////////////////////////
// Vector length related operations. //
///////////////////////////////////////

/// \return The length of this vector, using the euclides norm.
float vector_len(const vector_t self);
/// Normalizes this vector: makes it have unit length.
void vector_normalize(vector_t self);
/// \return A normalized copy of this vector. It has unit length.
vector_t vector_normalized(const vector_t self);

//////////////////////////////////////
// Vector interpolation operations. //
//////////////////////////////////////

/// Linear interpolation between self and v2
/// \param v2 The other vector with which to interpolate.
/// \param between The time of interpolation. 0.0f results in self, 1.0f results in \a v2.
/// \return A vector resulting from the linear interpolation of self and \a v2, at time \a between
vector_t vector_lerp(const vector_t self, const vector_t v2, float between);

///////////////////////////////////
// Vector comparison operations. //
///////////////////////////////////

/// \return true if self is longer than \a other.
inline int vector_gt(const vector_t self, const vector_t other) {return vector_len(self) > vector_len(other);};
/// \return true if self is shorter than \a other.
inline int vector_lt(const vector_t self, const vector_t other) {return vector_len(self) < vector_len(other);};
/// \return true if self is longer or has the same length as \a other.
inline int vector_ge(const vector_t self, const vector_t other) {return vector_len(self) >= vector_len(other);};
/// \return true if self is shorter or has the same length as \a other.
inline int vector_le(const vector_t self, const vector_t other) {return vector_len(self) <= vector_len(other);};
/// \return true if self is \e nearly the same as \a other.
int vector_eq(const vector_t self, const vector_t other);
/// \return true if self is \e not \e nearly the same as \a other.
inline int vector_ne(const vector_t self, const vector_t other) {return !vector_eq(self, other);};

#endif // VECTOR_H

