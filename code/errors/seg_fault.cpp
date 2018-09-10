#include <iostream>
using namespace std;

int foo(){
	cout <<"foo was called" << endl;
	return 2;
}
int bar(){
	int* m[1];
	m[3] = (int*) &foo; //main ret adress now points to foo
}

int main(){
	bar();
	cout << "vse ok";
	return 0;
}