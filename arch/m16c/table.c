#include "pass2.h"

# define TLL TLONGLONG|TULONGLONG
# define ANYSIGNED TINT|TLONG|TSHORT|TCHAR
# define ANYUSIGNED TUNSIGNED|TULONG|TUSHORT|TUCHAR
# define ANYFIXED ANYSIGNED|ANYUSIGNED
# define TUWORD TUNSIGNED
# define TSWORD TINT
# define TWORD TUWORD|TSWORD

struct optab table[] = {
/* First entry must be an empty entry */
{ -1, FOREFF, SANY, TANY, SANY, TANY, 0, 0, "", },

{ SCONV,	INTAREG,
	STAREG,		TCHAR,
	SANY,		TINT,
		0,	RLEFT,
		"	exts.b AL\n", },

{ OPSIMP,	INAREG|FOREFF,
	SAREG|STAREG,			TWORD|TPOINT,
	SAREG|STAREG|SNAME|SOREG,	TWORD|TPOINT,
		0,	RLEFT,
		"	Ow AR,AL\n", },

{ LS,		INTAREG,
	STAREG|SAREG,	TWORD,
	SCON,		TANY,
		0,	RLEFT,
		"	shl AR, AL\n", },

{ LS,		INTAREG,
	STAREG|SAREG,	TWORD,
	STAREG|SAREG,	TWORD,
		0,	RLEFT,
		"	shl AR, AL\n", },

{ RS,		INTAREG,
	STAREG|SAREG,	TUWORD,
	SCON,		TANY,
		0,	RLEFT,
		"	shl -AR, AL\n", },

{ RS,		INTAREG,
	STAREG|SAREG,	TSWORD,
	SCON,		TANY,
		0,	RLEFT,
		"	sha -AR, AL\n", },

{ OPLOG,	FORCC,
	SBREG|STBREG|SOREG,	TWORD|TPOINT,
	SCON,			TWORD|TPOINT,
		0,	RESCC,
		"	cmp AR,AL\n", },

{ GOTO,		FOREFF,
	SCON,	TANY,
	SANY,	TANY,
		0,	RNOP,
		"	jmp LL\n", },

{ OPLTYPE,	INTAREG,
	SANY,	TANY,
	SOREG,	TWORD|TPOINT,
		NAREG,	RESC1,
		"	mov.w AR, A1\n", },	

{ OPLTYPE,	INTBREG,
	SANY,	TANY,
	SOREG,	TWORD|TPOINT,
		NBREG,	RESC1,
		"	mov.w AR, A1\n", },	

{ OPLTYPE,	INTAREG,
	SANY,		TANY,
	SCON|SNAME,	TWORD|TPOINT|TCHAR|TUCHAR|TSHORT|TUSHORT,
		NAREG,	RESC1,
		"	mov.w AR, A1\n", },

{ OPLTYPE,	INTAREG,
	SANY,	TANY,
	SOREG,	TCHAR|TUCHAR,
		NAREG,	RESC1,
		"	mov.b AL, A1\n", },

{ COMPL,	INTAREG,
	SAREG|STAREG,	TWORD,
	SANY,		TANY,
		0,	RLEFT,
		"	not.w AL\n", },

{ FUNARG,	FOREFF,
	SCON|SAREG|SNAME|SOREG,	TWORD|TPOINT,
	SANY,			TANY,
		0,	RNULL,
		"	push.w AL\n", },

{ FUNARG,	FOREFF,
	SAREG|STAREG,	TCHAR|TUCHAR,
	SANY,			TANY,
		0,	RNULL,
		"	exts.b AL\n	push.w AL\n", },

{ ASSIGN,	FOREFF,
	SAREG|STAREG|SNAME|SOREG,	TWORD|TPOINT,
	SCON,				TANY,
		0,	0,
		"	mov.w AR, AL\n", },

{ ASSIGN,	FOREFF|INTAREG,
	SOREG|SNAME,	TWORD|TPOINT,
	SAREG|STAREG,	TWORD|TPOINT,
		0,	RRIGHT,
		"	mov.w AR, AL\n", },

{ MOVE,		FOREFF|INTAREG,
	SAREG|STAREG|STBREG|SBREG,	TWORD|TPOINT,
	SAREG|STAREG,			TWORD|TPOINT,
		NAREG,	RESC1,
		"	mov.w AL, AR\n", },

{ UMUL, 	INTAREG,
	SBREG|STBREG,	TPOINT|TWORD,
	SANY,		TPOINT|TWORD,
		NAREG,	RESC1,
		"	mov.w [AL],A1\n", },

{ UMUL, 	INTBREG,
	SBREG|STBREG,	TPOINT|TWORD,
	SANY,		TPOINT|TWORD,
		NBREG|NBSL,	RESC1,
		"	mov.w [AL],A1\n", },

{ UMUL,		INTAREG,
	SBREG|STBREG,	TCHAR|TUCHAR|TPTRTO,
	SANY,		TCHAR|TUCHAR,
		NAREG,	RESC1,
		"	mov.b [AL], A1\n", }, 

{ UCALL,	FOREFF|INTAREG,
	SCON,	TANY,
	SANY,	TANY,
		NAREG|NASL,	RESC1,
		"	jsr.w CL\n", },

{ FREE, FREE,	FREE,	FREE,	FREE,	FREE,	FREE,	FREE,	"help; I'm in trouble\n" },
};

int tablesize = sizeof(table)/sizeof(table[0]);

