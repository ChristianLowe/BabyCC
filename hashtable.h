#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "your_code.h"

#define TABLE_SIZE 128

typedef struct HTNode {
	ASTNode* item;
	struct HTNode* next;
} HTNode;

HTNode* table[TABLE_SIZE];

void ht_init();
void ht_insert(ASTNode* node);
int ht_find(ASTNode* node);

#endif