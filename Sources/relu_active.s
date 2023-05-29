	PRESERVE8
	AREA relu, CODE, READONLY
	EXPORT relu_active

relu_active
	PUSH	{r2-r11}

	LDM		r0, {r1-r10} ; Load 10 in once
	MOV		r11, #0
	CMP		r1, r11	; r1 < 0 ?
	MOVLT	r1, r11	; r1 = 0
	CMP		r2, r11
	MOVLT	r2, r11
	CMP		r3, r11
	MOVLT	r3, r11
	CMP		r4, r11
	MOVLT	r4, r11
	CMP		r5, r11
	MOVLT	r5, r11
	CMP		r6, r11
	MOVLT	r6, r11
	CMP		r7, r11
	MOVLT	r7, r11
	CMP		r8, r11
	MOVLT	r8, r11
	CMP		r9, r11
	MOVLT	r9, r11
	CMP		r10,r11
	MOVLT	r10,r11
	STM		r0!, {r1-r10} ; Save 10 in once

	POP		{r2-r11}
	BX		LR
	end
	