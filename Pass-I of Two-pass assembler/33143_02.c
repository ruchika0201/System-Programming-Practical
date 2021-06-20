#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1

int sym_ind = 0, ad_flag = 0, dl_flag = 0, lit_ind = 0, lit_flag = 0, sym_flag = 0, pool_count=0, pool_ind=0;
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
}pool_tab[10];

int getWords(char base[], char target[10][20])
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

void display_table()
{
	int i;
	printf("\nSERIAL NO.\tMNEUMONIC\tOPCODE\tNO OF OPERANDS\t\t SIZE\t TYPE\n");
	for (i = 0; i < 17; i++)
	{
		printf("\n%d\t\t%s\t\t%d\t\t%d\t\t%d\t%s", i + 1, table_rows[i].mneumo, table_rows[i].opcode, table_rows[i].no_of_operands, table_rows[i].size, table_rows[i].type);
	}

	printf("\n");

}

void display_star()
{
	int i;
	printf("\n");
	for (i = 0; i < 30; i++)
	{
		printf("*");
	}

	printf("\n");
}
void display_star1()
{
	int i;
	printf("\n");
	for (i = 0; i < 60; i++)
	{
		printf("*");
	}

	printf("\n");
}

void display_dash()
{
	int i;
	printf("\n");
	for (i = 0; i < 30; i++)
	{
		printf("-");
	}

	printf("\n");
}
void display_dash1()
{
	int i;
	printf("\n");
	for (i = 0; i < 60; i++)
	{
		printf("-");
	}

	printf("\n");
}

void display_file()
{
	FILE * f;
	int wc, k = 0;
	char buf[1000];

	f = fopen("file2.txt", "r");
	if (f == NULL)
	{
		printf("\nFile not opened");
	}
	else
	{
		while (fgets(buf, 1000, f))
		{
			printf("%d\t", ++k);
			wc = countfunc(buf);

			printf("%s\t%d ", buf, wc);
			//	printf("\t%d\t",wc);
			printf("\n");

		}
	}
}

struct table search(char target[20], int wc)
{
	int i;

	for (i = 0; i < 18; i++)
	{
		if (strcmp(table_rows[i].mneumo, target) == 0)
		{
			return table_rows[i];
		}
	}
}

