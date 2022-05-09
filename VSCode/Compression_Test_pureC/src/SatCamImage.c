/*
 * SatCamImage.h - Library for using the data stream from SatCam to build into a JPEG file with compression
 * Created by person, month date, 2022
*/

/* Include header files */
#include "SatCamImage.h"
#include "jpegheader.h"

/* Markers for JPEG creation */
BYTE SOI[2] = {0xff, 0xd8}; /* Start of Image Marker */
BYTE SOS[2] = {0xff, 0xda}; /* Start of Scan Marker */
BYTE EOI[2] = {0xff, 0xd9}; /* End of Image Marker */

<<<<<<< HEAD
// BitPos variables
int maxBitPos;
int bitPosInOutString;
=======
/* Defining extern variables */
size_t bitPosInOutString = 0;
size_t maxBitPos = sizeof(huffOutput) * 8;

YCBCR yccBuffer[BUFFERX][BUFFERY];
DCTPIXEL dctBuffer[BUFFERX][BUFFERY];
unsigned char huffOutput[BUFFERLEN];
>>>>>>> dc61d2b3faf26126e89e1a7f2a2223aca61f7817

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
int AddToBitString(int len, signed short bitsToAdd, int isNegative) {
    if(isNegative) {
        bitsToAdd = bitsToAdd-1;
    }

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

		// printf("Byte 1: %d  ", huffOutput[0]);
		// printf("Byte 2: %d  ", huffOutput[1]);
		// printf("Byte 3: %d  ", huffOutput[2]);
		// printf("Byte 4: %d  ", huffOutput[3]);
		// printf("Byte 5: %d  ", huffOutput[4]);
		// printf("Byte 6: %d  ", huffOutput[5]);
		// printf("bitPos: %d  ", bitPosInOutString);
		// printf("bitPos/8: %d\n", (bitPosInOutString/8));

		bitPosInOutString++;

        if(bitPosInOutString%8 == 0) {
            // printf("aaaa\n");
            if(huffOutput[(bitPosInOutString/8) - 1] == 255) {
                // printf("AAAA\n");
                bitPosInOutString = bitPosInOutString + 8;
            }
        }
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
    enum RESMODE res = MID;

    // FILE* fInput = fopen("memdump_comp_buf_fhd", "r");
    // FILE* fInput = fopen("C:\\Users\\sande\\Documents\\Git\\EIT4-410-SatCam\\VSCode\\Compression_Test_pureC\\output\\memdump_comp_buf_fhd", "r");
<<<<<<< HEAD
    FILE* fInput = fopen("C:\\Users\\sande\\Documents\\Git\\EIT4-410-SatCam\\VSCode\\Compression_Test_pureC\\output\\21MP-Garbage.bin", "r");
=======
    FILE* fInput = fopen("/home/mark_el/Documents/Programming/Python_BACKUP/Compression/EIT4-410-SatCam/VSCode/Compression_Test_pureC/output/memdump_comp_buf_fhd", "r");
>>>>>>> dc61d2b3faf26126e89e1a7f2a2223aca61f7817

    if(fInput == NULL){
		printf("\nError opening file in fInput.\n");
		return 0;
	}

    printf("Input file is open.\n");

    fseek(fInput, 0, SEEK_END);
	long fileLength = ftell(fInput);
	fseek(fInput, 0, SEEK_SET);

    char *buffer = (char*) malloc(sizeof(char)*fileLength);

	char ch = (char) fgetc(fInput);

	printf("We are set up.\n");

	int buffIndex = 0;
	while(!feof(fInput)) {
		*(buffer + buffIndex) = ch;
		// buffer[i] = ch;
		ch = (char) fgetc(fInput);
		buffIndex++;
	}

	printf("We are past feof.\n");

    if(ReadDataToBuffer(buffer, res)) {
        printf("ReadDataToBuffer returned fine.\n");
        FILE* yccOutput = fopen("YCC_buf", "w");
        
        char *yccOutBuf = (char*) malloc(sizeof(char)*MIDRESLEN*3);

        int i = 0;
        for(int y = 0; y < MIDYRES; y++) {
            for(int x = 0; x < MIDXRES; x++) {
                *(yccOutBuf + i) = yccBuffer[x][y].Y;
                *(yccOutBuf + i + 1) = yccBuffer[x][y].Cb;
                *(yccOutBuf + i + 2) = yccBuffer[x][y].Cr;

                i = i+3;
            }
        }
        
        fwrite(yccOutBuf, 1, 3*MIDRESLEN, yccOutput);
        fclose(yccOutput);

        // fwrite(*yccBuffer, 1, 3*MIDRESLEN, yccOutput);
        // fclose(yccOutput);

        return 0;
        
        // OutputYCbCr(res, 0);
    }
    else {
        printf("Oops\n");
        return 0;
    }

    free(buffer);
    fclose(fInput);
    // return 0;

    // signed int yBuf[64] = {
    //     -7, -16, 70, 69, 71, 67, 70, 65, 
    //     -6, -20, 67, 66, 75, 67, 71, 65, 
    //     -5, -7, 87, 89, 91, 86, 88, 73, 
    //     -6, -16, 77, 72, 78, 70, 77, 68, 
    //     1, -2, 90, 91, 90, 93, 93, 91, 
    //     -4, -7, 88, 92, 93, 89, 89, 77, 
    //     1, -6, 88, 90, 89, 92, 91, 83, 
    //     0, -2, 87, 90, 87, 93, 93, 93
    // };
    //
    // signed int cbBuf[64] = {
    //     2, -64, 11, 5, 13, 1, 15, 3, 
    //     0, -61, -2, 2, 2, 4, -2, 1, 
    //     -1, -69, 1, -11, 1, -7, 3, -3, 
    //     4, -64, 7, 19, 9, 15, 11, 13, 
    //     0, -72, 1, 8, 1, 2, 3, 0, 
    //     2, -69, 0, 4, 0, 8, 2, 14, 
    //     0, -70, 5, 6, 3, 6, 1, 10, 
    //     -1, -72, 2, 4, 2, 4, 3, 5
    // };
    //
    // signed int crBuf[64] = {
    //     -1, -80, -6, -7, -8, -7, -9, -7, 
    //     -1, -78, 8, -9, 2, -6, 3, -7, 
    //     0, -87, -7, -8, -10, -8, -10, 0, 
    //     -1, -80, 7, -9, 4, -9, 3, -8, 
    //     -1, -91, -2, -5, -4, -8, -8, -9, 
    //     -1, -87, -6, -10, -7, -10, -8, -3, 
    //     0, -88, -6, -5, -4, -10, -9, -2, 
    //     0, -91, -7, -4, -8, -8, -9, -10
    // };
    //
    // for(int y = 0; y < 8; y++) {
    //     for(int x = 0; x < 8; x++) {
    //         yccBuffer[x][y].Y = yBuf[x+(y*8)];
    //         yccBuffer[x][y].Cb = cbBuf[x+(y*8)];
    //         yccBuffer[x][y].Cr = crBuf[x+(y*8)];
    //     }
    // }
    //
    // signed int yBuf[256] = {
    //     -7, -16, 70, 69, 71, 67, 70, 65, -6, -20, 67, 66, 75, 67, 71, 65, -5, -7, 87, 89, 91, 86, 88, 73, -6, -16, 77, 72, 78, 70, 77, 68, 1, -2, 90, 91, 90, 93, 93, 91, -4, -7, 88, 92, 93, 89, 89, 77, 1, -6, 88, 90, 89, 92, 91, 83, 0, -2, 87, 90, 87, 93, 93, 93, 68, 68, 70, 62, 64, 67, 69, 69, 70, 64, 69, 62, 69, 68, 73, 69, 75, 84, 88, 85, 88, 81, 83, 82, 74, 71, 77, 66, 72, 70, 73, 72, 91, 92, 91, 92, 91, 85, 83, 87, 78, 87, 87, 88, 87, 83, 84, 85, 81, 82, 83, 90, 88, 88, 88, 89, 90, 91, 89, 91, 90, 85, 85, 87, 1, -8, 90, 85, 85, 93, 92, 88, 1, -6, 88, 90, 89, 91, 91, 81, -2, -6, 93, 96, 95, 91, 92, 87, 1, -8, 91, 85, 88, 92, 93, 88, 1, -6, 86, 95, 94, 92, 92, 90, -1, -6, 95, 96, 91, 92, 92, 89, 3, -4, 91, 88, 87, 88, 87, 92, 1, -6, 86, 95, 92, 92, 91, 90, 86, 84, 83, 86, 85, 90, 88, 82, 81, 83, 85, 89, 89, 88, 89, 89, 89, 86, 85, 89, 89, 88, 88, 89, 88, 84, 84, 87, 85, 90, 87, 82, 88, 88, 87, 90, 89, 89, 88, 92, 89, 86, 85, 90, 88, 89, 86, 89, 91, 91, 91, 93, 92, 92, 92, 86, 88, 89, 87, 90, 89, 88, 88, 93
    // };
    //
    // signed int cbBuf[256] = {
    //     2, -64, 11, 5, 13, 1, 15, 3, 0, -61, -2, 2, 2, 4, -2, 1, -1, -69, 1, -11, 1, -7, 3, -3, 4, -64, 7, 19, 9, 15, 11, 13, 0, -72, 1, 8, 1, 2, 3, 0, 2, -69, 0, 4, 0, 8, 2, 14, 0, -70, 5, 6, 3, 6, 1, 10, -1, -72, 2, 4, 2, 4, 3, 5, 13, 1, 11, 7, 14, 3, 12, 1, -2, 2, 2, 5, -1, 5, -4, 0, 8, -10, 5, -8, 4, -2, 5, -7, 9, 16, 7, 21, 9, 18, 10, 14, -1, 4, 1, 6, -1, 10, 1, 5, 7, 3, 5, 6, 5, 8, 4, 7, 2, 5, 6, 6, 1, 5, 2, 5, 0, 1, 2, 1, 0, 8, 0, 6, -1, -69, 1, 7, 8, 4, 1, 8, 2, -70, 5, 7, 3, 1, 1, 2, 3, -69, 2, 3, 1, 1, 2, -2, -1, -69, 1, 8, 6, 1, 0, 8, 0, -70, 4, 2, -1, 2, 2, 7, 4, -69, 2, 3, 3, 3, 2, 6, 2, -71, 0, 8, 3, 5, 1, 5, 1, -70, 4, 2, 0, 1, 2, 8, 1, 6, 2, 4, 2, 5, -1, 9, 2, 9, 4, 2, 1, 5, 1, 5, 6, 8, 2, 2, 0, 5, 2, 5, 0, 7, 1, 8, 2, 5, 0, 6, -2, 5, 2, 7, 2, 6, 1, 0, 6, 7, 2, 6, 0, 6, 2, 5, 2, 4, 2, 4, 0, 4, 2, 7, -2, 7, 2, 6, 1, 5, 1, 3
    // };
    //
    // signed int crBuf[256] = {
    //     -1, -80, -6, -7, -8, -7, -9, -7, -1, -78, 8, -9, 2, -6, 3, -7, 0, -87, -7, -8, -10, -8, -10, 0, -1, -80, 7, -9, 4, -9, 3, -8, -1, -91, -2, -5, -4, -8, -8, -9, -1, -87, -6, -10, -7, -10, -8, -3, 0, -88, -6, -5, -4, -10, -9, -2, 0, -91, -7, -4, -8, -8, -9, -10, -8, -6, -8, -5, -7, -5, -6, -4, 2, -4, 3, -5, 7, -13, 0, -8, -2, -7, -10, -4, -6, -6, -7, -7, 3, -9, 3, -8, 6, -7, 0, -7, -9, -8, -7, -8, -7, -9, -7, -12, 2, -9, -11, -7, -8, -8, -4, -9, -1, -8, -8, -10, -10, -8, -7, -7, -11, -7, -10, -7, -9, -8, -4, -12, 0, -87, -9, -6, -6, -9, -8, -9, -1, -88, -7, -5, -4, -9, -8, -1, -1, -88, -10, -9, -8, -8, -8, -6, 0, -87, -8, -6, -2, -8, -7, -9, 0, -88, -4, -7, -6, -6, -7, -8, -1, -88, -8, -9, -15, -9, -8, -7, -1, -89, -6, -12, -11, -6, -5, -10, -1, -88, -4, -6, -10, -6, -8, -8, -8, -6, -6, -6, -6, -7, -6, -1, -1, -8, -3, -10, -8, -8, -5, -7, -7, -4, -3, -8, -8, -5, -4, -9, -6, -6, -4, -7, -7, -7, -8, -1, -6, -7, -6, -11, -10, -9, -8, -6, -8, -4, -3, -9, -9, -5, -6, -9, -9, -7, -7, -12, -11, -10, -10, -7, -6, -7, -6, -11, -8, -9, -7, -7
    // };
    //
    // for(int yBlock = 0; yBlock < 2; yBlock++) {
    //     for(int xBlock = 0; xBlock < 2; xBlock++) {
    //         for(int y = 0; y < 8; y++) {
    //             for(int x = 0; x < 8; x++) {
    //                 yccBuffer[x+(xBlock * 8)][y+(yBlock * 8)].Y = yBuf[x+(y*8)+(64*xBlock)+(128*yBlock)];
    //                 yccBuffer[x+(xBlock * 8)][y+(yBlock * 8)].Cb = cbBuf[x+(y*8)+(64*xBlock)+(128*yBlock)];
    //                 yccBuffer[x+(xBlock * 8)][y+(yBlock * 8)].Cr = crBuf[x+(y*8)+(64*xBlock)+(128*yBlock)];
    //             }
    //         }
    //     }
    // }
    //
    // int printx = 16;
    // int printy = 16;
    // printDCTY(8, 8, 1912, 1072);

    if(DCTToBuffers(res)) {
        printf("DCT returned fine.\n");

        // printDCTY(printx, printy);

        // OutputYCbCr(res, 1, 1);
        // return 0;
    }
    else {
        printf("Oops\n");
        return 0;
    }

    // printDCTY(8, 8, 1904, 1072);
    // printDCTY(8, 8, 1912, 1072);

    if(QuantBuffers(res)) {
        printf("Quant returned fine.\n");

        // printDCTY(printx, printy);

        // OutputYCbCr(res, 1, 2);
        // return 0;
    }
    else {
        printf("Oops\n");
        return 0;
    }

    // printDCTY(8, 8, 1904, 1072);
    // printDCTY(8, 8, 1912, 1072);

    if(DiffDCBuffers(res)) {
        printf("DiffDC returned fine.\n");

        // printDCTY(printx, printy);

        // OutputYCbCr(res, 1, 3);
        // return 0;
    }
    else {
        printf("Oops\n");
        return 0;
    }

    // printDCTY(72, 1, 1800, 0);
    // printDCTCb(72, 1, 1800, 0);
    // printDCTCr(72, 1, 1800, 0);
    // printDCTY(8, 8, 1912, 1072);

    if(ZigzagBuffers(res)) {
        printf("Zigzag returned fine.\n");

        // printDCTY(printx, printy);

        // OutputYCbCr(res, 1, 4);
        // return 0;
    }
    else {
        printf("Oops\n");
        return 0;
    }

    // signed int yBuf[64] = {
    //     127, 127, -4, -1, 1, -17, -4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    // };
    //
    // signed int cbBuf[64] = {
    //     -2, -5, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    // };
    //
    // signed int crBuf[64] = {
    //     -7, -5, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    // };
    //
    // for(int y = 0; y < 8; y++) {
    //     for(int x = 0; x < 8; x++) {
    //         dctBuffer[x][y].Y = yBuf[x+(y*8)];
    //         dctBuffer[x][y].Cb = cbBuf[x+(y*8)];
    //         dctBuffer[x][y].Cr = crBuf[x+(y*8)];
    //     }
    // }
    //
    // signed int yBuf[256] = {
    //     30, -20, -4, -1, 1, -17, -4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, -5, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6, -22, 0, 0, 0, -17, -5, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    // };
    //
    // signed int cbBuf[256] = {
    //     -2, -5, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, -5, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    // };
    //
    // signed int crBuf[256] = {
    //     -7, -5, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, -5, 0, 0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    // };
    //
    // for(int yBlock = 0; yBlock < 2; yBlock++) {
    //     for(int xBlock = 0; xBlock < 2; xBlock++) {
    //         for(int y = 0; y < 8; y++) {
    //             for(int x = 0; x < 8; x++) {
    //                 dctBuffer[x+(xBlock * 8)][y+(yBlock * 8)].Y = yBuf[x+(y*8)+(64*xBlock)+(128*yBlock)];
    //                 dctBuffer[x+(xBlock * 8)][y+(yBlock * 8)].Cb = cbBuf[x+(y*8)+(64*xBlock)+(128*yBlock)];
    //                 dctBuffer[x+(xBlock * 8)][y+(yBlock * 8)].Cr = crBuf[x+(y*8)+(64*xBlock)+(128*yBlock)];
    //             }
    //         }
    //     }
    // }
    //
    // printDCTY(8, 8, 1912, 1072);
    // res = TEST2;

    if(HuffmanEncode(res)) {
        printf("Huff returned fine.\n");
        // OutputYCbCr(res, 1, 5);
        // OutputYCbCr(TEST, 1, 5);
        // return 0;
    }
    else {
        printf("Oops\n");
        return 0;
    }

    while(!(bitPosInOutString%8 == 0)) {
        AddToBitString(1, 1, 0);
    }

    // FILE* fOutput = fopen("memdump_comp_buf_fhd_after_new_colour", "w");
    // fwrite(huffOutput, 1, bitPosInOutString/8, fOutput);

    FILE* fOutput = fopen("memdump_comp_buf_fhd_after_data_change.jpeg", "w");
    // FILE* fOutput = fopen("21MP_LUL.jpeg", "r");

    fwrite(jpegheader, 1, sizeof(jpegheader), fOutput);
    fwrite(huffOutput, 1, bitPosInOutString/8, fOutput);
    fwrite(jpegfooter, 1, sizeof(jpegfooter), fOutput);
    fclose(fOutput);

    return 1;
}

