#include <stdio.h>

int max(int a, int b){
	int z = a;
	if (b > z)
		z = b;
	return z;
}

int main(void){
	printf("Input a,b\n");
	setbuf(stdout, NULL);
	int a,b;
	scanf("%d %d", &a, &b);
	printf("%d", max(a, b));
	return 0;
}
