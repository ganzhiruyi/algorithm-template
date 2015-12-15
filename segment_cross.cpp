#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;
const double eps = 1e-6;
struct Point{
	double x,y;
};
int dblcmp(double a){
	return fabs(a) < eps ? 0 : (a < 0 ? -1 : 1);
}
double det(double ax,double ay,double bx,double by){
	//计算向量(ax,ay)与(bx,by)的叉积
	return ax*by - bx*ay;
}
double cross(Point a,Point b,Point c){
	return det(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
}
bool simple_cross(Point a,Point b,Point c,Point d){
	int d1 = dblcmp(cross(a,b,c));
	int d2 = dblcmp(cross(a,b,d));
	int d3 = dblcmp(cross(c,d,a));
	int d4 = dblcmp(cross(c,d,b));
	if(d1 ^d2 == -2 && d3 ^ d4 == -2) return true;
	return false;
}

int main(){
	Point a,b,c,d;
	while(~scanf("%lf %lf",&a.x,&a.y)){
		scanf("%lf %lf",&b.x,&b.y);
		scanf("%lf %lf",&c.x,&c.y);
		scanf("%lf %lf",&d.x,&d.y);
		printf("%s\n", simple_cross(a,b,c,d) ? "yes" : "no");
	}
	return 0;
}