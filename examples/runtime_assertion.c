#include "../scrutiny/scrutiny.h"

/*
 * Shows how you can use scrutiny's assertions as an alternative to the
 * standard library's during application runtime or debugging.
 */

int main()
{
	int a = 8;
	int b = 4;

	scrutiny_assert_equal_int(a, b * 2);
	printf("Passed One!\n");

	/*
	 * If you want to make runtime assertions like this after running unit tests
	 * you will need to make a call to scrutiny_clear_results().
	 */

	int arr1[] = { 2, 4, 6, 8 };
	int arr2[] = { 2, 4, 5, 7 };

	scrutiny_assert_not_equal_array(arr1, arr2, sizeof(int), sizeof arr1);
	scrutiny_assert_equal_int(arr1[2], arr2[2]);
}

