#include<stdio.h>
#include<ctype.h>
#include<string.h>

void followfirst(char, int, int);
void follow(char c);
void findfirst(char, int, int);

int count/*no of productions*/, n = 0,m = 0,k,e,p1 = 0, p2, tmp;
char firstmat[10][100],followmat[10][100], production[10][10],f[10], first[10],ck;

int main(int argc, char ** argv) {// to read no. of arg and string arg
	int jm = 0;
	int km = 0;
	int i, choice;
	char c, ch;
	printf("\nEnter the productions: ");

	scanf("%d", & count);
	for (i = 0; i < count; i++)
		scanf("%s", production[i]);//productions entered as strings
	int kay;
	char done[count];
	int ptr = -1; 
	for (k = 0; k < count; k++) {
		for (kay = 0; kay < 100; kay++) 
			firstmat[k][kay] = '!';//initialising the first matrix
	}
	int p1 = 0, p2, tmp;//This is the index representing the row of the firstmat array. Each row corresponds to a non-terminal (e.g., First(E), First(T)
	//This is the index representing the current column in the row p1. p2 is incremented after the assignment (p2++), which ensures that the next element of the FIRST set is stored in the next column.
	for (k = 0; k < count; k++) {//iterates over each production rule
		c = production[k][0];// c set to first left hand side non terminal of production rule
		p2 = 0;
		tmp = 0;
		//This part checks if the non-terminal c has already been processed:
		for (kay = 0; kay <= ptr; kay++)
		if (c == done[kay])//The array done[] keeps track of non-terminals that have already been processed for their FIRST set.
		tmp = 1;
		if (tmp == 1)//if tmp is 1 then it exits the current iteraion
		continue;
		findfirst(c, 0, 0);//  this function will update the global first[] array with the FIRST set of c
		ptr += 1;//ptr keeps track of length of done array
		done[ptr] = c;// add c to done array
		printf("\nFirst(%c) = { ", c);
		firstmat[p1][p2++] = c;//?
		for (i = 0 + jm; i < n; i++) {
			int lark = 0, chk = 0;
			for (lark = 0; lark < p2; lark++) {
				if (first[i] == firstmat[p1][lark]) {
					  chk = 1;
					  break;
				}
			}
			if (chk == 0) {
				printf("%c, ", first[i]);
				firstmat[p1][p2++] = first[i];
			}
		}
		printf("}\n");
		jm = n;
		p1++;
	}
	printf("\n\n\n");


	//Follow printing
	char donee[count];
	ptr = -1;
	for (k = 0; k < count; k++) {
		for (kay = 0; kay < 100; kay++) 
			followmat[k][kay] = '!';
	}
	p1 = 0; //in p
	int kk, u, flag, land = 0;
	char s[10];
	u = 0;
	flag = 0;
	for (e = 0; e < count; e++) {
		kk = 0;
		ck = production[e][0];
		for (i = 0; i <= u; i++) {
			if (s[i] == ck) {
				kk++;
			}
		}
		if (kk == 0) { 
		
			s[u] = ck;
			u++;
			p2 = 0;
			tmp = 0;
			for (kay = 0; kay <= ptr; kay++)
			if (ck == donee[kay])
			  tmp = 1;

			if (tmp == 1)
			continue;
			land += 1;
			follow(ck);

			ptr += 1;
			printf("Follow(%c) = { ", ck);
			followmat[p1][p2++] = ck;
			for (i = 0 + km; i < m; i++) {
				int lark = 0, chk = 0;
				for (lark = 0; lark < p2; lark++) {
					  if (f[i] == followmat[p1][lark]) {
					  	chk = 1;
					  	break;
					  }
				}
				if (chk == 0) {
					printf("%c, ", f[i]);
					followmat[p1][p2++] = f[i];
				}
			}
			printf("}\n\n");
			km = m;
			p1++;
		}
	}
}

void follow(char c) {
	int i, j;
	if (production[0][0] == c) 
		f[m++] = '$';

	for (i = 0; i < 10; i++) {
		for (j = 2; j < 10; j++) {
			if (production[i][j] == c) {
				if (production[i][j + 1] != '\0') 
					followfirst(production[i][j + 1], i,(j + 2));

				if (production[i][j + 1] == '\0' && c != production[i][0]) 
					follow(production[i][0]);
			
			}
		}
	}
}

//q1-this is the index of the production rule being analyzed. It refers to which production of a non-terminal is currently being processed.
//q2-This is the index within the current production (production[q1]) that refers to the symbol being analyzed.navigate right hand side

void findfirst(char c, int q1, int q2) {
	int j;
	if (!(isupper(c))) 
		first[n++] = c;	// if c is not a non terminal add c to the first set 
	for (j = 0; j < count; j++) {// iterate through production rules
		if(production[j][0] == production[j][2])// skip if it is of left recursion form 
			continue;	
		
		if (production[j][0] == c) {// if the current  production starts with c
			if (production[j][2] == '#') // check if it has a epsilon production
			{
				if (production[q1][q2] == '\0')//production[q1][q2] == '\0' checks whether the current character in the production string is the null terminator ('\0'), which marks the end of the string.
				  first[n++] = '#';// add epsilon to first set 
				else if (production[q1][q2] != '\0' && (q1 != 0 || q2 != 0))
					findfirst(production[q1][q2], q1,(q2 + 1));//Recursively find the FIRST set of the next symbol.
				else
					first[n++] = '#';//If no further symbols, add epsilon.
			} 
			else if (!isupper(production[j][2])) 
				first[n++] = production[j][2];// if it is a terminal symbol directly add the terminal 
			else 
				findfirst(production[j][2], j, 3);// if non terminal again find its first 
		}
	}
}
void followfirst(char c, int c1, int c2) {
	int k;
	if (!(isupper(c)))
	f[m++] = c;
	else{
		int i = 0, j = 1;
		for (i = 0; i < count; i++){
			if (firstmat[i][0] == c)
			break;
		}
		while (firstmat[i][j] != '!'){
			if (firstmat[i][j] != '#') 
			f[m++] = firstmat[i][j];
			else {
				if (production[c1][c2] == '\0') 
				  follow(production[c1][0]);
				else 
					followfirst(production[c1][c2], c1, c2 + 1);
			}
			j++;
		}
	}
}
