#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

char s[100], post[100], stack[100], queue[100];
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
		return 0;
	}
}

void postfix(){
	int n = strlen(s), i = 0;
	while(s[i] != '\0'){
		if(s[i] == '('){
			top++;
			stack[top] = s[i];
		}
		else if(isalpha(s[i])){
			post[j++] = s[i];
		}
		else if(precedence(s[i])){
			while(precedence(stack[top]) >= precedence(s[i])){
				post[j++] = stack[top--];
			}
			top++;
			stack[top] = s[i];
		}
		else if(s[i] == ')'){
			while(stack[top] != '('){
				post[j++] = stack[top--];
			}
			top--;
		}
		i++;
	}
	while(top!=-1){
		post[j++] = stack[top--];
	}
	post[j] = '\0';
}

void main(){
	int i = 0;
	char ind = '1';
	
	FILE *fp,*fp1,*fp2,*fp3;
	fp = fopen( "3addr.txt","w");
	fp1 = fopen( "quadraple.txt","w");
	fp2 = fopen( "triple.txt","w");
	fprintf(fp,"Three Address\n");
	fprintf(fp1,"Quadruple\nOP\tO1\tO2\tRES\n");
	fprintf(fp2,"Triple\nIN\tOP\tO1\tO2\n");
	fp3=fopen( "input.txt","r");
	printf("Input the string: ");
	
	postfix(); /*not needed i guess*/
	while((fscanf(fp3,"%s",s))!=EOF)
	{
	postfix();
	printf("Infix : %s \nPostfix : %s\n", s, post);
	while(post[i] != '\0'){
		if(precedence(post[i])){
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
				fprintf(fp,"t%c = %c %c %c\n", ind, b, post[i], a);
				fprintf(fp1,"%c\t%c\t%c\tt%c\n", post[i], b, a, ind);
			}
			fprintf(fp2,"%c\t%c\t%c\t%c\n", ind, post[i], b, a);/*in triple you always write the number or variable name same as a and b */
			front++;
			queue[front] = ind;/*ind is used to create unique temporary variable like t1 , t2 , t3*/
			ind++;
		}
		else{
			front++;
			queue[front] = post[i];
		}
		i++;
	}
	}
}
