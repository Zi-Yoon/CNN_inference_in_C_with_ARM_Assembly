#ifndef CNN_H
# define CNN_H
# define IMAGE_SIZE 1920
# define COLOR_TYPE 3	// RGB = 3, RGBA = 4
# define ZERO_PADDING 1	// Zero padding area = 1
# define FILTER_SIZE 3	// Convolution Filter = 3 x 3 
# define FIXED_POINT_FRACTIONAL_BITS 16
# define FIXED_POINT_SCALE_FACTOR (1 << FIXED_POINT_FRACTIONAL_BITS)

# include "base.h"

// 32bit fixed point Data type
typedef		int	fixed32_t;

// *** Global Variable ***

// IN : [0x40000000 ~ 0x405EEBFF]
// OUT: [0x41000000 ~ 0x427BAFFF]
// fixed32_t		*after_relocation = (fixed32_t*)0x41000000;

// IN : [0x41000000 ~ 0x427BAFFF]
// OUT: [0x43000000 ~ 0x43873FFF] Save after Grayscale & Zeropadding
// fixed32_t		*after_grayscale = (fixed32_t*)0x43000000;

// IN : [0x43000000 ~ 0x43873FFF]
// OUT: [0x44000000 ~ 0x4486FFFF] Save after Convolution
// fixed32_t		*after_convolution = (fixed32_t*)0x44000000;

// IN : [0x44000000 ~ 0x4486FFFF]
// OUT: [0x44000000 ~ 0x4486FFFF] Save after ReLU
// fixed32_t		*after_relu_activation = (fixed32_t*)0x44000000;

// IN : [0x44000000 ~ 0x4486FFFF]
// OUT: [0x45000000 ~ 0x4517BAFF] Save after Max Pooling
// unsigned char	*after_pooling = (unsigned char*)0x45000000;

// float weight
// [[0.125, -0.14 ,  0.05], 
// [-0.14 ,  0    , -0.075], 
// [ 0.05 , -0.075,  0.125]]

void	uchar_to_fixed32_and_relocation(fixed32_t *after_relocation);
void	zeropadd_and_grayscale(fixed32_t *after_relocation, fixed32_t *after_grayscale);
void	convolution_3by3(fixed32_t *after_grayscale, fixed32_t *after_convolution);
void	relu_activation(fixed32_t *after_convolution);
void	max_pooling_and_store_data(fixed32_t *after_relu_activation, unsigned char *after_pooling);
void	output_pixels(unsigned char *after_pooling, unsigned int x, unsigned int y);

// Assembly
extern fixed32_t		uchar_to_fixed32(unsigned char x);
extern fixed32_t		make_gray(fixed32_t* reloc_addr);
extern fixed32_t		conv_mul(fixed32_t* gray_addr, fixed32_t* weight_addr);
extern fixed32_t*		relu_active(fixed32_t* after_conv);
extern unsigned char	max_pooling(fixed32_t* after_relu);
// extern unsigned char	fixed32_to_uchar(fixed32_t x); = (ASR r0, r0, #16)

/* == Usefull for Keil == */
// load florence.hex
// save .hex 0x45000000, 0x4517BAFF
// 0x40000000, 0xffffffff
// 
#endif
