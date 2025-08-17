// Кочнов КМБО-02-22

// <Z>::=<T> <Z>|<T>
// <T>::= <func>|<call>
// <func>::=<type> name(<par>) {<funcImpl>}
// <par>::=int name|λ
// <call> ::=name(<value>);
// <value>::=<notNullValue>|λ
// <notNullValue>::=i|name
// <type>::=void|int
// <funcImpl>::=<funcImpl><printCall>|<printCall>
// <printCall>::=print(<value>);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {false, true} bool;

#define I 256
#define NAME 257
#define LFBRACE 258
#define RFBRACE 259
#define LBRACE 260
#define RBRACE 261
#define POINT 262
#define END 263
#define INT 264
#define VOID 265

void z();
void T();
void func();
bool par();
struct func_call* call();
struct func_call* printCall();
char* value();
void type();
struct func_impl* funcImpl();
bool isImpl = false;

int symbol;

int t = -1;
void error(char* er);

struct func_call {
    char* value;
    char* name;
};

struct func_impl {
    struct func_call* calls[16];
    int num;
};

struct function {
    char* name;
    struct func_impl* impl;
    bool isType;
};

struct function* createFunction(char* name, struct func_impl* impl, bool isType) {
    struct function* res = (struct function*)calloc(1, sizeof(struct function));
    res->name = name;
    res->impl = impl;
    res->isType = isType;
    return res;
}

struct func_impl* createImpl() {
    struct func_impl* res = (struct func_impl*)calloc(1, sizeof(struct func_impl));
    res->num = 0;
    return res;
}

struct func_call* createfuncCall(char* value, char* name) {
    struct func_call* res = (struct func_call*)calloc(1, sizeof(struct func_call));
    res->value = value;
    res->name = name;
    return res;
}

struct function* functions[16];
int funcCount = 0;
struct func_call* funcCalls[16];
int callCount = 0;
char* lastStr = NULL;
int lastInt = -1;

void freeResources() {
    for (int i = 0; i < callCount; ++i) {
        if (funcCalls[i]->value != NULL) {
            free(funcCalls[i]->value);
        } 
        free(funcCalls[i]->name);
        free(funcCalls[i]);
    }
    for (int i = 0; i < funcCount; ++i) {
        for (int j = 0; j < functions[i]->impl->num; ++j) {
            if (functions[i]->impl->calls[j]->value != NULL) {
                free(functions[i]->impl->calls[j]->value);
            } 
            free(functions[i]->impl->calls[j]->name);
            free(functions[i]->impl->calls[j]);
        }
        free(functions[i]->impl);
        free(functions[i]->name);
    }
    return;
}

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
            return I;
        }
        char* str = (char*)
        calloc(64, sizeof(char));
        int i = 0;
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
            if (!strcmp(str, "void")) {
                free(str);
                return VOID;
            }
            if (!strcmp(str, "int")) {
                free(str);
                return INT;
            }
            free(str);
            return NAME;
        }
        free(str);
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
            case '{' :
            {
                t = -1;
                return LFBRACE;
            }
            case '}' : 
            {
                t = -1;
                return RFBRACE;
            }
            case ';' :
            {
                t = -1;
                return POINT;
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
    freeResources();
    exit(1);
}

void foundErrorCall(struct func_call* call) {
    struct function* func;
    if (!strcmp(call->name, "print")) {
        return;
    }
    bool isFound = false;
    for (int i = 0; i < funcCount; ++i) {
        if (!strcmp(call->name, functions[i]->name)) {
            isFound = true;
            func = functions[i];
            break;
        }
    }
    if (!isFound) {
        error(strcat(strcat(strdup("Implementation of function "), call->name), strdup(" was not found"))); 
    }
    if (func->isType == true) {
        if (call->value == NULL) {
            error(strcat(strdup("Expected parametr in function call "), call->name)); 
        }
    }
    else {
        if (call->value != NULL) {
            error(strcat(strdup("No parametr should be in function call "), call->name));
        }
        for (int i = 0; i < func->impl->num; ++i) {
            if (func->impl->calls[i]->value == NULL) {
                error(strcat(strdup("No parametr should be in function call print in implementation of "), call->name));
            }
        }
    }
    return;
}

