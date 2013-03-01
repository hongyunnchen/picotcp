/*********************************************************************
PicoTCP. Copyright (c) 2012 TASS Belgium NV. Some rights reserved.
See LICENSE and COPYING for usage.

Author: Andrei Carp <andrei.carp@tass.be>
*********************************************************************/

#ifndef __PICO_RBTREE_H__
#define __PICO_RBTREE_H__

#include <stdint.h>
#include "pico_config.h"

// This is used to declare a new tree, leaf root by default
#define PICO_TREE_DECLARE(name,compareFunction) \
pico_tree name =\
{ \
	&LEAF, \
	compareFunction \
}


struct pico_tree_node
{
  void* keyValue; // generic key
  struct pico_tree_node* parent;
  struct pico_tree_node* leftChild;
  struct pico_tree_node* rightChild;
  uint8_t color;
};

struct pico_tree
{
	struct pico_tree_node * root; // root of the tree

	// this function directly provides the keys as parameters not the nodes.
  int (*compare)(void* keyA, void* keyB);
};

extern struct pico_tree_node LEAF; // generic leaf node
/*
 * Manipulation functions
 */
void * pico_tree_insert(struct pico_tree * tree, void * node);
void * pico_tree_delete(struct pico_tree * tree, void * key);
void * pico_tree_findKey(struct pico_tree * tree, void * key);
void 	pico_tree_drop(struct pico_tree * tree);
int 	pico_tree_empty(struct pico_tree * tree);
struct pico_tree_node * pico_tree_findNode(struct pico_tree * tree, void * key);

/*
 * Traverse functions
 */
struct pico_tree_node * pico_tree_maximum(struct pico_tree_node * node);
struct pico_tree_node * pico_tree_minimum(struct pico_tree_node * node);
struct pico_tree_node * pico_tree_next(struct pico_tree_node * node);
struct pico_tree_node * pico_tree_prev(struct pico_tree_node * node);

/*
 * For each macros
 */

#define pico_tree_foreach(idx,tree) \
		for ((idx) = pico_tree_minimum((tree)->root); \
		     (idx) != &LEAF; \
		     (idx) = pico_tree_next(idx))

#define pico_tree_foreach_reverse(idx,tree) \
		for ((idx) = pico_tree_maximum((tree)->root); \
		     (idx) != &LEAF; \
		     (idx) = pico_tree_prev(idx))

#define pico_tree_foreach_safe(idx,tree,idx2) \
		for ((idx) = pico_tree_minimum((tree)->root);	\
		     ((idx) != &LEAF) && ((idx2) = pico_tree_next(idx), 1); \
		      (idx) = (idx2))

#define pico_tree_foreach_reverse_safe(idx,tree,idx2) \
		for ((idx) = pico_tree_maximum((tree)->root); \
				((idx) != &LEAF) && ((idx2) = pico_tree_prev(idx), 1); \
				 (idx) = (idx2))

#endif