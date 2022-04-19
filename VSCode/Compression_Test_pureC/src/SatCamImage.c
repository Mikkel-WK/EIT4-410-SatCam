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

// This tests DCT
int TestInput() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            yccBuffer[j][i].Y = 255;
            yccBuffer[j][i].Cb = 255;
            yccBuffer[j][i].Cr = 255;
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
            printf("%d, ", dctYBuffer[j][i]);
        }
        printf("\n");
    }
    printf(")\n");
    
    return 1;
}

// This tests zig-zag + run-length
/*int TestInput() {
    ZigzagBuffers(TEST);
    // int result = DCTToBuffers(TEST);

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

    for(size_t yNum = 0; yNum < yRes; yNum++) {
        for(size_t xNum = 0; xNum < xRes; xNum++) {
            if(xNum == 0)   aP = 1 / sqrt(xRes);
            else            aP = sqrt(2) / sqrt(xRes);

            if(yNum == 0)   aQ = 1 / sqrt(yRes);
            else            aQ = sqrt(2) / sqrt(yRes);

            dctYSum = 0;
            dctCbSum = 0;
            dctCrSum = 0;

            for(size_t yPos = 0; yPos < yRes; yPos++) {
                for(size_t xPos = 0; xPos < xRes; xPos++) {
                    
                    dctY =  yccBuffer[xPos][yPos].Y *
                            cos(((2 * xPos + 1) * 3.142857 * xNum) / (2 * xRes)) *
                            cos(((2 * yPos + 1) * 3.142857 * yNum) / (2 * yRes));
                    dctYSum = dctYSum + dctY;

                    dctCb =  yccBuffer[xPos][yPos].Cb *
                            cos(((2 * xPos + 1) * 3.142857 * xNum) / (2 * xRes)) *
                            cos(((2 * yPos + 1) * 3.142857 * yNum) / (2 * yRes));
                    dctCbSum = dctCbSum + dctCb;

                    dctCr =  yccBuffer[xPos][yPos].Cr *
                            cos(((2 * xPos + 1) * 3.142857 * xNum) / (2 * xRes)) *
                            cos(((2 * yPos + 1) * 3.142857 * yNum) / (2 * yRes));
                    dctCrSum = dctCrSum + dctCr;
                }
            }

            dctYBuffer[xNum][yNum] = aP * aQ * dctYSum;
            dctCbBuffer[xNum][yNum] = aP * aQ * dctCbSum;
            dctCrBuffer[xNum][yNum] = aP * aQ * dctCrSum;
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
    else return 0;

    for(size_t yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(size_t xBlock = 0; xBlock < xRes/8; xBlock++) {
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {

                    size_t xIndex = x + (xBlock * 8);
                    size_t yIndex = y + (yBlock * 8);

                    size_t indexInTable = x + (y * 8);

                    dctYBuffer[xIndex][yIndex] = dctYBuffer[xIndex][yIndex] / lumiQuantTable[indexInTable];
                    dctCbBuffer[xIndex][yIndex] = dctCbBuffer[xIndex][yIndex] / chromiQuantTable[indexInTable];
                    dctCrBuffer[xIndex][yIndex] = dctCrBuffer[xIndex][yIndex] / chromiQuantTable[indexInTable];
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

            newYValue = dctYBuffer[xIndex][yIndex];
            dctYBuffer[xIndex][yIndex] = dctYBuffer[xIndex][yIndex] - oldYValue;
            oldYValue = newYValue;

            newCbValue = dctCbBuffer[xIndex][yIndex];
            dctCbBuffer[xIndex][yIndex] = dctCbBuffer[xIndex][yIndex] - oldCbValue;
            oldCbValue = newCbValue;

            newCrValue = dctCrBuffer[xIndex][yIndex];
            dctCrBuffer[xIndex][yIndex] = dctCrBuffer[xIndex][yIndex] - oldCrValue;
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

    // Go by 8*8 blocks
    for(size_t yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(size_t xBlock = 0; xBlock < xRes/8; xBlock++) {
            
            DCT zzBuffer[64];

            for(int i = 0; i < 64; i++) {
                size_t zzIndex = i + (64*xBlock) + ((xRes*8)*yBlock);

                // zzBuffer[zzIndex] = dctYBuffer[blockXIndex[i]][blockYIndex[i]];
                zzBuffer[zzIndex] = testBuffer[blockXIndex[i]][blockYIndex[i]];
            }
            
            for(int i = 0; i < 64; i++) {
                printf("%d, ", zzBuffer[i]);
            }
            fflush(stdout);

            // // Put DC value in zz buffer right away
            // zzBuffer[0][0] = dctYBuffer[8*xBlock][8*yBlock];

            // int blockXIndex = 0, blockYIndex = 0, bufferXIndex = 0, bufferYIndex = 0, zzXIndex = 0, zzYIndex = 0;
            // int zzFlag = 0;

            // while(blockXIndex != 6 && blockYIndex != 7) {
                
            //     if((blockXIndex != 0) || (blockXIndex==0 && blockYIndex==0)) {
            //         blockXIndex++;

            //         for(int i = blockXIndex; i > 0; i--) {
                        
            //         }
            //     }

            //     if(blockYIndex == 7) zzFlag = 1;
            // }

            // bufferXIndex = 7 + (8*xBlock);
            // bufferYIndex = 7 + (8*yBlock);

            // zzBuffer[7][7] = dctYBuffer[bufferXIndex][bufferYIndex];

            // // if x != 0 and flag not set OR x,y==0 { xIndex+1, put in buffer, and run in zig (put in buffers during loop)
            // // if y != 0 and flag not set { yIndex+1, put in buffer, and run in zag (put in buffers during loop)
            // // if x != 7 and flag is set { xIndex+1, put in buffer, and run in zig (put in buffers during loop)
            // // if y != 7 and flag is set { yIndex+1, put in buffer, and run in zig (put in buffers during loop)

            // // if y == 7 { set flag
            // // if x == 6 && y == 7 { do the last one and be done

        }
    }

    return 1;
}

// Run skal også være her

/*
 * Function: HuffmanBuffer
 * Purpose: Apply Huffman coding to buffers
 * Input: 
 * Output: Error code
*/
int HuffmanBuffer() {


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
