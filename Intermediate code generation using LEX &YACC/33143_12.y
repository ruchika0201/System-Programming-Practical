%{
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "lex.yy.c"

char st[100][10];
int top=0;
char i_[2]="0";
char temp[2]="t";

int lnum=1;
int start=1;

int yylex();
int yyerror();


void push();
void lab1();
void lab2();
void lab3();
void codegen();
void codegen_assign();
void codegen_umin();

extern char* yytext;

%}

%token WHILE ID NUM
%right '='
%left '-' '+'
%left '*' '/'
%left UMINUS

%%
S:	WHILE { lab1(); } '(' E ')' { lab2(); } E ';' { lab3(); }
 ;

E:	 V '=' { push(); } E { codegen_assign(); }
	|E '+' { push(); } E { codegen(); }
	|E '-' { push(); } E { codegen(); }
	|E '*' { push(); } E { codegen(); }
	|E '/' { push(); } E { codegen(); }
	|'(' E ')'
	|V
	|NUM  { push(); }
	| '-' { push(); } E { codegen_umin(); } %prec UMINUS
 	;

V:	ID { push(); }
 ;



%%

void main()
{
	printf("Enter the expression ? ");
	yyparse();
}

void push()
{
	strcpy(st[++top],yytext);

}

void codegen()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("%s = %s %s %s \n",temp,st[top-2],st[top-1],st[top]);
	top=top-2;
	strcpy(st[top],temp);
	i_[0]++;
}

void codegen_assign()
{

	printf("%s = %s \n",st[top-2],st[top]);
	top=top-2;


}

void codegen_umin()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("%s = -%s \n",temp,st[top]);
	top=top-2;
	strcpy(st[top],temp);
	i_[0]++;

}

void lab1()
{
	printf("L%d:\n",lnum++);
}

void lab2()
{
	strcpy(temp,"t");
	strcat(temp,i_);
	printf("%s = not %s\n",temp,st[top]);
	printf("if %s goto L%d\n",temp,lnum);
	i_[0]++;
}

void lab3()
{
	printf("goto L%d \n",start);
	printf("L%d: \n",lnum);

}


int yyerror()
{}

int yywrap()
{
	return 1;
}









