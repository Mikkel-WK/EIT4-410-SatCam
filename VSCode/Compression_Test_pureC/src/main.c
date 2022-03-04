#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* fInput = fopen("C:\\Users\\sande\\Documents\\PlatformIO\\Projects\\Compression_Test_pureC\\src\\inputfile.txt", "r");
	FILE* fOutput = fopen("C:\\Users\\sande\\Documents\\PlatformIO\\Projects\\Compression_Test_pureC\\src\\file.txt", "w");

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
}

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