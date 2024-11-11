#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isKeyword(char buffer[]) // char buffer as input 
{
	char keywords[35][10] =// 35 keywords , char
	{"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", 
	"float", "for", "goto","if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", 
	"switch", "typdef", "union", "unsigned", "void", "volatile", "while", "printf", "scanf","main"};
	
	int i,flag =0;
	for(i=0;i<35;i++)
	{
		if(strcmp(keywords[i],buffer)==0)
		{
			flag=1;
			break;
		}
	}
	return flag;// return the flagvalue
}

void main()
{
	char ch,ch1, buffer[50], operator[]="+-*/%";//operator char array
	FILE *fp,*fp2;// FILE is very important 
	int i, j=0, l=1, index = 1;
	char arr[1000][3];//?
	fp=fopen("inp.txt", "r");
	fp2=fopen("output.txt", "w+");//fopen function used
	if(fp==NULL)
	{
		printf("Error while opening file\n");
		exit(0);
	}
	else
	{
		printf("Lexeme: \t L.no:\t Token:");
		fprintf(fp2,"Lexeme: \t L.no:\t Token:");
		while((ch=fgetc(fp))!=EOF)// read charcetr by charactre using fgetc(fp) till end of line
		{
			for(i=0;i<5;++i)// first check for operator case 1
			{
				if(ch==operator[i])
				{
					printf("\n%c \t\t %d\t Arithmetic Operator ", ch,l);// l is used for line number 
					break;
				}
			}
			if(i==5)//case 2 
			{
				if(isalnum(ch))// check if its alphanumeric Build a buffer by collecting characters until a non-alphanumeric character is encountered.
				{
					if(isdigit(ch) && j==0)// check if its a digit and also 
					{ 
						j=0;// if its starting of buffer 
					}
					else 
					{
						buffer[j++] = ch;
						ch1= fgetc(fp);
						if(isalnum(ch1))
							fseek(fp, -1, SEEK_CUR);
						else 
						{
							fseek (fp,-1,SEEK_CUR);
							buffer[j]='\0';
							if(isKeyword(buffer)==1)//Check if the buffer content matches a keyword using isKeyword()
							{
								if(strcmp(buffer, "printf")==0){// if its a printf  then remove all the words in between ""
								while((ch=fgetc(fp))!='\n'){// not equal to next line remove them 
								
								}
								}
								printf("\n%s \t\t %d \t keyword ", buffer, l);//print keywporf
								j=0;//buffer starting =0 reset
							}
							else
							{
								if(strcmp(buffer, "main")!=0)
								
								{
									fseek(fp2, SEEK_SET, 0);//sets the file pointer to the start of output.txt so the program can search for duplicate identifiers from the beginning of the file.
									char a[50], b[50], c[50], ch2, ch3;
									int flag1 = 0;
									while(!feof(fp2)){//again reads output file
									fscanf(fp2, "%s\t%s\t%s", a, b, c);//t checks if the identifier buffer matches any identifier a found in the output file.
									if(strcmp(a, buffer) == 0){// if it matches flag set to 1 and break
									flag1 = 1;
									break;
								}
							}
								if(flag1==0){// if match onnum illa then
									ch2 = fgetc(fp);
									if(ch2=='='){// check for assignment operator
									ch3 = fgetc(fp);
									fprintf(fp2,"\n%s \t\t %d\t identifier, %c", buffer, index, ch3);
									fseek(fp,-2,SEEK_CUR);//rewinds the pointer in fp by two characters to keep the context in the main file.
									}
									else{
									fprintf(fp2,"\n%s \t\t %d\t identifier", buffer, index);//all fprintf aahto
									}
									printf("\n%s \t\t %d\t Identifier, %d", buffer, l, index);	
									index++;
									}
								else{
									printf("\n%s \t\t %d\t Identifier, %s", buffer, l, b);
									}
									}
								j=0;
							}
						}
					}
				}
				if(ch=='<')// case 3
				{
					ch1= fgetc(fp);
					if(ch1=='=')
					{
						printf("\n%c%c \t\t %d \t Relop LE",ch,ch1,l);
					}
					else
					{
						fseek(fp,-1,SEEK_CUR);
						printf("\n%c \t\t %d \t RelOP LT", ch,l);// set to back of the current 
					}
				}
				else if(ch=='>')
				{
					ch1= fgetc(fp);
					if(ch1=='=')
					{
						printf("\n%c%c \t\t %d \t Relop GE",ch,ch1,l);
					}
					else
					{
						fseek(fp,-1,SEEK_CUR);
						printf("\n%c \t\t %d \t Relop GT", ch,l);
					}
				}
				else if(ch=='=')
				{
					ch1=fgetc(fp);
					if(ch1=='=') 
					{
						printf("\n%c%c \t\t %d \t Relop EQ", ch, ch1, l);
					}
					else
					{
						fseek(fp, -1, SEEK_CUR);
						printf("\n%c \t\t %d \t Assign OP, EQ",ch,l);
					}
				}
				if(ch=='\n'){
					l++;
				}
			}
		}
	}
	printf("\n");
}
