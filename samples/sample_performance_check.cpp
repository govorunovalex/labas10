#include <iostream>
#include "tpolynomial.h"
#include "time.h"

using namespace std;

int main()
{
    int max_count = 0;
    cout << "Enter number of checks - ";
    cin >> max_count;
    clock_t time;
    clock_t average_time;
    for (unsigned size = 10; size < 1000000; size *= 10) {
	int *powers = new int[size];
	for (int i = 0; i < size; i++) {
	    powers[i] = i;
	}
	TMonomial A(size, powers, 1);
	TPolynomial p1(size);
	average_time = 0;
	for (unsigned count = 0; count < max_count; count++) {
	    time = clock();
	    p1 += A;
	    average_time += clock() - time;
	}
	average_time /= max_count;
	cout << "Time is: " << average_time << endl;
    }
    return 0;
}
