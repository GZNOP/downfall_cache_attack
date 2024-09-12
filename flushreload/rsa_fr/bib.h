#pragma once
#include <inttypes.h>

typedef __uint128_t lluint;

void foo(void);


lluint add(lluint a, lluint b);
lluint mult(lluint a, lluint b);
lluint expo(lluint a, lluint b, lluint n);
lluint mod(lluint a, lluint b);
lluint div(lluint a, lluint b);