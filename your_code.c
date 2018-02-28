#include "your_code.h"
#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>


// Write the implementations of the functions that do the real work here

ASTNode* CreateNumNode(int num){
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_NUM; 
    node->num = num;
    return node;
}


ASTNode* CreateIdentNode(char* name){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_IDENT;
	node->name = name;
	if (ht_find(node)) {
		return node;
	} else {
		yyerror("Ident not declared");
	}
}

// Take a statement node and a statement list node and connect them together
// to form a bigger statement list node (add the statement to the statement list).
// Return a pointer to the bigger list that resulted from this linking
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList){
	st->next = stList;
	return st;
}

ASTNode* CreateAssignmentNode(ASTNode* ident, ASTNode* expr){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_ASSIGN;
	node->left = ident;
	node->right = expr;
	return node;
}

ASTNode* CreateIfNode(ASTNode* condition, ASTNode* stList){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_IF;
	node->left = condition;
	node->right = stList;
	return node;
}

ASTNode* CreateIfElseNode(ASTNode* condition, ASTNode* ifStList, ASTNode* elseStList){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_IF;
	node->left = condition;
	node->middle = ifStList;
	node->right = elseStList;
	return node;
}

ASTNode* CreateOrNode(ASTNode* condition, ASTNode* lTerm){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_LOGIC_OP;
	node->left = condition;
	node->right = lTerm;
	return node;
}

ASTNode* CreateAndNode(ASTNode* lTerm, ASTNode* compare){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_LOGIC_OP;
	node->left = lTerm;
	node->right = compare;
	return node;
}

ASTNode* CreateCompareNode(ASTNode* lExpr, char* op, ASTNode* rExpr){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_COMPARE;

	if (strcmp(op, "<") == 0) {
		node->op = LT_OP;
	} else if (strcmp(op, ">") == 0) {
		node->op = GT_OP;
	} else if (strcmp(op, "<=") == 0) {
		node->op = LE_OP;
	} else if (strcmp(op, ">=") == 0) {
		node->op = GE_OP;
	} else if (strcmp(op, "==") == 0) {
		node->op = EQ_OP;
	} else if (strcmp(op, "!=") == 0) {
		node->op = NE_OP;
	}

	node->left = lExpr;
	node->right = rExpr;
	return node;
}

ASTNode* CreateWhileNode(ASTNode* condition, ASTNode* stList){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_WHILE;
	node->left = condition;
	node->right = stList;
	return node;
}

ASTNode* CreateAdditionNode(ASTNode* expr, ASTNode* term){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_ARITH_OP;
	node->left = expr;
	node->right = term;
	return node;
}

ASTNode* CreateSubtractionNode(ASTNode* expr, ASTNode* term){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_ARITH_OP;
	node->left = expr;
	node->right = term;
	return node;
}

ASTNode* CreateMultiplicationNode(ASTNode* term, ASTNode* factor){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_ARITH_OP;
	node->left = term;
	node->right = factor;
	return node;
}

ASTNode* CreateDivisionNode(ASTNode* term, ASTNode* factor){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_ARITH_OP;
	node->left = term;
	node->right = factor;
	return node;
}

void AddDeclaration(char* name)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASTNODE_IDENT;
	node->name = name;
	if (!ht_find(node)) {
		ht_insert(node);
	} else {
		char error[128];
		sprintf(error, "Multiple declarations of '%s'", name);
		yyerror(error);
	}
}

// Commented out in this assignment 
/*void GenerateILOC(ASTNode* node);
{

}*/

