	PRESERVE8
	AREA gray, CODE, READONLY
	EXPORT make_gray

; input	: (relocation_address)
; gray	: (after_reloc)
make_gray
	PUSH	{r2-r11}
	LDM		r0, {r1, r2, r3} ; R G B

	CMP		r1, r2	; if r1 > r2 ?
	MOVGT	r4, r1	; r4 = r1 (r1 > r2)
	MOVLE	r4, r2	; r4 = r2 (r1 < r2)
	CMP		r4, r3	; if r4 > r3 ?
	MOVLE	r4, r3	; r4 = r3 (r4 < r4)

	CMP		r1, r2	; if r1 < r2 ?
	MOVLT	r5, r1	; r5 = r1 (r1 < r2)
	MOVGE	r5, r2	; r5 = r2 (r1 > r2)
	CMP		r5, r3	; if r5 < r3 ?
	MOVGE	r5, r3	; 

	ADD		r1, r4, r5	; r1 = r4 + r5
	ASR		r0, r1, #1	; r1 / 2
	POP		{r2-r11}
	BX		LR
	end