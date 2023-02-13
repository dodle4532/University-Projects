#include <stdio.h>

#define SIZE 10
int main()
{
    int n;int a;
    a = 1;
    printf("Insert n < %d:\n", SIZE);
    scanf("%d",&n);
    if(n > SIZE || n < 1){
        printf("Error\n");
        return 0;
    }
    while (a != n + 1){
        for (int i = 1; i < SIZE + 1 - a; ++i){
            printf(" ");
        }
        for (int i =1; i <= 2 * a - 1; ++i){
            printf("*");
        }
        printf("\n");
        a += 1;
    }
    return 0;
}