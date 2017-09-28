#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void error(int code)
{
	printf("Error: fill character should be between 0 - 255 or 0x00 to 0xFF\n\n");
	exit(code);
}

int main(int argc, char *argv[])
{
	int				i;
	int				value = 0;
	int				numBytes = 0;
	unsigned char	b = 0x00;
	unsigned char *	buffer;
	char			szFilename[128];
	char			szByteStr[8];
	char			ch;
	FILE *			fptr;
	
	if (argc > 3) {
		strcpy(szFilename, argv[1]);
		strcpy(szByteStr, argv[2]);
		numBytes = atoi(argv[3]);
	}
	else {
		printf("Usage: filefill <out filename> <fill char (ASCII code - [dec val | 0xhex val])> <num bytes>\n\n");
		exit(-1);
	}

	if (szByteStr[0] == '0' && tolower(szByteStr[1]) == 'x') {
		if (strlen(szByteStr) == 4) {
			for (i = 0;i < 2;i++) {
				ch = toupper(szByteStr[i + 2]);
				
				if (ch >= 'A' && ch <= 'F') {
					b += ((ch - 'A') + 10) * (i == 0 ? 16 : 1);
				}
				else if (ch >= '0' && ch <= '9') {
					b += (ch - '0') * (i == 0 ? 16 : 1);
				}
				else {
					error(-1);
				}
			}
		}
		else {
			error(-1);
		}
	}
	else {
		value = atoi(szByteStr);
		
		if (value >= 0 && value <= 255) {
			b = (unsigned char)(value & 0xFF);
		}
		else {
			error(-1);
		}
	}
		
	fptr = fopen(szFilename, "wb");
	
	if (fptr == NULL) {
		printf("Failed to open file %s\n\n", szFilename);
		exit(-1);
	}
	
	buffer = malloc(numBytes);
	
	if (buffer == NULL) {
		printf("Failed to allocate %d bytes for file buffer\n\n", numBytes);
		exit(-1);
	}
	
	for (i = 0;i < numBytes;i++) {
		buffer[i] = b;
	}
	
	fwrite(buffer, 1, numBytes, fptr);
	
	fclose(fptr);
	
	free(buffer);
	
	return 0;
}
