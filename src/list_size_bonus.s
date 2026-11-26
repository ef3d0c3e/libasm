global ft_list_size

ft_list_size:
	xor eax, eax
.L1:
	test rdi, rdi
	jz .ret
	add eax, 1
	mov rdi, [rdi + 8] ; begin_list = begin_list->next
	jmp .L1
.ret:
	ret
