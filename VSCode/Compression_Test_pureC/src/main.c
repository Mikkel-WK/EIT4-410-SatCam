/*
 * Checkliste til brug af bibliotek
 * 
 * 
 * 
 * 
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// #include "../lib/SatCamImage.h"
#include "SatCamImage.h"

int main() {
    SYSTEMTIME t_start, t_stop;

    GetSystemTime(&t_start); 
    TestInput();
    GetSystemTime(&t_stop);

    printf("The start time was: %02d:%02d:%02d.%03d\n", 
                t_start.wHour, t_start.wMinute, t_start.wSecond, t_start.wMilliseconds);

    printf("The stop time was: %02d:%02d:%02d.%03d\n", 
            t_stop.wHour, t_stop.wMinute, t_stop.wSecond, t_stop.wMilliseconds);


    return 0;
}

/*int main() {
	char testArr[64*4] = 
	{
		149, 124, 154, 255, 153, 128, 158, 255, 151, 128, 157, 255, 152, 129, 158, 255, 153, 133, 160, 255, 150, 132, 158, 255, 149, 133, 159, 255, 147, 123, 155, 255,
		137, 101, 137, 255, 142, 108, 141, 255, 143, 109, 142, 255, 144, 113, 145, 255, 145, 118, 149, 255, 140, 115, 145, 255, 140, 117, 146, 255, 146, 122, 158, 255,
		127,  96, 130, 255, 130,  99, 133, 255, 127,  96, 128, 255, 134, 105, 136, 255, 135, 110, 140, 255, 128, 108, 136, 255, 136, 117, 145, 255, 142, 117, 156, 255, 
		118,  97, 128, 255, 116,  92, 124, 255, 104,  83, 114, 255, 112,  93, 121, 255, 114, 100, 126, 255, 111, 101, 126, 255, 127, 122, 145, 255, 131, 106, 146, 255,
		116,  99, 131, 255, 108,  90, 128, 255,  91,  74, 116, 255, 105,  90, 121, 255, 107,  94, 124, 255, 107,  93, 126, 255, 125, 113, 135, 255, 131,  98, 141, 255,
		145, 118, 151, 255, 143, 115, 156, 255, 117,  88, 132, 255, 116,  89, 124, 255, 122,  95, 130, 255, 121,  95, 134, 255, 127, 102, 131, 255, 127,  91, 137, 255,
		156, 125, 157, 255, 153, 121, 162, 255, 143, 107, 153, 255, 146, 112, 147, 255, 150, 115, 155, 255, 146, 110, 154, 255, 143, 109, 144, 255, 142, 106, 152, 255,
		146, 121, 150, 255, 145, 119, 156, 255, 147, 119, 160, 255, 150, 123, 156, 255, 151, 121, 159, 255, 149, 118, 162, 255, 155, 125, 161, 255, 148, 112, 158, 255
	};

	ReadDataToBuffer(testArr, TEST);

	TestInput();

	return 0;
}*/

/*int main() {
	int xRes = 8;
	int yRes = 8;

	int blockXIndex[] = {
        0, 
		1, 0, 
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
        0, 
		0, 1,
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

	for(size_t yBlock = 0; yBlock < yRes/8; yBlock++) {
        for(size_t xBlock = 0; xBlock < xRes/8; xBlock++) {
			// Define a temporary buffer
			DCT zzBuffer[64];

            for(int i = 0; i < 64; i++) {
                size_t zzIndex = i + (64*xBlock) + ((xRes*8)*yBlock);

                // zzBuffer[zzIndex] = dctYBuffer[blockXIndex[i]][blockYIndex[i]];
                zzBuffer[zzIndex] = testBuffer[blockYIndex[i]][blockXIndex[i]];
            }
            
			for(int i = 0; i < 8; i++) {
				for(int j = 0; j < 8; j++) {
					testBuffer[i][j] = zzBuffer[i+(8*j)];
				}
			}

            for(int j = 0; j < 8; j++) {
				for(int i = 0; i < 8; i++) {
					printf("%d, ", testBuffer[i][j]);
				}
            }
            fflush(stdout);
        }
    }

	// TestInput();

	return 0;
}*/

/*
int main() {
	BYTE xDensity[2] = {0x01, 0x2c};
	BYTE yDensity[2] = {0x01, 0x2c};
	
	JFIFHEADER header;
	BuildJFIFHeader(&header, 0x00, xDensity, yDensity, 0x00, 0x00);

	for(unsigned int i = 0; i<sizeof(header); i++) {
		BYTE charToWrite = &header + i;
		printf("%#08x\n", charToWrite);
	}

	return 0;
}*/

/* 
int main() {
	FILE* fInput = fopen("ahaha.png", "rb");
	FILE* fOutput = fopen("output.png", "wb");

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

	fwrite(buffer, sizeof(char)*fileLength, 1, fOutput);

	free(buffer);

	fclose(fInput);
	fclose(fOutput);

	return 0;
}*/

/*
int main() {
	FILE* fOutput = fopen("C:\\Users\\sande\\Documents\\PlatformIO\\Projects\\Compression_Test_pureC\\src\\file.txt", "w");

	char testArray[] = "test";
	fprintf(fOutput, testArray);
	
	// char buffer[] = "Testing";
	// fwrite(buffer, sizeof(buffer), 1, fOutput);

	fclose(fOutput);

	return 0;
}*/