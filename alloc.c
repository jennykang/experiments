#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int width);
int tonumber(char s[]);
void getLine (char s[], int size);
void reverse (char s[]);
char memory[10000];
char *last = memory;
char *myalloc(int size) {
	if (last + size > memory+10000){
		printf("Not enough memory ;n;\n");
		return 0;
	}

	else {
		last += size;
		return (last-size);
	}
}

void myfree(char *buffer) {
	if (buffer < last && buffer > memory){
		last = buffer;
	}
}

int main () {
	int n, width;

	char *buffer = myalloc(100);
	char *s = myalloc(100);

	printf("Please input a number \n");
	getLine(buffer, 100);
	n = tonumber(buffer);

	printf("Please enter a width\n");
	getLine(buffer, 100);
	width = tonumber(buffer);

	printf("Setting number to fit width now... \n");
	itoa(n, s, width);
	printf("Padded number is %s \n", s);

	myfree(buffer);
	myfree(s);

	return 0;
}

void getLine (char *s, int size){
	int i;
	char c;
	for (i = 0; (c = getchar()) != '\n' && i < size; i++){
		s[i] = c;
	}
	s[i] = '\0';
}

int tonumber(char s[]){
	int result, sign;
	int i = 0;
	result = 0;
	sign = 1;

	if (s[0] == '-'){
		sign = -1;
		i = 1;
	}

	for (; s[i] >= '0' && s[i] <= '9'; i++){
		result = (10 * result) + s[i] - '0';
	}

	return result * sign ;
}

void itoa(int n, char s[], int width){ //partly taken from K&R textbook. number to char string
	int i, sign, counter;

	if ((sign = n) < 0)  
		n = -n;          
	i = 0;
    
	do { 
		s[i++] = n % 10 + '0';
	} 
	while ((n /= 10) > 0);
    
	if (sign < 0)
		s[i++] = '-';

	while (i < width){
		s[i++] = ' ';
	}

	s[i] = '\0';
    
	reverse(s);
}

void reverse (char s[]){
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i <j; i++, j--){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}