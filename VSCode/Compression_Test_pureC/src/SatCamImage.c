/*
 * SatCamImage.h - Library for using the data stream from SatCam to build into a JPEG file with compression
 * Created by person, month date, 2022
*/

/* Include header file */
#include "SatCamImage.h"

/* Markers for JPEG creation */
BYTE SOI[2] = {0xff, 0xd8}; /* Start of Image Marker */
BYTE SOS[2] = {0xff, 0xda}; /* Start of Scan Marker */
BYTE EOI[2] = {0xff, 0xd9}; /* End of Image Marker */

/*
 * Function: BuildJFIFHeader
 * Purpose: Builds JFIF header with some basic variables, then puts in custom values
 * Input: Header pointer, Unit, XDensity, YDensity, XThumbnail, YThumbnail
 * Output: Error code
*/
int BuildJFIFHeader(JFIFHEADER* headerptr, 
                    BYTE unit, 
                    BYTE xDensity[2], 
                    BYTE yDensity[2], 
                    BYTE xThumbnail, 
                    BYTE yThumbnail) {
    /* Write constants to header */
    BYTE app[2] = {0xff, 0xe0};
    memcpy(headerptr->APP0, &app, 2);

    BYTE id[5] = {0x4a, 0x46, 0x49, 0x46, 0x00};
    memcpy(headerptr->ID, &id, 5);

    BYTE version[2] = {0x01, 0x02};
    memcpy(headerptr->Version, &version, 2);

    /* Write custom values to header */
    headerptr->Unit = unit;
    memcpy(headerptr->XDensity, &xDensity, 2);
    memcpy(headerptr->YDensity, &yDensity, 2);
    headerptr->XThumbnail = xThumbnail;
    headerptr->YThumbnail = yThumbnail;

    /* Write Length of application segment to header */
    uint16_t length = 16 + (3*xThumbnail*yThumbnail);
    BYTE lengthArr[2] = {length >> 8, length};
    memcpy(headerptr->Length, &lengthArr, 2);

    return 1;
}

/*
int BuildEXIFHeader(EXIFHEADER* headerptr) {


    return 1;
}*/

/* Function: DestroyJFIFHeader
 * Purpose: Destroy header after use
 * Input: Header pointer
 * Output: Error code
*/
int DestroyJFIFHeader(JFIFHEADER* headerptr) {
    free(headerptr);

    return 1;
}

// This adds bits to the huffman output string
int AddToBitString(int len, short bitsToAdd) {
	unsigned char b;

	for(int i = len - 1; 0 <= i; i--) {
		/* If we reach the boundary of our buffer, exit */
		if(bitPosInOutString+1 >= maxBitPos) return 0;

		b = (bitsToAdd >> i) & 0b01;

		if(b) {
			huffOutput[(bitPosInOutString/8)] |= (b<<(7-bitPosInOutString+(8*(bitPosInOutString/8))));
		}
		else {
			huffOutput[(bitPosInOutString/8)] &= ~(b<<(7-bitPosInOutString+(8*(bitPosInOutString/8))));
		}

		// printf("Byte 1: %d  ", outString[0]);
		// printf("Byte 2: %d  ", outString[1]);
		// printf("Byte 3: %d  ", outString[2]);
		// printf("Byte 4: %d  ", outString[3]);
		// printf("Byte 5: %d  ", outString[4]);
		// printf("Byte 6: %d  ", outString[5]);
		// printf("bitPos: %d  ", bitPosInOutString);
		// printf("bitPos/8: %d\n", (bitPosInOutString/8));

		bitPosInOutString++;
	}

	return 1;
}

// This tests file opening and closing
/*int TestInput() {

    FILE* fInput = fopen("memdump_bin_720p", "rb");
    FILE* fOutput = fopen("memdump_ycc_bin_720p", "wb");

    if(fInput == NULL){
		printf("\nError opening file.\n");
		return(0);
	}

    printf("Input file is open.\n");

    fseek(fInput, 0, SEEK_END);
	long fileLength = ftell(fInput);
	fseek(fInput, 0, SEEK_SET);

	char *buffer = (char*) malloc(sizeof(char)*fileLength);

	char ch = (char) fgetc(fInput);

	printf("We are set up.\n");

	int i = 0;
	while(!feof(fInput)) {
		// *(buffer + i) = ch;
		buffer[i] = ch;
		ch = (char) fgetc(fInput);
		i++;
	}

	printf("We are past feof.\n");

    int ReadDataErr = ReadDataToBuffer(buffer, SMALLRESLEN);
    if(ReadDataErr == 1) {
        printf("ReadDataToBuffer returned fine.\n");
    }

    fwrite(yccBuffer, sizeof(char)*1280*720, 1, fOutput);

    free(buffer);

    return 1;
}*/

// This tests the whole shebang
int TestInput() {
    FILE* fInput = fopen("memdump_bin_720p", "rb");
    FILE* fOutput = fopen("memdump_ycc_bin_720p", "wb");

    if(fInput == NULL){
		printf("\nError opening file.\n");
		return(0);
	}

    printf("Input file is open.\n");

    fseek(fInput, 0, SEEK_END);
	long fileLength = ftell(fInput);
	fseek(fInput, 0, SEEK_SET);

    char *buffer = (char*) malloc(sizeof(char)*fileLength);

	char ch = (char) fgetc(fInput);

	printf("We are set up.\n");

	int i = 0;
	while(!feof(fInput)) {
		// *(buffer + i) = ch;
		buffer[i] = ch;
		ch = (char) fgetc(fInput);
		i++;
	}

	printf("We are past feof.\n");

    int ReadDataErr = ReadDataToBuffer(buffer, SMALLRESLEN);
    if(ReadDataErr == 1) {
        printf("ReadDataToBuffer returned fine.\n");
    }

    free(buffer);

    if(DCTToBuffers(SMALL)) {
        printf("DCT returned fine.\n");
    }

    if(QuantBuffers(SMALL)) {
        printf("Quant returned fine.\n");
    }

    if(DiffDCBuffers(SMALL)) {
        printf("Quant returned fine.\n");
    }

    if(ZigzagBuffers(SMALL)) {
        printf("Zigzag returned fine.\n");
    }

    if(HuffmanEncode(SMALL)) {
        printf("Huff returned fine.\n");
    }
 
    fwrite(huffOutput, 1, 1280*720, fOutput);
    
    return 1;
}

