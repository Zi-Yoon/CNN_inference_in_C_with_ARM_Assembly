#include "../Headers/cnn.h"

// IN : [0x44000000 ~ 0x4486FFFF]
// OUT: [0x44000000 ~ 0x4486FFFF] Save after ReLU
void	relu_activation(fixed32_t *after_convolution)
{
	fixed32_t	*after_conv = after_convolution;

	for (int x = 0; x < 1080; x++)	// 0~1079
	{
		for (int y = 0; y < 1920; y = y+10)	// 0~1919
		{
			after_conv = relu_active(after_conv); // 10 data in once
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
			temp =  max_pooling(after_relu);
			// temp = temp * 5; // for visualize, remove before submit
			*after_pool = temp;
			after_pool++;
			*after_pool = temp;
			after_pool++;
			*after_pool = temp;
			after_pool++;
			after_relu = (after_relu + 2); // move 2 pixel
		}
		after_relu = (after_relu + 2176); // 2048(1 line) + 128
	}
}
