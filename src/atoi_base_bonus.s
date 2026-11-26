global ft_atoi_base

; int ft_atoi_base(const char *str, const char *base)
;   rdi = str, rsi = base
;   rdx = base length, r8d = negative flag, r9d = result
ft_atoi_base:
	; validate base and compute its length
	xor edx, edx
.validate:
	movzx eax, byte [rsi + rdx]
	test al, al
	jz .validate3
	cmp al, '+'
	je .zero
	cmp al, '-'
	je .zero
	cmp al, ' '
	je .zero
	lea ecx, [rax - 9] ; '\t' '\n' '\v' '\f' '\r' are 9..13
	cmp ecx, 4
	jbe .zero
	; reject duplicates: compare with base[0 .. rdx)
	xor ecx, ecx
.validate1:
	cmp rcx, rdx
	je .validate2
	cmp al, [rsi + rcx]
	je .zero
	add rcx, 1
	jmp .validate1
.validate2:
	add rdx, 1
	jmp .validate
.validate3:
	cmp rdx, 2
	jb .zero

	; skip leading whitespace
.ws:
	movzx eax, byte [rdi]
	cmp al, ' '
	je .ws1
	lea ecx, [rax - 9]
	cmp ecx, 4
	ja .sign
.ws1:
	add rdi, 1
	jmp .ws

	; optional single sign
.sign:
	xor r8d, r8d
	cmp al, '-'
	jne .plus
	mov r8d, 1
	add rdi, 1
	jmp .digits
.plus:
	cmp al, '+'
	jne .digits
	add rdi, 1

	; accumulate digits until a char not in base
.digits:
	xor r9d, r9d
.digits1:
	movzx eax, byte [rdi]
	test al, al
	jz .digits2
	xor ecx, ecx
.find:
	cmp rcx, rdx
	je .digits2
	cmp al, [rsi + rcx]
	je .found
	add rcx,1
	jmp .find
.found:
	imul r9d, edx ; result = result * len + digit (wraps like int)
	add r9d, ecx
	add rdi,1
	jmp .digits1

.digits2:
	mov eax, r9d
	test r8d, r8d
	jz .ret
	neg eax
.ret:
	ret

.zero:
	xor eax, eax
	ret