// This tests DCT
// int TestInput() {
//     signed int yBuf[64] = {
//         -7, -16, 70, 69, 71, 67, 70, 65, 
//         -6, -20, 67, 66, 75, 67, 71, 65, 
//         -5, -7, 87, 89, 91, 86, 88, 73, 
//         -6, -16, 77, 72, 78, 70, 77, 68, 
//         1, -2, 90, 91, 90, 93, 93, 91, 
//         -4, -7, 88, 92, 93, 89, 89, 77, 
//         1, -6, 88, 90, 89, 92, 91, 83, 
//         0, -2, 87, 90, 87, 93, 93, 93
//     };
//
//     signed int cbBuf[64] = {
//         2, -64, 11, 5, 13, 1, 15, 3, 
//         0, -61, -2, 2, 2, 4, -2, 1, 
//         -1, -69, 1, -11, 1, -7, 3, -3, 
//         4, -64, 7, 19, 9, 15, 11, 13, 
//         0, -72, 1, 8, 1, 2, 3, 0, 
//         2, -69, 0, 4, 0, 8, 2, 14, 
//         0, -70, 5, 6, 3, 6, 1, 10, 
//         -1, -72, 2, 4, 2, 4, 3, 5
//     };
//
//     signed int crBuf[64] = {
//         -1, -80, -6, -7, -8, -7, -9, -7, 
//         -1, -78, 8, -9, 2, -6, 3, -7, 
//         0, -87, -7, -8, -10, -8, -10, 0, 
//         -1, -80, 7, -9, 4, -9, 3, -8, 
//         -1, -91, -2, -5, -4, -8, -8, -9, 
//         -1, -87, -6, -10, -7, -10, -8, -3, 
//         0, -88, -6, -5, -4, -10, -9, -2, 
//         0, -91, -7, -4, -8, -8, -9, -10
//     };
//
//     // signed int yBuf[256] = {
//     //     -7, -16, 70, 69, 71, 67, 70, 65, -6, -20, 67, 66, 75, 67, 71, 65, -5, -7, 87, 89, 91, 86, 88, 73, -6, -16, 77, 72, 78, 70, 77, 68, 1, -2, 90, 91, 90, 93, 93, 91, -4, -7, 88, 92, 93, 89, 89, 77, 1, -6, 88, 90, 89, 92, 91, 83, 0, -2, 87, 90, 87, 93, 93, 93, 68, 68, 70, 62, 64, 67, 69, 69, 70, 64, 69, 62, 69, 68, 73, 69, 75, 84, 88, 85, 88, 81, 83, 82, 74, 71, 77, 66, 72, 70, 73, 72, 91, 92, 91, 92, 91, 85, 83, 87, 78, 87, 87, 88, 87, 83, 84, 85, 81, 82, 83, 90, 88, 88, 88, 89, 90, 91, 89, 91, 90, 85, 85, 87, 1, -8, 90, 85, 85, 93, 92, 88, 1, -6, 88, 90, 89, 91, 91, 81, -2, -6, 93, 96, 95, 91, 92, 87, 1, -8, 91, 85, 88, 92, 93, 88, 1, -6, 86, 95, 94, 92, 92, 90, -1, -6, 95, 96, 91, 92, 92, 89, 3, -4, 91, 88, 87, 88, 87, 92, 1, -6, 86, 95, 92, 92, 91, 90, 86, 84, 83, 86, 85, 90, 88, 82, 81, 83, 85, 89, 89, 88, 89, 89, 89, 86, 85, 89, 89, 88, 88, 89, 88, 84, 84, 87, 85, 90, 87, 82, 88, 88, 87, 90, 89, 89, 88, 92, 89, 86, 85, 90, 88, 89, 86, 89, 91, 91, 91, 93, 92, 92, 92, 86, 88, 89, 87, 90, 89, 88, 88, 93
//     // };
//
//     // signed int cbBuf[256] = {
//     //     2, -64, 11, 5, 13, 1, 15, 3, 0, -61, -2, 2, 2, 4, -2, 1, -1, -69, 1, -11, 1, -7, 3, -3, 4, -64, 7, 19, 9, 15, 11, 13, 0, -72, 1, 8, 1, 2, 3, 0, 2, -69, 0, 4, 0, 8, 2, 14, 0, -70, 5, 6, 3, 6, 1, 10, -1, -72, 2, 4, 2, 4, 3, 5, 13, 1, 11, 7, 14, 3, 12, 1, -2, 2, 2, 5, -1, 5, -4, 0, 8, -10, 5, -8, 4, -2, 5, -7, 9, 16, 7, 21, 9, 18, 10, 14, -1, 4, 1, 6, -1, 10, 1, 5, 7, 3, 5, 6, 5, 8, 4, 7, 2, 5, 6, 6, 1, 5, 2, 5, 0, 1, 2, 1, 0, 8, 0, 6, -1, -69, 1, 7, 8, 4, 1, 8, 2, -70, 5, 7, 3, 1, 1, 2, 3, -69, 2, 3, 1, 1, 2, -2, -1, -69, 1, 8, 6, 1, 0, 8, 0, -70, 4, 2, -1, 2, 2, 7, 4, -69, 2, 3, 3, 3, 2, 6, 2, -71, 0, 8, 3, 5, 1, 5, 1, -70, 4, 2, 0, 1, 2, 8, 1, 6, 2, 4, 2, 5, -1, 9, 2, 9, 4, 2, 1, 5, 1, 5, 6, 8, 2, 2, 0, 5, 2, 5, 0, 7, 1, 8, 2, 5, 0, 6, -2, 5, 2, 7, 2, 6, 1, 0, 6, 7, 2, 6, 0, 6, 2, 5, 2, 4, 2, 4, 0, 4, 2, 7, -2, 7, 2, 6, 1, 5, 1, 3
//     // };
//
//     // signed int crBuf[256] = {
//     //     -1, -80, -6, -7, -8, -7, -9, -7, -1, -78, 8, -9, 2, -6, 3, -7, 0, -87, -7, -8, -10, -8, -10, 0, -1, -80, 7, -9, 4, -9, 3, -8, -1, -91, -2, -5, -4, -8, -8, -9, -1, -87, -6, -10, -7, -10, -8, -3, 0, -88, -6, -5, -4, -10, -9, -2, 0, -91, -7, -4, -8, -8, -9, -10, -8, -6, -8, -5, -7, -5, -6, -4, 2, -4, 3, -5, 7, -13, 0, -8, -2, -7, -10, -4, -6, -6, -7, -7, 3, -9, 3, -8, 6, -7, 0, -7, -9, -8, -7, -8, -7, -9, -7, -12, 2, -9, -11, -7, -8, -8, -4, -9, -1, -8, -8, -10, -10, -8, -7, -7, -11, -7, -10, -7, -9, -8, -4, -12, 0, -87, -9, -6, -6, -9, -8, -9, -1, -88, -7, -5, -4, -9, -8, -1, -1, -88, -10, -9, -8, -8, -8, -6, 0, -87, -8, -6, -2, -8, -7, -9, 0, -88, -4, -7, -6, -6, -7, -8, -1, -88, -8, -9, -15, -9, -8, -7, -1, -89, -6, -12, -11, -6, -5, -10, -1, -88, -4, -6, -10, -6, -8, -8, -8, -6, -6, -6, -6, -7, -6, -1, -1, -8, -3, -10, -8, -8, -5, -7, -7, -4, -3, -8, -8, -5, -4, -9, -6, -6, -4, -7, -7, -7, -8, -1, -6, -7, -6, -11, -10, -9, -8, -6, -8, -4, -3, -9, -9, -5, -6, -9, -9, -7, -7, -12, -11, -10, -10, -7, -6, -7, -6, -11, -8, -9, -7, -7
//     // };
//
//     // for(int yBlock = 0; yBlock < 2; yBlock++) {
//     //     for(int xBlock = 0; xBlock < 2; xBlock++) {
//     //         for(int y = 0; y < 8; y++) {
//     //             for(int x = 0; x < 8; x++) {
//     //                 yccBuffer[x+(xBlock * 8)][y+(yBlock * 8)].Y = yBuf[x+(y*8)+(64*xBlock)+(128*yBlock)];
//     //                 yccBuffer[x+(xBlock * 8)][y+(yBlock * 8)].Cb = cbBuf[x+(y*8)+(64*xBlock)+(128*yBlock)];
//     //                 yccBuffer[x+(xBlock * 8)][y+(yBlock * 8)].Cr = crBuf[x+(y*8)+(64*xBlock)+(128*yBlock)];
//     //             }
//     //         }
//     //     }
//     // }
//
//     signed int yBuf[64] = {
//         -7, -16, 70, 69, 71, 67, 70, 65, 
//         -6, -20, 67, 66, 75, 67, 71, 65, 
//         -5, -7, 87, 89, 91, 86, 88, 73, 
//         -6, -16, 77, 72, 78, 70, 77, 68, 
//         1, -2, 90, 91, 90, 93, 93, 91, 
//         -4, -7, 88, 92, 93, 89, 89, 77, 
//         1, -6, 88, 90, 89, 92, 91, 83, 
//         0, -2, 87, 90, 87, 93, 93, 93
//     };
//
//     for(int y = 0; y < 8; y++) {
//         for(int x = 0; x < 8; x++) {
//             yccBuffer[x][y].Y = yBuf[x+(y*8)];
//             yccBuffer[x][y].Cb = cbBuf[x+(y*8)];
//             yccBuffer[x][y].Cr = crBuf[x+(y*8)];
//         }
//     }
//
//     printf("ycc buffer:\n(\n");
//     for(int y = 0; y < 8; y++) {
//         for(int x = 0; x < 8; x++) {
//             printf("%d, ", yccBuffer[x][y].Y);
//         }
//         printf("\n");
//     }
//     printf(")\n");
//
//     if(DCTToBuffers(TEST) == 1) {
//         printf("DCT good\n");
//     }
//
//     printf("DCT Y buffer:\n(\n");
//     for(int y = 0; y < 8; y++) {
//         for(int x = 0; x < 8; x++) {
//             printf("%d, ", dctBuffer[x][y].Y);
//         }
//         printf("\n");
//     }
//     printf(")\n");
//
//     printf("DCT Cb buffer:\n(\n");
//     for(int y = 0; y < 8; y++) {
//         for(int x = 0; x < 8; x++) {
//             printf("%d, ", dctBuffer[x][y].Cb);
//         }
//         printf("\n");
//     }
//     printf(")\n");
//
//     printf("DCT Cr buffer:\n(\n");
//     for(int y = 0; y < 8; y++) {
//         for(int x = 0; x < 8; x++) {
//             printf("%d, ", dctBuffer[x][y].Cr);
//         }
//         printf("\n");
//     }
//     printf(")\n");
//
//     return 1;
// }

