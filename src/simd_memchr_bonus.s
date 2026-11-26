global ft_simd_memchr

; memchr using SSE2, 16 bytes per comparison
;
; xmm0 = c broadcast to all 16 bytes
; rax = current aligned block from rdi
; rdx = bytes of s remaining from rax (after the first block)
; r8d = match bitmask (bit i set <=> byte i of the block == c)
ft_simd_memchr:
	test rdx, rdx
	jz .null

	; broadcast searched bytes to all 16 lanes of xmm0
	movd xmm0, esi
	punpcklbw xmm0, xmm0 ; byte to word
	punpcklwd xmm0, xmm0 ; word to dword
	pshufd xmm0, xmm0, 0 ; dword to all 4 dwords

	; manually search on the first block because it may not be aligned to 16-bytes
	mov rcx, rdi
	and rcx, 15 ; offset of s in its block
	mov rax, rdi
	and rax, -0x10 ; align down to 16-bytes
	movdqa xmm1, [rax]
	pcmpeqb xmm1, xmm0 ; compare 16 bytes at once
	pmovmskb r8d, xmm1  ; one bit per byte
	shr r8d, cl ; drop bytes before s: bit 0 is now s[0]
	test r8d, r8d
	jz .miss
	bsf r8d, r8d ; index of first match, relative to s
	cmp r8, rdx
	jae .null ; match lies beyond s + n
	lea rax, [rdi + r8]
	ret

.miss:
	; the first block held (16 - offset) bytes of s
	mov r9d, 16
	sub r9, rcx
	cmp rdx, r9
	jbe .null
	sub rdx, r9 ; no overflow, even for n = SIZE_MAX

.loop:
	add rax, 16
	movdqa xmm1, [rax]
	pcmpeqb xmm1, xmm0 ; compare 16 bytes at once
	pmovmskb r8d, xmm1
	test r8d, r8d
	jnz .found
	cmp rdx, 16
	jbe .null
	sub rdx, 16
	jmp .loop

.found:
	bsf r8d, r8d
	cmp r8, rdx
	jae .null ; match lies beyond s + n
	add rax, r8
	ret

.null:
	xor eax, eax
	ret
