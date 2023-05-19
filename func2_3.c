#include "cnn.h"

fixed32_t	weight[][3] =	{{(int)( 0.125f*FIXED_POINT_SCALE_FACTOR), (int)(-0.14f*FIXED_POINT_SCALE_FACTOR) , (int)( 0.05f*FIXED_POINT_SCALE_FACTOR) }, 
							{ (int)(-0.14f*FIXED_POINT_SCALE_FACTOR) , (int)( 0.f*FIXED_POINT_SCALE_FACTOR)   , (int)(-0.075f*FIXED_POINT_SCALE_FACTOR)}, 
							{ (int)( 0.05f*FIXED_POINT_SCALE_FACTOR) , (int)(-0.075f*FIXED_POINT_SCALE_FACTOR), (int)( 0.125f*FIXED_POINT_SCALE_FACTOR)}};

//fixed32_t	weight[][3] =	{{(int)(8192), (int)(-9175) , (int)(3275) }, 
//							{ (int)(-9175) , (int)(0)   , (int)(-4915)}, 
//							{ (int)(3275) , (int)(-4915), (int)(8192)}};

// IN : [0x41000000 ~ 0x427BAFFF]
// OUT: [0x43000000 ~ 0x43873FFF]
void	zeropadd_and_grayscale(fixed32_t *after_relocation, fixed32_t *after_grayscale)
{
	fixed32_t	*after_reloc = after_relocation;
	fixed32_t	*after_gray = after_grayscale;
	
	// (1920+2) * (1080+2)
	for (int x = 0; x < 1080 + ZERO_PADDING*2; x++) 
	{
		for (int y = 0; y < 1920 + ZERO_PADDING*2; y++)
		{
			if (x == 0 || y == 0 || x == (1079 + ZERO_PADDING*2) || y == (1919 + ZERO_PADDING*2))
			{
				*after_gray = 0;
				after_gray++;
			}
			else
			{
				*after_gray = make_gray(after_reloc);
				after_gray++;
			}
		}
		// One cycle = 1922 * 4
		// 1922 + 126 = 2048
		after_gray = after_gray + 126;
	}
}

// IN : [0x43000000 ~ 0x43873FFF]
// OUT: [0x44000000 ~ 0x4486FFFF]
void	convolution_3by3(fixed32_t *after_grayscale, fixed32_t *after_convolution)
{
	fixed32_t	*after_gray = after_grayscale;
	fixed32_t	*after_conv = after_convolution;

	for(int x = 1; x <= 1080; x++)	// 1~1080
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
