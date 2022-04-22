/*
 * SatCamImage.h - Library for using the data stream from SatCam to build into a JPEG file with compression
 * Created by person, month date, 2022
*/

/* 
 * Error codes:
 * 
*/

/* Define everything if it is not already defined */
#ifndef SatCamImage_h
#define SatCamImage_h

/* Include necessary libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

/* Define data types for ease of use */
#define BYTE unsigned char
#define SBYTE unsigned char 
#define DCT signed short

/* Define variables to use during data reading */
/*
 * Big resolution: 21MP
 * Mid resolution: Full HD
*/
#define BIGXRES 5344
#define BIGYRES 4016
#define BIGRESLEN 21461504

#define MIDXRES 1920
#define MIDYRES 1080
#define MIDRESLEN 2073600

#define SMALLXRES 1280
#define SMALLYRES 720
#define SMALLRESLEN 921600

#define TESTXRES 8
#define TESTYRES 8
#define TESTRESLEN 64

#define TEST2XRES 16
#define TEST2YRES 16
#define TEST2RESLEN 256

#define TEST3XRES 32
#define TEST3YRES 16
#define TEST3RESLEN 512

/* Enum to pass into functions */
enum RESMODE 
{
    BIG = 0,
    MID = 1,
    SMALL = 2,
    TEST = 3,
    TEST2 = 4,
    TESTWIDE = 5
} resMode;

/* Define buffers to use for compression */
// extern BYTE huffmanBuffer[]; // Buffer for huffman coefficients

/* Struct defined to hold YCbCr values */
typedef struct
{
    SBYTE Y;
    SBYTE Cb;
    SBYTE Cr;
} YCBCR;

/* Struct defined to hold DCT values */
typedef struct
{
    DCT Y;
    DCT Cb;
    DCT Cr;
} DCTPIXEL;

/* Define buffers to use for compression */
// YCBCR yccBuffer[BIGXRES][BIGYRES];
// DCT dctYBuffer[BIGXRES][BIGYRES];
// DCT dctCbBuffer[BIGXRES][BIGYRES];
// DCT dctCrBuffer[BIGXRES][BIGYRES];
YCBCR yccBuffer[MIDXRES][MIDYRES];
// DCT dctYBuffer[MIDXRES][MIDYRES];
// DCT dctCbBuffer[MIDXRES][MIDYRES];
// DCT dctCrBuffer[MIDXRES][MIDYRES];
DCTPIXEL dctBuffer[MIDXRES][MIDYRES];
// DCT zzBuffer[MIDXRES*MIDYRES];

/* Define buffers to use for compression */
// BYTE yccBuffer[BIGRESLEN*3];
// DCT dctYBuffer[BIGRESLEN];
// DCT dctCbBuffer[BIGRESLEN];
// DCT dctCrBuffer[BIGRESLEN];

/* Markers for JPEG creation */
extern BYTE SOI[2], SOS[2], EOI[2];

typedef struct
{
    BYTE APP0[2]; /* Application marker, APP0 is JFIF */
    BYTE Length[2]; /* Length of the header, excluding APP0 */ /* This value equals 16+3*XThumbnail*YThumbnail */
    BYTE ID[5]; /* Identifier: JFIF + zero terminated */
    BYTE Version[2]; /* JFIF format revision: 1.02 */
    BYTE Unit; /* Units of resolution. 00 = no units, 01 = dpi, 02 = ppc */
    BYTE XDensity[2]; /* Horizontal resolution */
    BYTE YDensity[2]; /* Vertical resolution */
    BYTE XThumbnail; /* Horizontal pixel count in thumbnail */
    BYTE YThumbnail; /* Vertical pixel count in thumbnail */
} JFIFHEADER;

typedef struct
{
    BYTE APP1[2]; /* Application marker, APP1 if EXIF */
    BYTE Length[2]; /* Length of the header, excluding APP1 */
    BYTE ID[6]; /* Identifier: EXIF + double zero terminated */
    // TIFF Header is meant to be here?
    

} EXIFHEADER;

/* Functions for constructing headers */
int BuildJFIFHeader(JFIFHEADER* headerptr, BYTE unit, BYTE xDensity[2], BYTE yDensity[2], BYTE xThumbnail, BYTE yThumbnail);
// int BuildEXIFHeader(EXIFHEADER* headerptr);

/* Functions for destroying headers in case it is necessary */
int DestroyJFIFHeader(JFIFHEADER* headerptr);
// int DestroyEXIFHeader();

/* Functions specifically for testing purposes */
int TestInput();

/* Some functions are written with ints to return potential errors */
int ReadDataToBuffer(char* dataAddr, enum RESMODE resMode);
int DCTToBuffers(enum RESMODE resMode);
int QuantBuffers(enum RESMODE resMode);
int DiffDCBuffers(enum RESMODE resMode);
int ZigzagBuffers(enum RESMODE resMode);

int RunLengthBuffers();

int HuffmanBuffer();
int WriteToJPEG();

#endif