// This tests DCT
/*int TestInput() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            yccBuffer[j][i].Y = 127;
            yccBuffer[j][i].Cb = 127;
            yccBuffer[j][i].Cr = 127;
        }
    }

    printf("ycc Y buffer:\n(\n");
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%d, ", yccBuffer[j][i].Y);
        }
        printf("\n");
    }
    printf(")\n");

    if(DCTToBuffers(TEST) == 1) {
        printf("DCT good\n");
    }

    printf("Y buffer:\n(\n");
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%d, ", dctBuffer[j][i].Y);
        }
        printf("\n");
    }
    printf(")\n");
    
    return 1;
}*/

// This tests zig-zag
/*int TestInput() {

    int testBuffer[8][8] = {
        {0,   1,  5,  6, 14, 15, 27, 28},
        {2,   4,  7, 13, 16, 26, 29, 42},
        {3,   8, 12, 17, 25, 30, 41, 43},
        {9,  11, 18, 24, 31, 40, 44, 53},
        {10, 19, 23, 32, 39, 45, 52, 54},
        {20, 22, 33, 38, 46, 51, 55, 60},
        {21, 34, 37, 47, 50, 56, 59, 61},
        {35, 36, 48, 49, 57, 58, 62, 63},
    };

    int testBuffer2[16][16] = {
        {0,   1,  5,  6, 14, 15, 27, 28, 0,   1,  5,  6, 14, 15, 27, 28},
        {2,   4,  7, 13, 16, 26, 29, 42, 2,   4,  7, 13, 16, 26, 29, 42},
        {3,   8, 12, 17, 25, 30, 41, 43, 3,   8, 12, 17, 25, 30, 41, 43},
        {9,  11, 18, 24, 31, 40, 44, 53, 9,  11, 18, 24, 31, 40, 44, 53},
        {10, 19, 23, 32, 39, 45, 52, 54, 10, 19, 23, 32, 39, 45, 52, 54},
        {20, 22, 33, 38, 46, 51, 55, 60, 20, 22, 33, 38, 46, 51, 55, 60},
        {21, 34, 37, 47, 50, 56, 59, 61, 21, 34, 37, 47, 50, 56, 59, 61},
        {35, 36, 48, 49, 57, 58, 62, 63, 35, 36, 48, 49, 57, 58, 62, 63},
        {0,   1,  5,  6, 14, 15, 27, 28, 0,   1,  5,  6, 14, 15, 27, 28},
        {2,   4,  7, 13, 16, 26, 29, 42, 2,   4,  7, 13, 16, 26, 29, 42},
        {3,   8, 12, 17, 25, 30, 41, 43, 3,   8, 12, 17, 25, 30, 41, 43},
        {9,  11, 18, 24, 31, 40, 44, 53, 9,  11, 18, 24, 31, 40, 44, 53},
        {10, 19, 23, 32, 39, 45, 52, 54, 10, 19, 23, 32, 39, 45, 52, 54},
        {20, 22, 33, 38, 46, 51, 55, 60, 20, 22, 33, 38, 46, 51, 55, 60},
        {21, 34, 37, 47, 50, 56, 59, 61, 21, 34, 37, 47, 50, 56, 59, 61},
        {35, 36, 48, 49, 57, 58, 62, 63, 35, 36, 48, 49, 57, 58, 62, 63},
    };

    for(int j = 0; j < 16; j++) {
        for(int i = 0; i < 16; i++) {
            dctYBuffer[i][j] = testBuffer2[j][i];
        }
    }
    
    ZigzagBuffers(TEST2);
    // int result = DCTToBuffers(TEST);

    printf("Y buffer:\n(\n");
    for(int j = 0; j < 16; j++) {
        for(int i = 0; i < 16; i++) {
            printf("%d, ", dctYBuffer[i][j]);
        }
        printf("\n");
    }
    printf(")\n");

    return 1;
}*/

// This tests run-length and Huffman
/*int TestInput() {

    return 1;
}*/

/*
 * Function: ReadDataToBuffer
 * Purpose: Read data from RAM, sanitise (remove alpha data)
 * Input: Address in RAM of data, resolution (is multiplied by 4 during function)
 * Output: Error code
*/
int ReadDataToBuffer(char* dataAddr, enum RESMODE resMode) {
    int xRes = 0;
    int yRes = 0;
    if(resMode == BIG) {
        xRes = BIGRESLEN;
        yRes = BIGRESLEN;
    }
    else if(resMode == MID) {
        xRes = MIDXRES;
        yRes = MIDYRES;
    }
    else if(resMode == SMALL) {
        xRes = SMALLXRES;
        yRes = SMALLYRES;
    }
    else if(resMode == TEST) {
        xRes = TESTXRES;
        yRes = TESTYRES;
    }
    else if(resMode == TEST2) {
        xRes = TEST2XRES;
        yRes = TEST2YRES;
    }
    else if(resMode == TESTWIDE) {
        xRes = TEST3XRES;
        yRes = TEST3YRES;
    }
    else return 0;
    
    // Source: https://ebookcentral.proquest.com/lib/aalborguniv-ebooks/reader.action?docID=867675
    // Using BT.709 standard
    int transMatrix[] = 
    {
        47, 157, 16,
        -26, -87, 112,
        112, -102, -10
    };

    BYTE r, g, b;
    for(size_t yPos = 0; yPos < yRes; yPos++) {
        for(size_t xPos = 0; xPos < xRes; xPos++) {
            size_t dataIndex = (xPos + (yPos * xRes)) * 4;

            // Order is rgba
            b = *(dataAddr + (dataIndex + 2));
            g = *(dataAddr + (dataIndex + 1));
            r = *(dataAddr + (dataIndex));

            // Note: var >> 8 is the same as var/256
            // Note also: Normally Y would have 16 added, and Cb Cr would have 128 added
            // They all have -128 to level shift
            yccBuffer[xPos][yPos].Y = (((transMatrix[0]*r) + (transMatrix[1]*g) + (transMatrix[2]*b)) >> 8) - 112;
            yccBuffer[xPos][yPos].Cb = (((transMatrix[3]*r) + (transMatrix[4]*g) + (transMatrix[5]*b)) >> 8);
            yccBuffer[xPos][yPos].Cr = (((transMatrix[6]*r) + (transMatrix[7]*g) + (transMatrix[8]*b)) >> 8);
        }
    }

    return 1;
}