int main()
{
    symbol = scan();
    z();
    if (symbol != END)
        error("still some input");
    for (int i = 0; i < callCount; ++i) {
        foundErrorCall(funcCalls[i]);
    }
    printf("Output of functions:\n");
    for (int i = 0; i < callCount; ++i) {
        bool isFound = false;
        if (!strcmp(funcCalls[i]->name, "print")) {
            printf("%s", funcCalls[i]->value);
        }
        else {
            for (int j = 0; j < funcCount; ++j) {
                if (!strcmp(funcCalls[i]->name, functions[j]->name)) {
                    isFound = true;
                    for (int k = 0; k < functions[j]->impl->num; ++k) {
                        char* par = functions[j]->impl->calls[k]->value;
                        if (par == NULL) {
                            printf("%s", funcCalls[i]->value);
                        }
                        else {
                            printf("%s", par);
                        }
                    }
                }
            }
            if (!isFound) {
                error("function undefined\n");
            }
        }
        char* val = funcCalls[i]->value;
    }
    freeResources(); 
    return 0;
}

void z()
{
    T();
    if (symbol != END) {
        z();
    }
    return;
}

void T()
{
    if (symbol == NAME) {
        call();
    }
    else if (symbol == VOID || symbol == INT) {
        func();
    }
    
    return;
}

struct func_call* call()
{
    struct func_call* res;
    if (symbol == NAME)
    {
        char* name = strdup(lastStr);
        symbol = scan();
        if (symbol != LBRACE) {
            error("Error");
        }
        symbol = scan();
        if (!strcmp(name, "print")) {
            if (symbol != I) {
                error("Calling print outside of function implementation can be done only with int as a parametr");
            }
        }
        char* val = value();
        if (symbol != RBRACE) {
            error("Brackets disbalance");
        }
        symbol = scan();
        if (symbol != POINT) {
            error("Error");
        }
        res = createfuncCall(val, name);
        if (isImpl) {
            symbol = scan();
            return res;
        }
        funcCalls[callCount] = res;
        callCount++;
    }
    else {
        error("Incorrect sentence");
    }
    symbol = scan();
    return res;
}

char* value()
{
    char* res = (char*)calloc(8, sizeof(char));
    if (symbol == RBRACE) {
        free(res);
        return NULL;
    }
    if ((symbol != I) && (symbol != NAME)){
        error("Incorrect sentence");
    }
    if (symbol == I) {
        sprintf(res, "%d", lastInt);
        symbol = scan();
        return res;
    }
    symbol = scan();
    free(res);
    return NULL;
}

void func() {
    type();
    if (symbol != NAME) {
        error("Incorrect sentence");
    }
    char* name = strdup(lastStr);
    symbol = scan();
    if (symbol != LBRACE) {
        error("Incorrect sentence");
    }
    symbol = scan();
    bool isType = par();
    if (symbol != RBRACE) {
        error("Incorrect sentence");
    }
    symbol = scan();
    if (symbol != LFBRACE) {
        error("Incorrect sentence");
    }
    symbol = scan();
    struct func_impl* impl = funcImpl();
    if (symbol != RFBRACE) {
        error("Incorrect sentence");
    }
    symbol = scan();
    functions[funcCount] = createFunction(name, impl, isType);
    funcCount++;
    return;
}

void type() {
    if (symbol != VOID && symbol != INT) {
        error("Unknown error");
    }
    symbol = scan();
    return;
}

bool par() {
    if (symbol == RBRACE) {
        return false;
    }
    if (symbol != INT) {
        error("Incorrect sentence");
    }
    symbol = scan();
    if (symbol != NAME) {
        error("Incorrect sentence");
    }
    symbol = scan();
    return true;
}

struct func_impl* funcImpl() {
    isImpl = true;
    struct func_impl* res = createImpl();
    res->calls[0] = printCall();
    res->num = 1;
    if (symbol != RFBRACE) {
        struct func_impl* prevRes = funcImpl();
        for (int i = 0; i < prevRes->num; ++i) {
            res->calls[i+1] = prevRes->calls[i];
        }
        res->num = prevRes->num + 1;
    }
    isImpl = false;
    return res;
}

struct func_call* printCall() {
    struct func_call* res;
    if (symbol == NAME)
    {
        char* name = strdup(lastStr);
        if (strcmp(name, "print")) {
            error("Only print() can be in function implementation");
        }
        symbol = scan();
        if (symbol != LBRACE) {
            error("Error");
        }
        symbol = scan();
        if (symbol == RBRACE) {
            error("Print function should have parametr");
        }
        char* val = value();
        if (symbol != RBRACE) {
            error("Brackets disbalance");
        }
        symbol = scan();
        if (symbol != POINT) {
            error("Error");
        }
        res = createfuncCall(val, name);
        if (isImpl) {
            symbol = scan();
            return res;
        }
        funcCalls[callCount] = res;
        callCount++;
    }
    else {
        error("Incorrect sentence");
    }
    symbol = scan();
    return res;
}
