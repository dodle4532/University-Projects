#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	char view[3][3] = {' '};
	for (int i = 0; i < 3;++i){
		for (int j = 0;j < 3; ++j){
			view[i][j] = ' ';
		}
	}
	int a,b,p,x,y = 0;
	while (p != 2){
		printf("Choose coordinates to put X\n");
		scanf("%d %d",&x,&y);
		if (view[x-1][y-1] != ' ' || x < 1 || x > 3 || y < 1 || y > 3){
			printf("ERROR\n");
			continue;
		}
		view[x-1][y-1] = 'X';
		for (int i = 0; i < 3;++i){
                        if (view[i][0] == view[i][1] && view[i][1] == view[i][2] && view[i][0] == view[i][2] && view[i][0]!=' '){
                                p = 2;
                        }
		}
                for (int j = 0; j < 3;++j){
                        if (view[0][j] == view[1][j] && view[1][j] == view[2][j] && view[0][j] == view[2][j] && view[0][j]!=' '){
                                p = 2;
                        }
		}
                if (view[0][0] == view[1][1] && view[1][1] == view[2][2] && view[0][0] == view[2][2] && view[0][0]!=' '){
                                p = 2;
                }
                if (view[0][2] == view[1][1] && view[1][1] == view[2][0] && view[0][2] == view[2][0] && view[0][2]!=' '){
                                p = 2;
                }
		if (p == 2){
			for (int i = 0; i < 3;++i){
                 	       for (int j = 0;j <3;++j){
                         	      printf("%c ",view[i][j]);
                        	}
                        	printf("\n");
                	}
			printf("GAME OVER\n");
			break;
		}
		srand(time(0));
		while (p != 3){
			a = rand()%3;
			b = rand()%3;
			if (view[a][b] == ' '){
				view[a][b] = 'O';
				break;
			}
		}
		for (int i = 0; i < 3;++i){
			for (int j = 0;j <3;++j){
				printf("%c ",view[i][j]);
			}
			printf("\n");
		}
		for (int i = 0; i < 3;++i){
			if (view[i][0] == view[i][1] && view[i][1] == view[i][2] && view[i][0] == view[i][2] && view[i][0]!=' '){
				printf("GAME OVER\n");
				p = 2;
			}
		}
		for (int j = 0; j < 3;++j){
                        if (view[0][j] == view[1][j] && view[1][j] == view[2][j] && view[0][j] == view[2][j] && view[0][j]!=' '){
                                printf("GAME OVER\n");
                                p = 2;
                        }
		} 
                if (view[0][0] == view[1][1] && view[1][1] == view[2][2] && view[0][0] == view[2][2] && view[0][0]!=' '){
                                printf("GAME OVER\n");
                                p = 2;
                }
		if (view[0][2] == view[1][1] && view[1][1] == view[2][0] && view[0][2] == view[2][0] && view[0][0]!=' '){
                                printf("GAME OVER\n");
                                p = 2;
                }
		
		
	}
	return 0;
}
