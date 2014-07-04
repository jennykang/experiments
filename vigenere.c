/*

HOW THIS WORKS

*/

#include <stdio.h>

#define END '!'
#define SIZE 10000

int table [26*26*26][SIZE];

void gettext (char s[SIZE], int size);
void fillindex (char s[SIZE], int table [26*26*26][SIZE], int size); //fills table with index and distances from the occurance of 2 same sequences
void caldis (int table [26*26*26][SIZE]);
int calkey (int table [26*26*26][SIZE]); // calculates the possible length of the key
int isletter (char);

int main (){
	char buffer[SIZE];
	printf("This decoder will attempt to decrypt Vigeneré cyphers!\n");

	printf("Please enter the encrypted text:\n");
	gettext(buffer,SIZE);

	printf("Thank you. Performing frequency analysis on 3 character sequences now...\n");
	fillindex(buffer, table, SIZE);

	printf("Calculating distances between each sequence of 3 characters now...\n");
	caldis(table);

	int length;
	printf("Calculating possible length of keyword now...\n");
	length = calkey(table);
	printf("A possible length of the keyword is %d \n", length);

	return 0;
}

void gettext (char s[], int size){
	int i;
	char c;
	for (i = 0; (c = getchar()) != END && i < size; i++){
		if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
		s[i] = c;
	}
	s[i] = '\0';
}

int isletter (char c){
	return (c >= 'A' && c <= 'Z');
}

void fillindex (char s[], int table [26*26*26][SIZE], int size){
	int spcounti, spcountj;// space count until index i, space count until index j
	printf("filling the index now...\n");

	for (int i = 0; i < (26*26*26); i++){
		for (int j = 0; j < size; j++){
			table[i][j] = 0;
		}
	}

	spcounti = spcountj = 0;

	int i, j, k;
	i = j = k = 0; // invarient: i <= j <= k

	while (1){
		while (!isletter(s[i]) && (s[i] != '\0')){
			spcounti++;
			i++;
		}

		if (s[i] == '\0'){
			return;
		}

		j = i + 1;
		spcountj = spcounti;
		while (!isletter(s[j]) && (s[j] != '\0')){
			spcountj++;
			j++;
		}

		if (s[j] == '\0'){
			return;
		}

		k = j + 1;
		while (!isletter(s[k]) && (s[k] != '\0')){
			k++;
		}

		if (s[k] == '\0'){
			return;
		}

		int l = 0;
		while (table[((s[i] - 'A') * 26 * 26) + ((s[j] - 'A') * 26) + (s[k] - 'A')][l] != 0){
			l++;
		}

		table[((s[i] - 'A') * 26 * 26) + ((s[j] - 'A') * 26) + (s[k] - 'A')][l] = i - spcounti;

		i = j;
		spcounti = spcountj;
	}

}

void caldis (int table [26*26*26][SIZE]){
	int i, j;

	for (i = 0; i <= (26*26*26); i++){
		for (j = 0; (j <= 1000); j++){
			if (table[i][j+1] != 0){
				table[i][j] = table[i][j+1] - table[i][j];
			}

			else{
				table[i][j] = 0;
				break;
			}
		}
	}
}

int calkey (int table[26*26*26][SIZE]){
	int frequency[SIZE];

	for (int f = 0; f < SIZE; f++){
		frequency[f] = 0;
	}

	int i, j, k, l;

	for (i = 0; i < (26*26*26); i++){
		for (j = 0; ((j < SIZE) && (table[i][j] != 0)); j++){
			for (k = 2; k <= table[i][j]; k++){
				l = table[i][j] % k;
				if (l == 0){
					frequency[k]++;
				}
			}
		}
	}

	int max1, max2, max3;
	max1 = max2 = max3 = 0;

	for (int f = 0; f < SIZE; f++){
		if (frequency[f] >= frequency[max1]){
			max3 = max2;
			max2 = max1;
			max1 = f;

		}

		else if (frequency[f] >= frequency[max2]){
			max3 = max2;
			max2 = f;
		}

		else if (frequency[f] >= frequency[max3]){
			max3 = f;
		}
	}

	int m;
	for (m = 0; m < 20; m++){
		printf("%d: %d\n", m, frequency[m]);
	}

	printf("The three most likely key lengths are %d, %d, %d \n", max1, max2, max3);
	return max1;
}
