#define NIL 0
typedef enum {FALSE,TRUE} BOOLEAN;
typedef enum e_node_name {
	N_NULL,
	N_PROGRAM,
	N_EXP_IDENT,
	N_EXP_INT_CONST,
	N_EXP_FLOAT_CONST,
	N_EXP_CHAR_CONST,
	N_EXP_STRING_LITERAL,
	N_EXP_ARRAY,
	N_EXP_FUNCTION_CALL,
	N_EXP_STRUCT,
	N_EXP_ARROW,
	N_EXP_POST_INC,
	N_EXP_POST_DEC,
	N_EXP_PRE_INC,
	N_EXP_PRE_DEC,
	N_EXP_AMP,
	N_EXP_STAR,
	N_EXP_NOT,
	N_EXP_PLUS,
	N_EXP_MINUS,
	N_EXP_SIZE_EXP,
	N_EXP_SIZE_TYPE,
	N_EXP_CAST,
	N_EXP_MUL,
	N_EXP_DIV,
	N_EXP_MOD,
	N_EXP_ADD,
	N_EXP_SUB,
	N_EXP_LSS,
	N_EXP_GTR,
	N_EXP_LEQ,
	N_EXP_GEQ,
	N_EXP_NEQ,
	N_EXP_EQL,
	N_EXP_AND,
	N_EXP_OR,
	N_EXP_ASSIGN,
	
	N_ARG_LIST,
	N_ARG_LIST_NIL,
	
	N_STMT_LABEL_CASE,
	N_STMT_LABEL_DEFAULT,
	N_STMT_COMPOUND,
	N_STMT_EMPTY,
	N_STMT_EXPRESSION,
	N_STMT_IF,
	N_STMT_IF_ELSE,
	N_STMT_SWITCH,
	N_STMT_WHILE,
	N_STMT_DO,
	N_STMT_FOR,
	N_STMT_RETURN,
	N_STMT_CONTINUE,
	N_STMT_BREAK,
	
	N_FOR_EXP,
	N_STMT_LIST,
	N_STMT_LIST_NIL,
	
	N_INIT_LIST,
	N_INIT_LIST_ONE,
	N_INIT_LIST_NIL} NODE_NAME;

typedef enum {T_NULL,T_ENUM,T_ARRAY,T_STRUCT,T_UNION,T_FUNC,T_POINTER,
		T_VOID} T_KIND;
typedef enum {Q_NULL,Q_CONST,Q_VOLATILE} Q_KIND;
typedef enum {S_NULL,S_AUTO,S_STATIC,S_TYPEDEF,S_EXTERN,S_REGISTER} S_KIND;
typedef enum {ID_NULL,ID_VAR,ID_FUNC,ID_PARM,ID_FIELD,ID_TYPE,ID_ENUM,
		ID_STRUCT,ID_ENUM_LITERAL}  ID_KIND;

typedef struct s_node {
	NODE_NAME name;
	int line;
	int value;
	struct s_type  *type;
	struct s_node *llink;
	struct s_node *clink;
	struct s_node *rlink;} A_NODE;

typedef struct s_type {
	T_KIND kind;
	int size;
	int local_var_size;
	struct s_type *element_type;
	struct s_id *field;
	struct s_node *expr;
	int line;
	BOOLEAN check; 
	BOOLEAN prt; } A_TYPE;


typedef struct s_id {
	char *name;
	ID_KIND kind;
	S_KIND specifier;
	int level;
	int address;
	int value;
	A_NODE *init;
	A_TYPE *type;
	int line;
	struct s_id *prev;
	struct s_id *link;} A_ID;

typedef union {int i; float f; char c; char *s;} LIT_VALUE;
typedef struct lit {int addr; A_TYPE *type; LIT_VALUE value;} A_LITERAL;
typedef struct {
	A_TYPE *type;
	S_KIND stor;
	int line;} A_SPECIFIER;

// print.c function prototype
void print_ast(A_NODE *);
void prt_program(A_NODE *, int);
void prt_initializer(A_NODE *, int);
void prt_arg_expr_list(A_NODE *, int);
void prt_statement(A_NODE *, int);
void prt_statement_list(A_NODE *, int);
void prt_for_expression(A_NODE *, int);
void prt_expression(A_NODE *, int);
void prt_A_TYPE(A_TYPE *, int);
void prt_A_ID_LIST(A_ID *, int);
void prt_A_ID(A_ID *, int);
void prt_A_ID_NAME(A_ID *, int);
void prt_STRING(char *, int);
void prt_integer(int, int);
void print_node(A_NODE *,int);
void print_space(int);

