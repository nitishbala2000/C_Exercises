#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List *cons(int head, List *tail) { 
  /* malloc() will be explained in the next lecture! */
  List *cell = malloc(sizeof(List));
  cell->head = head;
  cell->tail = tail;
  return cell;
}

/* Functions for you to implement */

int sum(List *list) {
	
	int sum = 0;
	while (list != NULL) {
		sum += list->head;
		list = list->tail;
	}

	return sum;
 
}

void iterate(int (*f)(int), List *list) {

	while (list != NULL) {
		list->head = (*f) (list->head);
		list = list->tail;
	}
    
}

void print_list(List *list) { 
  /* TODO */
	printf("[");
	while (list != NULL) {
		printf("%d", list->head);
		if (list->tail != NULL) {
			printf(",");
		}
		list = list->tail;
	}
	printf("] \n");
}

/**** CHALLENGE PROBLEMS ****/

List *merge(List *list1, List *list2) { 
  /* TODO */
	if (list1 == NULL) {
		return list2;
    }

	if (list2 == NULL) {
		return list1;
	}

	if (list1->head < list2->head) {
		list1->tail = merge(list1->tail, list2);
		return list1;
	}
	else {
		list2->tail = merge(list1, list2->tail);
		return list2;
	}
}



void split(List *list, List **list1, List **list2) { 
	int count = 0;
	while (list != NULL) {
		if (count % 2 == 0) {
			*list1 = cons(list->head, *list1);
		}
		else {
			*list2 = cons(list->head, *list2);
		}

		list = list->tail;
		count++;
	}

}

int len(List* lst) {
	int count = 0;
	while (lst != NULL) {
		count++;
		lst = lst->tail;
	}
	return count;
}

/* You get the mergesort implementation for free. But it won't
   work unless you implement merge() and split() first! */

List *mergesort(List *list) { 

	if (list == NULL || list->tail == NULL) {
		return list;
	}

	List* lefthalf = NULL;
	List* rightHalf = NULL;
	split(list, &lefthalf, &rightHalf);

	return merge(mergesort(lefthalf), mergesort(rightHalf));

}
