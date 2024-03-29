%define parse.error verbose

%{
	#include <stdio.h>
	#include "your_code.h"

// The parser needs to call the scanner to get the next token 
	extern int yylex();

// The error function 
	extern int yyerror(const char *);

// The ASTNode root
    extern ASTNode* gASTRoot;
%}

//Put any initialization code here 
%initial-action 
{

}

%token <op> LE "<="
%token <op> GE ">="
%token <op> EQ "=="
%token <op> NE "!="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"

//Define the types for the grammar attributes ($$, $1, $2, ...) 
%union 
{
	ASTNode* node; // Most $$ values will be ASTNodes 
	int num; // Integer numbers
	char* string; // Strings for identifiers 
	char* op;     // Representing the operator in a compare
}

//Specify the type for each token. Only needed for IDENT and NUM, because they are the only ones that have actual regexp rules
%token <string> IDENT
%token <num> NUM

//Specify the type for each non-terminal in the grammar. Here are some samples:
%type <node> Statement
%type <node> Assignment
%type <node> Expr
%type <node> Term
%type <node> Factor
// Add the rest of the types for the grammar's symbols
%type <node> Goal
%type <node> DeclarationList
%type <node> Declaration
%type <node> StatementList
%type <node> LHS
%type <node> Conditional
%type <node> Condition
%type <node> LTerm
%type <node> Compare
%type <node> Loop
%type <string> Op

%%

// Write the grammar for BabyC, and write an embedded action for each production. Here are some samples for you:

Goal: "main" '(' ')' '{' DeclarationList StatementList '}'	{gASTRoot=$6;} // Store the AST root node in gASTRoot
;

DeclarationList: 									{$$ = NULL;}
					| Declaration DeclarationList
;

Declaration: "int" IDENT ';' {AddDeclaration($2); printf("Processing declaration of %s\n", $2);}
;

Factor: IDENT 		{$$ = CreateIdentNode($1); printf("Creating IDENT node for %s\n", $1);}
	| NUM 			{$$ = CreateNumNode($1); printf("Creating NUM node for %d\n", $1);}
	| '('Expr')'	{$$ = $2; printf("Creating Expression node in parentheses\n");}
;

StatementList: 								{$$ = NULL;} 
               | Statement StatementList	{$$ = CreateStatementListNode($1,$2); printf("Adding a Statement to a Statement list \n");}
;

Statement: Assignment	{$$ = $1;}
	| Conditional		{$$ = $1;}
	| Loop				{$$ = $1;}
;

Assignment: LHS '=' Expr ';' 	{$$ = CreateAssignmentNode($1, $3); printf("Creating Assignment node\n");}
;

LHS: IDENT 						{$$ = CreateIdentNode($1); printf("Creating left-hand IDENT node for %s\n", $1);}
;

Conditional: "if" '(' Condition ')' '{' StatementList '}' 						{$$ = CreateIfNode($3, $6); printf("Creating if Statement node\n");}
	| "if" '(' Condition ')' '{' StatementList '}' "else" '{' StatementList '}' {$$ = CreateIfElseNode($3, $6, $10); printf("Creating if-else Statement node\n");}
;

Condition: LTerm			{$$ = $1;}
	| Condition "||" LTerm	{$$ = CreateOrNode($1, $3); printf("Creating OR node\n");}
;

LTerm: LTerm "&&" Compare	{$$ = CreateAndNode($1, $3); printf("Creating AND node\n");}
	| Compare				{$$ = $1;} 
;

Compare: Expr Op Expr		{$$ = CreateCompareNode($1, $2, $3); printf("Creating Compare node\n");}
;

Loop: "while" '(' Condition ')' '{' StatementList '}'	{$$ = CreateWhileNode($3, $6); printf("Creating while loop node\n");}
;

Op:   '<'					{$$ = "<";}
	| '>'					{$$ = ">";}
	| LE					{$$ = $1;}
	| GE					{$$ = $1;}
	| EQ					{$$ = $1;}
	| NE					{$$ = $1;}
;

Expr: Term 					{$$ = $1;}
	| Expr '+' Term 		{$$ = CreateAdditionNode($1, $3); printf("Creating Addition node\n");}
	| Expr '-' Term 		{$$ = CreateSubtractionNode($1, $3); printf("Creating Subtraction node\n");}
;

Term: Factor				{$$ = $1;}
	| Term '*' Factor		{$$ = CreateMultiplicationNode($1, $3); printf("Creating Multiplication node\n");}
	| Term '/' Factor		{$$ = CreateDivisionNode($1, $3); printf("Creating Division node\n");}
;

%%
