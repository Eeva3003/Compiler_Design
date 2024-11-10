#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

char s[100]/*to input string*/, post[100]/*to store postfix*/, stack[100]/*to store stack(convert to postfix)*/, queue[100]/*to store queue(output)*/;// all are character array
int top = -1, j = 0, front = -1;

int precedence(char c){
	if(c == '+' || c == '-'){
		return 1;
	}
	else if(c == '*' || c == '/'){
		return 2;
	}
	else if(c == '^'){
		return 3;
	}
	else{
		return 0;//shows its not an operator
	}
}

void postfix(){
	int n = strlen(s), i = 0;//calculate the length of string
	while(s[i] != '\0'){//iterate till end of string is reach(while loop)
		if(s[i] == '('){// if open paranthesis directly insert onto top of stack
			top++;
			stack[top] = s[i];
		}
		else if(isalpha(s[i])){// if alphanumeric add to the psotfix expression
			post[j++] = s[i];//post increament is done
		}
		else if(precedence(s[i])){// if an operator 
			while(precedence(stack[top]) >= precedence(s[i])){// while the precendance of the input sympol is greatre than or equal to one on top of stack
				post[j++] = stack[top--];//add the stack top onto postfix
			}
			top++;
			stack[top] = s[i];// at the end the cureent symbol is added to the top of the stack
		}
		else if(s[i] == ')'){// if its a closing bracket
			while(stack[top] != '('){// till an opening bracket is observed 
				post[j++] = stack[top--];// add the elements onto postfix expression
			}
			top--;// decrement top of the stack to remove opening bracket
		}
		i++;//increament i to set to next symbol
	}
	while(top!=-1){ // if the stack is not compleletly traveersed empty it onto postfix expression
		post[j++] = stack[top--];
	}
	post[j] = '\0';// add end of stack to postfix expression
}

void main(){
	int i = 0;
	char ind = '1';// the temporray variable which holds t1, t2 etc hence initialised to one 
	
	FILE *fp,*fp1,*fp2,*fp3;// one for input and three for output
	fp = fopen( "3addr.txt","w");
	fp1 = fopen( "quadraple.txt","w");
	fp2 = fopen( "triple.txt","w");
	fprintf(fp,"Three Address\n");
	fprintf(fp1,"Quadruple\nOP\tO1\tO2\tRES\n");
	fprintf(fp2,"Triple\nIN\tOP\tO1\tO2\n");
	fp3=fopen( "input.txt","r");//fopent o open all the text files
	printf("Input the string: ");
	
	postfix(); /*not needed i guess*/
	while((fscanf(fp3,"%s",s))!=EOF)// scan each string till the end if file is reached
	{
	postfix();// call postfix to convert the expression and store it in postfix array
	printf("Infix : %s \nPostfix : %s\n", s, post);

		//PARTIAL OUTPUT INFIX TO POSTFIX CONVERSION


		
	while(post[i] != '\0'){// traverse till the end of postfix array is reached
		if(precedence(post[i])){// if it is an operator
			char a = queue[front--];/*retrieve two most recent operands from stack to queue*/
			char b = queue[front--];
			if(isdigit(a) && isdigit(b)){
				fprintf(fp,"t%c = t%c %c t%c\n", ind, b, post[i], a); /*fp=3 address code, fp1=quadruple. if they are digits then write as t3, t2 etc */
				fprintf(fp1,"%c\tt%c\tt%c\tt%c\n", post[i], b, a, ind);
			}
			else if(isdigit(b)){
				fprintf(fp,"t%c = t%c %c %c\n", ind, b, post[i], a);/*if not digit directly write the variable name*/
				fprintf(fp1,"%c\tt%c\t%c\tt%c\n", post[i], b, a, ind);
			}
			else if(isdigit(a)){
				fprintf(fp,"t%c = %c %c t%c\n", ind, b, post[i], a);
				fprintf(fp1,"%c\t%c\tt%c\tt%c\n", post[i], b, a, ind);
			}
			else{
				fprintf(fp,"t%c = %c %c %c\n", ind, b, post[i], a);// mostly used when all are variabels
				fprintf(fp1,"%c\t%c\t%c\tt%c\n", post[i], b, a, ind);// in quadruple only result (index needs t)
			}
			fprintf(fp2,"%c\t%c\t%c\t%c\n", ind, post[i], b, a);/*in triple you always write the number or variable name same as a and b */
			front++;// increament front first
			queue[front] = ind;/*ind is used to create unique temporary variable like t1 , t2 , t3*/
			ind++;// add the temporary variable onto front of queue and increamnet index
		}
		else{
			front++; // just adding the operands onto the queue
			queue[front] = post[i];
		}
		i++;// increament i at last with eveyrhitng else
	}
	}
}
