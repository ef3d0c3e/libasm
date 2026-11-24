global ft_strdup

extern malloc
extern ft_strlen

ft_strdup:
	push rdi ; save input string, also align the stack for SysV
	call ft_strlen

	; call malloc, stack is still aligned
	mov rdi, rax
	add rdi, 1
	call malloc wrt ..plt
	pop rdi
	test rax, rax
	je .L1

	; rdi = input string
	; rax = output string
	xor rcx, rcx
.L2:
	mov dl, BYTE [rdi + rcx]
	mov BYTE [rax + rcx], dl
	test dl, dl
	je .L1
	add rcx, 1
	jmp .L2
.L1:
	ret
