#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char *input;
int i=0;
char lasthandle[6],stack[50],handles[][7]={")E(","E*E","E+E","i","E^E","E-E","E/E"};
//(E) becomes )E( when pushed to stack

int top=0,l;
char prec[9][9]={

                            /*input*/

            /*stack    +    -   *   /   ^   i   (   )   $  */

            /*  + */  '>', '>','<','<','<','<','<','>','>',

            /*  - */  '>', '>','<','<','<','<','<','>','>',

            /*  * */  '>', '>','>','>','<','<','<','>','>',

            /*  / */  '>', '>','>','>','<','<','<','>','>',

            /*  ^ */  '>', '>','>','>','<','<','<','>','>',

            /*  i */  '>', '>','>','>','>','e','e','>','>',

            /*  ( */  '<', '<','<','<','<','<','<','>','e',

            /*  ) */  '>', '>','>','>','>','e','e','>','>',

            /*  $ */  '<', '<','<','<','<','<','<','<','>',

                };

int getindex(char c)
{
switch(c)
    {
    case '+':return 0;
    case '-':return 1;
    case '*':return 2;
    case '/':return 3;
    case '^':return 4;
    case 'i':return 5;//identifier
    case '(':return 6;
    case ')':return 7;
    case '$':return 8;//end of stack symbol
    }
}


int shift()
{
stack[++top]=*(input+i++);
stack[top+1]='\0';
}


int reduce()
{
int i,len,found,t;
for(i=0;i<7;i++)//selecting handles
    {
    len=strlen(handles[i]);
    if(stack[top]==handles[i][0]&&top+1>=len)
        {
        found=1;
        for(t=0;t<len;t++)
            {
            if(stack[top-t]!=handles[i][t])
                {
                found=0;
                break;
                }
            }
        if(found==1)
            {
            stack[top-t+1]='E';
            top=top-t+1;
            strcpy(lasthandle,handles[i]);
            stack[top+1]='\0';
            return 1;//successful reduction
            }
        }
   }
return 0;
}



void dispstack()
{
int j;
for(j=0;j<=top;j++)
    printf("%c",stack[j]);
}



void dispinput()
{
int j;
for(j=i;j<l;j++)//from i to l (length of input)
    printf("%c",*(input+j));\\also printing input +j
}



void main()
{
int j;

input=(char*)malloc(50*sizeof(char));//use of malloc to dynamically alloacte memory
printf("\nEnter the string\n");
scanf("%s",input);
input=strcat(input,"$");//appending the end of string
l=strlen(input);
strcpy(stack,"$");//appending the end of stack(since the $ symbol is in precedance graph it is of atmost importance)
printf("\nSTACK\tINPUT\tACTION");
while(i<=l)
	{
	shift();//the first operation is shifting
	printf("\n");
	dispstack();//then display the stack after each shift
	printf("\t");
	dispinput();//display input
	printf("\tShift");
	if(prec[getindex(stack[top])][getindex(input[i])]=='>')// here get the prec of element at the top of stack(stack[top]) to that of current input(input[i]), if it is '>'
		//'>' means reduce and '< 'means shift
	{
		while(reduce())
			{
			printf("\n");
			dispstack();
			printf("\t");
			dispinput();
			printf("\tReduced: E->%s",lasthandle);// also print handle used for reduction
			}
		}
	}

if(strcmp(stack,"$E$")==0)//if the end of stack is a E symbpl then string is accepted else not
    printf("\nAccepted;");
else
    printf("\nNot Accepted;");
}

























