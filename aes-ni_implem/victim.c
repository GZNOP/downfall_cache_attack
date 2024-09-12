#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <immintrin.h>

float data[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
int main() {
    // attention ça s'inverse 
    // rempli index avec 4 int32.
    // du poids fort au poids faible
    __m128i index = _mm_set_epi32(7, 3, 1, 0);
    __m128 result;
    
    //while (1){
    result = _mm_i32gather_ps(data, index, 4);
    //}
    // Affichage du résultat
    float res_data[4];
    _mm_store_ps(res_data, result);
    printf("Result: %f, %f, %f, %f\n", res_data[0], res_data[1], res_data[2], res_data[3]);

    return 0;
}