void pass1()
{
	FILE * fp1;
	int k = 0, j = 0, a[40], lc = 0, ptp = 1, ltp = 1, stp = 1, curr_sym_ind, curr_lit_ind, rg = 0;
	char buf[1000], start[] = "START";
	int wc = 0, i = 0, n;
	char ch = buf[0], target[10][20] = {
		{ 0 }
	};
	char *p, *q;
	char end[] = "END";
	char dc[] = "DC";
	char ds[] = "DS";
	char is[] = "IS";
	char ad[] = "AD";
	char dl[] = "DL";
	char origin[] = "ORIGIN";
	char equ[] = "EQU";
	char ltorg[] = "LT";
	char word[] = "N";
	
	char areg[] = "AREG,";
	char breg[] = "BREG,";
	char creg[] = "CREG,";
	char equal[] = "=";
	char plus[] = "+";
	fp1 = fopen("file2.txt", "r");
	if (fp1 == NULL)
	{
		printf("\nFile not opened");
	}
	else
	{
		display_star1();
		printf("\n|\tLC\t\t|\tIntermediate Code\t|");
		display_star1();
		while (fgets(buf, 1000, fp1))
		{
			wc = countfunc(buf);
			n = getWords(buf, target);

			if (wc == 2)
			{
				tab = search(target[0], wc);
					if(tab.opcode==0)
				{
					printf("\nInvalid");
					break;
				}
				if (strcmp(start, target[0]) == 0)
				{
					int x = atoi(target[1]);
					lc = x;
					ad_flag = 1;
					printf("\n\t\t\t\t(AD 01) (C %d) \t", lc);
					//display_dash1();
					//continue;	
				}
				else if (strcmp(is, tab.type) == 0)
				{
					for (i = 0; i < 9; i++)
					{
						if (strcmp(sym_tab[i].symbol, target[1]) == 0)
						{
							curr_sym_ind = i;
							break;
						}
					}

					if (i == 9)
					{
						strcpy(sym_tab[sym_ind].symbol, target[1]);
						curr_sym_ind = sym_ind;
						sym_ind++;

					}

					printf("\n\t%d\t\t\t(%s 0%d) (S %d) \t", lc, tab.type, tab.opcode, curr_sym_ind);
					//display_dash1();
					lc = lc + 1;
					ad_flag = 0;
				}
				else {}
			}

//EQU
			p = strstr(buf, equ);
			int v;
			if (p)
			{
				tab=search(target[1], wc);
				if(tab.opcode==0)
				{
					printf("\nInvalid");
					break;
				}
				int eqflag=0;
						for (i = 0; i < 9; i++)
						{
							if (strcmp(sym_tab[i].symbol, target[0]) == 0)
							{
								
								for(v=0;v<9;v++)
								{
						
							
									if (strcmp(sym_tab[v].symbol, target[2]) == 0)
									{
											//printf("\nHeyy");
									
										printf("\n%s",sym_tab[v].symbol);
										sym_tab[i].add=sym_tab[v].add;
									
										curr_sym_ind=v;
										eqflag=1;
										break;
									}
								}
								if(eqflag==1)
								{
									break;
								}
								
								

								
							}
						}
						
				printf("\n\t%d\t\t\t(%s 0%d) (S %d) \t", lc, tab.type, tab.opcode, curr_sym_ind);	
				//display_dash1();	
				lc=lc+1;
						
				continue;
			}

		

			p = strstr(buf, origin);
			if (wc == 2 && p)
			{
				int g;
				tab = search(target[0], wc);
					if(tab.opcode==0)
				{
					printf("\nInvalid");
					break;
				}
				char *arg = strchr(buf, '+');
				char *arg4 = strchr(buf, '-');
				if (arg != NULL || arg4 != NULL)
				{
					arg++; 
					g = atoi(arg);
					
				}

				char arg1[10];
				strcpy(arg1, target[1]);

				char arg2[10];
				int j;
				for (i = 0; i < 10; i++)
				{
					if (arg1[i] == '+' || arg1[i] == '-')
					{
						j = i;
						while (j != 10)
						{
							arg2[j] = '\0';
							j++;
						}

						break;
					}

			
					arg2[i] = arg1[i];
				}

				
				int origin_add;
				for (i = 0; i < 9; i++)
				{
					if (strcmp(sym_tab[i].symbol, arg2) == 0)
					{
						//	printf("\n%d",sym_tab[i].add);
						//curr_sym_ind = i;
						origin_add = sym_tab[i].add;
						//	lc=+g;
						//printf("\n%d",lc);
						break;
					}
				}

				if (i == 9)
				{
					printf("\nNot found");

				}

				printf("\n\t%d\t\t\t(%s 0%d) ((S %d))+%d \t", lc, tab.type, tab.opcode, i, g);
				//display_dash1();
				lc = origin_add + g;

			}

			if (wc != 2)
				if (wc == 3 && strcmp(ds, target[1]) != 0 && strcmp(dc, target[1]) != 0)
				{
//printf("\nHey");
					tab = search(target[0], wc);
						if(tab.opcode==0)
				{
					printf("\nInvalid");
					break;
				}
					if (strcmp(areg, target[1]) == 0)
					{
						rg = 1;
						//printf("\n\t%d\t\t\t(%s 0%d) (RG 01) \t", lc, tab.type, tab.opcode);
					}
					else if (strcmp(breg, target[1]) == 0)
					{
						rg = 2;
						//printf("\n\t%d\t\t\t(%s 0%d) (RG 02) \t", lc, tab.type, tab.opcode);
					}
					else if (strcmp(creg, target[1]) == 0)
					{
						rg = 3;
						//printf("\n\t%d\t\t\t(%s 0%d) (RG 03) \t", lc, tab.type, tab.opcode);
						//display_dash1();
					}
					else
					{
						rg = 0;
						
					}

				
					char d1 = '=';
					char d2 = target[2][0];
					char d3 = target[2][2];
					//printf("\n%c",d3);
				//	strcpy(found, target[2]);
					//	p = strstr(buf, equal);

					if (d1 == d2)
					{
						strcpy(lit_tab[lit_ind].literal, target[2]);
						//int g =(int)d3;
						//printf("\n%d",g);
						//printf("\nheyyyyyy");
					//	printf("\n%s", target[2]);
						curr_lit_ind = lit_ind;
						lit_ind++;

						if (rg != 0)
						{
							printf("\n\t%d\t\t\t(%s 0%d) (RG 0%d) (L %d) \t", lc, tab.type, tab.opcode, rg, curr_lit_ind);
							//display_dash1();
						}
						else
						{
							printf("\n\t%d\t\t\t(%s 0%d)  (L %d) \t", lc, tab.type, tab.opcode, curr_lit_ind);
							//display_dash1();
						}

						lc = lc + 1;
continue;
						ad_flag = 0;
					}
					else
					{
						for (i = 0; i < 9; i++)
						{
							if (strcmp(sym_tab[i].symbol, target[2]) == 0)
							{
								curr_sym_ind = i;

								break;
							}
						}

						if (i == 9)
						{

							strcpy(sym_tab[sym_ind].symbol, target[2]);

							curr_sym_ind = sym_ind;
							sym_ind++;

						}

						if (rg != 0)
						{
							printf("\n\t%d\t\t\t(%s 0%d) (RG 0%d) (S %d) \t", lc, tab.type, tab.opcode, rg, curr_sym_ind);
							//display_dash1();
						}
						else
						{
							printf("\n\t%d\t\t\t(%s 0%d) (S %d) \t", lc, tab.type, tab.opcode, curr_sym_ind);
							//display_dash1();
						}

						lc = lc + 1;
tab_initialize(tab);
continue;
						//ad_flag = 0;

					}
				}

			p = strstr(buf, dc);
			if (p)
			{
//printf("\nHey dc");
				tab = search(target[1], wc);
				//printf("\n%s\t%s",target[1],tab.mneumo);
					if(tab.opcode==0)
				{
					printf("\nInvalid");
					break;
				}
				if (strcmp(dc, tab.mneumo) == 0)
				{
					for (i = 0; i < 9; i++)
					{
						q = strstr(sym_tab[i].symbol, target[0]);
						if (q)
						{
							sym_tab[i].add = lc;
							curr_sym_ind = i;

							break;
						}
					}

					if (i == 9)
					{
						strcpy(sym_tab[sym_ind].symbol, target[0]);
						sym_tab[sym_ind].add = lc;
						curr_sym_ind = sym_ind;
						sym_ind++;

					}

					int x = atoi(target[2]);
					printf("\n\t%d\t\t\t(%s 0%d) (S %d) (C %c) \t", lc, tab.type, tab.opcode, curr_sym_ind, target[2][1]);
					//display_dash1();
					lc = lc + 1;

				}
			}

			p = strstr(buf, ds);
			if (p)
			{
				//	printf("\nIn ds");

				for (i = 0; i < 9; i++)
				{
					q = strstr(sym_tab[i].symbol, target[0]);
					if (q)
					{
						sym_tab[i].add = lc;
						//	printf("\nFound");
						// sym_flag = 1;
						break;
					}
				}

				if (i == 9)
				{
					strcpy(sym_tab[sym_ind].symbol, target[0]);
					sym_tab[sym_ind].add = lc;
					curr_sym_ind = sym_ind;
					sym_ind++;

				}

				int d = atoi(target[2]);
				//printf("\n\t%d\t\t\t(DL 02) (C %s)", lc, target[2]);
				printf("\n\t%d\t\t\t(DL 02) (C %d) \t", lc, d);
				//display_dash1();
				int x = atoi(target[2]);
				lc = lc + x;
				dl_flag = 1;
			}

			if (wc == 4)
			{
				for(i=0;i<9;i++)
				{
				if(strcmp(sym_tab[i].symbol, target[0])==0)
				{
				break;
				}
				}
				if(i==9)
				{
				strcpy(sym_tab[sym_ind].symbol, target[0]);
				
				sym_tab[sym_ind].add = lc;
				sym_ind++;
				}
				
				tab = search(target[1], wc);
					if(tab.opcode==0)
				{
					printf("\nInvalid");
					break;
				}
				if (strcmp(is, tab.type) == 0)
				{
					//	printf("\n%s",tab.mneumo);
						if (strcmp(areg, target[2]) == 0)
					{
						rg = 1;
						//printf("\n\t%d\t\t\t(%s 0%d) (RG 01) \t", lc, tab.type, tab.opcode);
					}
					else if (strcmp(breg, target[2]) == 0)
					{
						rg = 2;
						//printf("\n\t%d\t\t\t(%s 0%d) (RG 02) \t", lc, tab.type, tab.opcode);
					}
					else if (strcmp(creg, target[2]) == 0)
					{
						rg = 3;
					//	printf("\n\t%d\t\t\t(%s 0%d) (RG 03) \t", lc, tab.type, tab.opcode);
					}
					else
					{
						rg = 0;
					}
					char d1 = '=';
					char d2 = target[3][0];
					if (d1 == d2)
					{
						
						strcpy(lit_tab[lit_ind].literal, target[3]);
					//	printf("\n%s", target[2]);
						curr_lit_ind = lit_ind;
						lit_ind++;

						if (rg != 0)
						{
								printf("\n\t%d\t\t\t(S %d) (%s 0%d) (RG 0%d) (L %d)", lc, sym_ind, tab.type, tab.opcode, rg, curr_lit_ind);
								//display_dash1();
						//	printf("\n\t%d\t\t\t(%s 0%d) (RG 0%d) (L %d) \t", lc, tab.type, tab.opcode, rg, curr_lit_ind);
						}
						else
						{
							printf("\n\t%d\t\t\t(%s 0%d)  (L %d) \t", lc, tab.type, tab.opcode, curr_lit_ind);
						//	display_dash1();
						}

					
					}
				
				
				//	ad_flag = 0;
				}
			
				

				for (i = 0; i < 9; i++)
				{
					if (strcmp(sym_tab[i].symbol, target[3]) == 0)
					{
						curr_sym_ind = i;
						break;
					}
				}

				if (i == 9)
				{
					strcpy(sym_tab[sym_ind].symbol, target[0]);
					sym_tab[sym_ind].add = lc;
					curr_sym_ind = sym_ind;
					sym_ind++;
				}
					lc = lc + 1;
					
			}

			
			if(wc==1)
			{
			char stop[]="STOP";
			//printf("\nHii");
			tab=search(target[0],wc);
if (p = strstr(buf, stop))
{

//printf("\nIn stop");
printf("\n\t%d\t\t\t(%s %d)", lc,tab.type, tab.opcode);
			lc=lc+1;
//display_dash1();
tab_initialize(tab);
			continue;
}

			if (p = strstr(buf, end))
			{
			
			//printf("\nHey");
			printf("\n\t%d\t\t\t(AD 02)\n", lc);
				//display_dash1();
				int m = lc;
				int b;
				for (i = 0; i < 9; i++)
				{
					//p = strstr(lit_tab[i].literal, equal);
					if (lit_tab[i].add == 0 && lit_tab[i].literal[0] != '\0')
					{
					
						lit_tab[i].add = m;
						m++;
						lc = m;
						pool_count++;
					}
				}
				pool_tab[pool_ind].count=pool_count;
				pool_ind++;
tab_initialize(tab);
				lc = lc + 1;
			
				break;
			
			}
				p = strstr(buf, ltorg);
			if (p)
			{
				//printf("\nIn ltorg");
				tab = search(target[0], wc);
				if(tab.opcode==0)
				{
					printf("\nInvalid");
					break;
				}
				int m = lc;
				int b;
				for (i = 0; i < 9; i++)
				{
					p = strstr(lit_tab[i].literal, equal);
					if (lit_tab[i].add == 0 && lit_tab[i].literal[0] != '\0')
					{
					
						lit_tab[i].add = m;
						
					//	int c=atoi(lit_tab[i].literal[2]);
						printf("\n\t%d\t\t\t(%s 0%d) (L %d) (C %c)", lc, tab.type, tab.opcode, i,lit_tab[i].literal[2]);
						// printf("%c",lit_tab[i].literal[2]);
					
						//printf(")");
						//display_dash1();
						m++;
						lc = m;
						pool_count++;
					}
				}
				pool_tab[pool_ind].count=pool_count;
				pool_ind++;
tab_initialize(tab);
				continue;

				
			}
			
			
			
			printf("\n\t%d\t\t\t(%s %d)\n", lc,tab.type, tab.opcode);
			lc=lc+1;
tab_initialize(tab);
			continue;
			}
			tab_initialize(tab);
		}
	}	//END OF ELSE 
	display_star1();
	printf("\n\n\n");

}

