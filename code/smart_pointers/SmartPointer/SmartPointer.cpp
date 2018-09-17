#include <iostream>

using namespace std;

template <typename T>
class SmartPointer
{
public:
	SmartPointer( T* ptr){
		this->ptr = ptr;
	}
	~SmartPointer(){
		delete ptr;
	}

	T& operator *(){
		return *(this->ptr); 
	}
private:
	T* ptr;
	
};


int main(int argc, char const *argv[])
{
	SmartPointer<int> pointer = new int(5);
	cout << *pointer <<endl;
	
	return 0;
}