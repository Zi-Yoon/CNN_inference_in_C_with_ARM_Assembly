/* TEST CODE 4 */

// 원본 코드
// void	relu_activation(fixed32_t *after_convolution)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h> 

# define IMAGE_SIZE 1920
# define COLOR_TYPE 3	// RGB = 3, RGBA = 4
# define ZERO_PADDING 1	// Zero padding area = 1
# define FILTER_SIZE 3	// Convolution Filter = 3 x 3 
# define FIXED_POINT_FRACTIONAL_BITS 16
# define FIXED_POINT_SCALE_FACTOR (1 << FIXED_POINT_FRACTIONAL_BITS)

typedef		int32_t	fixed32_t;

fixed32_t* relu_active(fixed32_t* after_conv)
{
	for (int i = 0; i < 10; i++)
	{
		if (*after_conv < 0)
			*after_conv = (fixed32_t)0;
		after_conv++;
	}
	return (fixed32_t*)after_conv;
}

void	relu_activation(fixed32_t *after_convolution)
{
	fixed32_t	*after_conv = after_convolution;

	for (int x = 0; x < 2; x++)	// 0~1079
	{
		for (int y = 0; y < 1920; y = y+10)	// 0~1919
		{
			after_conv = relu_active(after_conv); // 10 data in once
		}
		after_conv = (after_conv + 128);
	}
}

unsigned char max_pooling(fixed32_t *after_reluactivation)
{
	fixed32_t* after_relu = after_reluactivation;
	fixed32_t a, b;

	a = *after_relu;
	after_relu++;
	b = *after_relu;

	if (a > b)
		return (unsigned char)(a >> 16);
	else
		return (unsigned char)(b >> 16);
}

void	max_pooling_and_store_data(fixed32_t *after_relu_activation, unsigned char *after_pooling)
{
	fixed32_t		*after_relu = after_relu_activation;
	unsigned char	*after_pool = after_pooling;
	unsigned char	temp;

	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 960; y++)
		{
			temp =  max_pooling(after_relu);
			*after_pool = temp;
			after_pool++;
			*after_pool = temp;
			after_pool++;
			*after_pool = temp;
			after_pool++;
			after_relu = (after_relu + 2); // move 2 pixel
		}
		after_relu = (after_relu + 128); // 2048(1 line) + 128
	}
}

int main()
{
	fixed32_t* test_after_convolution;
	unsigned char* test_after_pooling;
	test_after_convolution = (fixed32_t*) malloc((2*2048)*4);
	test_after_pooling   = (unsigned char*) malloc((2*960*3)*1);
	for (int i = 0; i < 2*2048; i++)
	{
		test_after_convolution[i] = (fixed32_t)0;
	}
	for (int i = 0; i < 2*960*3; i++)
	{
		test_after_pooling[i] = (unsigned char)0;
	}
	test_after_convolution[0] = (fixed32_t)0x00100000;
	test_after_convolution[1] = (fixed32_t)0xffff0000;
	test_after_convolution[2] = (fixed32_t)0xff100000;
	test_after_convolution[3] = (fixed32_t)0x00200000;
	test_after_convolution[4] = (fixed32_t)0xff000000;
	test_after_convolution[5] = (fixed32_t)0xff010000;
	printf("test\n");
	relu_activation(test_after_convolution);
	max_pooling_and_store_data(test_after_convolution, test_after_pooling);
	free(test_after_convolution);
	free(test_after_pooling);
	return 0;
}
