	PRESERVE8
	AREA conv, CODE, READONLY
	EXPORT conv_mul

; input	: (gray_address, weight_address)
; gray	: (after_gray-2049), (after_gray-1), (after_gray+2047)
; weight: (weight[0][0]), (weight[1][0]), (weight[2][0])
conv_mul
; 1st loop
	PUSH {r2-r11}
	LDM	r0, {r2, r3, r4}
	LDM	r1!, {r5, r6, r7}

	ASR	r8, r2, #16
	MUL r10, r8, r5

	ASR	r8, r3, #16
	MUL r11, r8, r6
	ADD	r10, r10, r11

	ASR	r8, r4, #16
	MUL r11, r8, r7
	ADD	r10, r10, r11

	ADD r0, r0, #8192

; 2nd loop
	LDM	r0, {r2, r3, r4}
	LDM	r1!, {r5, r6, r7}

	ASR	r8, r2, #16
	MUL r11, r8, r5
	ADD	r10, r10, r11

	ASR	r8, r3, #16
	MUL r11, r8, r6
	ADD	r10, r10, r11

	ASR	r8, r4, #16
	MUL r11, r8, r7
	ADD	r10, r10, r11

	ADD r0, r0, #8192

; 3rd loop
	LDM	r0, {r2, r3, r4}
	LDM	r1, {r5, r6, r7}

	ASR	r8, r2, #16
	MUL r11, r8, r5
	ADD	r10, r10, r11

	ASR	r8, r3, #16
	MUL r11, r8, r6
	ADD	r10, r10, r11

	ASR	r8, r4, #16
	MUL r11, r8, r7
	ADD	r10, r10, r11

	MOV r0, r10
	POP {r2-r11}
	BX	LR
	END