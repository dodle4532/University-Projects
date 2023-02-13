#include <stdio.h>
#include <string.h>

int getPower(int res, int k){	
	if (k == 0){
		return 1;
	}
        while (k != 1){
                res *= 2;
                k -=1;
        }
        return res;

}


int getTen(char *s){
	int k = strlen(s) - 2;
	int q = getPower(2,k);
	int res = 0;
	for (int i = 0; s[i] != '\0'; ++i){
		if (s[i] == '1'){
			res += q;
		}
		if (i == k ){
			break;
		}
		q /=2;
	}
	return res;
}


int getFirstNumber(char *s){
	int k = 0;
	for (int i = 0; i < strlen(s); ++i){
		k +=1;
		if (s[i] == ' '){
			break;
		}
	}
	char str[k];
	for (int i = 0; i < k; ++i){
		str[i] = s[i];
		if (i == k-1){
			str[i] == '\0';
			break;
		}
	}
	return getTen(str);
}		


char getChar(char *s){
	for (int i = 0; i < strlen(s); ++i){
		if (s[i] == ' '){
			return s[i+1];
		}
	}
}


int getSecondNumber(char *s){
	int k = 0;
	char str[50];
	int j = 0;
	for (int i = 0; i < strlen(s); ++i){
		if (k == 2){
			str[j] = s[i];
			j +=1;
			if (s[i] == '\0'){
				str[j] = '\0';
				break;
			}			
		}
		if (s[i] == ' '){
                        k +=1;
		}
	}
	for (int i = 0;i < strlen(str); ++i){
	}
	return getTen(str);
}


int getLen(int a){
	int b = 1;
	int len = 0;
	while (b <= a){
		b *=2;
		len +=1;
	}
	return len;
}


char *getBin(int a, int len){
	int l = getLen(a);
	static char s[256];
        s[l] = '\0';
        int b = a;
        int c = l - 1;
        while (b != 0){
                if (b % 2 == 1){
                        s[c] = '1';
                }
                else {
                        s[c] = '0';
                }
                b /=2;
                c -=1;
        }
	while (len - l != 0){
		printf("0");
		l +=1;
	}	
	return s;	
}

void inv (char *s) {
    printf(" ");
    for (int i = 0; i < strlen(s); ++i) {
        if (s[i] == '0') {
            printf("1");
        }
        else {
            printf("0");
        }
    }
    printf("\n");
}
