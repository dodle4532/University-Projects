#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {false, true} bool;

#define Num 256
#define LESS 257
#define MORE 258
#define EQ_LESS 259
#define EQ_MORE 260
#define EQUAL 261
#define N_EQUAL 262
#define PLUS 263
#define MINUS 264
#define LBRACE 265
#define RBRACE 266
#define END 267

struct Cmp* cmp();
char* cmp_val();
int _exp();
bool op();

int symbol;

int lastInt = 0;

int t = -1;
void error(char* er);

int scan()
{
    while (1)
    {
        if (t == -1)
            t = getchar();

        if (t == ' ' || t == '\t') {
            t = -1;
            continue;
        }
        if (t >= '0' && t <= '9')
        {
            char val[16];
            int index = 1;
            val[0] = t;
            t = getchar();
            while (t >= '0' && t <= '9')
            {
                val[index] = t;
                index++;
                t = getchar();
            }
            lastInt = atoi(val);
            return Num;
        }
        switch (t)
        {
            case '(' :
            {
                t = -1;
                return LBRACE;
            }
            case ')' : 
            {
                t = -1;
                return RBRACE;
            }
            case '<' :
            {
                t = getchar();
                if (t == '=') {
                    t = -1;
                    return EQ_LESS;
                }
                return LESS;
            }
            case '>' :
            {
                t = getchar();
                if (t == '=') {
                    t = -1;
                    return EQ_MORE;
                }
                return MORE;
            }
            case '=' :
            {
                t = getchar();
                if (t != '=') {
                    error("Incorrect sentence");
                }
                t = -1;
                return EQUAL;
            }
            case '!':
            {
                t = getchar();
                if (t != '=') {
                    error("Incorrect sentence");
                }
                t = -1;
                return N_EQUAL;
            }
            case '+':
            {
                t = -1;
                return PLUS;
            }
            case '-':
            {
                t = -1;
                return MINUS;
            }
            case '\n':
            {
                t = -1;
                return END;
            }
            default:
                error("Incorrect sentence");
        }
    }
}


void error(char* er)
{
    printf("%s\n", er);
    exit(1);
}

struct Cmp {
    char* cmp;
    int left;
    int right;
};

int main()
{
    symbol = scan();
    bool cmpRes = false;
    struct Cmp* res = cmp();
    if (symbol != END) {
        error("still some input");
    }
    printf("-----------------\n%d ", res->left);
    if (strlen(res->cmp) == 1) {
        if (res->cmp[0] == '<') {
            printf("< ");
            if (res->left < res->right) {
                cmpRes = true;
            }
        }
        if (res->cmp[0] == '>') {
            printf("> ");
            if (res->left > res->right) {
                cmpRes = true;
            }
        }
    }
    else {
        if (res->cmp[0] == '<') {
            printf("<= ");
            if (res->left <= res->right) {
                cmpRes = true;
            }
        }
        if (res->cmp[0] == '>') {
            printf(">= ");
            if (res->left >= res->right) {
                cmpRes = true;
            }
        }
        if (res->cmp[0] == '=') {
            printf("== ");
            if (res->left == res->right) {
                cmpRes = true;
            }
        }
        if (res->cmp[0] == '!') {
            printf("!= ");
            if (res->left != res->right) {
                cmpRes = true;
            }
        }
    }
    printf("%d\n", res->right);
    if (cmpRes) {
        printf("True");
    }
    else {
        printf("false");
    }
    free(res->cmp);
    free(res);
    return 0;
}

struct Cmp* cmp() {
    struct Cmp* res = calloc(1, sizeof(struct Cmp));
    res->left = _exp();
    res->cmp = cmp_val();
    res->right = _exp();
    return res;
}

char* cmp_val() {
    char* res = calloc(3, sizeof(char));
    if (symbol == LESS) {
        res[0] = '<';
        res[1] = '\0';
    }
    if (symbol == MORE) {
        res[0] = '>';
        res[1] = '\0';
    }
    if (symbol == EQ_LESS) {
        res[0] = '<';
        res[1] = '=';
        res[2] = '\0';
    }
    if (symbol == EQ_MORE) {
        res[0] = '>';
        res[1] = '=';
        res[2] = '\0';
    }
    if (symbol == EQUAL) {
        res[0] = '=';
        res[1] = '=';
        res[2] = '\0';
    }
    if (symbol == N_EQUAL) {
        res[0] = '!';
        res[1] = '=';
        res[2] = '\0';
    }
    if (res[0] != 0) {
        symbol = scan();
        return res;
    }
    error("Incorrect sentence");
    return res;
}

int _exp() {
    int res = 0;
    if (symbol == LBRACE) {
        symbol = scan();
        if (symbol != Num) {
            error("Incorrect sentence");
        }
        res += lastInt;
        symbol = scan();
        bool operation = op();
        int right = _exp();
        if (operation) {
            res += right;
        }
        else {
            res -= right;
        }
        if (symbol != RBRACE) {
            error("Incorrect sentence");
        }
        symbol = scan();
        return res;
    }
    if (symbol == Num) {
        res += lastInt;
        symbol = scan();
        if (symbol == PLUS || symbol == MINUS) {
            bool operation = op();
            int right = _exp();
            if (operation) {
                res += right;
            }
            else {
                res -= right;
            }
            return res;
        }
        else {
            return res;
        }
    }
    error("Incorrect sentence");
    return -1;
}

bool op() {
    if (symbol == PLUS) {
        symbol = scan();
        return true;
    }
    if (symbol == MINUS) {
        symbol = scan();
        return false;
    }
    error("Incorrect sentence");
    return false;
}