// This tests zig-zag
// int TestInput() {
//
//     int testBuffer[8][8] = {
//         {0,   1,  5,  6, 14, 15, 27, 28},
//         {2,   4,  7, 13, 16, 26, 29, 42},
//         {3,   8, 12, 17, 25, 30, 41, 43},
//         {9,  11, 18, 24, 31, 40, 44, 53},
//         {10, 19, 23, 32, 39, 45, 52, 54},
//         {20, 22, 33, 38, 46, 51, 55, 60},
//         {21, 34, 37, 47, 50, 56, 59, 61},
//         {35, 36, 48, 49, 57, 58, 62, 63},
//     };
//
//     int testBuffer2[16][16] = {
//         {0,   1,  5,  6, 14, 15, 27, 28, 0,   1,  5,  6, 14, 15, 27, 28},
//         {2,   4,  7, 13, 16, 26, 29, 42, 2,   4,  7, 13, 16, 26, 29, 42},
//         {3,   8, 12, 17, 25, 30, 41, 43, 3,   8, 12, 17, 25, 30, 41, 43},
//         {9,  11, 18, 24, 31, 40, 44, 53, 9,  11, 18, 24, 31, 40, 44, 53},
//         {10, 19, 23, 32, 39, 45, 52, 54, 10, 19, 23, 32, 39, 45, 52, 54},
//         {20, 22, 33, 38, 46, 51, 55, 60, 20, 22, 33, 38, 46, 51, 55, 60},
//         {21, 34, 37, 47, 50, 56, 59, 61, 21, 34, 37, 47, 50, 56, 59, 61},
//         {35, 36, 48, 49, 57, 58, 62, 63, 35, 36, 48, 49, 57, 58, 62, 63},
//         {0,   1,  5,  6, 14, 15, 27, 28, 0,   1,  5,  6, 14, 15, 27, 28},
//         {2,   4,  7, 13, 16, 26, 29, 42, 2,   4,  7, 13, 16, 26, 29, 42},
//         {3,   8, 12, 17, 25, 30, 41, 43, 3,   8, 12, 17, 25, 30, 41, 43},
//         {9,  11, 18, 24, 31, 40, 44, 53, 9,  11, 18, 24, 31, 40, 44, 53},
//         {10, 19, 23, 32, 39, 45, 52, 54, 10, 19, 23, 32, 39, 45, 52, 54},
//         {20, 22, 33, 38, 46, 51, 55, 60, 20, 22, 33, 38, 46, 51, 55, 60},
//         {21, 34, 37, 47, 50, 56, 59, 61, 21, 34, 37, 47, 50, 56, 59, 61},
//         {35, 36, 48, 49, 57, 58, 62, 63, 35, 36, 48, 49, 57, 58, 62, 63},
//     };
//
//     for(int j = 0; j < 16; j++) {
//         for(int i = 0; i < 16; i++) {
//             dctYBuffer[i][j] = testBuffer2[j][i];
//         }
//     }
//
//     ZigzagBuffers(TEST2);
//     // int result = DCTToBuffers(TEST);
//
//     printf("Y buffer:\n(\n");
//     for(int j = 0; j < 16; j++) {
//         for(int i = 0; i < 16; i++) {
//             printf("%d, ", dctYBuffer[i][j]);
//         }
//         printf("\n");
//     }
//     printf(")\n");
//
//     return 1;
// }

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
    
    // Source: https://ebookcentral.proquest.com/lib/aalborguniv-ebooks/reader.action?docID=867675
    // Using BT.709 standard
    int transMatrix[] = 
    {
        47, 157, 16,
        -26, -87, 112,
        112, -102, -10
    };

    // printf("r    g    b    y  cb  cr\n");
    BYTE r, g, b;
    for(int yPos = 0; yPos < yRes; yPos++) {
        for(int xPos = 0; xPos < xRes; xPos++) {
            int dataIndex = ((xPos*4) + (yPos * xRes));

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
            // yccBuffer[xPos][yPos].Y = ((transMatrix[0]*r) + (transMatrix[1]*g) + (transMatrix[2]*b)) - 112;
            // yccBuffer[xPos][yPos].Cb = ((transMatrix[3]*r) + (transMatrix[4]*g) + (transMatrix[5]*b));
            // yccBuffer[xPos][yPos].Cr = ((transMatrix[6]*r) + (transMatrix[7]*g) + (transMatrix[8]*b));

            // if(dataIndex % 131072 == 0) {
            //     printf("%d  %d  %d  %d  %d  %d\n", r, g, b, yccBuffer[xPos][yPos].Y, yccBuffer[xPos][yPos].Cb, yccBuffer[xPos][yPos].Cr);
            // }
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

    for(int yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(int xBlock = 0; xBlock < xRes/8; xBlock++) {
            
            for(int yStart = 0; yStart < 8; yStart++) {
                for(int xStart = 0; xStart < 8; xStart++) {
                    if(xStart == 0)   aP = 1 / sqrt(8);
                    else            aP = sqrt(2) / sqrt(8);

                    if(yStart == 0)   aQ = 1 / sqrt(8);
                    else            aQ = sqrt(2) / sqrt(8);

                    dctYSum = 0;
                    dctCbSum = 0;
                    dctCrSum = 0;

                    for(int y = 0; y < 8; y++) {
                        for(int x = 0; x < 8; x++) {
                            int xIndex = x + (xBlock * 8);
                            int yIndex = y + (yBlock * 8);

                            dctY =  yccBuffer[xIndex][yIndex].Y *
                                cos(((2 * x + 1) * 3.142857 * xStart) / (2 * 8)) *
                                cos(((2 * y + 1) * 3.142857 * yStart) / (2 * 8));
                            dctYSum = dctYSum + dctY;

                            dctCb =  yccBuffer[xIndex][yIndex].Cb *
                                cos(((2 * x + 1) * 3.142857 * xStart) / (2 * 8)) *
                                cos(((2 * y + 1) * 3.142857 * yStart) / (2 * 8));
                            dctCbSum = dctCbSum + dctCb;

                            dctCr =  yccBuffer[xIndex][yIndex].Cr *
                                cos(((2 * x + 1) * 3.142857 * xStart) / (2 * 8)) *
                                cos(((2 * y + 1) * 3.142857 * yStart) / (2 * 8));
                            dctCrSum = dctCrSum + dctCr;

                        }
                    }

                    dctBuffer[xStart + (xBlock * 8)][yStart + (yBlock * 8)].Y = aP * aQ * dctYSum;
                    dctBuffer[xStart + (xBlock * 8)][yStart + (yBlock * 8)].Cb = aP * aQ * dctCbSum;
                    dctBuffer[xStart + (xBlock * 8)][yStart + (yBlock * 8)].Cr = aP * aQ * dctCrSum;
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

    for(int yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(int xBlock = 0; xBlock < xRes/8; xBlock++) {
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {

                    int xIndex = x + (xBlock * 8);
                    int yIndex = y + (yBlock * 8);

                    int indexInTable = x + (y * 8);

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

    int yDC = 0;
    int xDC = 0;

    for(yDC = 0; yDC < yRes/8; yDC++) {
        for(xDC = 0; xDC < xRes/8; xDC++) {
            int xIndex = (xDC * 8);
            int yIndex = (yDC * 8);

            // printf("   old new\n");

            newYValue = dctBuffer[xIndex][yIndex].Y; 
            dctBuffer[xIndex][yIndex].Y = dctBuffer[xIndex][yIndex].Y - oldYValue; 
            // printf("Y  %d", newYValue);
            // printf("  %d\n", dctBuffer[xIndex][yIndex].Y);
            oldYValue = newYValue; 

            newCbValue = dctBuffer[xIndex][yIndex].Cb; 
            dctBuffer[xIndex][yIndex].Cb = dctBuffer[xIndex][yIndex].Cb - oldCbValue; 
            // printf("Cb  %d", newCbValue);
            // printf("  %d\n", dctBuffer[xIndex][yIndex].Cb);
            oldCbValue = newCbValue; 

            newCrValue = dctBuffer[xIndex][yIndex].Cr; 
            dctBuffer[xIndex][yIndex].Cr = dctBuffer[xIndex][yIndex].Cr - oldCrValue; 
            // printf("Cr  %d", newCrValue);
            // printf("  %d\n", dctBuffer[xIndex][yIndex].Cr);
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
    for(int yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(int xBlock = 0; xBlock < xRes/8; xBlock++) {
            
            // First with Y buffer
            DCT zzBuffer[8][8];
            // Put the data from the DCT buffer in the right order
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    int dctXIndex = blockXIndex[x + y * 8] + (8*xBlock);
                    int dctYIndex = blockYIndex[x + y * 8] + (8*yBlock);

                    zzBuffer[x][y] = dctBuffer[dctXIndex][dctYIndex].Y;
                }
            }
            // Put the rightly ordered data back into the DCT buffer
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    int dctXIndex = x + (8*xBlock);
                    int dctYIndex = y + (8*yBlock);
                    
                    dctBuffer[dctXIndex][dctYIndex].Y = zzBuffer[x][y];
                }
            }

            // Then with Cb buffer
            memset(zzBuffer, 0, 8*8*sizeof(DCT));
            // Put the data from the DCT buffer in the right order
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    int dctXIndex = blockXIndex[x + y * 8] + (8*xBlock);
                    int dctYIndex = blockYIndex[x + y * 8] + (8*yBlock);

                    zzBuffer[x][y] = dctBuffer[dctXIndex][dctYIndex].Cb;
                }
            }
            // Put the rightly ordered data back into the DCT buffer
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    int dctXIndex = x + (8*xBlock);
                    int dctYIndex = y + (8*yBlock);
                    
                    dctBuffer[dctXIndex][dctYIndex].Cb = zzBuffer[x][y];
                }
            }

            // Finally with Cr buffer
            memset(zzBuffer, 0, 8*8*sizeof(DCT));
            // Put the data from the DCT buffer in the right order
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    int dctXIndex = blockXIndex[x + y * 8] + (8*xBlock);
                    int dctYIndex = blockYIndex[x + y * 8] + (8*yBlock);

                    zzBuffer[x][y] = dctBuffer[dctXIndex][dctYIndex].Cr;
                }
            }
            // Put the rightly ordered data back into the DCT buffer
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    int dctXIndex = x + (8*xBlock);
                    int dctYIndex = y + (8*yBlock);
                    
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

    // Initializing variable
    bitPosInOutString = 0;

    /* Tables for categories */
    static const int huffCatTable[12][2] = {
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
    //int numBits = 0; // Keeps track of how many bits to add from original value
    int tableIndex; // Holds whichever index is needed for the table

    for(int yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(int xBlock = 0; xBlock < xRes/8; xBlock++) {
            /*---------------------------------------------------------------*/
            // Y
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    int xIndex = x + (xBlock * 8);
                    int yIndex = y + (yBlock * 8);

                    // Find category
                    cat = -1;
                    for(int i = 0; i < catAmount; i++) {
                        if((huffCatTable[i][0] <= dctBuffer[xIndex][yIndex].Y && huffCatTable[i][1] >= dctBuffer[xIndex][yIndex].Y) 
                            || (-huffCatTable[i][0] >= dctBuffer[xIndex][yIndex].Y && -huffCatTable[i][1] <= dctBuffer[xIndex][yIndex].Y)) {
                            
                            cat = i;
                            i = catAmount+1;
                        }
                    }
                    if(cat == -1) return -1; // Sanity check, exits if problem arises
                    
                    // If it is a DC value, do thing like this. Otherwise do it normally
                    if(x == 0 && y == 0) {
                        // Add the base code
                        if(!AddToBitString(dcLumiCodeTable[cat][0], dcLumiCodeTable[cat][1], 0)) {
                            printf("Something went wrong on AddToBitString 1\n");
                        }

                        // Add the at most last 4 bits
                        //numBits = 0;
                        //if(cat > 4) numBits = 4;
                        //else numBits = cat;

                        if(dctBuffer[xIndex][yIndex].Y < 0) {
                            if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Y, 1)) {
                                printf("Something went wrong on AddToBitString 2\n");
                            }
                        }
                        else{
                            if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Y, 0)) {
                                printf("Something went wrong on AddToBitString 2\n");
                            }
                        }

                    }
                    else {
                        if(dctBuffer[xIndex][yIndex].Y == 0){
                          zeroCtr++;
                          if(zeroCtr > 15) {
                              zeroCtr = 0;
                              bigZeroCtr++;
                          }
                        }
                        else{
                            // So long as there are 15 zeros in a row
                            while(bigZeroCtr != 0) {
                                if(!AddToBitString(acLumiCodeTable[161][0], acLumiCodeTable[161][1], 0)) {
                                    printf("Something went wrong on AddToBitString 3\n");
                                }
                                
                                bigZeroCtr--;
                            }
                            
                            tableIndex = zeroCtr*10 + cat;
				
                            // Add in base code
                            if(!AddToBitString(acLumiCodeTable[tableIndex][0], acLumiCodeTable[tableIndex][1], 0)) {
                                printf("Something went wrong on AddToBitString 1\n");
                            }

                            // Add in last bits
                            //numBits = 0;
                            //if(cat > 4) numBits = 4;
                            //else numBits = cat;

                            if(dctBuffer[xIndex][yIndex].Y < 0) {
                                if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Y, 1)) {
                                    printf("Something went wrong on AddToBitString 2\n");
                                }
                            }
                            else{
                                if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Y, 0)) {
                                    printf("Something went wrong on AddToBitString 2\n");
                                }
                            }

                            zeroCtr = 0;
                        }
                    }
                }
            }

            // Add EOB
            if (zeroCtr != 0 || bigZeroCtr != 0) {
                AddToBitString(acLumiCodeTable[0][0], acLumiCodeTable[0][1], 0);
            }
            zeroCtr = 0;
            bigZeroCtr = 0;

            /*---------------------------------------------------------------*/
            // Cb
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    int xIndex = x + (xBlock * 8);
                    int yIndex = y + (yBlock * 8);

                    // Find category
                    cat = -1;
                    for(int i = 0; i < catAmount; i++) {
                        if((huffCatTable[i][0] <= dctBuffer[xIndex][yIndex].Cb && huffCatTable[i][1] >= dctBuffer[xIndex][yIndex].Cb) 
                            || (-huffCatTable[i][0] >= dctBuffer[xIndex][yIndex].Cb && -huffCatTable[i][1] <= dctBuffer[xIndex][yIndex].Cb)) {
                            
                            cat = i;
                            i = catAmount+1;
                        }
                    }
                    if(cat == -1) return -1; // Sanity check, exits if problem arises
                    
                    // If it is a DC value, do thing like this. Otherwise do it normally
                    if(x == 0 && y == 0) {
                        // Add the base code
                        if(!AddToBitString(dcChromiCodeTable[cat][0], dcChromiCodeTable[cat][1], 0)) {
                            printf("Something went wrong on AddToBitString 1\n");
                        }

                        // Add the at most last 4 bits
                        //numBits = 0;
                        //if(cat > 4) numBits = 4;
                        //else numBits = cat;

                        if(dctBuffer[xIndex][yIndex].Cb < 0) {
                            if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Cb, 1)) {
                                printf("Something went wrong on AddToBitString 2\n");
                            }
                        }
                        else{
                            if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Cb, 0)) {
                                printf("Something went wrong on AddToBitString 2\n");
                            }
                        }

                    }
                    else {
                        if(dctBuffer[xIndex][yIndex].Cb == 0){
                          zeroCtr++;
                          if(zeroCtr > 15) {
                              zeroCtr = 0;
                              bigZeroCtr++;
                          }
                        }
                        else{
                            // So long as there are 15 zeros in a row
                            while(bigZeroCtr != 0) {
                                if(!AddToBitString(acChromiCodeTable[161][0], acChromiCodeTable[161][1], 0)) {
                                    printf("Something went wrong on AddToBitString 3\n");
                                }
                                
                                bigZeroCtr--;
                            }
                            
                            tableIndex = zeroCtr*10 + cat;
				
                            // Add in base code
                            if(!AddToBitString(acChromiCodeTable[tableIndex][0], acChromiCodeTable[tableIndex][1], 0)) {
                                printf("Something went wrong on AddToBitString 1\n");
                            }

                            // Add in last bits
                            //numBits = 0;
                            //if(cat > 4) numBits = 4;
                            //else numBits = cat;

                            if(dctBuffer[xIndex][yIndex].Cb < 0) {
                                if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Cb, 1)) {
                                    printf("Something went wrong on AddToBitString 2\n");
                                }
                            }
                            else{
                                if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Cb, 0)) {
                                    printf("Something went wrong on AddToBitString 2\n");
                                }
                            }

                            zeroCtr = 0;
                        }
                    }
                }
            }

            // Add EOB
            if (zeroCtr != 0 || bigZeroCtr != 0) {
                AddToBitString(acChromiCodeTable[0][0], acChromiCodeTable[0][1], 0);
            }
            zeroCtr = 0;
            bigZeroCtr = 0;
            

            /*---------------------------------------------------------------*/
            // Cr
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {
                    int xIndex = x + (xBlock * 8);
                    int yIndex = y + (yBlock * 8);

                    // Find category
                    cat = -1;
                    for(int i = 0; i < catAmount; i++) {
                        if((huffCatTable[i][0] <= dctBuffer[xIndex][yIndex].Cr && huffCatTable[i][1] >= dctBuffer[xIndex][yIndex].Cr) 
                            || (-huffCatTable[i][0] >= dctBuffer[xIndex][yIndex].Cr && -huffCatTable[i][1] <= dctBuffer[xIndex][yIndex].Cr)) {
                            
                            cat = i;
                            i = catAmount+1;
                        }
                    }
                    if(cat == -1) return -1; // Sanity check, exits if problem arises
                    
                    // If it is a DC value, do thing like this. Otherwise do it normally
                    if(x == 0 && y == 0) {
                        // Add the base code
                        if(!AddToBitString(dcChromiCodeTable[cat][0], dcChromiCodeTable[cat][1], 0)) {
                            printf("Something went wrong on AddToBitString 1\n");
                        }

                        // Add the at most last 4 bits
                        //numBits = 0;
                        //if(cat > 4) numBits = 4;
                        //else numBits = cat;

                        if(dctBuffer[xIndex][yIndex].Cr < 0) {
                            if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Cr, 1)) {
                                printf("Something went wrong on AddToBitString 2\n");
                            }
                        }
                        else{
                            if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Cr, 0)) {
                                printf("Something went wrong on AddToBitString 2\n");
                            }
                        }

                    }
                    else {
                        if(dctBuffer[xIndex][yIndex].Cr == 0){
                          zeroCtr++;
                          if(zeroCtr > 15) {
                              zeroCtr = 0;
                              bigZeroCtr++;
                          }
                        }
                        else{
                            // So long as there are 15 zeros in a row
                            while(bigZeroCtr != 0) {
                                if(!AddToBitString(acChromiCodeTable[161][0], acChromiCodeTable[161][1], 0)) {
                                    printf("Something went wrong on AddToBitString 3\n");
                                }
                                
                                bigZeroCtr--;
                            }
                            
                            tableIndex = zeroCtr*10 + cat;
				
                            // Add in base code
                            if(!AddToBitString(acChromiCodeTable[tableIndex][0], acChromiCodeTable[tableIndex][1], 0)) {
                                printf("Something went wrong on AddToBitString 1\n");
                            }

                            // Add in last bits
                            //numBits = 0;
                            //if(cat > 4) numBits = 4;
                            //else numBits = cat;

                            if(dctBuffer[xIndex][yIndex].Cr < 0) {
                                if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Cr, 1)) {
                                    printf("Something went wrong on AddToBitString 2\n");
                                }
                            }
                            else{
                                if(!AddToBitString(cat, dctBuffer[xIndex][yIndex].Cr, 0)) {
                                    printf("Something went wrong on AddToBitString 2\n");
                                }
                            }

                            zeroCtr = 0;
                        }
                    }
                }
            }

            // Add EOB
            if (zeroCtr != 0 || bigZeroCtr != 0) {
                AddToBitString(acChromiCodeTable[0][0], acChromiCodeTable[0][1], 0);
            }
            zeroCtr = 0;
            bigZeroCtr = 0;
            
            // printf("Out of block %d %d\n", xBlock, yBlock);
        }
    }

    return 1;
}

