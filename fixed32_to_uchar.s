	PRESERVE8
	AREA Multiply, CODE, READONLY
	EXPORT fixed32_to_uchar

fixed32_to_uchar
	ASR	r0, r0, #16
	BX	LR
	END