/*
 * Function: DCTToBuffers
 * Purpose: Perform DCT on YCbCr data, split into 3 separate buffers
 * Input: Mode (0 = bigres, 1 = midres), pixel amount
 * Output: Error code
*/
int DCTToBuffers(enum RESMODE resMode) {
    int xRes = 0;
    int yRes = 0;
    if(resMode == BIG) {
        xRes = BIGXRES;
        yRes = BIGYRES;
    }
    else if(resMode == MID) {
        xRes = MIDXRES;
        yRes = MIDYRES;
    }
    else if(resMode == SMALL) {
        xRes = SMALLXRES;
        yRes = SMALLYRES;
    }
    else if(resMode == TEST) {
        xRes = TESTXRES;
        yRes = TESTYRES;
    }
    else if(resMode == TEST2) {
        xRes = TEST2XRES;
        yRes = TEST2YRES;
    }
    else if(resMode == TESTWIDE) {
        xRes = TEST3XRES;
        yRes = TEST3YRES;
    }
    else return 0;

    // Sources:
    // https://se.mathworks.com/help/images/discrete-cosine-transform.html#:~:text=Discrete%20Cosine%20Transform-,DCT%20Definition,(DCT)%20of%20an%20image
    // https://www.geeksforgeeks.org/discrete-cosine-transform-algorithm-program/
    
    // Order of pixels is YCbCr

    float aP = 0; // alphaP is for x
    float aQ = 0; // alphaQ is for y
    
    // for each DCT calculated at each initial coordinate
    float dctY = 0; 
    float dctCb = 0;
    float dctCr = 0;

    // For the sums of all DCT's calculated
    float dctYSum = 0;
    float dctCbSum = 0;
    float dctCrSum = 0;

    for(size_t yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(size_t xBlock = 0; xBlock < xRes/8; xBlock++) {
            
            for(int yStart = 0; yStart < 8; yStart++) {
                for(int xStart = 0; xStart < 8; xStart++) {
                    if(xStart == 0)   aP = 1 / sqrt(xRes);
                    else            aP = sqrt(2) / sqrt(xRes);

                    if(yStart == 0)   aQ = 1 / sqrt(yRes);
                    else            aQ = sqrt(2) / sqrt(yRes);

                    dctYSum = 0;
                    dctCbSum = 0;
                    dctCrSum = 0;

                    for(size_t y = 0; y < 8; y++) {
                        for(size_t x = 0; x < 8; x++) {
                            size_t xIndex = x + (xBlock * 8);
                            size_t yIndex = y + (yBlock * 8);

                            dctY =  yccBuffer[xIndex][yIndex].Y *
                                cos(((2 * x + 1) * 3.142857 * xStart) / (2 * xRes)) *
                                cos(((2 * y + 1) * 3.142857 * yStart) / (2 * yRes));
                            dctYSum = dctYSum + dctY;

                            dctCb =  yccBuffer[xIndex][yIndex].Cb *
                                cos(((2 * x + 1) * 3.142857 * xStart) / (2 * xRes)) *
                                cos(((2 * y + 1) * 3.142857 * yStart) / (2 * yRes));
                            dctCbSum = dctCbSum + dctCb;

                            dctCr =  yccBuffer[xIndex][yIndex].Cr *
                                cos(((2 * x + 1) * 3.142857 * xStart) / (2 * xRes)) *
                                cos(((2 * y + 1) * 3.142857 * yStart) / (2 * yRes));
                            dctCrSum = dctCrSum + dctCr;

                        }
                    }

                    dctBuffer[xStart][yStart].Y = aP * aQ * dctYSum;
                    dctBuffer[xStart][yStart].Cb = aP * aQ * dctCbSum;
                    dctBuffer[xStart][yStart].Cr = aP * aQ * dctCrSum;
                }
            }
        }
    }

    return 1;
}

/*
 * Function: QuantBuffers
 * Purpose: Apply quantization table to DCT buffers in 8x8 blocks
 * Input: Mode (0 = bigres, 1 = midres), pixel amount
 * Output: Error code
*/
int QuantBuffers(enum RESMODE resMode) {
    /* Quantization tables */
    const int lumiQuantTable[] = 
    {
        16, 11, 10, 16, 24, 40, 51, 61,
        12, 12, 14, 19, 26, 58, 60, 55,
        14, 13, 16, 24, 40, 57, 69, 56,
        14, 17, 22, 29, 51, 87, 80, 62,
        18, 22, 37, 56, 68, 109, 103, 77,
        24, 35, 55, 64, 81, 104, 113, 92,
        49, 64, 78, 87, 103, 121, 120, 101,
        72, 92, 95, 98, 112, 100, 103, 99
    };

    const int chromiQuantTable[] = 
    {
        17, 18, 24, 47, 99, 99, 99, 99,
        18, 21, 26, 66, 99, 99, 99, 99,
        24, 26, 56, 99, 99, 99, 99, 99,
        47, 66, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99,
    };

    int xRes = 0;
    int yRes = 0;
    if(resMode == BIG) {
        xRes = BIGXRES;
        yRes = BIGYRES;
    }
    else if(resMode == MID) {
        xRes = MIDXRES;
        yRes = MIDYRES;
    }
    else if(resMode == SMALL) {
        xRes = SMALLXRES;
        yRes = SMALLYRES;
    }
    else if(resMode == TEST) {
        xRes = TESTXRES;
        yRes = TESTYRES;
    }
    else if(resMode == TEST2) {
        xRes = TEST2XRES;
        yRes = TEST2YRES;
    }
    else if(resMode == TESTWIDE) {
        xRes = TEST3XRES;
        yRes = TEST3YRES;
    }
    else return 0;

    for(size_t yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(size_t xBlock = 0; xBlock < xRes/8; xBlock++) {
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {

                    size_t xIndex = x + (xBlock * 8);
                    size_t yIndex = y + (yBlock * 8);

                    size_t indexInTable = x + (y * 8);

                    dctBuffer[xIndex][yIndex].Y = dctBuffer[xIndex][yIndex].Y / lumiQuantTable[indexInTable];
                    dctBuffer[xIndex][yIndex].Cb = dctBuffer[xIndex][yIndex].Cb / chromiQuantTable[indexInTable];
                    dctBuffer[xIndex][yIndex].Cr = dctBuffer[xIndex][yIndex].Cr / chromiQuantTable[indexInTable];
                }
            }
        }
    }

    return 1;
}

