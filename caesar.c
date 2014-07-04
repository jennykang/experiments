#include <stdio.h>
#include <strings.h>

void getLine (char s[], int size);
void decipher (char s[], char result[], int size, int shift);
int getword (char s[], int index, char result[]);
int decrypt (char s[]);
int main () {
	char buffer[100];
	char result[100];
	int size = 100;
	int shift;
	printf("Please enter a string: \n");

	getLine(buffer, size);

	printf("Thank you. Deciphering the text now... \n");
	printf("All versions of text are below:\n");

	shift = decrypt(buffer);
	if (shift != -1) {
		printf("Match found ;u;! \n")
		decipher(buffer, result, size, shift);
		printf("result: %s\n", result);

		return 0;
	}

	printf("No match. Printing all possibilities: \n");
	for (shift = 0; shift < ('Z' - 'A' + 1); shift++){
		decipher(buffer, result, size, shift);
		printf("%s\n", result);
	}

	return 0;
}

void getLine (char s[], int size){
	int i;
	char c;

	for (i = 0; (c = getchar()) != '\n' && i < size; i++){
		if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
		s[i] = c;
	}
	s[i] = '\0';
}

int getword (char s[], int index, char word[]){
	int i;

	for (i = 0; (s[i + index] != '\0') && (s[i + index] != ' '); i++){
		word[i] = s[i + index];
	}
	word[i] = '\0';

	if (s[i + index] == ' ') i++;
	return i;
}

int decrypt (char s[]){
	char result[100];
	char word[100];
	int index = 0, size = 0;
	while ((size = getword(s, index, word)) > 0){
		printf("Got back word: %s\n", word);
		index += size;
		for (int i = 0; i < ('Z' - 'A' + 1); i++) {
			decipher(word, result, 100, i);

			printf("Decyphering word %s => %s\n", word, result);

			if (strcmp("SUCCESS", result) == 0) {
				return i;
			}

			else if(strcmp("IS", result) == 0) {
				return i;
			}

			else if(strcmp("WHEN", result) == 0) {
				return i;
			}

			else if(strcmp("HOW", result) == 0) {
				return i;
			}

			else if(strcmp("IF", result) == 0) {
				return i;
			}
			else if(strcmp("THE", result) == 0) {
				return i;
			}
			else if(strcmp("BE", result) == 0) {
				return i;
			}
			else if(strcmp("TO", result) == 0) {
				return i;
			}
			else if(strcmp("OF", result) == 0) {
				return i;
			}
			else if(strcmp("AND", result) == 0) {
				return i;
			}
			else if(strcmp("IN", result) == 0) {
				return i;
			}
			else if(strcmp("THAT", result) == 0) {
				return i;
			}
			else if(strcmp("KNOW", result) == 0) {
				return i;
			}
			else if(strcmp("DONT", result) == 0) {
				return i;
			}
			else if(strcmp("HAVE", result) == 0) {
				return i;
			}
			else if(strcmp("IT", result) == 0) {
				return i;
			}

		}

		printf("Cannot decypher word: %s\n", word);
	}

	return -1;
}


void decipher (char s[], char result[], int size, int shift){
	int i;
	for (i = 0; s[i] != '\0' && i < size; i++){
		if ((s[i] == ' ') || (s[i] == '\t')){
			result[i] = s[i];
			continue;
		}

		if ((s[i] + shift) > 'Z'){
			result[i] = s[i] + shift - ('Z' - 'A' + 1);
		}

		else result[i] = s[i] + shift;	
	}

	result[i] = '\0';
}
