#include <stdio.h>

int main() {
	FILE *fp;
	int blanks = 0, lines = 0, chars = 0;
	char ch;
	fp = fopen("lab5.txt", "r");
	if (fp == NULL) {
		printf("File not found!\n");
		return 1;
	}
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == ' ')
			blanks++;
		if (ch == '\n')
			lines++;
			chars++;
	}

	fclose(fp);
	printf("No. of blanks: %d\n", blanks);
	printf("No. of lines: %d\n", lines);
	printf("No. of characters: %d\n", chars);

	return 0;
}
