#include <stdio.h>
#include <string.h>
#include<stdlib.h>
void main()
{
    char code[10][30], str[20], opr[10];
    int i = 0,k=0;
    FILE *fp1,*fp2;
    fp1=fopen("input.txt","r");
    printf("file opened\n");
    fp2=fopen("result.txt","w");
    char op,fir[10],sec[10],res[10];
    while(!feof(fp1)){/*remember the function feof*/

    	fscanf(fp1,"%c%s%s%s\n",&op,fir,sec,res);/*fscanf is used in this C program to read formatted input from a file*/
    	printf("%c %s %s %s\n",op,fir,sec,res);
    
    	switch (op){
		case '+':    
		    	strcpy(opr, "ADD ");/*ariable opr is used to hold the string representing the operation, which will later be written to the output file (result.txt).*/
		    	i=0;/*The variable i is being used to indicate whether the operation involves a single operand or two operands.*/
		    	break;
	    	case '-':
			strcpy(opr, "SUB");
			i=0;/* The program generates an instruction where both operands are used in a two-operand operation.
   In this case, for addition and subtraction, the operands are stored in registers like AX and BX.*/
			break;
		case '*':
			strcpy(opr, "MUL ");
			i=1;/*where only one of the operands is involved in the operation (this could be related to multiplying or dividing a value by the contents of the register BX)*/
			break;
		case '/' :
		    	strcpy(opr, "DIV");
			i=1;
			break;
	    }

	    /*checks the length of the string fir and then performs different actions based on the second character of the string (fir[1]).
      strings '1', '2', '3', '4' likely correspond to different registers in a CPU architecture, where each register is represented by a character (e.g., 'CH', 'CL', 'DH', 'DL').*/
	    if(strlen(fir)==2)
    	    {	
    	    	if (fir[1]=='1')
    	    		fprintf(fp2,"MOV AX,CH\n");
    	    	else if (fir[1]=='2')
    	    		fprintf(fp2,"MOV BX,CL\n");
    	    	else if (fir[1]=='3')
    	    		fprintf(fp2,"MOV CX,DH\n");
    	    	else if (fir[1]=='4')
    	    		fprintf(fp2,"MOV DX,DL\n");
    	    }
    	    else
    	    fprintf(fp2,"MOV AX,[%s]\n", fir);
/*It writes to the output file (fp2) a MOV instruction that moves the value stored at the memory location referenced by fir into the AX register.
The format [%s] indicates that fir is being treated as a memory address or pointer, not just a value.
Example: If fir = "var1", this would generate
MOV AX,[var1]
*/
	    
    	    if(strlen(sec)==2)
    	    {	
    	    	if (sec[1]=='1')
    	    		fprintf(fp2,"MOV BX,CH\n");
    	    	else if (sec[1]=='2')
    	    		fprintf(fp2,"MOV BX,CL\n");
    	    	else if (sec[1]=='3')
    	    		fprintf(fp2,"MOV BX,DH\n");
    	    	else if (sec[1]=='4')
    	    		fprintf(fp2,"MOV BX,DL\n");
    	    }
/*same as above*/
    	    else
    	    	fprintf(fp2,"MOV BX,[%s]\n",sec);

/*Typically, for addition (+) or subtraction (-), both operands are involved explicitly, so i = 0 is used to format ADD AX, BX. 
For multiplication (*) or division (/), the operation might be implied to involve the AX register as a default, and i = 1 is used.*/
    	    if (i==0)
	    fprintf(fp2,"%sAX,BX\n", opr);
	    else
	    fprintf(fp2,"%s BX\n", opr);

	    
	    if(strlen(res)==2)
    	    {	
    	    	if (res[1]=='1')
    	    		fprintf(fp2,"MOV CH,AX\n");
    	    	else if (res[1]=='2')
    	    		fprintf(fp2,"MOV CL,AX\n");
    	    	else if (res[1]=='3')
    	    		fprintf(fp2,"MOV DH,AX\n");
    	    	else if (res[1]=='4')
    	    		fprintf(fp2,"MOV DL,AX\n");
    	    }
    	    
	    k++;//Number of operations processed
	    
    }
}
