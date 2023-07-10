#include "../scrutiny/scrutiny.h"
#include <stdio.h>

// This time we dont define the `SCRUTINY_DEBUG` macro so that we can use
// scrutiny's assertions during the runtime of our program.

int main()
{
	int a = 8;
	int b = 4;

	scrutiny_assert_equal(a, b * 2);
	printf("Passed One!\n");

	int arr1[] = { 2, 4, 6, 8 };
	int arr2[] = { 2, 4, 5, 7 };

	for (unsigned int i = 0; i < sizeof(arr1) / sizeof(int); i++) {
		scrutiny_assert_equal(arr1[i], arr2[i]);
	}
}

