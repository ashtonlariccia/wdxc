.text
    .global _start
_start:
    xor %ebp, %ebp
    mov %rsp, %rdi
    and $-16, %rsp
    call __start_c
    hlt

    .section .note.GNU-stack, "", @progbits