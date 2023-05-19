	PRESERVE8
	AREA gray, CODE, READONLY
	EXPORT make_gray

; input	: (relocation_address)
; gray	: (after_reloc)
make_gray
	PUSH	{r2-r11}
	LDM		r0, {r1, r2, r3} ; R G B

	CMP		r1, r2	; max = r4
	MOVGT	r4, r1
	MOVLE	r4, r2
	CMP		r4, r3
	MOVGT	r4, r4
	MOVLE	r4, r3

	CMP		r1, r2	; min = r5
	MOVLT	r5, r1
	MOVGE	r5, r2
	CMP		r5, r5
	MOVLT	r5, r4
	MOVGE	r5, r3

	ASR		r6, r4, #1	; r4 / 2
	MUL		r0, r6, r5	; r0 = r5 * r6
	POP		{r2-r11}
	BX		LR
	end