/**
 * \file Vector.h
 * \author Pompei2
 * \date 1 February 2010
 * \brief This file contains the vector class definition. This class defines a 3-component vector.
 **/

#pragma once

#include "Utilities/Math.h"

#ifdef __cplusplus

#include <string>

namespace PyGlMath {
    class Vector;
}

///////////////////////////
// Vector serialization. //
///////////////////////////
/// Serializes a vector to a file. Use it like this: f << v1 << v2 << etc.
/// \param f The file to write the vector to.
/// \param v The vector to write to the file.
/// \return a reference to the file to allow chaining.
template<class T>
T& operator<<(T& f, const PyGlMath::Vector& v);
/// Extracts a vector from a file. Use it like this: f >> v1 >> v2 >> etc.
/// \param f The file to read the vector from.
/// \param v The vector to write the read values to.
/// \return a reference to the file to allow chaining.
template<class T>
T& operator>>(T& f, PyGlMath::Vector& v);

namespace PyGlMath {
    class Base4x4Matrix;

/// This class represents a point in 3D space given in homogeneous coordinates.\n
/// Homogeneous coordinates are, briefly said, a 4-component vector (x,y,z,w)
/// where w is some very clever coordinate. When w is 0, (x,y,z,w) represent
/// only the direction (x,y,z) in space, but no specific point on it.
/// But when w is 1, it represents the specific point at coordinate (x,y,z).\n
/// Some operations, like multiplication with a matrix (linear transformation)
/// make the w component become something else than 1. Those operations are
/// more than just affine transformations. Perspective projections are an
/// example. After such a transformation, the coordinate needs to be
/// de-homogenized. De-homogenisation is the act of dividing all components by
/// w, thus making it become the special point again: (x/w,y/w,z/w,1).\n
/// This class currently only always holds the de-homogenised version of the
/// coordinates. You may fiddle with it using the operator[] but it is not
/// guaranteed to produce the expected results. More support for de/homogenisation
/// will be added when needed.
class Vector {
public:
    ////////////////////////////////////////////
    // Constructors and assignment operators. //
    ////////////////////////////////////////////

    /// Creates a vector with all components set to 0 except w set to 1.
    Vector();
    /// Creates a vector based on the contents of a float array.
    /// \param in_v The three coordinates of the vector.
    Vector(float in_v[3]);
    /// Creates a vector.
    /// \param in_fX The value of the first component of the vector.
    /// \param in_fY The value of the second component of the vector.
    /// \param in_fZ The value of the third component of the vector.
    Vector(float in_fX, float in_fY, float in_fZ);
    /// Creates a \e dehomogenized vector or a vector with the homogeneous
    /// component (w) set to 0 using the arguments.
    /// \param in_fX The value of the first component of the vector.
    /// \param in_fY The value of the second component of the vector.
    /// \param in_fZ The value of the third component of the vector.
    /// \param in_fW The value of the homogeneous component of the vector.
    /// \warning the value of the homogeneous component of the vector will
    ///          \e not be stored. Rather, the coordinate will be dehomogenized.
    /// \note \e IF \a in_fW is nearly zero, it will be stored as 0.
    Vector(float in_fX, float in_fY, float in_fZ, float in_fW);
    /// Creates a \e dehomogenized vector or a vector with the homogeneous
    /// component (w) set to 0 using the arguments.
    /// \param in_v The first three components to be copied.
    /// \param in_fW The value of the homogeneous component of the vector.
    /// \warning the value of the homogeneous component of the vector will
    ///          \e not be stored. Rather, the coordinate will be dehomogenized.
    /// \note \e IF \a in_fW is nearly zero, it will be stored as 0.
    Vector(const Vector& in_v, float in_fW);
    /// Copies a vector.
    /// \param in_v The vector to be copied.
    Vector(const Vector& in_v);
    /// Copies a vector.
    /// \param in_v The vector to be copied.
    /// \return a const reference to myself that might be used as a rvalue.
    const Vector& operator=(const Vector& in_v);
    /// Moves a vector.
    /// \param in_v The vector to be moved.
    Vector(Vector&& in_v);
    /// Moves a vector.
    /// \param in_v The vector to be moved.
    /// \return a const reference to myself that might be used as a rvalue.
    const Vector& operator=(Vector&& in_v);
    ~Vector();

    ///////////////////////////////////////
    // Conversion methods and operators. //
    ///////////////////////////////////////

    /// \return A read-only array of three floats holding the values of the
    ///         three components of this vector.
    inline const float *array3f() const {return m_v;};
    /// \return A read-only array of four floats holding the values of the
    ///         three components of this vector and the w component set to 1.0f.
    inline const float *array4f() const {return m_v;};

    /// \return A string-representation of the vector.
    /// \param in_iDecimalPlaces The amount of numbers to print behind the dot.
    std::string to_s(unsigned int in_iDecimalPlaces = 2) const;
    /// \return A string-representation of the vector.
    operator std::string() const;

    /////////////////////////////////////
    // Accessors, getters and setters. //
    /////////////////////////////////////

