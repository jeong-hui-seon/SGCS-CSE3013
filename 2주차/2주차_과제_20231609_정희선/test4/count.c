#include "count.h"

#include <stdio.h>

void count(int n, int* count_num) {
	for (int i = 0; i < 10; i++) {
		count_num[i] = 0;
	}
	for (int p = 1; p <= n; p++) {
		int temp = p;

		while (temp > 0) {
			int num = temp % 10;
			count_num[num]++;
			temp = temp / 10;
		}
	}
}