int main()
{
	int b, k;
	initialize();
	display_table();
	display_file();
	pass1();
		display_star();
	printf("\n\tSYMBOL TABLE");
display_star();
printf("\nIndex | Symbols | Address");
	display_dash();
int v;
	for (k = 0; k < 4; k++)
	{
			if(sym_tab[k].add!=0)
			{
int p=strlen(sym_tab[k].symbol);
if(sym_tab[k].symbol[p-1]=='\n')
{
printf("\n%d\t",k);
for(v=0;v<p-1;v++)
{
printf("%c",sym_tab[k].symbol[v]);
}
printf("\t%d",sym_tab[k].add);
continue;
}
//printf("\n%c",sym_tab[k].symbol[p-1]);

				printf("\n%d\t%s  \t%d",k, sym_tab[k].symbol, sym_tab[k].add);
				//display_dash();
			}
	
	}
display_star();
printf("\n\n");
	display_star();
	printf("\n\tLITERAL TABLE");
display_star();
	printf("\nIndex | Literals | Address");
	display_dash();
	char g[5];
	int i,j,m=0;
	for (b = 0; b < 4; b++)
	{
		if(lit_tab[b].add!=0)
		{
			printf("\n%d\t='%c'\t   %d",b, lit_tab[b].literal[2], lit_tab[b].add);
				//display_dash();
		}
		
	
	}
	display_star();
	printf("\n\n");
	display_star();
		printf("\n\tPOOL TABLE");
display_star();
	printf("\nIndex | Pool Count");
	display_dash();
		for (b = 0; b < 4; b++)
	{
		if(pool_tab[b].count!=0)
		{
			printf("\n%d\t%d",b, pool_tab[b].count);
				//display_dash();
		}
		
	
	}
display_star();
	//search();

}
/*
SERIAL NO.      MNEUMONIC       OPCODE  NO OF OPERANDS           SIZE    TYPE

1               START           1               1               1       AD
2               READ            9               1               1       IS
3               MOVEM           5               2               1       IS
4               ADD             1               2               1       IS
5               PRINT           10              1               1       IS
6               BC              7               1               1       IS
7               END             2               0               1       AD
8               MOVER           4               2               1       IS
9               SUB             2               2               1       IS
10              MULT            3               2               1       IS
11              DIV             8               2               1       IS
12              COMP            6               2               1       IS
13              EQU             5               0               1       AD
14              ORIGIN          4               0               1       AD
15              LTORG           3               0               1       AD
16              DC              1               0               1       DL
17              STOP            11              0               1       IS
1       START 200
        2
2       MOVER AREG, ='5'
        3
3       MOVEM AREG, A
        3
4       LOOP MOVER AREG, A
        4
5       MOVER CREG, B
        3
6       ADD CREG, ='1'
        3
7       LTORG
        1
8       NEXT1 SUB AREG, ='1'
        4
9       ORIGIN LOOP+6
        2
10      MULT CREG, B
        3
11      STOP
        1
12      A DS 2
        3
13      B DC '3'
        3
14      NEXT1 EQU LOOP
        3
15      END
        1
16
        1

************************************************************

|       LC              |       Intermediate Code       |
************************************************************

                                (AD 01) (C 200)
        200                     (IS 04) (RG 01) (L 0)
        201                     (IS 05) (RG 01) (S 0)
        203                     (IS 04) (RG 03) (S 2)
        204                     (IS 01) (RG 03) (L 1)
        205                     (IS 01) (L 0) (C 5)
        206                     (IS 01) (L 1) (C 1)
        207                     (S 4) (IS 02) (RG 01) (L 2)
        208                     (AD 04) ((S 1))+6
        208                     (IS 03) (RG 03) (S 2)
        209                     ( 0)
        210                     (DL 02) (C 2)
        212                     (DL 01) (S 2) (C 3)
        213                     (AD 05) (S 2)
        214                     (AD 02)

************************************************************




******************************

        SYMBOL TABLE
******************************

Index | Symbols | Address
------------------------------

0       A       210
1       LOOP    202
2       B       212
3       NEXT1   207
******************************



******************************

        LITERAL TABLE
******************************

Index | Literals | Address
------------------------------

0       ='5'       205
1       ='1'       206
2       ='1'       214
******************************



******************************

        POOL TABLE
******************************

Index | Pool Count
------------------------------

0       2
1       3
******************************

--------------------------------
Process exited after 0.3562 seconds with return value 10
Press any key to continue . . .*/
