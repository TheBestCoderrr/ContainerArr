#include "Array.h"
using namespace std;

int main() {
	Array<int> arr;
	for (int i = 1; i <= 5; i++)
		arr.push_back(10 * i);
	Array<int> arr2;
	for (int i = 1; i <= 5; i++)
		arr2.push_back(1 * i);
	arr.Print();
	arr2.Print();
	Array<int> arr3;
	arr3 = arr + arr2;
	arr3.Print();
	arr3.PrintReverse();
	cout << endl;
	
	arr2.Reverse();
	arr2.Print();
	arr2.PrintReverse();
	cout << endl;

	arr3.insert(1, 555);
	arr3.Print();
	arr3.pop_position(2);
	arr3.Print();
	cout << endl;
	arr3.insert(3, 555);
	arr3.push_back(555);
	arr3.push_front(555);
	arr3.Print();
	arr3.Replace(555, 444);
	arr3.Print();
	cout << endl;

	cout << arr3[1] << "\t" << arr3[3] << endl;
}