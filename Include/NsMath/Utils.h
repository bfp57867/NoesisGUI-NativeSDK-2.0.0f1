////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__


#include <Noesis.h>
#include <NsMath/UtilsApi.h>

#include <float.h>


namespace Noesis
{
namespace Math
{
/// Tests if a number is a power of 2
inline NsBool IsPow2(NsSize x);

/// Gets nearest power of 2
inline NsUInt32 NearestPow2(NsUInt32 x);

/// Gets next power of 2
inline NsUInt32 NextPow2(NsUInt32 x);

/// Gets previous power of 2
inline NsUInt32 PrevPow2(NsUInt32 x);

inline NsBool IsOne(NsFloat32 val, NsFloat32 epsilon = 10.0f * FLT_EPSILON);
inline NsBool IsZero(NsFloat32 val, NsFloat32 epsilon = 10.0f * FLT_EPSILON);
inline NsBool AreClose(NsFloat32 a, NsFloat32 b, NsFloat32 epsilon = 10.0f * FLT_EPSILON);

/// Tests if a number is positive infinity
//@{
inline NsBool IsPositiveInfinity(NsFloat32 val);
inline NsBool IsPositiveInfinity(NsFloat64 val);
//@}

/// Tests if a number is negative infinity
//@{
inline NsBool IsNegativeInfinity(NsFloat32 val);
inline NsBool IsNegativeInfinity(NsFloat64 val);
//@}

/// Tests if a number is positive infinity or negative infinity
//@{
inline NsBool IsInfinity(NsFloat32 val);
inline NsBool IsInfinity(NsFloat64 val);
//@}

/// Tests if a number is NaN
//@{
inline NsBool IsNaN(NsFloat32 val);
inline NsBool IsNaN(NsFloat64 val);
//@}

/// Tests if a number is finite (not infinity and not Nan)
//@{
inline NsBool IsFinite(NsFloat32 val);
inline NsBool IsFinite(NsFloat64 val);
//@}

/// Float to Signed Int conversion with truncation towards zero
inline NsInt Trunc(NsFloat32 val);

/// Float to Signed Int conversion rounding to nearest integer
inline NsInt Round(NsFloat32 val);

/// Calculates the floor of a value
inline NsFloat32 Floor(NsFloat32 val);

/// Calculates the ceil of a value
inline NsFloat32 Ceil(NsFloat32 val);

/// Max returns the greater of its two arguments
template<class T> const T& Max(const T& a, const T& b);

/// Min returns the lesser of its two arguments
template<class T> const T& Min(const T& a, const T& b);

/// Clips a value between a minimum and a maximum
template<class T> T Clip(T val, T min, T max);

/// \return a linear interpolation between x and y. 0 <= t <= 1
inline NsFloat32 Lerp(NsFloat32 x, NsFloat32 y, NsFloat32 t);

/// \return 0 if x < edge and 1 if x >= edge
inline NsFloat32 Step(NsFloat32 edge, NsFloat32 x);

/// \return 0 if x <= edge0, returns 1 if x >= edge1, and performs a smooth Hermite interpolation
/// between 0 a 1 when edge0 < x < edge1
inline NsFloat32 SmoothStep(NsFloat32 edge0, NsFloat32 edge1, NsFloat32 x);

/// \return 0 if x <= edge0, returns 1 if edge1 < x < edge2, returns 0 if x >= edge3 and in the two
/// transitions a smooth Hermite interpolation is returned
inline NsFloat32 SmoothPulse(NsFloat32 edge0, NsFloat32 edge1, NsFloat32 edge2, NsFloat32 edge3,
    NsFloat32 x);
    
/// Logarithm base 2
//@{
inline NsUInt64 Log2(NsUInt64 v);
inline NsUInt32 Log2(NsUInt32 v);
//@}

/// Calculates the logarithm of a value in the given base
//@{
inline NsFloat32 LogBase(NsFloat32 val, NsFloat32 base);
inline NsFloat64 LogBase(NsFloat64 val, NsFloat64 base);
//@}

/// \return a random float between 0.0 and 1.0 (inclusive)
inline NsFloat32 FRand();

/// Standard math functions
//@{
inline NsFloat32 Pow(NsFloat32 base, NsFloat32 exponent);
inline NsFloat64 Pow(NsFloat64 base, NsFloat64 exponent);

inline NsFloat32 Sqr(NsFloat32 v);
inline NsFloat64 Sqr(NsFloat64 v);

inline NsFloat32 Sqrt(NsFloat32 v);
inline NsFloat64 Sqrt(NsFloat64 v);

inline NsFloat32 Sin(NsFloat32 v);
inline NsFloat64 Sin(NsFloat64 v);

inline NsFloat32 Cos(NsFloat32 v);
inline NsFloat64 Cos(NsFloat64 v);

inline NsFloat32 ASin(NsFloat32 v);
inline NsFloat64 ASin(NsFloat64 v);

inline NsFloat32 ACos(NsFloat32 v);
inline NsFloat64 ACos(NsFloat64 v);

inline NsFloat32 Tan(NsFloat32 v);
inline NsFloat64 Tan(NsFloat64 v);

inline NsFloat32 ATan2(NsFloat32 v0, NsFloat32 v1);
inline NsFloat64 ATan2(NsFloat64 v0, NsFloat64 v1);

inline NsInt Abs(NsInt v);
inline NsFloat32 Abs(NsFloat32 v);
inline NsFloat64 Abs(NsFloat64 v);
//@}

}
}

/// Inline Include
#include <NsMath/Utils.inl>

#endif
