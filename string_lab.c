#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string_lab.h"
#include <assert.h>


char *_strremove(char *str, const char ch) {
	if (str == NULL || ch == 0) { 
                return NULL;
        }
	for (int i = 0; i < strlen(str); ++i) {
		if (str[i] == ch) {
			memmove(str + i, str + i + 1, strlen(str));
			i -=1;
		}
	}
	return str;
}


int _strcountchar(const char *str, const char ch) {
	if (str == NULL || ch == 0) {
		return -1;
	}
	int k = 0;
	char *p = NULL;
	p = strchr(str, ch);
        if (p == NULL) {
                return -1;
        }
        else {
                while (*p != '\0') {
                        p = strchr(p, ch);
                        if (p == NULL) {
                                break;
                        }
                        ++p;
                        k +=1;
                }

        }
	return k;
}


char *_strdelspaces(char *str) {
	if (str == NULL) {
                return NULL;
        }
	for (int i = 0; i < strlen(str) - 1; ++i) {
		if (str[i] == ' ' && str[i+1] == ' ' && str[i+1] != '\0') {
			memmove(str + i, str + i + 1, strlen(str) - i);
			i -=1;
		}
	}
	return str;
}

char *_strtolower(char *str) {
	if (str == NULL) {
                return NULL;
        }
	for (int i = 0; i < strlen(str); ++i) {
		if (str[i] > 64 && str[i] < 91) {
			str[i] +=32;
		}
	}
	return str;
}

char *_strtoupper(char *str) {
	if (str == NULL) {
                return NULL;
        }
	for (int i = 0; i < strlen(str); ++i) {
                if (str[i] > 96 && str[i] < 123) {
                        str[i] -=32;
                }
        }
        return str;

}

int _strcmp(const char *str1, const char *str2) {
	int k = 0;
	int max = 0;
	if (strlen(str1) > strlen(str2)) {
		max = strlen(str1);
	}
	else {
		max = strlen(str2);
	}
	for (int i = 0; i < max; ++i) {
		if (str1[i] != str2[i]) {
                        return str1[i] - str2[i];
                }
	}
	return 0;
}
char *_strreverse(const char *str1) {
	if (str1 == NULL) {
                return NULL;
        }
	char *str = NULL;
	str = calloc(strlen(str1) + 1, sizeof(char));
	strcpy(str,str1);
	for (int i = 0; i < strlen(str) - 1; ++i) {
		int t = str[strlen(str) - 1];
		memmove(str + strlen(str) - 1, str + strlen(str), 2);
		memmove(str + i, str - 1 + i, strlen(str) - i + 1);
		str[i] = t;
	}
	return str;
}

int _atoi(const char *str) {
	int a = 0;
	sscanf(str, "%d", &a);
	return a;
}

char *_strchr(char *str, int ch) {
	if (str == NULL || ch == 0) {
                return NULL;
        }
	for (int i = 0; i < strlen(str); ++i) {
		if (str[i] == ch) {
			return str + i;
		}
	}
	return NULL;
}

char *_strstr(const char *str, const char *substr) {
	if (str == NULL || substr == NULL) {
                return NULL;
        }
	char *p = NULL;
	int l = strlen(substr);
	int fl = 0;
	int k = 0;
	for (int i = 0; i < strlen(str) - l + 1; ++i) {
		fl = 0;
		k = 1;
		if (str[i] != substr[0]) {
			continue;
		}
		else {
			for (int j = i + 1; j < i + l - 1; ++j) {
				if (str[j] != substr[k]) {
					fl = 1;
					break;
				}		
				++k;
			}
		}
		if (fl == 0) {
			p = (char *)str + i;
			return p;
		}
	}
	return NULL;
}
