#include "cnn.h"

// IN : [0x40000000 ~ 0x405EEBFF]
// OUT: [0x41000000 ~ 0x427BAFFF]
void	uchar_to_fixed32_and_relocation(fixed32_t *after_relocation)
{
	unsigned char	*input_arr = (unsigned char*)0x40000000;
	fixed32_t		*after_reloc = after_relocation;

	// 1920 x 1080
	for (int x = 0; x < 1080; x++) 
	{
		for (int y = 0; y < 1920; y++)
		{
			*after_reloc = uchar_to_fixed32(*input_arr);
			after_reloc++;
			input_arr++;
			*after_reloc = uchar_to_fixed32(*input_arr);
			after_reloc++;
			input_arr++;
			*after_reloc = uchar_to_fixed32(*input_arr);
			after_reloc++;
			input_arr++;
		}
	}
}
