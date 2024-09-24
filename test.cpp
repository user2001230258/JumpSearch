#include <iostream>
#include <math.h>

using namespace std;

int jumpSearch(int a[], int x, int n) {
	int step = sqrt(n);
	int prev = 0;
	
	while (a[min(step,n) - 1] < x) {
		prev = step;
		step += sqrt(n);
		
		if (prev >= n)
			return -1;
	}
	
	while (a[prev] < x) {
		prev++;
		
		if (prev == min(step,n))
			return -1;
	}
	
	if (a[prev] == x)
		return prev;
		
	return -1;
}

int main() {
	int a[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
	int x = 17;
	int n = sizeof(a)/sizeof(a[0]);
	
	int index = jumpSearch(a,x,n);
	cout << "Number " << x << " is at index " << index;
	return 0;
}