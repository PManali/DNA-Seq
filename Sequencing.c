#include<stdio.h>
#include<fcntl.h>
#include<ctype.h>
#include<error.h>
#include<stdlib.h>
#include<string.h>
#include "mstring.h"
typedef struct format{
	char *pattern;
	int weight;
	char ddntp;
}format;
char complement_base(char ch){
	if(ch == 'A')
		return 'T';
	else if(ch == 'T')
		return 'A';
	else if(ch == 'G')
		return 'C';
	else
		return 'G';
}
void print(format *form){
	char arr[11], *ptr;
	printf("\n\t----------------------------------");
	int j;
	ptr = (char *)malloc(sizeof(char));
	printf("\n\n\tddAtp\tddGtp\tddCtp\tTTp\n");
	for(j=0; j < 11;j++)
		arr[j] = '\0';
	for(j = 0;j < 11;j++){
		arr[form[j].weight - 1] = form[j].ddntp;
	}
	for(j = 0; j < 11; j++){
		ptr = &(arr[0]);
		ptr[11] = '\0';;
		ptr = mstrrev(ptr);
		if(ptr[j] == 'T')
			printf("\t     \t     \t     \t _\tT\n");
		else if(ptr[j] == 'A')
			printf("\t  _  \t     \t     \t    \tA\n");
		else if(ptr[j] == 'G')
			printf("\t     \t  _  \t     \t    \tG\n");
		else
			printf("\t     \t     \t  _  \t    \tC\n");
	}
	printf("\n\t----------------------------------\n");
}
void process(char ch, int SKIP, format *form, char ddntp){
	FILE *fp;
	char line[50];
	char *token, *ptr;
	char arr[50];
	static int pos = 0;
	int k = 0, len = 0, dummyw;
	for(int i = 0;i<50;i++)
		arr[i] = ' ';
	token = (char *)malloc(sizeof(char));
	fp = fopen("DNA mol.txt", "r");
	if(fp == NULL){
		perror("NO such file");
	}
	else{
		if(fgets(line, 50, fp) != NULL){
			token = strtok(line, " ");
		}
	}
	token = mstrrev(token);
	while(token[k] != '\0'){
		arr[k] = complement_base(token[k]);
		if(token[k] == ch){
			if(SKIP == 0){
				k++;
				arr[k] = '\0';
				ptr = &(arr[0]);
				len = mstrlen(ptr);
				dummyw = len-3;
				if(dummyw > 0){
				form[pos].pattern = mstrrev(ptr);
				form[pos].weight = len-3;
				form[pos].ddntp = ddntp;
				//printf("\nform[%d] %s %d %c\n", pos, form[pos].pattern, form[pos].weight, form[pos].ddntp);
				printf("\t\t%s\n",form[pos].pattern);
				pos++;
				}
				break;
			}
			else{
				SKIP--;
			}
		}
		k++;
	}
}
int findcount(char ch, char *str){
	int i =0,cnt = 0;
	while(str[i] != '\0'){
		if(str[i] == ch){
			cnt++;
		}  
		i++;
	}
	return cnt;
}
int main(){
	FILE *fp;
	char line[50];
	int upper_len = 0, i = 0, count = 1, countchr, SKIP = 0;
	char ddntp;
	char *upper, *lower, *token, *initial_DNA_primer, *DNA_primer, *upp, *primer, *format1;
	format form[10];
	format *f;
	f = &(form[0]);
	for(i = 0; i<10;i++){
		form[i].pattern = (char *)malloc(sizeof(char));
		form[i].pattern = NULL;
		form[i].weight = 0;
		form[i].ddntp = '\0';
	}
	i = 0;
	token = (char *)malloc(sizeof(char));
	initial_DNA_primer = (char *)malloc(sizeof(char));
	DNA_primer = (char *)malloc(sizeof(char));
	fp = fopen("DNA mol.txt", "r");
	if(fp == NULL){
		perror("NO such file");
	}
	else{
		while(fgets(line, 50, fp) != NULL){
			token = strtok(line, " ");
			upper = token;
			token = strtok(NULL," ");
			lower = token;
		}
		printf("DNA double stranded molecule to be sequenced - \n");
		printf("\t--------------\n\t%s\n\t%s\t--------------\n",upper, lower);
		printf("Denatured and separated - \n");
		printf("\t--------------\n\t%s\n\n\n\t%s\t--------------\n",upper, lower);
		upper_len = strlen(upper);
		upper_len -= 3;
		initial_DNA_primer = &(upper[upper_len]);
		while(i < 3){
			switch(initial_DNA_primer[i]){
				case 'A':
					DNA_primer[i] = 'T';
					break;
				case 'C':
					DNA_primer[i] = 'G';
					break;
				case 'T':
					DNA_primer[i] = 'A';
					break;
				case 'G':
					DNA_primer[i] = 'C';
					break;
			}
			i++;
		}
		DNA_primer[i] = '\0';
		printf("\n\tDNA primer %s\n\n", DNA_primer);
	}
	upp = mstrrev(upper);
	primer = mstrrev(DNA_primer);
	while(count <= 4){
		switch(count){
		case 1:
			countchr = findcount('T', upp);
			SKIP = count;
			ddntp = 'A';
			printf("\t ddNtp : %c\n", ddntp);
			for(int k = 1; k <= countchr; k++){
				process('T', count - SKIP, f, ddntp);
				SKIP--;
			}
			break;
		case 2:
			countchr = findcount('C', upp);
			SKIP = count;
			ddntp = 'G';
			printf("\t ddNtp : %c\n", ddntp);
			for(int k = 1; k <= countchr; k++){
				process('C', count - SKIP, f, ddntp);
				SKIP--;
			}
			break;	
		case 3:
			countchr = findcount('G', upp);
			SKIP = count;
			ddntp = 'C';
			printf("\t ddNtp : %c\n", ddntp);
			for(int k = 1; k <= countchr; k++){
				process('G', count - SKIP, f, ddntp);
				SKIP--;
			}
			break;
		case 4:
			countchr = findcount('A', upp);
			SKIP = count;
			ddntp = 'T';
			printf("\t ddNtp : %c\n", ddntp);
			for(int k = 1; k <= countchr; k++){
				process('A', count - SKIP, f, ddntp);
				SKIP--;
			}
			break;
		}
		count++;
	}
	print(f);
	fclose(fp);
	return 0;
}