/*
 * bufMode: 0 is ycc buffer, 1 is dct buffer
 * fileMode: 0=read, 1=dct, 2=quant, 3=diff, 4=zigzag, 5=huff
*/
int OutputYCbCr(enum RESMODE resMode, int bufMode, int fileMode) {
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
    int resTotal = xRes*yRes;

    char *buffer = (char*) malloc(sizeof(char)*resTotal*3);

    printf("y  cb  cr\n");
    if(bufMode == 0) {
        for(int yPos = 0; yPos < yRes; yPos++) {
            for(int xPos = 0; xPos < xRes; xPos++) {
                int dataIndex = (xPos + (yPos * xRes)) * 3;

                *(buffer + dataIndex) = yccBuffer[xPos][yPos].Y;
                *(buffer + (dataIndex+1)) = yccBuffer[xPos][yPos].Cb;
                *(buffer + (dataIndex+2)) = yccBuffer[xPos][yPos].Cr;

                if(dataIndex % 131072 == 0) {
                    printf("%d  %d  %d\n", *(buffer + dataIndex), *(buffer + (dataIndex+1)), *(buffer + (dataIndex+2)));
                }
            }
        }
    }
    else if(bufMode == 1) {
        for(int yPos = 0; yPos < yRes; yPos++) {
            for(int xPos = 0; xPos < xRes; xPos++) {
                int dataIndex = (xPos + (yPos * xRes)) * 3;

                *(buffer + dataIndex) = dctBuffer[xPos][yPos].Y;
                *(buffer + (dataIndex+1)) = dctBuffer[xPos][yPos].Cb;
                *(buffer + (dataIndex+2)) = dctBuffer[xPos][yPos].Cr;
                
                if(dataIndex % 131072 == 0) {
                    printf("%d  %d  %d\n", *(buffer + dataIndex), *(buffer + (dataIndex+1)), *(buffer + (dataIndex+2)));
                }
            }
        }
    }
    else{ return 0; }

    FILE* fTestOutput;
    if(fileMode == 0) {
        fTestOutput = fopen("memdump_test_read", "w");
    }
    else if(fileMode == 1) {
        fTestOutput = fopen("memdump_test_dct", "w");
    }
    else if(fileMode == 2) {
        fTestOutput = fopen("memdump_test_quant", "w");
    }
    else if(fileMode == 3) {
        fTestOutput = fopen("memdump_test_diff", "w");
    }
    else if(fileMode == 4) {
        fTestOutput = fopen("memdump_test_zigzag", "w");
    }
    else if(fileMode == 5) {
        fTestOutput = fopen("memdump_test_huff", "w");
    }

    fwrite(buffer, 1, resTotal*3, fTestOutput);
    fclose(fTestOutput);

    return 1;
}

