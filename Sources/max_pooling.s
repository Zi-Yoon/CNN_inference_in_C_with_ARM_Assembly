	PRESERVE8
	AREA pooling, CODE, READONLY
	EXPORT max_pooling

; input	: (after_relu)
max_pooling
; 1st loop
	PUSH 	{r2-r11}
	LDM		r0, {r2, r3}
	ADD		r0, r0, #8192
	LDM		r0, {r4, r5}
	CMP		r2, r3	; r2 ? r3 => r6
	MOVGT	r6, r2
	MOVLE	r6, r3
	CMP		r4, r5	; r4 ? r5 => r7
	MOVGT	r7, r4
	MOVLE	r7, r5
	CMP		r6, r7	; r6 ? r7 => r0
	MOVGT	r0, r6
	MOVLE	r0, r7
	ASR		r0, r0, #16
	POP 	{r2-r11}
	BX		LR
	END