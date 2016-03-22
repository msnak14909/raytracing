#ifndef __RAY_MATH_TOOLKIT_H
#define __RAY_MATH_TOOLKIT_H

#include <math.h>
#include <stdio.h>
#include <assert.h>
//#include <immintrin.h>

static inline __attribute__((always_inline))
void normalize(double *v)
{
    double d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    assert(d != 0.0 && "Error calculating normal");

    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
}

static inline __attribute__((always_inline))
double length(const double *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

static inline __attribute__((always_inline))
void add_vector(const double *a, const double *b, double *out)
{
    //__m128d an = __extension__ (__m128d) { a[0], a[1]};
    //__m128d bn = __extension__ (__m128d) { b[0], b[1]};
    //__m128d num = (__m128d) ((__v2df)an + (__v2df)bn);
    //*(__m128d*)out = num;
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    /*
      for (int i = 0; i < 3; i++)
      out[i] = a[i] + b[i];
    */
}

static inline __attribute__((always_inline))
void subtract_vector(const double *a, const double *b, double *out)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    /*
      for (int i = 0; i < 3; i++)
      out[i] = a[i] - b[i];*/
}

static inline __attribute__((always_inline))
void multiply_vectors(const double *a, const double *b, double *out)
{
    //__m128d an = __extension__ (__m128d) { a[0], a[1]};
    //__m128d bn = __extension__ (__m128d) { b[0], b[1]};
    //__m128d num = (__m128d) ((__v2df)an * (__v2df)bn);
    //*(__m128d*)out = num;
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
    /*
      for (int i = 0; i < 3; i++)
      out[i] = a[i] * b[i];*/
}

static inline __attribute__((always_inline))
void multiply_vector(const double *a, double b, double *out)
{
    out[0]=a[0]*b;
    out[1]=a[1]*b;
    out[2]=a[2]*b;
    /*
      for (int i = 0; i < 3; i++)
      out[i] = a[i] * b;*/
}

static inline __attribute__((always_inline))
void cross_product(const double *v1, const double *v2, double *out)
{
    /*
    register __m128d a1 = __extension__ (__m128d) { v1[1], v1[2]};
    register __m128d b1 = __extension__ (__m128d) { v2[2], v2[1]};
    register __m128d a2 = __extension__ (__m128d) { v1[2], v1[0]};
    register __m128d b2 = __extension__ (__m128d) { v2[0], v2[2]};
    register __m128d a3 = __extension__ (__m128d) { v1[0], v1[1]};
    register __m128d b3 = __extension__ (__m128d) { v2[1], v2[0]};
    
    
    register __m128d num1 = (__m128d) ((__v2df)a1 * (__v2df)b1);
    register __m128d num2 = (__m128d) ((__v2df)a2 * (__v2df)b2);
    register __m128d num3 = (__m128d) ((__v2df)a3 * (__v2df)b3);
    
    out[0] = num1[0] - num1[1];
    out[1] = num2[0] - num2[1];
    out[2] = num3[0] - num3[1];*/
    out[0] = v1[1] * v2[2] - v1[2] * v2[1];
    out[1] = v1[2] * v2[0] - v1[0] * v2[2];
    out[2] = v1[0] * v2[1] - v1[1] * v2[0];
    
}

static inline __attribute__((always_inline))
double dot_product(const double *v1, const double *v2)
{
    //__m128d an = __extension__ (__m128d) { v1[0], v1[1]};
    //__m128d bn = __extension__ (__m128d) { v2[0], v2[1]};
    //__m128d num = (__m128d) ((__v2df)an * (__v2df)bn);
    //*(__m128d*)out = num;
    //return num[0] + num[1] + v1[2]*v2[2];
    return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];

    /*
      for (int i = 0; i < 3; i++)
      dp += v1[i] * v2[i];
      return dp;*/
}

static inline __attribute__((always_inline))
void scalar_triple_product(const double *u, const double *v, const double *w,
                           double *out)
{
    cross_product(v, w, out);
    multiply_vectors(u, out, out);
}

static inline __attribute__((always_inline))
double scalar_triple(const double *u, const double *v, const double *w)
{
    double tmp[3];
    cross_product(w, u, tmp);
    return dot_product(v, tmp);
}

#endif
