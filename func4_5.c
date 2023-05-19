#include "cnn.h"

unsigned char	max_pixel_to_8bit(fixed32_t a, fixed32_t b, fixed32_t c, fixed32_t d)
{
	if (a >= b && a >= c && a >= d)
		return fixed32_to_uchar(a);
	else if (b >= a && b >= c && b >= d)
		return fixed32_to_uchar(b);
	else if (c >= a && c >= b && c >= d)
		return fixed32_to_uchar(c);
	else
		return fixed32_to_uchar(d);
}

// IN : [0x44000000 ~ 0x4486FFFF]
// OUT: [0x44000000 ~ 0x4486FFFF] Save after ReLU
void	relu_activation(fixed32_t *after_convolution)
{
	fixed32_t	*after_conv = after_convolution;

	for (int x = 0; x < 1080; x++)	// 0~1079
	{
		for (int y = 0; y < 1920; y = y+4)	// 0~1919
		{
			if (*after_conv < 0)
				*after_conv = 0;
			after_conv++;
			if (*after_conv < 0)
				*after_conv = 0;
			after_conv++;
			if (*after_conv < 0)
				*after_conv = 0;
			after_conv++;
			if (*after_conv < 0)
				*after_conv = 0;
			after_conv++;
		}
		after_conv = (after_conv + 128);
	}
}

// IN : [0x44000000 ~ 0x4486FFFF]
// OUT: [0x45000000 ~ 0x4517BAFF] Save after Max Pooling
void	max_pooling_and_store_data(fixed32_t *after_relu_activation, unsigned char *after_pooling)
{
	fixed32_t		*after_relu = after_relu_activation;
	unsigned char	*after_pool = after_pooling;
	unsigned char	temp;

	for (int x = 0; x < 540; x++)
	{
		for (int y = 0; y < 960; y++)
		{
			temp =  max_pixel_to_8bit(*after_relu, *(after_relu+1), *(after_relu+2048), *(after_relu+2049));
			temp = temp * 5; /* ==remove this code when submit== */
			*after_pool = temp;
			after_pool++;
			*after_pool = temp;
			after_pool++;
			*after_pool = temp;
			after_pool++;
			after_relu = (after_relu + 2); // move 2 pixel
		}
		after_relu = (after_relu + 2176); // 2048 + 128
	}
}
