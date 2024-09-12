#include "bib.h"

void foo(void){
  int z;
  for (int i = 0; i < 500; i++){
    z *= i;
  }
}

lluint add(lluint a, lluint b){
  int z;
  for (int i = 0; i < 500; i++){
    z *= i;
  }
  return a + b;
}

lluint mult(lluint a, lluint b){
  int z;
  for (int i = 0; i < 500; i++){
    z *= i;
  }  
  return a * b;
}

lluint mod(lluint a, lluint b){
  int z;
  for (int i = 0; i < 500; i++){
    z *= i;
  }  
  return a % b;
}

lluint div(lluint a, lluint b){
  int z;
  for (int i = 0; i < 500; i++){
    z *= i;
  }
  return a / b;
}

lluint expo(lluint a, lluint b, lluint n){
  lluint res = 1;
  while (b > 0){
    if (b & 1){
      res = mod(mult(res, a), n);
    }
    a = mod(mult(a, a), n);
    b = div(b, 2);
  }
  return res;
}