// syntax.c function prototype
A_NODE			*makeNode (NODE_NAME,A_NODE *,A_NODE *,A_NODE *);
A_NODE			*makeNodeList (NODE_NAME,A_NODE *,A_NODE *);
A_ID			*makeIdentifier(char *);
A_ID			*makeDummyIdentifier();
A_TYPE			*makeType(T_KIND);
A_SPECIFIER		*makeSpecifier(A_TYPE *,S_KIND);
A_ID			*searchIdentifier(char *,A_ID *);
A_ID			*searchIdentifierAtCurrentLevel(char *,A_ID *);
A_SPECIFIER		*updateSpecifier(A_SPECIFIER *, A_TYPE *, S_KIND);
void			checkForwardReference();
void			setDefaultSpecifier(A_SPECIFIER *);
A_ID			*linkDeclaratorList(A_ID *,A_ID *) ;
A_ID			*getIdentifierDeclared(char *);
A_TYPE			*getTypeOfStructOrEnumRefIdentifier(T_KIND,char *,ID_KIND);
A_ID			*setDeclaratorInit(A_ID *,A_NODE *);
A_ID			*setDeclaratorKind(A_ID *,ID_KIND);
A_ID			*setDeclaratorType(A_ID *,A_TYPE *);
A_ID			*setDeclaratorElementType(A_ID *,A_TYPE *);
A_ID			*setDeclaratorTypeAndKind(A_ID *,A_TYPE *,ID_KIND);
A_ID			*setDeclaratorListSpecifier(A_ID *,A_SPECIFIER *);
A_ID			*setFunctionDeclaratorSpecifier(A_ID *, A_SPECIFIER *);
A_ID			*setFunctionDeclaratorBody(A_ID *, A_NODE *);
A_ID			*setParameterDeclaratorSpecifier(A_ID *, A_SPECIFIER *);
A_ID			*setStructDeclaratorListSpecifier(A_ID *, A_TYPE *);
A_TYPE			*setTypeNameSpecifier(A_TYPE *, A_SPECIFIER *);
A_TYPE			*setTypeElementType(A_TYPE *,A_TYPE *);
A_TYPE			*setTypeField(A_TYPE *,A_ID *);
A_TYPE			*setTypeExpr(A_TYPE *,A_NODE *);
A_TYPE			*setTypeAndKindOfDeclarator(A_TYPE *,ID_KIND,A_ID *);
A_TYPE			*setTypeStructOrEnumIdentifier(T_KIND,char *,ID_KIND);
BOOLEAN			isNotSameFormalParameters(A_ID *, A_ID *);
BOOLEAN			isNotSameType(A_TYPE *, A_TYPE *);
BOOLEAN			isPointerOrArrayType(A_TYPE *);
void			syntax_error(int i, char *s);
void			initialize();

// print_sem.c function prototype
void print_sem_ast(A_NODE *);
void prt_sem_program(A_NODE *, int);
void prt_sem_initializer(A_NODE *, int);
void prt_sem_arg_expr_list(A_NODE *, int);
void prt_sem_statement(A_NODE *, int);
void prt_sem_statement_list(A_NODE *, int);
void prt_sem_for_expression(A_NODE *, int);
void prt_sem_expression(A_NODE *, int);
void prt_sem_A_TYPE(A_TYPE *, int);
void prt_sem_A_ID_LIST(A_ID *, int);
void prt_sem_A_ID(A_ID *, int);
void prt_sem_A_ID_NAME(A_ID *, int);
void prt_sem_LITERAL(int, int);
void prt_sem_integer(int, int);

