/* TEST CODE 2 */

// 원본 코드
// void	zeropadd_and_grayscale(fixed32_t *after_relocation, fixed32_t *after_grayscale)

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

fixed32_t make_gray_test(fixed32_t a, fixed32_t b, fixed32_t c)
{
	return (fixed32_t)((min(min(a,b),c)+max(max(a,b),c))/2);
}

void	zeropadd_and_grayscale_test(fixed32_t *test_after_relocation, fixed32_t *test_after_grayscale)
{
	fixed32_t* test_gray = test_after_grayscale;
	fixed32_t a, b, c;
	// (1920+2) * (1080+2)
	for (int y = 0; y < 2; y++) 
	{
		for (int x = 0; x < 1920 + ZERO_PADDING*2; x++)
		{
			if (x == 0 || y == 0 || x == (1079 + ZERO_PADDING*2) || y == (1919 + ZERO_PADDING*2))
				*test_gray = (fixed32_t)0x11000011; // 제로 패딩된 부분 표시
			else
			{
				a = *test_after_relocation;
				test_after_relocation++;
				b = *test_after_relocation;
				test_after_relocation++;
				c = *test_after_relocation;
				test_after_relocation++;
				*test_gray = (fixed32_t)make_gray_test(a, b, c);
			}
			test_gray++;
		}
		// One cycle = 1922 * 4
		// 1922 + 126 = 2048
		test_gray = test_gray + 126;
	}
}

int main()
{
	fixed32_t* test_after_relocation;
	fixed32_t* test_after_grayscale;
	test_after_relocation = (fixed32_t*) malloc((2*1920*3)*4);
	test_after_grayscale  = (fixed32_t*) malloc((2*2048)*4);
	for (int i = 0; i < 2*1920*3; i++)
		test_after_relocation[i] = (fixed32_t)0;
	for (int i = 0; i < 2*2048; i++)
		test_after_grayscale[i] = (fixed32_t)0;
	test_after_relocation[0] = (fixed32_t)0x00420000;
	test_after_relocation[1] = (fixed32_t)0x00820000;
	test_after_relocation[2] = (fixed32_t)0x00B00000;
	test_after_relocation[3] = (fixed32_t)0x00420000;
	test_after_relocation[4] = (fixed32_t)0x00820000;
	test_after_relocation[5] = (fixed32_t)0x00B00000;
	printf("test\n");
	zeropadd_and_grayscale_test(test_after_relocation, test_after_grayscale);
	free(test_after_relocation);
	free(test_after_grayscale);
	return 0;
}