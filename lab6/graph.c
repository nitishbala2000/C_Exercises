#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

Node *empty = NULL;

Node *node(int value, Node *left, Node *right) { 
  Node *r = malloc(sizeof(Node));
  r->marked = false;
  r->value = value;
  r->left = left;
  r->right = right;
  return r;
}


/* Basic Problems */

int size(Node *node) { 
	

	if (node == NULL || node->marked) {
		return 0;
	}
	
	node->marked = true;
	return 1 + size(node->left) + size(node->right);

}


void unmark(Node *node) { 
	
	if (node == NULL || !(node->marked)) {
		return;
	}

	node->marked = false;
	unmark(node->left);
	unmark(node->right);
}

bool path_from(Node *node1, Node *node2) {
  /* TODO */
	if (node1 == node2) {
		return true;
	}

	if (node1 == NULL || node1->marked) {
		return false;
	}

	node1->marked = true;
	return path_from(node1->left, node2) || path_from(node1->right, node2);
}

bool cyclic(Node *node) { 
	return path_from(node->left, node) || path_from(node->right, node);
} 


/* Challenge problems */

void get_nodes(Node *node, Node **dest) { 
  /* TODO */
	if (node == NULL || node->marked) {
		return;
	}

	node->marked = true;
	*dest = node;
	dest++;

	get_nodes(node->left, dest);
	get_nodes(node->right, dest);
}

void graph_free(Node *node) { 
  /* TODO */
	unmark(node);
	int s = size(node);
	unmark(node);

	Node* reachableNodes[s];
	get_nodes(node, reachableNodes);

	for (int i = 0; i < s; i++) {
		free(reachableNodes[i]);
	}


}


