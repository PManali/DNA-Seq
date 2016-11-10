#include<stdlib.h>
#include "mstring.h"
int mstrlen(char *str){
	char *dummy;
	int len=0;
	dummy = str;
	while(*dummy != '\0'){
		len++;
		++dummy;
	}
	return len;
}
char *mstrrev(char *str){
	int len, i, j;
	char *dummy = (char *)malloc(sizeof(char));
	len = mstrlen(str);
	for(i = (len-1), j = 0; i >= 0; i--, j++){
		dummy[j] = str[i];
	}
	dummy[j] = '\0';
	return dummy;
}
