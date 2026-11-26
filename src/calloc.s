global ft_calloc
extern malloc
extern __errno_location

ft_calloc:
	mov rax, rdi
	mul rsi                 ; rdx:rax = n * count
	jc .overflow
	push rax                ; save size (also aligns stack to 16)
	mov rdi, rax
	call malloc wrt ..plt
	pop rcx                 ; rcx = size, used as the rep counter
	test rax, rax
	jz .ret                 ; malloc already set errno
	mov rdi, rax            ; destination
	mov rdx, rax            ; keep the pointer to return
	xor eax, eax            ; al = 0
	rep stosb
	mov rax, rdx
.ret:
	ret

.overflow:
	sub rsp, 8              ; realign before the call
	call __errno_location wrt ..plt
	mov dword [rax], 12     ; ENOMEM
	add rsp, 8
	xor eax, eax
	ret
