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
#define SBYTE signed char 
#define DCT signed short

/* Define variables to use during data reading */
/*
 * Big resolution: 21MP
 * Mid resolution: Full HD
 * Small resolution: 720p
 * Test resolution: 8x8
 * Test resolution 2: 16x16
 * Test resolution 3: 32x16
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

#define BUFFERX MIDXRES
#define BUFFERY MIDYRES
#define BUFFERLEN MIDRESLEN

/* Enum to pass into functions */
enum RESMODE 
{
    BIG = 0,
    MID = 1,
    SMALL = 2,
    TEST = 3,
    TEST2 = 4,
    TESTWIDE = 5
};

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

/* Declare buffers to use for compression */
extern YCBCR yccBuffer[BUFFERX][BUFFERY];
extern DCTPIXEL dctBuffer[BUFFERX][BUFFERY];
extern unsigned char huffOutput[BUFFERLEN];

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

/* 
 * Function for getting resolutions 
 * Return is resolutions, not error
*/
int getXRes(enum RESMODE resMode);
int getYRes(enum RESMODE resMode);

/* Function built to move bits into the huffman buffer */
int AddToBitString(int len, signed short bitsToAdd, int isNegative);

/* Functions specifically for testing purposes */
int TestInput();

/* Pipeline functions */
int ReadDataToBuffer(char* dataAddr, enum RESMODE resMode);
int DCTToBuffer(enum RESMODE resMode);
int QuantBuffer(enum RESMODE resMode);
int DiffDCBuffer(enum RESMODE resMode);
int ZigzagBuffer(enum RESMODE resMode);
int HuffmanEncode(enum RESMODE resMode);

/* Debugging functions */
int OutputYCbCr(enum RESMODE resMode, int bufMode, int fileMode);
int printYCC(int printX, int printY, int xIndex, int yIndex);
int printDCTAll(int printX, int printY, int xIndex, int yIndex);
int printDCTY(int printX, int printY, int xIndex, int yIndex);
int printDCTCb(int printX, int printY, int xIndex, int yIndex);
int printDCTCr(int printX, int printY, int xIndex, int yIndex);

/* Ease-of-use functions */
int RawFileToHuffman(FILE* rawFile, unsigned char** huffPtr, int* huffPtrLen, enum RESMODE resMode); // File to Huffman
int RawFileToJPEG(FILE* rawFile, FILE* jpegFile, enum RESMODE resMode);// File to JPEG
int RAMToHuffman(char* dataAddr, unsigned char** huffPtr, int* huffPtrLen, enum RESMODE resMode); // RAM to Huffman
int RAMToJPEG(char* dataAddr, FILE* jpegFile, enum RESMODE resMode); // RAM to JPEG

/* New function being tested */
int FastDCTToBuffer(enum RESMODE resMode);

#endif