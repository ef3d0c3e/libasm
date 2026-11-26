global ft_list_sort

; bubble sort implementation
;
; r12 = cmp
; r13 = swapped flag for the current pass
; r14 = head
; r15 = end: first node of the already-sorted tail
; rbx = current node
ft_list_sort:
	push rbx
	push r12
	push r13
	push r14
	push r15

	test rdi, rdi
	jz .done
	mov r14, [rdi]
	test r14, r14
	jz .done
	mov r12, rsi
	xor r15d, r15d

.outer:
	xor r13d, r13d
	mov rbx, r14
.inner:
	mov rax, [rbx + 8] ; next
	cmp rax, r15
	je .pass_end
	mov rdi, [rbx] ; cur->data
	mov rsi, [rax] ; next->data
	call r12
	mov rcx, [rbx + 8]
	test eax, eax
	jle .advance
	; cmp > 0: swap cur->data and next->data
	mov rdx, [rbx]
	mov r8, [rcx]
	mov [rbx], r8
	mov [rcx], rdx
	mov r13d, 1
.advance:
	mov rbx, rcx
	jmp .inner
.pass_end:
	mov r15, rbx ; rbx now holds its final value
	test r13d, r13d
	jnz .outer

.done:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	ret
