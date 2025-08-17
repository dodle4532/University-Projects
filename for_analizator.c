#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {false, true} bool;
typedef enum {LESS_I, MORE_I, LESS_P, MORE_P} ro;

#define Num 256
#define L 257
#define DoublePlus 258
#define DoubleMinus 259
#define Lbrace 260
#define Rbrace 261
#define Semicolon 262
#define Equal 263
#define For 264
#define Print 265
#define Less 266
#define More 267
#define END 268

struct cycle* F();
struct cycle* S();
struct cycle* Init();
struct cycle* Cond();
ro RO();
struct cycle* Incr();
struct print* P();

int symbol;

char* lastStr = NULL;
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
        char* str = (char*)
        calloc(64, sizeof(char));
        int i = 0;
        if (t == '+') {
            t = getchar();
            if (t == '+') {
                t = -1;
                return DoublePlus;
            }
            else {
                error("Unknown symbol");
            }
        }
        if (t == '-') {
            t = getchar();
            if (t == '-') {
                t = -1;
                return DoubleMinus;
            }
            else {
                error("Unknown symbol");
            }
        }
        if ((t >= 'A' && t <= 'Z') || (t >= 'a' && t <= 'z')) {
            str[i] = t;
            i++;
            t = getchar();
            str[i] = t;
            i++;
            while ((t >= 'A' && t <= 'Z') || (t >= 'a' && t <= 'z') || (t >= '0' && t <= '9'))
            {
                t = getchar();
                str[i] = t;
                i++;
            }
            str[i-1] = '\0';
            if (lastStr != NULL) free(lastStr);
            lastStr = strdup(str);
            if (!strcmp(str, "for")) {
                free(str);
                return For;
            }
            if (!strcmp(str, "print")) {
                free(str);
                return Print;
            }
            free(str);
            return L;
        }
        free(str);
        switch (t)
        {
            case '(' :
            {
                t = -1;
                return Lbrace;
            }
            case ')' : 
            {
                t = -1;
                return Rbrace;
            }
            case ';' :
            {
                t = -1;
                return Semicolon;
            }
            case '<' :
            {
                t = -1;
                return Less;
            }
            case '>' :
            {
                t = -1;
                return More;
            }
            case '=' :
            {
                t = -1;
                return Equal;
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

struct value {
    char* name;
    int num;
};

struct value* values[32];
int valCount = 0;

struct print {
    ro Ro;
    struct value* val;
};

struct cycle {
    struct value* val;
    struct cycle* internalCycle;
    struct value* startVal;
    struct value* endVal;
    ro Ro;
    struct print* printAction;
    bool isLess;
};

struct cycle* createCycle() {
    struct cycle* res = calloc(1, sizeof(struct cycle));
    res->val = calloc(1, sizeof(struct value));
    res->startVal = calloc(1, sizeof(struct value));
    res->endVal = calloc(1, sizeof(struct value));
}

int findValueIndex(char* str) {
    for (int i = 0; i < valCount; ++i) {
        if (!strcmp(str, values[i]->name)) {
            return i;
        }
    }
}

void printFor(struct cycle* cycle) {
    int index = findValueIndex(cycle->val->name);
    if (cycle->endVal->name) {
        cycle->endVal->num = values[findValueIndex(cycle->endVal->name)]->num;
    }
    switch (cycle->Ro)
    {
    case LESS_I:
    case LESS_P:
        for (values[index]->num = cycle->startVal->num; values[index]->num > cycle->endVal->num; --values[index]->num) {
            if (cycle->printAction) {
                switch (cycle->printAction->Ro)
                {
                case LESS_I:
                    printf("%d\n", --values[findValueIndex(cycle->printAction->val->name)]->num);
                    break;
                case LESS_P:
                    printf("%d\n", values[findValueIndex(cycle->printAction->val->name)]->num--);
                    break;
                case MORE_I:
                    printf("%d\n", ++values[findValueIndex(cycle->printAction->val->name)]->num);
                    break;
                case MORE_P:
                    printf("%d\n", values[findValueIndex(cycle->printAction->val->name)]->num++);
                    break;
                
                default:
                    break;
                }
            }
            else if (cycle->internalCycle) {
                printFor(cycle->internalCycle);
            }
        }
        break;
    
    case MORE_I:
    case MORE_P:
        for (values[index]->num = cycle->startVal->num; values[index]->num < cycle->endVal->num; ++values[index]->num) {
            if (cycle->printAction) {
                switch (cycle->printAction->Ro)
                {
                case LESS_I:
                    printf("%d\n", --values[findValueIndex(cycle->printAction->val->name)]->num);
                    break;
                case LESS_P:
                    printf("%d\n", values[findValueIndex(cycle->printAction->val->name)]->num--);
                    break;
                case MORE_I:
                    printf("%d\n", ++values[findValueIndex(cycle->printAction->val->name)]->num);
                    break;
                case MORE_P:
                    printf("%d\n", values[findValueIndex(cycle->printAction->val->name)]->num++);
                    break;
                
                default:
                    break;
                }
            }
            else if (cycle->internalCycle) {
                printFor(cycle->internalCycle);
            }
        }
        break;
    default:
        break;
    }
}

void error(char* er)
{
    printf("%s\n", er);
    exit(1);
}

void freeCycle(struct cycle* cycle) {
    free(cycle->val->name);
    free(cycle->val);
    if (cycle->endVal->name) {
        free(cycle->endVal);
    }
    free(cycle->startVal);
    if (cycle->printAction) {
        free(cycle->printAction->val->name);
        free(cycle->printAction);
    }
    if (cycle->internalCycle) {
        freeCycle(cycle->internalCycle);
    }
    free(cycle);
}

int main()
{
    symbol = scan();
    struct cycle* res = F();
    if (symbol != END) {
        error("still some input");
    }
    printFor(res);
    freeCycle(res);
    return 0;
}

struct cycle* F() {
    if (symbol != For) {
        error("Incorrect sentence");
    }
    symbol = scan();
    if (symbol != Lbrace) {
        error("Incorrect sentence");
    }
    symbol = scan();
    struct cycle* res = createCycle();
    struct cycle* init = Init();
    res->val->num = init->val->num;
    res->val->name = strdup(init->val->name);
    res->startVal = init->startVal;
    res->val->num = res->startVal->num; // поменять на просто инт
    free(init->val->name);
    free(init->val);
    free(init);
    values[valCount++] = res->val;
    if (symbol != Semicolon) {
        error("Incorrect sentence");
    }
    symbol = scan();
    struct cycle* cond = Cond();
    res->isLess = cond->isLess;
    res->endVal = cond->endVal;
    if (strcmp(cond->val->name, res->val->name)) {
        free(cond->val->name); // выкинуть за цикл
        free(cond->val);
        free(cond);
        error("Incorrect parametr");
    }
    free(cond->val->name);
    free(cond->val);
    free(cond);
    if (symbol != Semicolon) {
        error("Incorrect sentence");
    }
    symbol = scan();
    struct cycle* incr = Incr();
    if (strcmp(incr->val->name, res->val->name)) {
        free(incr->val->name);
        free(incr->val);
        free(incr);
        error("Incorrect parametr");
    }
    res->Ro = incr->Ro;
    free(incr->val->name);
    free(incr->val);
    free(incr);
    if (symbol != Rbrace) {
        error("Incorrect sentence");
    }
    symbol = scan();
    struct cycle* s = S();
    if (!s->val->name) {
        res->printAction = s->printAction;
    }
    else {
        res->internalCycle = s;
    }
    return res;
}

struct cycle* S() {
    if (symbol == Print) {
        struct cycle* res = createCycle();
        res->printAction = P();
        return res;
    }
    else if (symbol == For) {
        return F();
    }
    else {
        error("Incorrect sentence");
    }
}

struct cycle* Init() {
    struct cycle* res = createCycle();
    if (symbol != L) {
        error("Incorrect sentence");
    }
    res->val->name = strdup(lastStr);
    symbol = scan();
    if (symbol != Equal) {
        error("Incorrect sentence");
    }
    symbol = scan();
    if (symbol != Num) {
        error("Incorrect sentence");
    }
    res->startVal->num = lastInt;
    symbol = scan();
    return res;
}

struct cycle* Cond() {
    struct cycle* res = createCycle();
    if (symbol != L) {
        error("Incorrect sentence");
    }
    res->val->name = strdup(lastStr);
    symbol = scan();
    ro curRo = RO();
    if (curRo == LESS_I || curRo == LESS_P) {
        res->isLess = true;
    }
    else {
        res->isLess = false;
    }
    if (symbol == L) {
        res->endVal->name = strdup(lastStr);
    }
    else if (symbol == Num) {
        res->endVal->num = lastInt;
    }
    else {
        error("Incorrect sentence");
    }
    symbol = scan();
    return res;
}

ro RO() {
    ro res;
    if (symbol == Less) {
        res = LESS_I;
    }
    else if (symbol == More) {
        res = MORE_I;
    }
    else {
        error("Incorrect sentence");
    }
    symbol = scan();
    return res;
}

struct cycle* Incr() {
    struct cycle* res = createCycle();
    if (symbol == L) {
        res->val->name = strdup(lastStr);
        symbol = scan();
        if (symbol == DoublePlus) {
            res->Ro = MORE_P;
        }
        else if (symbol == DoubleMinus) {
            res->Ro = LESS_P;
        }
        else {
            error("Incorrect sentence");
        }
    }
    else if (symbol == DoubleMinus) {
        res->Ro = LESS_I;
        symbol = scan();
        if (symbol != L) {
            error("Incorrect sentence");
        }
        res->val->name = strdup(lastStr);

    }
    else if (symbol == DoublePlus) {
        res->Ro = MORE_I;
        symbol = scan();
        if (symbol != L) {
            error("Incorrect sentence");
        }
        res->val->name = strdup(lastStr);

    }
    else {
        error("Incorrect sentence");
    }
    symbol = scan();
    return res;
}

struct print* P() {
    if (symbol != Print) {
        error("Incorrect sentence");
    }
    symbol = scan();
    if (symbol != Lbrace) {
        error("Incorrect sentence");
    }
    symbol = scan();
    struct cycle* incr = Incr();
    struct print* printAction = calloc(1, sizeof(struct print));
    printAction = calloc(1, sizeof(struct print));
    printAction->Ro = incr->Ro;
    printAction->val = calloc(1, sizeof(struct value));
    printAction->val->name = strdup(incr->val->name);
    free(incr->val->name);
    free(incr->val);
    free(incr);
    if (symbol != Rbrace) {
        error("Incorrect sentence");
    }
    symbol = scan();
    return printAction;
}