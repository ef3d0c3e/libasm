global ft_strlen

ft_strlen:
	mov rax, rdi
.L1:
	cmp BYTE [rax], 0
	je .L2
	add rax, 1
	jmp .L1
.L2:
	sub rax, rdi
	ret
