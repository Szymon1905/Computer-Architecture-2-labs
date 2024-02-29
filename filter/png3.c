#include <png.h>
#include <stdio.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>
#define ERROR                                                   \
	fprintf (stderr, "ERROR at %s:%d.\n", __FILE__, __LINE__) ;   \
	return -1 ;                                                   \


void filter(unsigned char * M, unsigned char * W, int width, int height)
{

};


void test3(unsigned char * M, unsigned char * W, int width, int height)
{

int L=0;

for (int d = 0; d < (width*height); d++){

//loades values
__m128i xmm_dane = _mm_setr_epi16(M[L + 0], M[L + 1], M[L + 2], M[L+width], M[L+width+2], M[L+(width*2)], M[L+(width*2)+1], M[L+(width*2)+2]);

//multiplication
__m128i xmm_values = _mm_mullo_epi16(xmm_dane, _mm_setr_epi16(-1, -1, 0, -1, 1, 0, 1, 1));

//array of unsigned 16 bit integers
int16_t values[8];

//multiplication values stored to array
_mm_storeu_si128((__m128i*)values, xmm_values);

int16_t to_scale = 0;


/sums values to scale later
for (int i = 0; i < 8; i++) {
        to_scale = to_scale + values[i];
}

//scaling
to_scale = (to_scale + 765) / 6;

//saves scaled value
W[L+width+1] = to_scale;

// next in loop
L++;
}

};


void test2(unsigned char * M, unsigned char * W, int width, int height)
{

int L=0;

for (int d = 0; d < (width*height); d++){

//loades values
__m128i xmm_dane = _mm_setr_epi16(M[L + 0], M[L + 1], M[L + 2], M[L+width], M[L+width+2], M[L+(width*2)], M[L+(width*2)+1], M[L+(width*2)+2]);

//multiplication
__m128i xmm_values = _mm_mullo_epi16(xmm_dane, _mm_setr_epi16(-1, -1, 0, -1, 1, 0, 1, 1));

//tablica unsigned 16 bit integerow
int16_t values[8];

//multiplication values stored to array
_mm_storeu_si128((__m128i*)values, xmm_values);

int16_t to_scale = 0;

values[7] = _mm_extract_epi16(xmm_values , 7);
values[6] = _mm_extract_epi16(xmm_values , 6);
values[5] = _mm_extract_epi16(xmm_values , 5);
values[4] = _mm_extract_epi16(xmm_values , 4);
values[3] = _mm_extract_epi16(xmm_values , 3);
values[2] = _mm_extract_epi16(xmm_values , 2);
values[1] = _mm_extract_epi16(xmm_values , 1);
values[0] = _mm_extract_epi16(xmm_values , 0);

//sums values to scale later
for (int i = 0; i < 8; i++) {
        to_scale = to_scale + values[i];
}

//scales
to_scale = (to_scale + 765) / 6;

//saves scaled value
W[L+width+1] = to_scale;

// next in loop
L++;
}

};


// my notes
//int16_t - unsigned 16 bit integer
//values[7] = _mm_extract_epi16(xmm_values , 7);
//_mm_storeu_si16((int*)values, xmm_values);

void test1()
{
int a[4] = {10, 20, 30, 40};
int b[4] = {5, 15, 25, 35};
int wynik[4];

// Wczytuje dane do rejestrów SIMD
__m128i xmm_a = _mm_loadu_si128((__m128i*)a);
__m128i xmm_b = _mm_loadu_si128((__m128i*)b);

// dodaje
__m128i xmm_result = _mm_add_epi32(xmm_a, xmm_b);

// ³aduje dane do wynik
_mm_storeu_si128((__m128i*)wynik, xmm_result);

printf("\n");

for (int i = 0; i < 4; i++) {
        printf("%d ", wynik[i]);
}

printf("\n");

};


int main (int argc, char ** argv)
{
	if (2 != argc)
	{
		printf ("\nUsage:\n\n%s file_name.png\n\n", argv[0]) ;

		return 0 ;
	}

	const char * file_name = argv [1] ;
	
	#define HEADER_SIZE (1)
	unsigned char header [HEADER_SIZE] ;

	FILE *fp = fopen (file_name, "rb");
	if (NULL == fp)
	{
		fprintf (stderr, "Can not open file \"%s\".\n", file_name) ;
		ERROR
	}

	if (fread (header, 1, HEADER_SIZE, fp) != HEADER_SIZE)
	{
		ERROR
	}

	if (0 != png_sig_cmp (header, 0, HEADER_SIZE))
	{
		ERROR
	}

	png_structp png_ptr = 
		png_create_read_struct
			(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
	if (NULL == png_ptr)
	{
		ERROR
	}

	png_infop info_ptr = png_create_info_struct (png_ptr);
	if (NULL == info_ptr)
	{
		png_destroy_read_struct (& png_ptr, NULL, NULL);

		ERROR
	}

	if (setjmp (png_jmpbuf (png_ptr))) 
	{
		png_destroy_read_struct (& png_ptr, & info_ptr, NULL);

		ERROR
	}

	png_init_io       (png_ptr, fp);
	png_set_sig_bytes (png_ptr, HEADER_SIZE);
	png_read_info     (png_ptr, info_ptr);

	png_uint_32  width, height;
	int  bit_depth, color_type;
	
	png_get_IHDR
	(
		png_ptr, info_ptr, 
		& width, & height, & bit_depth, & color_type,
		NULL, NULL, NULL
	);

	if (8 != bit_depth)
	{
		ERROR
	}
	if (0 != color_type)
	{
		ERROR
	}

	size_t size = width ;
	size *= height ;

	unsigned char * M = malloc (size) ;

	png_bytep ps [height] ;
	ps [0] = M ;
	for (unsigned i = 1 ; i < height ; i++)
	{
		ps [i] = ps [i-1] + width ;
	}
	png_set_rows (png_ptr, info_ptr, ps);
	png_read_image (png_ptr, ps) ;

	printf 
	(
		"Image %s loaded:\n"
		"\twidth      = %lu\n"
		"\theight     = %lu\n"
		"\tbit_depth  = %u\n"
		"\tcolor_type = %u\n"
		, file_name, width, height, bit_depth, color_type
	) ;

	unsigned char * W = malloc (size) ;

	//test1(M, W, width, height);

	//test2(M, W, width, height);

	test3(M, W, width, height);

	//filter(M, W, width, height);




	png_structp write_png_ptr =
		png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (NULL == write_png_ptr)
	{
		ERROR
	}

	for (unsigned i = 0 ; i < height ; i++)
	{
		ps [i] += W - M ;
	}
	png_set_rows (write_png_ptr, info_ptr, ps);

	FILE *fwp = fopen ("out.png", "wb");
	if (NULL == fwp)
	{
		ERROR
	}

	png_init_io   (write_png_ptr, fwp);
	png_write_png (write_png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
	fclose (fwp);

	return 0;
}
