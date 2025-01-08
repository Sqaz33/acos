#include <smmintrin.h>
#include <stdio.h>


void main() {
    const float A[] = {1, 2, 3, 4};
    const float B[] = {5, 6, 7, 8};

    __m128 a_vector = _mm_loadu_ps(A);
    __m128 b_vector = _mm_loadu_ps(B);
    __m128 res_vector = _mm_dp_ps(a_vector, b_vector, 0b11110001);

    float res = 0.0f;
    _mm_store_ss(&res, res_vector);
    printf("%f\n", res);
}