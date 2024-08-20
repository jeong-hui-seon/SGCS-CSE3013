#include "test.h"
#include "count.h"
#include <stdio.h>


void test(int test_num) {
	while (test_num--) {
		int Num;
		scanf("%d", &Num);
		int count_num[10] = { 0 };
		count(Num, count_num);

		for (int i = 0; i < 10; i++) {
			printf("%d ", count_num[i]);
		}
		printf("\n");
	}
}
