#include<iostream>
#include<random>
#include<math.h>

using namespace std;

int num_s = 0, num_c = 0;

void whereIsPoint(float x, float y);

int main (){

	int n;
	//For a better accuracy input n = 10000
	cout<<"Enter the value of n\n";
	cin>>n;
	
	float x, y;
	// cout<<point;

	srand((unsigned) time(0));

	for(int i=0; i<n; i++){
		for(int j=0; j<sqrt(n); j++){
			x = (float)rand() / RAND_MAX;
			y = (float)rand() / RAND_MAX;
			printf("%f, %f\n", x, y);
			whereIsPoint(x, y);
		}
	}

	num_s = n*sqrt(n);

	float pi = 4.0 * num_c / num_s;

	cout<<"Approximate Value of PI = "<<pi<<endl;

	return 0;

}

void whereIsPoint(float x, float y){

	float distance = sqrt((x*x) + (y*y));

	if(distance < 1)
		num_c++;

}