// semantic.c function prototype
// float atof(); -> #include <stdlib.h>
void semantic_analysis(A_NODE *);
void set_literal_address(A_NODE *);
int put_literal(A_LITERAL, int);
void sem_program(A_NODE *);
A_TYPE *sem_expression(A_NODE *);
int sem_statement(A_NODE *, int, A_TYPE *, BOOLEAN, BOOLEAN, BOOLEAN);
int sem_statement_list(A_NODE *, int, A_TYPE *, BOOLEAN, BOOLEAN, BOOLEAN);
void sem_for_expression(A_NODE *);
int sem_A_TYPE(A_TYPE *);
int sem_declaration_list(A_ID *, int);
int sem_declaration(A_ID *, int);
void sem_arg_expr_list(A_NODE *, A_ID *);
A_ID *getStructFieldIdentifier(A_TYPE *, char *);
A_ID *getPointerFieldIdentifier(A_TYPE *, char *);
A_NODE *convertScalarToInteger(A_NODE *);
A_NODE *convertUsualAssignmentConversion(A_TYPE *, A_NODE *);
A_NODE *convertUsualUnaryConversion(A_NODE *);
A_TYPE *convertUsualBinaryConversion(A_NODE *);
A_NODE *convertCastingConversion(A_NODE *, A_TYPE *);
BOOLEAN isAllowableAssignmentConversion(A_TYPE *, A_TYPE *, A_NODE *);
BOOLEAN isAllowableCastingConversion(A_TYPE *, A_TYPE *);
BOOLEAN isModifiableLvalue(A_NODE *);
BOOLEAN isConstantZeroExp(A_NODE *);
BOOLEAN isSameParameterType(A_ID *, A_ID *);
BOOLEAN isNotSameType(A_TYPE *, A_TYPE *);
BOOLEAN isCompatibleType(A_TYPE *, A_TYPE *);
BOOLEAN isCompatiblePointerType(A_TYPE *, A_TYPE *);
BOOLEAN isIntType(A_TYPE *);
BOOLEAN isFloatType(A_TYPE *);
BOOLEAN isArithmeticType(A_TYPE *);
BOOLEAN isAnyIntegerType(A_TYPE *);
BOOLEAN isIntegralType(A_TYPE *);
BOOLEAN isStructOrUnionType(A_TYPE *);
BOOLEAN isFunctionType(A_TYPE *);
BOOLEAN isScalarType(A_TYPE *);
BOOLEAN isPointerType(A_TYPE *);
BOOLEAN isPointerOrArrayType(A_TYPE *);
BOOLEAN isArrayType(A_TYPE *);
BOOLEAN isStringType(A_TYPE *);
BOOLEAN isVoidType(A_TYPE *);
A_LITERAL checkTypeAndConvertLiteral(A_LITERAL, A_TYPE *, int);
A_LITERAL getTypeAndValueOfExpression(A_NODE *);
A_TYPE *setTypeElementType(A_TYPE *, A_TYPE *);
A_TYPE *makeType(T_KIND);
// void setTypeSize(A_TYPE *, int); -> not declared
void semantic_warning(int, int);
void semantic_error(int, int, char *);
A_NODE *makeNode(NODE_NAME, A_NODE *, A_NODE *, A_NODE *);

// code_generator.c function prototype
typedef enum op {
	OP_NULL,
	OP_LOD,
	OP_LDX,
	OP_LDXB,
	OP_LDA,
	OP_LITI,
	OP_STO,
	OP_STOB,
	OP_STX,
	OP_STXB,
	OP_SUBI,
	OP_SUBF,
	OP_DIVI,
	OP_DIVF,
	OP_ADDI,
	OP_ADDF,
	OP_OFFSET,
	OP_MULI,
	OP_MULF,
	OP_MOD,
	OP_LSSI,
	OP_LSSF,
	OP_GTRI,
	OP_GTRF,
	OP_LEQI,
	OP_LEQF,
	OP_GEQI,
	OP_GEQF,
	OP_NEQI,
	OP_NEQF,
	OP_EQLI,
	OP_EQLF,
	OP_NOT,
	OP_OR,
	OP_AND,
	OP_CVTI,
	OP_CVTF,
	OP_JPC,
	OP_JPCR,
	OP_JMP,
	OP_JPT,
	OP_JPTR,
	OP_INT,
	OP_INCI,
	OP_INCF,
	OP_DECI,
	OP_DECF,
	OP_SUP,
	OP_CAL,
	OP_ADDR,
	OP_RET,
	OP_MINUSI,
	OP_MINUSF,
	OP_CHK,
	OP_LDI,
	OP_LDIB,
	OP_SWITCH,
	OP_SWVALUE,
	OP_SWDEFAULT,
	OP_SWLABEL,
	OP_SWEND,
	OP_POP,
	OP_POPB} OPCODE;

typedef enum {SW_VALUE,SW_DEFAULT} SW_KIND;
typedef struct sw {SW_KIND kind; int val; int label;} A_SWITCH;

void code_generation(A_NODE *);
void gen_literal_table();
void gen_program(A_NODE *);
void gen_expression(A_NODE *);
void gen_expression_left(A_NODE *);
void gen_arg_expression(A_NODE *);
void gen_statement(A_NODE *, int, int, A_SWITCH[], int *);
void gen_statement_list(A_NODE *, int, int, A_SWITCH[], int *);
void gen_initializer_global(A_NODE *, A_TYPE *, int);
void gen_initializer_local(A_NODE *, A_TYPE *, int);
void gen_declaration_list(A_ID *);
void gen_declaration(A_ID *);
void gen_code_i(OPCODE,int,int);
void gen_code_f(OPCODE,int,float);
void gen_code_s(OPCODE,int,char *);
void gen_code_l(OPCODE,int,int);
void gen_label_number(int);
void gen_label_name(char *);
void gen_error(int, int, char *);
int get_label();

