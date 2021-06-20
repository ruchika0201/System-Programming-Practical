#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
int sym_ind = 0, ad_flag = 0, dl_flag = 0, lit_ind = 0, lit_flag = 0, sym_flag = 0, pool_count = 0, pool_ind = 0;
struct table
{
	char mneumo[50];
	int opcode;
	int no_of_operands;
	int size;
	char type[10];
}

table_rows[20], tab;

struct symtab
{
	char symbol[50];
	int add;
	int length;
}
sym_tab[10];
struct littab
{
	char literal[50];
	int add;
}

lit_tab[10];
struct pooltab
{
	int count;
}
pool_tab[10];

/*
int getWords(char base[], char target[50][50])
{
	int n = 0, i, j = 0;
	//printf("\nHello");
	for (i = 0; TRUE; i++)
	{
	//printf("\n%c",base[i]);
		if (base[i] != ' ')
		{
			target[n][j++] = base[i];
			//n++;
			//j=0;
		}
		else if(base[i]=='(')
		{
		//printf("\n%c",base[i]);
		// printf("\nHello");
		//target[n][j++] = base[i];
		   int v=i;
		 	// printf("\nHello");
		  while(base[v]!=')')
		  {
		 	//printf("\n%c",base[v]);
		   target[n][j++] = base[v];
		   v++;
		  }
		  target[n][j++] = base[v];
		  i=v;
		}
		else
		{
			target[n][j++] = '\0';	//insert NULL
			n++;
			j = 0;
		}

		if (base[i] == '\0')
			break;
	}

	return n;
}
*/
int getWords(char base[], char target[50][50])
{
	int n = 0, i, j = 0;

	for (i = 0; TRUE; i++)
	{
		if (base[i] != ' ')
		{
			target[n][j++] = base[i];
		}
		else
		{
			target[n][j++] = '\0';	//insert NULL
			n++;
			j = 0;
		}

		if (base[i] == '\0')
			break;
	}

	return n;
}
int countfunc(char buf[])
{
	int i, wc = 0;
	for (i = 0; buf[i] != '\0'; i++)
	{
		if (isspace(buf[i]))
		{
			wc = wc + 1;
		}
	}

	return wc;
}
void tab_initialize(struct table tab)
{
	tab.no_of_operands = 0;
	tab.opcode = 0;
	tab.size = 0;
	memset(tab.type, 0, 50);
	memset(tab.mneumo, 0, 50);

}

