%{
#include "y.tab.h"
#include<stdio.h>
extern int yylval;
%}

ALPHA [a-zA-Z]
DIGIT [0-9]

%%
while 	return WHILE;

{ALPHA}({ALPHA}|{DIGIT})*  return ID;

{DIGIT}+ {yylval=atoi(yytext); return NUM;}

[\t] ;

\n yyterminate();

. return yytext[0];

%%

