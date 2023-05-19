	PRESERVE8
	AREA Multiply, CODE, READONLY
	EXPORT uchar_to_fixed32

; FIXED_POINT_SCALE_FACTOR : 1 << 16 = 65536
uchar_to_fixed32
	MOV	r1, #65536
	MUL	r2, r0, r1
	MOV	r0, r2
	BX	LR
	END