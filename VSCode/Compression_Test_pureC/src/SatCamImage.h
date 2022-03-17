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

/* Define unsigned char as BYTE for ease of use */
#define BYTE unsigned char

/* Define variables to use during data reading */
extern size_t xRes; // Horizontal resolution
extern size_t yRes; // Vertical resolution
extern size_t dataLen; // Length of data in RAM (Resolution * 4)

/* Define buffers to use for compression */
// extern BYTE pixelBuffer[]; // Pixel buffer (Resolution * 3)
// extern BYTE dctBuffer[]; // Buffer for quantization and DCT
extern BYTE huffmanBuffer[]; // Buffer for huffman coefficients

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

/* Functions are written with ints to return potential errors */
BYTE* ReadDataToBuffer(long* dataAddr, size_t datalen, size_t pixelLen);
BYTE* RGBToYCBCR(BYTE* pixelArr, size_t arrLen);
BYTE* YCBCRToRGB(BYTE* yccArr, size_t arrLen);

BYTE* QuantToBuffer();
BYTE* HuffmanToBuffer();
int WriteToJPEG();

#endif