#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "hFile.h"
#include <string.h>


int main(){
	int p = 0;
	int t = 0;
	char str[50];
	for (int i = 0; i < 50; ++i){
		str[i] = 'q';
	}
	char *s = NULL;
	int ch,first,second = 0;
	int countOfSpace = 0;
	int count;
	int res;
	while (p != 2){
		printf("Введите сначала число в двоичной форме записи\n");
		printf("Затем через пробел операцию ");
		printf("затем снова число через пробел\n");
		printf("Если хотите сделать отрицание,\n");
		printf("введите ~ и сразу(без Пробела!)число\n");
		s = NULL;
		size_t n = 0;
		int a = getline(&s,&n,stdin);
		int countOfSpace = 0;
		for (int i = 0; i < strlen(s);++i){
			if (s[i] == ' '){
				countOfSpace +=1;
				count = countOfSpace;
			}
			count = countOfSpace;
		}
		if (countOfSpace > 2 || countOfSpace == 1){
			printf("Неверный ввод\n");
			continue;
		}
		p = 2;
	}
	if (count == 2){
		first = getFirstNumber(s);
		second = getSecondNumber(s);
		ch = getChar(s);
		switch (ch){
                	case '|':
                	        res = first | second;
                	        break;
                	case '&':
                	        res = first & second;
                	        break;
                	case '^':
                	        res = first ^ second;
                	        break;

		}
	}
	if (count == 0){
		if (s[0] != '~'){
			return 1;
		}
		for (int i = 0; i < strlen(s) - 1; ++i){
			if (s[i + 2] == '\0'){
				str[i] = '\0';
				break;
			}
			str[i] = s[i+1];
			if (s[i+2] == '\0'){
				str[i] = '\0';
				break;
			}

		}
		t = getPower(2,strlen(str) - 1);
		for (int i = 0; str[i] != '\0'; ++i){
			if (str[i] == '1'){
				res +=t;
			}
			t = t/2;
		}
		res = (getPower(2,strlen(str)) - res - 1);
        inv(str);
		//printf("q%s\n",getBin(res,strlen(str)));
		return 0;
	}
	int max = (first >= second)?getLen(first):getLen(second);
	printf("%s\n",getBin(res,max));
	free(s);
	return 0;
}
