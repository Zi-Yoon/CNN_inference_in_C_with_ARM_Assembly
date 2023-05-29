#include "../Headers/cnn.h"

int main()
{
	uchar_to_fixed32_and_relocation((fixed32_t*)0x41000000);
	zeropadd_and_grayscale((fixed32_t*)0x41000000, (fixed32_t*)0x43000000);
	convolution_3by3((fixed32_t*)0x43000000, (fixed32_t*)0x44000000);
	relu_activation((fixed32_t*)0x44000000);
	max_pooling_and_store_data((fixed32_t*)0x44000000, (unsigned char*)0x45000000);
	output_pixels((unsigned char*)0x45000000, 100, 100);
	output_pixels((unsigned char*)0x45000000, 100, 200);
	output_pixels((unsigned char*)0x45000000, 200, 100);
	output_pixels((unsigned char*)0x45000000, 200, 200);
	// additional test
	output_pixels((unsigned char*)0x45000000, 950, 516);
	_sys_exit(0);
}
