global ft_list_push_front
extern malloc

ft_list_push_front:
	push rdi ; begin_list
	push rsi ; data
	sub rsp, 8 ; align for sysv
	mov rdi, 16 ; sizeof(begin_list)
	call malloc wrt ..plt
	add rsp, 8
	pop rsi
	pop rdi
	test rax, rax
	jz .ret ; malloc failed, do nothing
	mov [rax], rsi ; new->data = data
	mov rcx, [rdi]
	mov [rax + 8], rcx ; new->next = *begin_list
	mov [rdi], rax ; *begin_list = new
.ret:
	ret
