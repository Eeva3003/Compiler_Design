#include<stdio.h>
#include<ctype.h>
#include<string.h>

char production[10][10],ch,first[10],done[10];
	int count,c=0,ptr=-1,flag,ind=0;

void firstof(char ch)
{
	for(int i=0;i<count;i++)
	{
		if(production[i][0] == production[i][2])
			continue;
		if(ch==production[i][0])
		{
			if(production[i][2]=='#')
				first[c++]='#';
		
			else if(!isupper(production[i][2]))
				first[c++]=production[i][2];
			else
				firstof(production[i][2]);
		}
	}
}

void main()
{
	

	printf("\nEnter no of productions:");
	scanf("%d",&count);

	for(int i=0;i<count;i++)
	{
		scanf("%s",production[i]);
	}
	for(int i=0;i<count;i++)
	{
		ch=production[i][0];
		flag=0;
		for(int j=0;j<=ptr;j++)
		{
			if(done[j]==ch)
				flag=1;
		}
		if(flag==1)
			continue;

		firstof(production[i][0]);
		done[++ptr]=ch;

		printf("First(%c) {",ch);
		for(int k=0+ind;k<c;k++)
			printf("%c,",first[k]);
		printf("}\n");
		ind=c;

	}
	
}
