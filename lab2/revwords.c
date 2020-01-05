#include <ctype.h>
#include <string.h>
#include "revwords.h"
#include <ctype.h >

void reverse_substring(char str[], int start, int end) { 
	int i, j;
	for (i = start, j = end; i < j; i++, j--) {
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	
}


int find_next_start(char str[], int len, int i) { 

	for (int k = i; k < len; k++) {
		if (isalpha(str[k]) && (k == 0 || !isalpha(str[k - 1]) ) ) {
			return k;
		}
	}

	return -1;


}

int find_next_end(char str[], int len, int i) {
   
	for (int k = i; k < len; k++) {
		
		if (!isalpha(str[k]) && isalpha(str[k - 1]) ) {
			return k - 1;
		}

		if (k == len - 1) {
			return len - 1;
		}
	}

	return -1;
	
}

void reverse_words(char s[]) { 
	int len = strlen(s);
	int word_start = find_next_start(s, len, 0);
	int word_end = find_next_end(s, len, word_start);
   
	while (word_start != -1) {
		reverse_substring(s, word_start, word_end);
		word_start = find_next_start(s, len, word_end);
		word_end = find_next_end(s, len, word_start);
	}
	
}
