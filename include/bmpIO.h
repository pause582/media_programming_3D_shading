#ifndef BMP_IO_H__
#define BMP_IO_H__

bool readBmpImage(
	const char *filename,
	int *width,
	int *height,
	int *nchannel,
	unsigned char **pixel
);

bool writeBmpImage(
	const char* filename,
	int width,
	int height,
	int nchannel,
	unsigned char *pixel
);

#endif
