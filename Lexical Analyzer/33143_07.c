#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct trm
{
	int index;
	char symbol[8];
}

trm_tab[80];

struct idn
{
	int index;
	char symbol[10];

}

idn_tab[100];
struct lit{
	char symbol[1000];
	int index;
}lit_tab[100];

struct ust
{
	char symbol[10];
	char type[5];
	int index_no;
}

ust_tab[100];

int ust_ind = 0, idn_ind = 0, tar_ind = 0, lit_ind=0;
void trm_initialize()
{
	strcpy(trm_tab[0].symbol, "auto");
	trm_tab[0].index = 1;

	strcpy(trm_tab[1].symbol, "break");
	trm_tab[1].index = 2;

	strcpy(trm_tab[2].symbol, "case");
	trm_tab[2].index = 3;

	strcpy(trm_tab[3].symbol, "char");
	trm_tab[3].index = 4;

	strcpy(trm_tab[4].symbol, "const");
	trm_tab[4].index = 5;

	strcpy(trm_tab[5].symbol, "continue");
	trm_tab[5].index = 6;

	strcpy(trm_tab[6].symbol, "default");
	trm_tab[6].index = 7;

	strcpy(trm_tab[7].symbol, "do");
	trm_tab[7].index = 8;

	strcpy(trm_tab[8].symbol, "double");
	trm_tab[8].index = 9;

	strcpy(trm_tab[9].symbol, "else");
	trm_tab[9].index = 10;

	strcpy(trm_tab[10].symbol, "enum");
	trm_tab[10].index = 11;

	strcpy(trm_tab[11].symbol, "extern");
	trm_tab[11].index = 12;

	strcpy(trm_tab[12].symbol, "float");
	trm_tab[12].index = 13;

	strcpy(trm_tab[13].symbol, "for");
	trm_tab[13].index = 14;

	strcpy(trm_tab[14].symbol, "goto");
	trm_tab[14].index = 15;

	strcpy(trm_tab[15].symbol, "if");
	trm_tab[15].index = 16;

	strcpy(trm_tab[16].symbol, "int");
	trm_tab[16].index = 17;

	strcpy(trm_tab[17].symbol, "+");
	trm_tab[17].index = 18;

	strcpy(trm_tab[18].symbol, "-");
	trm_tab[18].index = 19;

	strcpy(trm_tab[19].symbol, "*");
	trm_tab[19].index = 20;

	strcpy(trm_tab[20].symbol, "/");
	trm_tab[20].index = 21;

	strcpy(trm_tab[21].symbol, ";");
	trm_tab[21].index = 22;
	
		strcpy(trm_tab[22].symbol, "=");
	trm_tab[22].index = 23;
	
		strcpy(trm_tab[23].symbol, "<");
	trm_tab[23].index = 24;
	
		strcpy(trm_tab[24].symbol, ">");
	trm_tab[24].index = 25;
	
	strcpy(trm_tab[25].symbol, "#");
	trm_tab[25].index = 26;
	
		strcpy(trm_tab[26].symbol, "(");
	trm_tab[26].index = 27;
	
		strcpy(trm_tab[27].symbol, ")");
	trm_tab[27].index = 28;
	
		strcpy(trm_tab[28].symbol, "{");
	trm_tab[28].index = 29;
	
		strcpy(trm_tab[29].symbol, "}");
	trm_tab[29].index = 30;
	
		strcpy(trm_tab[30].symbol, """");
	trm_tab[30].index = 31;
	
	strcpy(trm_tab[31].symbol, "'");
	trm_tab[31].index = 32;
}

void display_dash()
{
	int i;
	printf("\n");
	for (i = 0; i < 45; i++)
	{
		printf("-");
	}

	printf("\n");
}
void display_star()
{
	int i;
	printf("\n");
	for (i = 0; i < 45; i++)
	{
		printf("*");
	}

	printf("\n");
}



int check_trm(char token[100])
{
	int i;
	//char space[1], c=' ';
	//space[0]=c;
	if (!(token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z'))
	{
		//	printf("\nIn space hello");
		return 2;
	}

	for (i = 0; i < 35; i++)
	{
		if (strcmp(trm_tab[i].symbol, token) == 0)
		{
			//printf("Hellaiiuuyya %s\n",trm_tab[i].symbol);
			strcpy(ust_tab[ust_ind].symbol, token);
			//	printf("\nheyyyyyy%s",ust_tab[ust_ind].symbol);
			strcpy(ust_tab[ust_ind].type, "TRM");
			ust_tab[ust_ind].index_no = trm_tab[i].index;
			ust_ind++;
			//memset(token, 0, 1000);
			return 1;
		}
	}

	if (i == 35)
	{
		return 0;
	}
}
void idn_insert(char token[200])
{
	int i, ind = idn_ind;

	for (i = 0; i < 10; i++)
	{
		if (strcmp(idn_tab[i].symbol, token) == 0)
		{
			strcpy(ust_tab[ust_ind].symbol, idn_tab[i].symbol);
			strcpy(ust_tab[ust_ind].type, "IDN");
			ust_tab[ust_ind].index_no = idn_tab[i].index;
			ust_ind++;
			break;
		}
	}
	if (i == 10)
	{
		idn_tab[idn_ind].index = ind + 1;
		strcpy(idn_tab[idn_ind].symbol, token);

		strcpy(ust_tab[ust_ind].symbol, idn_tab[idn_ind].symbol);
		strcpy(ust_tab[ust_ind].type, "IDN");
		ust_tab[ust_ind].index_no = idn_tab[idn_ind].index;
		ust_ind++;
		idn_ind++;
	}
}
void lit_insert(char token[200])
{
	int i, lit = lit_ind;


		lit_tab[lit_ind].index = lit + 1;
		strcpy(lit_tab[lit_ind].symbol, token);

		strcpy(ust_tab[ust_ind].symbol, lit_tab[lit_ind].symbol);
		strcpy(ust_tab[ust_ind].type, "LIT");
		ust_tab[ust_ind].index_no = lit_tab[lit_ind].index;
		ust_ind++;
		lit_ind++;
	
}

int isoperator(char token)
{
	if (token == '+' || token == '-' || token == '*' || token == '=' || token == '/' || token == '<' || token == '>' || token == '(' || token == ')'|| token == '{' || token == '}'|| token == ';')
	{
		return 1;
	}

	return 0;
}

int isdoubleoperator(char token1, char token2)
{
	if (token1 == token2 || token1 == '<' && token2 == '=' || token1 == '>' && token2 == '=')
	{
		return 1;
	}

	return 0;
}

void lex()
{
	char buf[1000], target[10][20] = {
		{ 0 }
	};
	int n, i;
	//printf("\nHello");
	FILE * fp;
	fp = fopen("test6.txt", "r");
	if (fp == NULL)
	{
		printf("\nFile cannot be opened!\n");
	}
	else
	{
		int token_ind = 0;
		char token[1000];
		while (fgets(buf, 1000, fp))
		{
			int i = 0, trm_check = 0;

			//	printf("%s",buf);
			while (isoperator(buf[i]) || isalpha(buf[i]) || isspace(buf[i]) || isdigit(buf[i]) || buf[i] == ';' || buf[i] == '#' || buf[i] == '.' || buf[i]=='"'|| buf[i]==40)
			{
				if (isalpha(buf[i]) || buf[i]=='.')
				{
					token[token_ind] = buf[i];
					i++;
					token_ind++;
					continue;
				}
			
					
					int p = check_trm(token);
					if (p == 2)
					{
					 			// printf("\nIn space");
					}
					if (p == 0)
					{
						idn_insert(token);
					}
					token_ind = 0;
					memset(token, 0, 1000);
					if (isoperator(buf[i]) || buf[i]=='#')
					{
						
						char oper[10];
						int op_ind=0;
					token[token_ind] = buf[i];
			
						
						int y;
						for(y=0;y<35;y++)
						{
							if(token[0]==trm_tab[y].symbol[0])
						{
								strcpy(ust_tab[ust_ind].symbol, token);
		
			strcpy(ust_tab[ust_ind].type, "TRM");
			ust_tab[ust_ind].index_no = trm_tab[y].index;
			ust_ind++;
			break;
						
						}	
						}
		
						token_ind = 0;
					memset(token, 0, 1000);    
					}
					char literal[1000]={0}; 
					int litint=0;
				if(buf[i]=='"')
				{
					token[token_ind]=buf[i];
						strcpy(ust_tab[ust_ind].symbol, token);
		
			strcpy(ust_tab[ust_ind].type, "TRM");
			ust_tab[ust_ind].index_no = 31;
			ust_ind++;
			i++;
					while(buf[i]!='"')
					{
						literal[litint]=buf[i];
					i++;
						litint++;
						
					}
				//	strcpy(literal[litint], "\0");
			//	printf("%s",literal);
					lit_insert(literal);
					litint=0;
					token_ind = 0;
					memset(literal, 0, 1000);   
				}
				
					
			
			

					i++;

					continue;
				
				i++;
			}
		}
	}
}

int main()
{
	int i;
	trm_initialize();
	lex();
	//display_dash();
	display_star();
	printf("\n\t\tUST TABLE\n");
	display_star();
//	display_dash();
	printf("\nSYMBOL\t\tTYPE\t\tINDEX\n");
	display_dash();
	for (i = 0; i < ust_ind; i++)
	{
		printf("\n%s\t\t\t%s\t\t%d", ust_tab[i].symbol, ust_tab[i].type, ust_tab[i].index_no);
	}
display_star();;
//	display_dash();
	printf("\n");
	display_star();
	printf("\n\t\tIDN TABLE\n");
	display_star();
//	display_dash();
	printf("\nSYMBOL\t\tINDEX\n");
	display_dash();
	for (i = 0; i < idn_ind; i++)
	{
		printf("\n%s\t\t%d", idn_tab[i].symbol, idn_tab[i].index);
	}
display_star();

	printf("\n");
	display_star();
	printf("\n\t\tLITERAL TABLE\n");
	display_star();
//	display_dash();
	printf("\nSYMBOL\t\tINDEX\n");
	display_dash();
	for (i = 0; i < lit_ind; i++)
	{
		printf("\n%s\t\t%d", lit_tab[i].symbol, lit_tab[i].index);
	}
display_star();
	//display_dash();

}
/*
*********************************************

                UST TABLE

*********************************************

SYMBOL          TYPE            INDEX

---------------------------------------------

#                       TRM             26
include                 IDN             1
<                       TRM             24
stdio.h                 IDN             2
>                       TRM             25
int                     TRM             17
main                    IDN             3
(                       TRM             27
)                       TRM             28
{                       TRM             29
int                     TRM             17
sum                     IDN             4
=                       TRM             23
for                     TRM             14
(                       TRM             27
i                       IDN             5
=                       TRM             23
;                       TRM             22
i                       IDN             5
<                       TRM             24
;                       TRM             22
i                       IDN             5
+                       TRM             18
+                       TRM             18
)                       TRM             28
{                       TRM             29
sum                     IDN             4
=                       TRM             23
sum                     IDN             4
+                       TRM             18
i                       IDN             5
;                       TRM             22
}                       TRM             30
printf                  IDN             6
(                       TRM             27
"                       TRM             31
hello %d                        LIT             1
}                       TRM             30
*********************************************


*********************************************

                IDN TABLE

*********************************************

SYMBOL          INDEX

---------------------------------------------

include         1
stdio.h         2
main            3
sum             4
i               5
printf          6
*********************************************


*********************************************

                LITERAL TABLE

*********************************************

SYMBOL          INDEX

---------------------------------------------

hello %d                1
*********************************************

--------------------------------
Process exited after 0.4457 seconds with return value 10
Press any key to continue . . .*/