void initialize()
{
	strcpy(table_rows[0].mneumo, "START");

	table_rows[0].opcode = 01;
	table_rows[0].no_of_operands = 1;
	table_rows[0].size = 1;
	strcpy(table_rows[0].type, "AD");

	strcpy(table_rows[1].mneumo, "READ");
	table_rows[1].opcode = 9;
	table_rows[1].no_of_operands = 1;
	table_rows[1].size = 1;
	strcpy(table_rows[1].type, "IS");

	strcpy(table_rows[2].mneumo, "MOVEM");
	table_rows[2].opcode = 05;
	table_rows[2].no_of_operands = 2;
	table_rows[2].size = 1;
	strcpy(table_rows[2].type, "IS");

	strcpy(table_rows[3].mneumo, "ADD");
	table_rows[3].opcode = 01;
	table_rows[3].no_of_operands = 2;
	table_rows[3].size = 1;
	strcpy(table_rows[3].type, "IS");

	strcpy(table_rows[4].mneumo, "PRINT");
	table_rows[4].opcode = 10;
	table_rows[4].no_of_operands = 1;
	table_rows[4].size = 1;
	strcpy(table_rows[4].type, "IS");

	strcpy(table_rows[5].mneumo, "BC");
	table_rows[5].opcode = 07;
	table_rows[5].no_of_operands = 1;
	table_rows[5].size = 1;
	strcpy(table_rows[5].type, "IS");

	strcpy(table_rows[6].mneumo, "END");
	table_rows[6].opcode = 02;
	table_rows[6].no_of_operands = 0;
	table_rows[6].size = 1;
	strcpy(table_rows[6].type, "AD");

	strcpy(table_rows[7].mneumo, "MOVER");
	table_rows[7].opcode = 04;
	table_rows[7].no_of_operands = 2;
	table_rows[7].size = 1;
	strcpy(table_rows[7].type, "IS");

	strcpy(table_rows[8].mneumo, "SUB");
	table_rows[8].opcode = 02;
	table_rows[8].no_of_operands = 2;
	table_rows[8].size = 1;
	strcpy(table_rows[8].type, "IS");

	strcpy(table_rows[9].mneumo, "MULT");
	table_rows[9].opcode = 03;
	table_rows[9].no_of_operands = 2;
	table_rows[9].size = 1;
	strcpy(table_rows[9].type, "IS");

	strcpy(table_rows[10].mneumo, "DIV");
	table_rows[10].opcode = 8;
	table_rows[10].no_of_operands = 2;
	table_rows[10].size = 1;
	strcpy(table_rows[10].type, "IS");

	strcpy(table_rows[11].mneumo, "COMP");
	table_rows[11].opcode = 06;
	table_rows[11].no_of_operands = 2;
	table_rows[11].size = 1;
	strcpy(table_rows[11].type, "IS");

	strcpy(table_rows[12].mneumo, "EQU");
	table_rows[12].opcode = 05;
	table_rows[12].no_of_operands = 0;
	table_rows[12].size = 1;
	strcpy(table_rows[12].type, "AD");

	strcpy(table_rows[13].mneumo, "ORIGIN");
	table_rows[13].opcode = 04;
	table_rows[13].no_of_operands = 0;
	table_rows[13].size = 1;
	strcpy(table_rows[13].type, "AD");

	strcpy(table_rows[14].mneumo, "LTORG");
	table_rows[14].opcode = 03;
	table_rows[14].no_of_operands = 0;
	table_rows[14].size = 1;
	strcpy(table_rows[14].type, "AD");

	strcpy(table_rows[15].mneumo, "DC");
	table_rows[15].opcode = 01;
	table_rows[15].no_of_operands = 0;
	table_rows[15].size = 1;
	strcpy(table_rows[15].type, "DL");

	strcpy(table_rows[16].mneumo, "DS");
	table_rows[16].opcode = 02;
	table_rows[16].no_of_operands = 0;
	table_rows[16].size = 1;
	strcpy(table_rows[16].type, "DL");

	strcpy(table_rows[16].mneumo, "STOP");
	table_rows[16].opcode = 11;
	table_rows[16].no_of_operands = 0;
	table_rows[16].size = 1;
	strcpy(table_rows[16].type, "IS");

}
void pass2()
{
	FILE * fp1;
	int k = 0, j = 0, a[40], lc = 0, ptp = 1, ltp = 1, stp = 1, curr_sym_ind, curr_lit_ind, rg = 0;
	char buf[1000], start[] = "START";
	int wc = 0, i = 0, n;
	char ch = buf[0], target[50][50] = {
		{ 0 }
	};

	fp1 = fopen("IC.txt", "r");
	if (fp1 == NULL)
	{
		printf("\nFile not opened");
	}
	else
	{
		//display_star1();

		//display_star1();
		int y = 0;
		while (fgets(buf, 1000, fp1))
		{
			wc = countfunc(buf);
			n = getWords(buf, target);
printf("\n");
			//printf("\n%d",n);
			y = 0;
			//printf("\n%s",target[0]);
			//printf("\t%s",target[1]);
				//printf("\n%s",target[3]);
			//printf("\n%s\t%s\t%s\t%s\t%s\t%s", target[0], target[1], target[2], target[3], target[4], target[5]);
			//y++;
			//fflush(stdin);
			//	target[50][50] = {{0}};
			if (target[0][0] == '\0')
			{
				printf("-----START\n");
				continue;
			}
			if (target[1][1] == 'I' && target[1][2] == 'S')
			{
				printf("%s", target[0]);
				printf("\t(%c%c)", target[1][3], target[1][4]);

				if (target[2][1] == 'R' && target[2][2] == 'G' || target[3][1] == 'R' && target[3][2] == 'G')
				{
					if (target[2][1] == 'R' && target[2][2] == 'G')
					{
						printf("\t(%c%c)", target[2][3], target[2][4]);
					}
					if (target[3][1] == 'R' && target[3][2] == 'G')
					{
						printf("\t(%c%c)", target[3][3], target[3][4]);
					}
				}
				else
				{
					printf("\t(00)\n");
				}

				if (target[3][1] == 'S' || target[2][1] == 'S')
				{
					if (target[3][1] == 'S')
					{
						int f = target[3][2] - '0';
						int add = 0;
						add = sym_tab[f].add;
						printf("\t%d", add);
					}

					if (target[2][1] == 'S')
					{
						int f = target[2][2] - '0';
						int add = 0;
						add = sym_tab[f].add;
						printf("\t%d", add);
					}
				}
				if (target[3][1] == 'L' || target[2][1] == 'L')
				{

					if (target[3][1] == 'L')
					{
//printf("\nHeyy");
						int f = target[3][2] - '0';
//printf("\n%d",f);
						int add = 0;
						add = lit_tab[f].add;
						printf("\t%d", add);
					}

					if (target[2][1] == 'L')
					{
						int f = target[2][2] - '0';
						int add = 0;
						add = lit_tab[f].add;
						printf("\t%d", add);
					}
				}
			}	//end of IS

if(target[1][1] == 'D' && target[1][2] == 'L')
{
if(target[1][4] == '1')	//dc
{
printf("%s\t'=%c'",target[0], target[3][2]);

}

if(target[1][4] == '2')	//ds
{
int store=target[2][2]-'0';
int flag=0;
int lcdl=atoi(target[0]);
while(flag!=store)
{
printf("%d\n",lcdl);
lcdl++;
flag++;
}


}

}


			if(target[1][1] == 'A' && target[1][2] == 'D')
{
if(target[1][4] == '4' || target[1][4] == '3' || target[1][4] == '2' || target[1][4] == '5')
{
if(target[1][4] == '4' || target[1][4] == '5')
{
printf("------ORIGIN  OR EQU----\n");
}

if(target[1][4] == '3')
{
printf("%s\t'=%c'",target[0], target[3][2]);
}

if(target[1][4] == '2')
{
printf("%s",target[0]);
}
		
}

}
			n = 0;
			memset(target[0], 0, sizeof(target[0]));
			memset(target[1], 0, sizeof(target[1]));
			memset(target[2], 0, sizeof(target[2]));
			memset(target[3], 0, sizeof(target[3]));
			memset(target[4], 0, sizeof(target[4]));
		}
	}
}
void sym_initialize()
{
	int i;
	sym_tab[0].add = 210;
	strcpy(sym_tab[0].symbol, "A");
	//sym_tab[0].symbol="A";

	sym_tab[1].add = 202;
	strcpy(sym_tab[1].symbol, "LOOP");
	//sym_tab[1].symbol="LOOP";

	sym_tab[2].add = 212;
	strcpy(sym_tab[2].symbol, "B");
	//sym_tab[2].symbol="B";

	sym_tab[3].add = 202;
	strcpy(sym_tab[3].symbol, "NEXT1");
	//sym_tab[0].symbol="NEXT1";
}
void lit_initialize()
{
	int i;
	lit_tab[0].add = 205;
	strcpy(lit_tab[0].literal, "='5'");
	//sym_tab[0].symbol="A";

	lit_tab[1].add = 206;
	strcpy(lit_tab[1].literal, "='1'");
	//sym_tab[1].symbol="LOOP";

	lit_tab[2].add = 214;
	strcpy(lit_tab[2].literal, "='1'");
	//sym_tab[2].symbol="B";

	
}
int main()
{
	sym_initialize();
lit_initialize();
	pass2();

}
/*

200     (04)    (01)    205
201     (05)    (01)    210
203     (04)    (03)    212
204     (01)    (03)    206
205     (01)    (00)
        205
206     (01)    (00)
        206

------ORIGIN  OR EQU----

208     (03)    (03)    212
209     (03)    (00)

210
211

212     '=1'
------ORIGIN  OR EQU----

214

--------------------------------
Process exited after 0.1165 seconds with return value 0
Press any key to continue . . .*/
