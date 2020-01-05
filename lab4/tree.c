#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

Tree *empty = NULL;

/* BASE EXERCISE */

int tree_member(int x, Tree *tree) { 
	/*sdfdsf*/

	if (tree == NULL) {
		return 0;
	}
	if (tree->value == x) {
		return 1;
	}
	else if (x < tree->value) {
		return tree_member(x, tree->left);
	}
	else {
		return tree_member(x, tree->right);
	}
  
}

Tree *tree_insert(int x, Tree *tree) { 
	
	Tree* treeToInsert = malloc(sizeof(Tree));
	treeToInsert->value = x;
	treeToInsert->left = NULL;
	treeToInsert->right = NULL;


	if (tree == NULL) {
		return treeToInsert;
	}

	if (x < tree->value) {
		tree->left = tree_insert(x, tree->left);
		return tree;
	}
	else {
		tree->right = tree_insert(x, tree->right);
		return tree;
	}
	
}

void tree_free(Tree *tree) { 
  /* TODO */
	if (tree == NULL) {
		return;
	}

	
	tree_free(tree->left);
	tree_free(tree->right);
	free(tree);
}

/* CHALLENGE EXERCISE */ 

void pop_minimum(Tree *tree, int *min, Tree **new_tree) { 

	if (tree->left == NULL) {
		*min = tree->value;
		*new_tree = tree->right;
		return;
	}

	pop_minimum(tree->left, min, new_tree);
}

Tree *tree_remove(int x, Tree *tree) { 
	if (tree == NULL) {
		return NULL;
	}
	
	if (x == tree->value) {
		if (tree->right == NULL) {
			return tree->left;
		}
		else {
			int min;
			Tree* newRightTree;
			pop_minimum(tree->right, &(min), &(newRightTree));
			tree->value = min;
			return tree;
		}
	}
	else if (x < tree->value) {
		tree->left = tree_remove(x, tree->left);
		return tree;
	}
	else {
		tree->right = tree_remove(x, tree->right);
		return tree;
	}


}
