.data

.global source
source:
    .space 4096, 0


.text

.align 0x1000
.global gather_once
gather_once :
    lea source(%rip), %rsi
    
    vpxord %zmm1, %zmm1, %zmm1
    mov $1, %rdi
    kmovq %rdi, %k1
    vpgatherdd 0(%rsi, %zmm1, 1), %zmm2{%k1}

    //vmovups (%rsi), %zmm0
    //vmovups 64(%rsi), %zmm0
    //vmovups 128(%rsi), %zmm0

    //VMOVSHDUP (%rsi), %ymm0
    
    //VAESKEYGENASSIST $2, (%rsi), %xmm0


    ret