/* TEST CODE 3 */

// 원본 코드
// void	convolution_3by3(fixed32_t *after_grayscale, fixed32_t *after_convolution)

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

#ifndef max
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

typedef		int32_t	fixed32_t;

fixed32_t	weight[][3] =	{{(int)( 0.125f*FIXED_POINT_SCALE_FACTOR), (int)(-0.14f*FIXED_POINT_SCALE_FACTOR) , (int)( 0.05f*FIXED_POINT_SCALE_FACTOR) }, 
							{ (int)(-0.14f*FIXED_POINT_SCALE_FACTOR) , (int)( 0.f*FIXED_POINT_SCALE_FACTOR)   , (int)(-0.075f*FIXED_POINT_SCALE_FACTOR)}, 
							{ (int)( 0.05f*FIXED_POINT_SCALE_FACTOR) , (int)(-0.075f*FIXED_POINT_SCALE_FACTOR), (int)( 0.125f*FIXED_POINT_SCALE_FACTOR)}};

// 3개를 conv해서 더하는 함수
fixed32_t conv_mul(fixed32_t* gray, fixed32_t* we)
{
	fixed32_t *test_gray = gray;
	fixed32_t *w = we;
	fixed32_t temp = (fixed32_t)0;
	temp += *test_gray * *w;
	test_gray++;
	w++;
	temp += *test_gray * *w;
	test_gray++;
	w++;
	temp += *test_gray * *w;
	return (fixed32_t)temp;
}

void	convolution_3by3(fixed32_t *test_after_grayscale, fixed32_t *test_after_convolution)
{
	fixed32_t	*after_gray = test_after_grayscale;
	fixed32_t	*after_conv = test_after_convolution;

	for(int x = 1; x < 4; x++)	// 1~1080
	{
		for(int y = 1; y <= 1920; y++)	// 1~1920
		{
			*after_conv = conv_mul(after_gray, weight[0]);
			after_gray++;
			after_conv++;
		}
		// One cycle = 1920 * 4
		// 1920 + 128 = 2048
		after_conv = after_conv + 128;
		after_gray = after_gray + 128;
	}
}

int main()
{
	fixed32_t* test_after_grayscale;
	fixed32_t* test_after_convolution;
	test_after_grayscale   = (fixed32_t*) malloc((2*2048)*4);
	test_after_convolution = (fixed32_t*) malloc((2*2048)*4);
	for (int i = 0; i < 2*2048; i++)
	{
		test_after_grayscale[i] = (fixed32_t)0;
		test_after_convolution[i] = (fixed32_t)0;
	}
	test_after_grayscale[0] = (fixed32_t)0x00790000;
	test_after_grayscale[1] = (fixed32_t)0x00ff0000;
	test_after_grayscale[2] = (fixed32_t)0x00000000;
	test_after_grayscale[3] = (fixed32_t)0x00ff0000;
	test_after_grayscale[4] = (fixed32_t)0x00790000;
	test_after_grayscale[5] = (fixed32_t)0x00000000;

	printf("test\n");
	convolution_3by3(test_after_grayscale, test_after_convolution);
	free(test_after_convolution);
	free(test_after_grayscale);
	return 0;
}
