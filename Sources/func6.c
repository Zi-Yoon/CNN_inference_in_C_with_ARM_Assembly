#include "../Headers/cnn.h"

// Max pooling 값에서 [x,y] 픽셀을 UART에 출력하는 함수
void	output_pixels(unsigned char *after_pooling, unsigned int x, unsigned int y)
{
	sendstr("(R : ");
	printDecimal((int)*(after_pooling + 960*y*3 + x*3    )); // r [x][y]
	sendstr(", G : ");
	printDecimal((int)*(after_pooling + 960*y*3 + x*3 + 1)); // g [x][y]
	sendstr(", B : ");
	printDecimal((int)*(after_pooling + 960*y*3 + x*3 + 2)); // b [x][y]
	sendstr(")\n");
}
