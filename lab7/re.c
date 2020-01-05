#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "re.h"

arena_t create_arena(int size) { 
	arena_t output = (arena_t)malloc(sizeof(struct arena));

	output->size = size;
	output->current = 0;

	output->data = (Regexp*) malloc(sizeof(Regexp) * size);


	return output;
}

void arena_free(arena_t a) { 

	free(a->data);
	free(a);
 
}

Regexp *re_alloc(arena_t a) { 

	if (a->current < a->size) {

		Regexp* r = a->data + a->current;
		a->current++;
		return r;


	}

	return NULL;
	
 
}

Regexp *re_chr(arena_t a, char c) { 

	Regexp* ptr = re_alloc(a);
	if (ptr == NULL) {
		return NULL;
	}

	ptr->type = CHR;
	ptr->data.chr = c;
	return ptr;

  
}

Regexp *re_alt(arena_t a, Regexp *r1, Regexp *r2) { 

	Regexp* ptr = re_alloc(a);
	if (ptr == NULL) {
		return NULL;
	}

	ptr->type = ALT;
	ptr->data.pair.fst = r1;
	ptr->data.pair.snd = r2;
	return ptr;
	
}

Regexp *re_seq(arena_t a, Regexp *r1, Regexp *r2) { 
	Regexp* ptr = re_alloc(a);
	if (ptr == NULL) {
		return NULL;
	}

	ptr->type = SEQ;
	ptr->data.pair.fst = r1;
	ptr->data.pair.snd = r2;
	return ptr;
}

int match(Regexp* r, char* s, int i, int j) {
	if (r->type == CHR) {
		return (j == i + 1) && (s[i] == r->data.chr);
	}

	Regexp* fst = r->data.pair.fst;
	Regexp* snd = r->data.pair.snd;

	if (r->type == ALT) {
		return match(fst, s, i, j) || match(snd, s, i, j);
	}

	//r->type must be SEQ
	for (int k = i + 1; k < j; k++) {
		if (match(fst, s, i, k) && match(snd, s, k, j)) {
			return 1;
		}
	}

	return 0;



}


int re_match(Regexp *r, char *s, int i) { 

	for (int j = i + 1; j <= strlen(s); j++) {
		if (match(r, s, i, j)) {
			return j;
		}
	}

	return -1;
}



void re_print(Regexp *r) { 
  if (r != NULL) { 
    switch (r->type) {
    case CHR: 
      printf("%c", r->data.chr);
      break;
    case SEQ:
      if (r->data.pair.fst->type == ALT) { 
	printf("(");
	re_print(r->data.pair.fst);
	printf(")");
      } else {
	re_print(r->data.pair.fst);
      }
      if (r->data.pair.snd->type == ALT) { 
	printf("(");
	re_print(r->data.pair.snd);
	printf(")");
      } else {
	re_print(r->data.pair.snd);
      }
      break;
    case ALT:
      re_print(r->data.pair.fst);
      printf("+");
      re_print(r->data.pair.snd);
      break;
    }
  } else { 
    printf("NULL");
  }
}    


      
  
