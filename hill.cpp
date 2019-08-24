#include <iostream>
#include <math.h>

using namespace std;

float funcion(float x){
	return cos(x)+1;
}

float vecino(float x){
	return x+0.05;
}

void hill( float p_i ){

	int i=0;
	float x;
	float xnew;
	x=p_i;
	while( i<100){
		xnew = vecino(x);
		cout<<funcion(x)<<" - "<<xnew<<endl;
		if(funcion(xnew) > funcion(x)){
			x=xnew;
			cout<<x<<endl;
		}
		i++;
	}

	cout<<"valor final: "<<x<<endl;

}


float funcion2(float x, float y){
	return cos(x)+1;
}

void hill_2(float ix, float iy, float lx, float ly){
	int i=0;

	float x, xnew;
	float y, ynew;

	x=ix;
	y=iy;

	while(i<100){
		xnew=vecino(x);
		ynew=vecino(y);
		if (funcion2(xnew,ynew) > funcion2(x,y))
		{
			x=xnew;
			y=ynew;
		}

		i++;
	}
}

int main(int argc, char const *argv[])
{
	hill(9.424777);
	return 0;
}