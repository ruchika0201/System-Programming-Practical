#include<stdio.h>
#include<string.h>
/*
GRAMMAR CONSIDERED::
E->iEdash
Edash->iEdash|null

*/


//GLOBAL VAR
char input[10];
void E();
void Edash();
void match(char t);
int i=0, error=0;

//MAIN FUNCTION
int main() 
{ 

	
	printf("\nEnter the expression :: ");
	gets(input);
	E(); 
	if (strlen(input) == i && error==0) 
	{
		printf("\nParsing Successful"); 
	}
	else
	{
		printf("\nExpression is rejected by the grammar considered");
	}	
} 

void E() 
{ 
	if (input[i] == 'i') { 
		match('i'); 
		Edash(); 
	} 
} 


void Edash() 
{ 
	if (input[i] == '+') 
	{ 
		match('+'); 
		match('i'); 
		Edash(); 
	} 
	else
		return; 
} 

void match(char t) 
{ 
	if (input[i] == t) { 
	
		i++;
	} 
	else
		error=1; 
} 
/*
Enter the expression :: i+i

Parsing Successful
--------------------------------
Process exited after 4.119 seconds with return value 19
Press any key to continue . . .



Enter the expression :: i-i

Expression is rejected by the grammar considered
--------------------------------
Process exited after 5.543 seconds with return value 49
Press any key to continue . . .

*/
