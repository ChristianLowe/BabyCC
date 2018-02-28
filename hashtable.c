#include "hashtable.h"

int ht_hash(ASTNode* node) {
	// Java-style string hashing
	int hash = 7;

	for (int i = 0; node->name[i] != '\0'; i++) {
		hash = hash*31 + node->name[i];
	}

	return hash % TABLE_SIZE;
}

void ht_init() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		table[i] = NULL;
	}
}

void ht_insert(ASTNode* node) {
	int hash = ht_hash(node);

	HTNode* newHTNode = malloc(sizeof(HTNode));
	newHTNode->item = node;

	if (table[hash] == NULL) {
		table[hash] = newHTNode;
	} else {
		HTNode* collidingNode = table[hash];
		while (collidingNode->next != NULL) {
			collidingNode = collidingNode->next;
		}
		collidingNode->next = newHTNode;
	}
}

int ht_find(ASTNode* node) {
	int hash = ht_hash(node);

	HTNode* searchNode = table[hash];
	while (searchNode != NULL) {
		if (!strcmp(searchNode->item->name, node->name)) {
			return 1;
		}
		searchNode = searchNode->next;
	}

	return 0;
}