int printDCTY(int printX, int printY, int xIndex, int yIndex) {
    printf("DCT Y buffer:\n(\n");
    for(int y = 0; y < printY; y++) {
        if(y%8 == 0) {
            printf("\n");
        }
        for(int x = 0; x < printX; x++) {
            if(x%8 == 0) {
                printf("   ");
            }
            printf("%d, ", dctBuffer[x+xIndex][y+yIndex].Y);
        }
        printf("\n");
    }
    printf(")\n");

    return 1;    
}

int printDCTCb(int printX, int printY, int xIndex, int yIndex) {
    printf("DCT Cb buffer:\n(\n");
    for(int y = 0; y < printY; y++) {
        if(y%8 == 0) {
            printf("\n");
        }
        for(int x = 0; x < printX; x++) {
            if(x%8 == 0) {
                printf("   ");
            }
            printf("%d, ", dctBuffer[x+xIndex][y+yIndex].Cb);
        }
        printf("\n");
    }
    printf(")\n");

    return 1;    
}

int printDCTCr(int printX, int printY, int xIndex, int yIndex) {
    printf("DCT Cr buffer:\n(\n");
    for(int y = 0; y < printY; y++) {
        if(y%8 == 0) {
            printf("\n");
        }
        for(int x = 0; x < printX; x++) {
            if(x%8 == 0) {
                printf("   ");
            }
            printf("%d, ", dctBuffer[x+xIndex][y+yIndex].Cr);
        }
        printf("\n");
    }
    printf(")\n");

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
