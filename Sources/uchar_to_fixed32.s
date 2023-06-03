	PRESERVE8
	AREA Multiply, CODE, READONLY
	EXPORT uchar_to_fixed32

; FIXED_POINT_SCALE_FACTOR : 1 << 16
uchar_to_fixed32
	LSL	r0, r0, #16
	BX	LR
	END