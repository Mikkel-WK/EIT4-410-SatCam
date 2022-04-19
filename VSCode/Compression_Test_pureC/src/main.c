/*
 * Checkliste til brug af bibliotek
 * Indsæt opløsning i variabler (xRes, yRes)
 * Definer datalængde udfra variabler (dataLen = xRes * yRes * 4)
 * 
 * 
 * 
*/

#include <stdio.h>
#include <stdlib.h>

// #include "../lib/SatCamImage.h"
#include "SatCamImage.h"

int main() {
	TestInput();

	return 0;
}

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