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

int TestInput(int lumiQuantTable[], int chromiQuantTable[]) {

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
}

/*
 * Function: ReadDataToBuffer
 * Purpose: Read data from RAM, sanitise (remove alpha data)
 * Input: Address in RAM of data, resolution (is multiplied by 4 during function)
 * Output: Error code
*/
int ReadDataToBuffer(char* dataAddr, size_t res) {
    // Counter going through DataBuffer
    size_t byteNum = 0;
    size_t test = 0;

    BYTE r, g, b;

    // Source: https://ebookcentral.proquest.com/lib/aalborguniv-ebooks/reader.action?docID=867675
    // Using BT.709 standard
    int transMatrix[] = 
    {
        47, 157, 16,
        -26, -87, 112,
        112, -102, -10
    };

    for(size_t i = 0; i < (res * 4); i = i + 4) {
        // Order is rgba
        b = *(dataAddr + (i + 2));
        g = *(dataAddr + (i + 1));
        r = *(dataAddr + (i));

        // Note: var >> 8 is the same as var/256
        // Note also: Normally Y would have 16 added, and Cb Cr would have 128 added
        // They all have -128 to level shift
        yccBuffer[byteNum] = (((transMatrix[0]*r) + (transMatrix[1]*g) + (transMatrix[2]*b)) >> 8) - 112; // Y
        yccBuffer[byteNum + 1] = (((transMatrix[3]*r) + (transMatrix[4]*g) + (transMatrix[5]*b)) >> 8); // Cb
        yccBuffer[byteNum + 2] = (((transMatrix[6]*r) + (transMatrix[7]*g) + (transMatrix[8]*b)) >> 8); // Cr

        byteNum = byteNum + 3;
    }

    return 1;
}

/*
 * Function: DCTToBuffers
 * Purpose: Perform DCT on YCbCr data, split into 3 separate buffers
 * Input: Mode (0 = bigres, 1 = midres), pixel amount
 * Output: Error code
*/
int DCTToBuffers(int mode, size_t res) {

    return 1;
}

/*
 * Function: QuantBuffers
 * Purpose: Apply quantization table to DCT buffers in 8x8 blocks
 * Input: Mode (0 = bigres, 1 = midres), pixel amount
 * Output: Error code
*/
int QuantBuffers(int resMode, size_t res) {
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

    if(resMode == 0) {
        xRes = BIGXRES;
        yRes = BIGYRES;
    }
    else if(resMode == 1) {
        xRes = MIDXRES;
        yRes = MIDYRES;
    }
    else if(resMode == 2) {
        xRes = SMALLXRES;
        yRes = SMALLYRES;
    }
    else return 0;

    for(size_t yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(size_t xBlock = 0; xBlock < xRes/8; xBlock++) {
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    size_t xIndex = x + (xBlock * 8);
                    size_t yIndex = (y * xRes) + (yBlock * xRes * 8);
    
                    size_t indexToEdit = xIndex + yIndex;
                    size_t indexInTable = x*y;

                    dctYBuffer[indexToEdit] = dctYBuffer[indexToEdit]/lumiQuantTable[indexInTable];
                    dctCbBuffer[indexToEdit] = dctCbBuffer[indexToEdit]/chromiQuantTable[indexInTable];
                    dctCrBuffer[indexToEdit] = dctCrBuffer[indexToEdit]/chromiQuantTable[indexInTable];
                }
            }
        }
    }

    return 1;
}

int DiffDCBuffers(int resMode, size_t res) {
    int xRes = 0;
    int yRes = 0;

    if(resMode == 0) {
        xRes = 5344;
        yRes = 4016;
    }
    else if(resMode == 1) {
        xRes = 1920;
        yRes = 1080;
    }
    else return 0;

    int oldValue = 0;
    int newValue = 0;

    for(size_t yDC = 0; yDC < yRes/8; yDC++) {
        for(size_t xDC = 0; xDC < xRes/8; xDC++) {
            size_t xIndex = (xDC * 8);
            size_t yIndex = (yDC * xRes * 8);
    
            size_t indexToEdit = xIndex + yIndex;

            newValue = dctYBuffer[indexToEdit];
            dctYBuffer[indexToEdit] = dctYBuffer[indexToEdit] - oldValue;
            oldValue = newValue;
        }
    }

    oldValue = 0;
    newValue = 0;
    for(size_t yDC = 0; yDC < yRes/8; yDC++) {
        for(size_t xDC = 0; xDC < xRes/8; xDC++) {
            size_t xIndex = (xDC * 8);
            size_t yIndex = (yDC * xRes * 8);
    
            size_t indexToEdit = xIndex + yIndex;

            newValue = dctCbBuffer[indexToEdit];
            dctCbBuffer[indexToEdit] = dctCbBuffer[indexToEdit] - oldValue;
            oldValue = newValue;
        }
    }

    oldValue = 0;
    newValue = 0;
    for(size_t yDC = 0; yDC < yRes/8; yDC++) {
        for(size_t xDC = 0; xDC < xRes/8; xDC++) {
            size_t xIndex = (xDC * 8);
            size_t yIndex = (yDC * xRes * 8);
    
            size_t indexToEdit = xIndex + yIndex;

            newValue = dctCrBuffer[indexToEdit];
            dctCrBuffer[indexToEdit] = dctCrBuffer[indexToEdit] - oldValue;
            oldValue = newValue;
        }
    }

    return 1;
}

// Zig-zag og run skal også være her

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