    /// \return The X coordinate of the vector.
    inline float x() const { return m_v[0]; };
    /// \return The Y coordinate of the vector.
    inline float y() const { return m_v[1]; };
    /// \return The Z coordinate of the vector.
    inline float z() const { return m_v[2]; };
    /// \param in_fX The new X coordinate of the vector.
    inline Vector& x(float in_fX) { m_v[0] = in_fX; return *this; };
    /// \param in_fY The new Y coordinate of the vector.
    inline Vector& y(float in_fY) { m_v[1] = in_fY; return *this; };
    /// \param in_fZ The new Z coordinate of the vector.
    inline Vector& z(float in_fZ) { m_v[2] = in_fZ; return *this; };

    /// Access the elements of this vector.
    /// \param idx The index of the element of this vector. This may only be a
    ///            value between 0 and 3.
    /// \throws NotExistException if \a idx is >3.
    float& operator[](unsigned int idx);
    /// Access the elements of this vector in read-only.
    /// \param idx The index of the element of this vector. This may only be a
    ///            value between 0 and 3.
    /// \throws NotExistException if \a idx is >3.
    float operator[](unsigned int idx) const;

    ////////////////////////////////
    // Basic Vector calculations. //
    ////////////////////////////////

    /// \return A negated copy of this vector.
    Vector operator -() const;
    /// Adds two vectors.
    /// \param in_v The vector to add to this vector.
    /// \returns the vector resulting from this + \a in_v
    Vector operator +(const Vector& in_v) const;
    /// Subtracts two vectors.
    /// \param in_v The vector to subtract from this vector.
    /// \returns the vector resulting from this - \a in_v
    Vector operator -(const Vector& in_v) const;

    /// Creates a scaled vector.
    /// \param in_f The scaling factor.
    /// \returns the vector resulting from this * \a in_f (this multiplied component-wise by f).
    Vector operator *(float in_f) const;

    /// \param in_v The vector to add to this vector. The result is stored in this vector.
    void operator +=(const Vector& in_v);
    /// \param in_v The vector to subtract from this vector. The result is stored in this vector.
    void operator -=(const Vector& in_v);
    /// \param in_f The factor to scale this vector. The result is stored in this vector.
    void operator *=(float in_f);

    /// Calculate the cross product of two vectors. Returns a vector perpendicular to both other vectors.
    /// \param in_v The second vector of the cross product
    /// \return The resulting vector from *this CROSS \a in_v
    Vector cross(const Vector& in_v) const;
    /// Calculate the dot product of two vectors. Returns a number related to the cosine of the angle of both vectors.
    /// \param in_v The second vector of the dot product
    /// \return The resulting vector from *this DOT \a in_v
    /// \note If both vectors are noralized, the return value is the cosine of their angle.
    float dot(const Vector& in_v) const;

    ///////////////////////////////////////
    // Vector length related operations. //
    ///////////////////////////////////////

    /// \return The length of this vector, using the euclides norm.
    float len() const;
    /// Normalizes this vector: makes it have unit length.
    /// \return a reference to *this
    Vector& normalize();
    /// \return A normalized copy of this vector. It has unit length.
    Vector normalized() const;

    //////////////////////////////////////
    // Vector interpolation operations. //
    //////////////////////////////////////

    /// Linear interpolation between this and v2
    /// \param v2 The other vector with which to interpolate.
    /// \param between The time of interpolation. 0.0f results in this, 1.0f results in \a v2.
    /// \return A vector resulting from the linear interpolation of this and \a v2, at time \a between
    Vector lerp(const Vector& v2, float between) const;

    ///////////////////////////////////
    // Vector comparison operations. //
    ///////////////////////////////////

    /// \return true if this is longer than \a in_v.
    inline bool operator >(const Vector& in_v) const {return this->len() > in_v.len();};
    /// \return true if this is shorter than \a in_v.
    inline bool operator <(const Vector& in_v) const {return this->len() < in_v.len();};
    /// \return true if this is longer or has the same length as \a in_v.
    inline bool operator >=(const Vector& in_v) const {return this->len() >= in_v.len();};
    /// \return true if this is shorter or has the same length as \a in_v.
    inline bool operator <=(const Vector& in_v) const {return this->len() <= in_v.len();};
    /// \return true if this is \e nearly the same as \a in_v.
    inline bool operator ==(const Vector& in_v) const {
        Vector diff = *this - in_v;
        return nearZero(diff.x()) && nearZero(diff.y()) && nearZero(diff.z());
    };
    /// \return true if this is \e not \e nearly the same as \a in_v.
    inline bool operator !=(const Vector& in_v) const {return !this->operator==(in_v);};

private:
    /// The three components of the vector.
    /// \note this array actually holds four components in case it needs to be
    ///       given to a function that requires that. The fourth component is
    ///       always one though.
    float* m_v;
};

///////////////////////////
// Non-member operators. //
///////////////////////////

/// Transform a vector \a v by a matrix \a m. If necessary, the vector will be
/// de-homogenized right after the operation.
/// \param m The matrix describing the transformation.
/// \param v The vector to be transformed.
/// \return the transformed (de-homogenized) vector.
Vector operator*(const Base4x4Matrix& m, const Vector& v);

/// Creates a scaled vector.
/// \param in_f The scaling factor.
/// \param in_v The vector to be scaled.
/// \returns the vector resulting from \a in_v * \a in_f (this multiplied component-wise by f).
inline Vector operator *(float in_f, const Vector& in_v) {
    return in_v*in_f;
};

#include "Vector.inl"

} // namespace PyGlMath

