global ft_calloc

extern malloc

ft_calloc:
	; multiply size * count and check overflow
	mov rax, rdi
	mul rsi
	jc .L2
	; call malloc
	mov rdi, rax
	push rdi
	call malloc wrt ..plt
	pop rdi
	test rax,rax
	jz .L2

	; copy bytes
	xor rcx, rcx
.L1:
	cmp rcx, rdi
	je .L3
	mov [rax + rcx], BYTE 0
	add rcx, 1
	jmp .L1
.L2:
	xor rax, rax
.L3:
	ret
