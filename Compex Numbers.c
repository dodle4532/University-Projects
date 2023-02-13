#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct {
	float x;
	float y;
} Complex;

Complex add(Complex a, Complex b){
	Complex c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

Complex getLinked(Complex a){
        Complex c;
        c.x = a.x;
        c.y = -a.y;
        return c;
}

Complex mul(Complex a, Complex b){
	Complex c;
	c.x = a.x * b.x + a.y * b.y;
	c.y = a.y * b.x + a.x * b.y;
	return c;
}

Complex divi(Complex a, Complex b){
	assert(b.x != 0 && b.y != 0);	
        Complex c;
	c = mul(a,getLinked(b));
//	printf("%f %f\n",c.x, c.y);
	Complex d;
        d.x = c.x / (b.x * b.x + b.y * b.y);
	d.y = c.y / (b.x * b.x + b.y * b.y);
        return d;
}
float mod(Complex a){
	return sqrt(a.x * a.x + a.y * a.y);	
}

float getArg(Complex a){
        return a.x;
}

void printfAlg(Complex a){
	printf("%f + %.2fi\n",a.x, a.y);
}
int main(){
	Complex a;
	Complex b;
	scanf("%f %f", &a.x, &a.y);
	scanf("%f %f", &b.x, &b.y);
	Complex c = divi(a,b);
	printf("%f\n",mod(a));
	printfAlg(a);
	return 0;
}