int DiffDCBuffers(enum RESMODE resMode) {
    int xRes = 0;
    int yRes = 0;
    if(resMode == BIG) {
        xRes = BIGXRES;
        yRes = BIGYRES;
    }
    else if(resMode == MID) {
        xRes = MIDXRES;
        yRes = MIDYRES;
    }
    else if(resMode == SMALL) {
        xRes = SMALLXRES;
        yRes = SMALLYRES;
    }
    else if(resMode == TEST) {
        xRes = TESTXRES;
        yRes = TESTYRES;
    }
    else if(resMode == TEST2) {
        xRes = TEST2XRES;
        yRes = TEST2YRES;
    }
    else if(resMode == TESTWIDE) {
        xRes = TEST3XRES;
        yRes = TEST3YRES;
    }
    else return 0;

    int oldYValue = 0;
    int newYValue = 0;
    int oldCbValue = 0;
    int newCbValue = 0;
    int oldCrValue = 0;
    int newCrValue = 0;

    for(size_t yDC = 0; yDC < yRes/8; yDC++) {
        for(size_t xDC = 0; xDC < xRes/8; xDC++) {
            size_t xIndex = (xDC * 8);
            size_t yIndex = (yDC * 8);

            newYValue = dctBuffer[xIndex][yIndex].Y;
            dctBuffer[xIndex][yIndex].Y = dctBuffer[xIndex][yIndex].Y - oldYValue;
            oldYValue = newYValue;

            newCbValue = dctBuffer[xIndex][yIndex].Cb;
            dctBuffer[xIndex][yIndex].Cb = dctBuffer[xIndex][yIndex].Cb - oldCbValue;
            oldCbValue = newCbValue;

            newCrValue = dctBuffer[xIndex][yIndex].Cr;
            dctBuffer[xIndex][yIndex].Cr = dctBuffer[xIndex][yIndex].Cr - oldCrValue;
            oldCrValue = newCrValue;
        }
    }

    return 1;
}

int ZigzagBuffers(enum RESMODE resMode) {
    int xRes = 0;
    int yRes = 0;
    if(resMode == BIG) {
        xRes = BIGXRES;
        yRes = BIGYRES;
    }
    else if(resMode == MID) {
        xRes = MIDXRES;
        yRes = MIDYRES;
    }
    else if(resMode == SMALL) {
        xRes = SMALLXRES;
        yRes = SMALLYRES;
    }
    else if(resMode == TEST) {
        xRes = TESTXRES;
        yRes = TESTYRES;
    }
    else if(resMode == TEST2) {
        xRes = TEST2XRES;
        yRes = TEST2YRES;
    }
    else if(resMode == TESTWIDE) {
        xRes = TEST3XRES;
        yRes = TEST3YRES;
    }
    else return 0;

    // I hate these
    int blockXIndex[] = {
        0, 1, 0, 
        0, 1, 2, 
        3, 2, 1, 0, 
        0, 1, 2, 3, 4,
        5, 4, 3, 2, 1, 0, 
        0, 1, 2, 3, 4, 5, 6,
        7, 6, 5, 4, 3, 2, 1, 0, 
        1, 2, 3, 4, 5, 6, 7, 
		7, 6, 5, 4, 3, 2,
        3, 4, 5, 6, 7,
        7, 6, 5, 4,
        5, 6, 7,
        7, 6,
        7,
    };

    int blockYIndex[] = {
        0, 0, 1,
        2, 1, 0,
        0, 1, 2, 3, 
        4, 3, 2, 1, 0,
        0, 1, 2, 3, 4, 5,
        6, 5, 4, 3, 2 ,1, 0,
        0, 1, 2, 3, 4, 5, 6, 7,
        7, 6, 5, 4, 3, 2, 1,
        2, 3, 4, 5, 6, 7,
        7, 6, 5, 4, 3,
        4, 5, 6, 7,
        7, 6, 5,
        6, 7,
        7,
    };

    // Go by 8*8 blocks
    for(size_t yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(size_t xBlock = 0; xBlock < xRes/8; xBlock++) {
            
            // First with Y buffer
            DCT zzBuffer[8][8];
            // Put the data from the DCT buffer in the right order
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    size_t dctXIndex = blockXIndex[x + y * 8] + (8*xBlock);
                    size_t dctYIndex = blockYIndex[x + y * 8] + (8*yBlock);

                    zzBuffer[x][y] = dctBuffer[dctXIndex][dctYIndex].Y;
                }
            }
            // Put the rightly ordered data back into the DCT buffer
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    size_t dctXIndex = x + (8*xBlock);
                    size_t dctYIndex = y + (8*yBlock);
                    
                    dctBuffer[dctXIndex][dctYIndex].Y = zzBuffer[x][y];
                }
            }

            // Then with Cb buffer
            memset(zzBuffer, 0, 8*8*sizeof(DCT));
            // Put the data from the DCT buffer in the right order
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    size_t dctXIndex = blockXIndex[x + y * 8] + (8*xBlock);
                    size_t dctYIndex = blockYIndex[x + y * 8] + (8*yBlock);

                    zzBuffer[x][y] = dctBuffer[dctXIndex][dctYIndex].Cb;
                }
            }
            // Put the rightly ordered data back into the DCT buffer
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    size_t dctXIndex = x + (8*xBlock);
                    size_t dctYIndex = y + (8*yBlock);
                    
                    dctBuffer[dctXIndex][dctYIndex].Cb = zzBuffer[x][y];
                }
            }

            // Finally with Cr buffer
            memset(zzBuffer, 0, 8*8*sizeof(DCT));
            // Put the data from the DCT buffer in the right order
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    size_t dctXIndex = blockXIndex[x + y * 8] + (8*xBlock);
                    size_t dctYIndex = blockYIndex[x + y * 8] + (8*yBlock);

                    zzBuffer[x][y] = dctBuffer[dctXIndex][dctYIndex].Cr;
                }
            }
            // Put the rightly ordered data back into the DCT buffer
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    size_t dctXIndex = x + (8*xBlock);
                    size_t dctYIndex = y + (8*yBlock);
                    
                    dctBuffer[dctXIndex][dctYIndex].Cr = zzBuffer[x][y];
                }
            }


            // Old shit KEPT FOR PROSPERITY AND POTENTIALLY BETTER IMPLEMENTATION EVENTUALLY
                // if x != 0 and flag not set OR x,y==0 { xIndex+1, put in buffer, and run in zig (put in buffers during loop)
                // if y != 0 and flag not set { yIndex+1, put in buffer, and run in zag (put in buffers during loop)
                // if x != 7 and flag is set { xIndex+1, put in buffer, and run in zig (put in buffers during loop)
                // if y != 7 and flag is set { yIndex+1, put in buffer, and run in zig (put in buffers during loop)

                // if y == 7 { set flag
                // if x == 6 && y == 7 { do the last one and be done
        }
    }

    return 1;
}

