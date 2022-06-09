#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
    if(x >= 0){
		*y = x;
	}else{
		*y = -x;
	}
}

int main(void) {
    int a,res;
    res = 0;
    a = -98;
    int *p1 = NULL;
    p1 = &res;
    absolute(a,p1);
    printf("%d\n",res);
    res = 0;
    return EXIT_SUCCESS;
}

