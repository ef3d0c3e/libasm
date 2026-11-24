global ft_strcpy

ft_strcpy:
	mov rax, rdi
.L1:
	mov cl, BYTE [rsi]
	mov BYTE [rdi], cl
	test cl, cl
	je .L2
	add rdi, 1
	add rsi, 1
	jmp .L1
.L2:
	ret