/*
 * Function: HuffmanBuffer
 * Purpose: Apply Huffman coding to buffers
 * Input: 
 * Output: Error code
*/
int HuffmanEncode(enum RESMODE resMode) {
    int xRes = 0;
    int yRes = 0;
    if(resMode == BIG) {
        xRes = BIGXRES;
        yRes = BIGYRES;
    }
    else if(resMode == MID) {
        xRes = MIDXRES;
        yRes = MIDYRES;
    }
    else if(resMode == SMALL) {
        xRes = SMALLXRES;
        yRes = SMALLYRES;
    }
    else if(resMode == TEST) {
        xRes = TESTXRES;
        yRes = TESTYRES;
    }
    else if(resMode == TEST2) {
        xRes = TEST2XRES;
        yRes = TEST2YRES;
    }
    else if(resMode == TESTWIDE) {
        xRes = TEST3XRES;
        yRes = TEST3YRES;
    }
    else return 0;

    memset(huffOutput, 0, BUFFERLEN);

    // Variables
    maxBitPos = sizeof(huffOutput) * 8;
    bitPosInOutString = 0;

    /* Tables for categories */
    static const size_t huffCatTable[12][2] = {
        {0,0}, {1,1}, {2,3}, {4,7}, {8,15}, {16,31}, {32,63},
        {64,127}, {128,255}, {256,511}, {512,1023}, {1024,2047}
    };

    /* Tables for Huffman codes */
    static const unsigned short dcLumiCodeTable[12][2] = {
        {2, 0b00},
        {3, 0b010},
        {3, 0b011},
        {3, 0b100},
        {3, 0b101},
        {3, 0b110},
        {4, 0b1110},
        {5, 0b11110},
        {6, 0b111110},
        {7, 0b1111110},
        {8, 0b11111110},
        {9, 0b111111110}
    };

    static const unsigned short dcChromiCodeTable[12][2] = {
        {2, 0b00},
        {2, 0b01},
        {2, 0b10},
        {3, 0b110},
        {4, 0b1110},
        {5, 0b11110},
        {6, 0b111110},
        {7, 0b1111110},
        {8, 0b11111110},
        {9, 0b111111110},
        {10, 0b1111111110},
        {11, 0b11111111110}
    };

    static const unsigned short acLumiCodeTable[162][2] = {
        {4, 0b1010},
        {2, 0b00},
        {2, 0b01},
        {3, 0b100},
        {4, 0b1011},
        {5, 0b11010},
        {7, 0b1111000},
        {8, 0b11111000},
        {10, 0b1111110110},
        {16, 0b1111111110000010},
        {16, 0b1111111110000011},
        {4, 0b1100},
        {5, 0b11011},
        {7, 0b1111001},
        {9, 0b111110110},
        {11, 0b11111110110},
        {16, 0b1111111110000100},
        {16, 0b1111111110000101},
        {16, 0b1111111110000110},
        {16, 0b1111111110000111},
        {16, 0b1111111110001000},
        {5, 0b11100},
        {8, 0b11111001},
        {10, 0b1111110111},
        {12, 0b111111110100},
        {16, 0b1111111110001001},
        {16, 0b1111111110001010},
        {16, 0b1111111110001011},
        {16, 0b1111111110001100},
        {16, 0b1111111110001101},
        {16, 0b1111111110001110},
        {6, 0b111010},
        {9, 0b111110111},
        {12, 0b111111110101},
        {16, 0b1111111110001111},
        {16, 0b1111111110010000},
        {16, 0b1111111110010001},
        {16, 0b1111111110010010},
        {16, 0b1111111110010011},
        {16, 0b1111111110010100},
        {16, 0b1111111110010101},
        {6, 0b111011},
        {10, 0b1111111000},
        {16, 0b1111111110010110},
        {16, 0b1111111110010111},
        {16, 0b1111111110011000},
        {16, 0b1111111110011001},
        {16, 0b1111111110011010},
        {16, 0b1111111110011011},
        {16, 0b1111111110011100},
        {16, 0b1111111110011101},
        {7, 0b1111010},
        {11, 0b11111110111},
        {16, 0b1111111110011110},
        {16, 0b1111111110011111},
        {16, 0b1111111110100000},
        {16, 0b1111111110100001},
        {16, 0b1111111110100010},
        {16, 0b1111111110100011},
        {16, 0b1111111110100100},
        {16, 0b1111111110100101},
        {7, 0b1111011},
        {12, 0b111111110110},
        {16, 0b1111111110100110},
        {16, 0b1111111110100111},
        {16, 0b1111111110101000},
        {16, 0b1111111110101001},
        {16, 0b1111111110101010},
        {16, 0b1111111110101011},
        {16, 0b1111111110101100},
        {16, 0b1111111110101101},
        {8, 0b11111010},
        {12, 0b111111110111},
        {16, 0b1111111110101110},
        {16, 0b1111111110101111},
        {16, 0b1111111110110000},
        {16, 0b1111111110110001},
        {16, 0b1111111110110010},
        {16, 0b1111111110110011},
        {16, 0b1111111110110100},
        {16, 0b1111111110110101},
        {9, 0b111111000},
        {15, 0b111111111000000},
        {16, 0b1111111110110110},
        {16, 0b1111111110110111},
        {16, 0b1111111110111000},
        {16, 0b1111111110111001},
        {16, 0b1111111110111010},
        {16, 0b1111111110111011},
        {16, 0b1111111110111100},
        {16, 0b1111111110111101},
        {9, 0b111111001},
        {16, 0b1111111110111110},
        {16, 0b1111111110111111},
        {16, 0b1111111111000000},
        {16, 0b1111111111000001},
        {16, 0b1111111111000010},
        {16, 0b1111111111000011},
        {16, 0b1111111111000100},
        {16, 0b1111111111000101},
        {16, 0b1111111111000110},
        {9, 0b111111010},
        {16, 0b1111111111000111},
        {16, 0b1111111111001000},
        {16, 0b1111111111001001},
        {16, 0b1111111111001010},
        {16, 0b1111111111001011},
        {16, 0b1111111111001100},
        {16, 0b1111111111001101},
        {16, 0b1111111111001110},
        {16, 0b1111111111001111},
        {10, 0b1111111001},
        {16, 0b1111111111010000},
        {16, 0b1111111111010001},
        {16, 0b1111111111010010},
        {16, 0b1111111111010011},
        {16, 0b1111111111010100},
        {16, 0b1111111111010101},
        {16, 0b1111111111010110},
        {16, 0b1111111111010111},
        {16, 0b1111111111011000},
        {10, 0b1111111010},
        {16, 0b1111111111011001},
        {16, 0b1111111111011010},
        {16, 0b1111111111011011},
        {16, 0b1111111111011100},
        {16, 0b1111111111011101},
        {16, 0b1111111111011110},
        {16, 0b1111111111011111},
        {16, 0b1111111111100000},
        {16, 0b1111111111100001},
        {11, 0b11111111000},
        {16, 0b1111111111100010},
        {16, 0b1111111111100011},
        {16, 0b1111111111100100},
        {16, 0b1111111111100101},
        {16, 0b1111111111100110},
        {16, 0b1111111111100111},
        {16, 0b1111111111101000},
        {16, 0b1111111111101001},
        {16, 0b1111111111101010},
        {16, 0b1111111111101011},
        {16, 0b1111111111101100},
        {16, 0b1111111111101101},
        {16, 0b1111111111101110},
        {16, 0b1111111111101111},
        {16, 0b1111111111110000},
        {16, 0b1111111111110001},
        {16, 0b1111111111110010},
        {16, 0b1111111111110011},
        {16, 0b1111111111110100},
        {16, 0b1111111111110101},
        {16, 0b1111111111110110},
        {16, 0b1111111111110111},
        {16, 0b1111111111111000},
        {16, 0b1111111111111001},
        {16, 0b1111111111111010},
        {16, 0b1111111111111011},
        {16, 0b1111111111111100},
        {16, 0b1111111111111101},
        {16, 0b1111111111111110},
        {11, 0b11111111001}
    };
    
    static const unsigned short acChromiCodeTable[162][2] = {
        {2, 0b00},
        {2, 0b01},
        {3, 0b100},
        {4, 0b1010},
        {5, 0b11000},
        {5, 0b11001},
        {6, 0b111000},
        {7, 0b1111000},
        {9, 0b111110100},
        {10, 0b1111110110},
        {12, 0b111111110100},
        {4, 0b1011},
        {6, 0b111001},
        {8, 0b11110110},
        {9, 0b111110101},
        {11, 0b11111110110},
        {12, 0b111111110101},
        {16, 0b1111111110001000},
        {16, 0b1111111110001001},
        {16, 0b1111111110001010},
        {16, 0b1111111110001011},
        {5, 0b11010},
        {8, 0b11110111},
        {10, 0b1111110111},
        {12, 0b111111110110},
        {15, 0b111111111000010},
        {16, 0b1111111110001100},
        {16, 0b1111111110001101},
        {16, 0b1111111110001110},
        {16, 0b1111111110001111},
        {16, 0b1111111110010000},
        {5, 0b11011},
        {8, 0b11111000},
        {10, 0b1111111000},
        {12, 0b111111110111},
        {16, 0b1111111110010001},
        {16, 0b1111111110010010},
        {16, 0b1111111110010011},
        {16, 0b1111111110010100},
        {16, 0b1111111110010101},
        {16, 0b1111111110010110},
        {6, 0b111010},
        {9, 0b111110110},
        {16, 0b1111111110010111},
        {16, 0b1111111110011000},
        {16, 0b1111111110011001},
        {16, 0b1111111110011010},
        {16, 0b1111111110011011},
        {16, 0b1111111110011100},
        {16, 0b1111111110011101},
        {16, 0b1111111110011110},
        {6, 0b111011},
        {10, 0b1111111001},
        {16, 0b1111111110011111},
        {16, 0b1111111110100000},
        {16, 0b1111111110100001},
        {16, 0b1111111110100010},
        {16, 0b1111111110100011},
        {16, 0b1111111110100100},
        {16, 0b1111111110100101},
        {16, 0b1111111110100110},
        {7, 0b1111001},
        {11, 0b11111110111},
        {16, 0b1111111110100111},
        {16, 0b1111111110101000},
        {16, 0b1111111110101001},
        {16, 0b1111111110101010},
        {16, 0b1111111110101011},
        {16, 0b1111111110101100},
        {16, 0b1111111110101101},
        {16, 0b1111111110101110},
        {7, 0b1111010},
        {11, 0b11111111000},
        {16, 0b1111111110101111},
        {16, 0b1111111110110000},
        {16, 0b1111111110110001},
        {16, 0b1111111110110010},
        {16, 0b1111111110110011},
        {16, 0b1111111110110100},
        {16, 0b1111111110110101},
        {16, 0b1111111110110110},
        {8, 0b11111001},
        {16, 0b1111111110110111},
        {16, 0b1111111110111000},
        {16, 0b1111111110111001},
        {16, 0b1111111110111010},
        {16, 0b1111111110111011},
        {16, 0b1111111110111100},
        {16, 0b1111111110111101},
        {16, 0b1111111110111110},
        {16, 0b1111111110111111},
        {9, 0b111110111},
        {16, 0b1111111111000000},
        {16, 0b1111111111000001},
        {16, 0b1111111111000010},
        {16, 0b1111111111000011},
        {16, 0b1111111111000100},
        {16, 0b1111111111000101},
        {16, 0b1111111111000110},
        {16, 0b1111111111000111},
        {16, 0b1111111111001000},
        {9, 0b111111000},
        {16, 0b1111111111001001},
        {16, 0b1111111111001010},
        {16, 0b1111111111001011},
        {16, 0b1111111111001100},
        {16, 0b1111111111001101},
        {16, 0b1111111111001110},
        {16, 0b1111111111001111},
        {16, 0b1111111111010000},
        {16, 0b1111111111010001},
        {9, 0b111111001},
        {16, 0b1111111111010010},
        {16, 0b1111111111010011},
        {16, 0b1111111111010100},
        {16, 0b1111111111010101},
        {16, 0b1111111111010110},
        {16, 0b1111111111010111},
        {16, 0b1111111111011000},
        {16, 0b1111111111011001},
        {16, 0b1111111111011010},
        {9, 0b111111010},
        {16, 0b1111111111011011},
        {16, 0b1111111111011100},
        {16, 0b1111111111011101},
        {16, 0b1111111111011110},
        {16, 0b1111111111011111},
        {16, 0b1111111111100000},
        {16, 0b1111111111100001},
        {16, 0b1111111111100010},
        {16, 0b1111111111100011},
        {11, 0b11111111001},
        {16, 0b1111111111100100},
        {16, 0b1111111111100101},
        {16, 0b1111111111100110},
        {16, 0b1111111111100111},
        {16, 0b1111111111101000},
        {16, 0b1111111111101001},
        {16, 0b1111111111101010},
        {16, 0b1111111111101011},
        {16, 0b1111111111101100},
        {14, 0b11111111100000},
        {16, 0b1111111111101101},
        {16, 0b1111111111101110},
        {16, 0b1111111111101111},
        {16, 0b1111111111110000},
        {16, 0b1111111111110001},
        {16, 0b1111111111110010},
        {16, 0b1111111111110011},
        {16, 0b1111111111110100},
        {16, 0b1111111111110101},
        {15, 0b111111111000011},
        {16, 0b1111111111110110},
        {16, 0b1111111111110111},
        {16, 0b1111111111111000},
        {16, 0b1111111111111001},
        {16, 0b1111111111111010},
        {16, 0b1111111111111011},
        {16, 0b1111111111111100},
        {16, 0b1111111111111101},
        {16, 0b1111111111111110},
        {10, 0b1111111010}
    };

    // Various variables
    int catAmount = 12; // The amount of categories
    int zeroCtr = 0; // Keeps track of how many zeroes have been found on run
    int bigZeroCtr = 0; // Keeps track of how many times to write F/0 if applicable
    int cat = -1; // Keeps track of the category of value
    int numBits = 0; // Keeps track of how many bits to add from original value
    size_t tableIndex; // Holds whichever index is needed for the table

    for(size_t yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(size_t xBlock = 0; xBlock < xRes/8; xBlock++) {
            /*---------------------------------------------------------------*/
            // Y
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    
                    // Find category
                    cat = -1;
                    for(int i = 0; i < catAmount; i++) {
                        if((huffCatTable[i][0] <= dctBuffer[x][y].Y && huffCatTable[i][1] >= dctBuffer[x][y].Y) 
                            || (-huffCatTable[i][0] >= dctBuffer[x][y].Y && -huffCatTable[i][1] <= dctBuffer[x][y].Y)) {
                            
                            cat = i;
                            i = catAmount+1;
                        }
                    }
                    if(cat == -1) return -1; // Sanity check, exits if problem arises
                    
                    // If it is a DC value, do thing like this. Otherwise do it normally
                    if(x == 0 && y == 0) {
                        // Add the base code
                        if(!AddToBitString(dcLumiCodeTable[cat][0], dcLumiCodeTable[cat][1])) {
                            printf("Something went wrong on AddToBitString 1\n");
                        }

                        // Add the at most last 4 bits
                        numBits = 0;
                        if(cat > 4) numBits = 4;
                        else numBits = cat;

                        if(!AddToBitString(numBits, dctBuffer[x][y].Y)) {
                            printf("Something went wrong on AddToBitString 2\n");
                        }

                    }
                    else {
                        if(dctBuffer[x][y].Y == 0){
                          zeroCtr++;
                          if(zeroCtr >= 15) {
                              zeroCtr = 0;
                              bigZeroCtr++;
                          }
                        }
                        else{
                            // So long as there are 15 zeros in a row
                            while(bigZeroCtr != 0) {
                                if(!AddToBitString(acLumiCodeTable[161][0], acLumiCodeTable[161][1])) {
                                    printf("Something went wrong on AddToBitString 3\n");
                                }
                                
                                bigZeroCtr--;
                            }
                            
                            tableIndex = zeroCtr*10 + cat;
				
                            // Add in base code
                            if(!AddToBitString(acLumiCodeTable[tableIndex][0], acLumiCodeTable[tableIndex][1])) {
                                printf("Something went wrong on AddToBitString 1\n");
                            }

                            // Add in last bits
                            numBits = 0;
                            if(cat > 4) numBits = 4;
                            else numBits = cat;

                            if(!AddToBitString(numBits, dctBuffer[x][y].Y)) {
                                printf("Something went wrong on AddToBitString 2\n");
                            }

                            zeroCtr = 0;
                        }
                    }
                }
            }

            // Add EOB
            zeroCtr = 0;
            bigZeroCtr = 0;
            AddToBitString(acLumiCodeTable[0][0], acLumiCodeTable[0][1]);

            /*---------------------------------------------------------------*/
            // Cb
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    
                    // Find category
                    cat = -1;
                    for(int i = 0; i < catAmount; i++) {
                        if((huffCatTable[i][0] <= dctBuffer[x][y].Cb && huffCatTable[i][1] >= dctBuffer[x][y].Cb) 
                            || (-huffCatTable[i][0] >= dctBuffer[x][y].Cb && -huffCatTable[i][1] <= dctBuffer[x][y].Cb)) {
                            
                            cat = i;
                            i = catAmount+1;
                        }
                    }
                    if(cat == -1) return -1; // Sanity check, exits if problem arises
                    
                    // If it is a DC value, do thing like this. Otherwise do it normally
                    if(x == 0 && y == 0) {
                        // Add the base code
                        if(!AddToBitString(dcChromiCodeTable[cat][0], dcChromiCodeTable[cat][1])) {
                            printf("Something went wrong on AddToBitString 1\n");
                        }

                        // Add the at most last 4 bits
                        numBits = 0;
                        if(cat > 4) numBits = 4;
                        else numBits = cat;

                        if(!AddToBitString(numBits, dctBuffer[x][y].Cb)) {
                            printf("Something went wrong on AddToBitString 2\n");
                        }

                    }
                    else {
                        if(dctBuffer[x][y].Cb == 0){
                          zeroCtr++;
                          if(zeroCtr >= 15) {
                              zeroCtr = 0;
                              bigZeroCtr++;
                          }
                        }
                        else{
                            // So long as there are 15 zeros in a row
                            while(bigZeroCtr != 0) {
                                if(!AddToBitString(acChromiCodeTable[161][0], acChromiCodeTable[161][1])) {
                                    printf("Something went wrong on AddToBitString 3\n");
                                }
                                
                                bigZeroCtr--;
                            }
                            
                            tableIndex = zeroCtr*10 + cat;
				
                            // Add in base code
                            if(!AddToBitString(acChromiCodeTable[tableIndex][0], acChromiCodeTable[tableIndex][1])) {
                                printf("Something went wrong on AddToBitString 1\n");
                            }

                            // Add in last bits
                            numBits = 0;
                            if(cat > 4) numBits = 4;
                            else numBits = cat;

                            if(!AddToBitString(numBits, dctBuffer[x][y].Cb)) {
                                printf("Something went wrong on AddToBitString 2\n");
                            }

                            zeroCtr = 0;
                        }
                    }
                }
            }

            // Add EOB
            zeroCtr = 0;
            bigZeroCtr = 0;
            AddToBitString(acChromiCodeTable[0][0], acChromiCodeTable[0][1]);

            /*---------------------------------------------------------------*/
            // Cr
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    
                    // Find category
                    cat = -1;
                    for(int i = 0; i < catAmount; i++) {
                        if((huffCatTable[i][0] <= dctBuffer[x][y].Cr && huffCatTable[i][1] >= dctBuffer[x][y].Cr) 
                            || (-huffCatTable[i][0] >= dctBuffer[x][y].Cr && -huffCatTable[i][1] <= dctBuffer[x][y].Cr)) {
                            
                            cat = i;
                            i = catAmount+1;
                        }
                    }
                    if(cat == -1) return -1; // Sanity check, exits if problem arises
                    
                    // If it is a DC value, do thing like this. Otherwise do it normally
                    if(x == 0 && y == 0) {
                        // Add the base code
                        if(!AddToBitString(dcChromiCodeTable[cat][0], dcChromiCodeTable[cat][1])) {
                            printf("Something went wrong on AddToBitString 1\n");
                        }

                        // Add the at most last 4 bits
                        numBits = 0;
                        if(cat > 4) numBits = 4;
                        else numBits = cat;

                        if(!AddToBitString(numBits, dctBuffer[x][y].Cr)) {
                            printf("Something went wrong on AddToBitString 2\n");
                        }

                    }
                    else {
                        if(dctBuffer[x][y].Cr == 0){
                          zeroCtr++;
                          if(zeroCtr >= 15) {
                              zeroCtr = 0;
                              bigZeroCtr++;
                          }
                        }
                        else{
                            // So long as there are 15 zeros in a row
                            while(bigZeroCtr != 0) {
                                if(!AddToBitString(acChromiCodeTable[161][0], acChromiCodeTable[161][1])) {
                                    printf("Something went wrong on AddToBitString 3\n");
                                }
                                
                                bigZeroCtr--;
                            }
                            
                            tableIndex = zeroCtr*10 + cat;
				
                            // Add in base code
                            if(!AddToBitString(acChromiCodeTable[tableIndex][0], acChromiCodeTable[tableIndex][1])) {
                                printf("Something went wrong on AddToBitString 1\n");
                            }

                            // Add in last bits
                            numBits = 0;
                            if(cat > 4) numBits = 4;
                            else numBits = cat;

                            if(!AddToBitString(numBits, dctBuffer[x][y].Cr)) {
                                printf("Something went wrong on AddToBitString 2\n");
                            }

                            zeroCtr = 0;
                        }
                    }
                }
            }

            // Add EOB
            zeroCtr = 0;
            bigZeroCtr = 0;
            AddToBitString(acChromiCodeTable[0][0], acChromiCodeTable[0][1]);
        }
    }

    return 1;
}

int WriteToJPEG() {


    /*
     * Checklist for making JPEG file
     * 
     * Order of headers
     * SOI (not included in JPEG header)
     * APP0-14
     * DQT
     * SOF0
     * DHT
     * DRI
     * SOS
     * RST0-7 ad nauseam
     * EOI
    */
   return 1;
}
