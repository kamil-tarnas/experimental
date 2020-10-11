global _start

section .data
   theHello db "Hello, jou!", 0x0a
   len equ $ - theHello

section .text
_start
   mov eax, 4 ; sys_write system call
   mov ebx, 1 ; standard out file descriptor
   mov ecx, theHello ; the message (bytes) to write to stdout
   mov edx, len ; calculated number of bytes to write
   int 0x80 ; execute system call
   mov eax, 1 ; set sys_exit system call
   mov ebx, 0 ; the exit status is 0
   int 0x80 ; execute system call
