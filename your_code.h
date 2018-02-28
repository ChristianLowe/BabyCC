#ifndef YOUR_CODE_H
#define YOUR_CODE_H

extern int yyerror(const char *);

typedef enum{ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE, ASTNODE_ASSIGN, ASTNODE_IDENT, ASTNODE_NUM, ASTNODE_IF, ASTNODE_WHILE} ASTNodeType;

// Define all operation types (add, mult, etc) here.
typedef enum{ADD_OP, MULT_OP, LT_OP, GT_OP, LE_OP, GE_OP, EQ_OP, NE_OP/*, ....*/} ASTOp;  // TODO

typedef struct ASTNode ASTNode;
struct ASTNode{
	ASTNodeType type; 
    ASTOp op; // The actual operation (add, mult, etc)
	int num;  //Need to store the actual value for number nodes
	char *name; //Need to store the actual variable name for ident nodes
	ASTNode* left; // Left child
	ASTNode* middle; // Middle child
	ASTNode* right; // Right child
	
	// The following pointer is just a suggestion; you don't have to use it if you have a better design.
	ASTNode* next; // a pointer used to link statement nodes together in a statement list

// Depending on your implementation, you may need to add other fields to this struct 

};

// Add functions to create the different kinds of ASTNodes 
// These functions are called by the code embedded in the grammar.
// Here are some samples:  
ASTNode* CreateNumNode(int num);
ASTNode* CreateIdentNode(char* name);
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList);
ASTNode* CreateAssignmentNode(ASTNode* ident, ASTNode* expr);
ASTNode* CreateIfNode(ASTNode* condition, ASTNode* stList);
ASTNode* CreateIfElseNode(ASTNode* condition, ASTNode* ifStList, ASTNode* elseStList);
ASTNode* CreateOrNode(ASTNode* condition, ASTNode* lTerm);
ASTNode* CreateAndNode(ASTNode* lTerm, ASTNode* compare);
ASTNode* CreateCompareNode(ASTNode* lExpr, char* op, ASTNode* rExpr);
ASTNode* CreateWhileNode(ASTNode* condition, ASTNode* stList);
ASTNode* CreateAdditionNode(ASTNode* expr, ASTNode* term);
ASTNode* CreateSubtractionNode(ASTNode* expr, ASTNode* term);
ASTNode* CreateMultiplicationNode(ASTNode* term, ASTNode* factor);
ASTNode* CreateDivisionNode(ASTNode* term, ASTNode* factor);


// Need a function to add a declaration to your symbol table
void AddDeclaration(char* name);

// This is the function that generates ILOC code after the construction of the AST
//void GenerateILOC(ASTNode* node);
#endif
