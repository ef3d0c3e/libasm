global ft_strcmp

ft_strcmp:
.L1:
	mov al, BYTE [rdi]
	mov cl, BYTE [rsi]
	cmp al, cl
	jne .L2
	test al, al
	je .L3
	add rdi, 1
	add rsi, 1
	jmp .L1
.L2:
	movzx eax, al
	movzx ecx, cl
	sub eax, ecx
	ret
.L3:
	xor eax,eax
	ret

