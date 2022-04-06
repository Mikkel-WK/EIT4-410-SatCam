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