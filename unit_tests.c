void assert(bool condition, int* current, int* passed) {
	if (condition) {
		(*current)++;
		(*passed)++;
		printf("Test %d Passed\n", *current);
	} else {
		(*current)++;
		printf("!! Test %d Failed\n", *current);
	}
}

int square(int x) {
	return x * x;
}

int main() {
	printf("Running Unit Tests...\n\n");
	int current_test = 0;
	int tests_passed = 0;

	int a = 53;
	int b = 21;
	assert(a == 53, &current_test, &tests_passed);
	assert(a + b == 74, &current_test, &tests_passed);
	assert(a - b == 32, &current_test, &tests_passed);
	assert(a * b == 1113, &current_test, &tests_passed);
	assert(a / b == 2, &current_test, &tests_passed);
	assert(a % b == 11, &current_test, &tests_passed);
	assert(*(&a) == a, &current_test, &tests_passed);
	assert(a * b + a == 1166, &current_test, &tests_passed);
	assert(a * (b + a) == 3922, &current_test, &tests_passed);

	char* str = "hello world";
	assert(str[1] == 'e', &current_test, &tests_passed);
	assert(*(str + 2) == 'l', &current_test, &tests_passed);
	assert(*(str++) == 'h', &current_test, &tests_passed);
	assert(*(++str) == 'l', &current_test, &tests_passed);

	int x = 3;
	assert(++x == 4, &current_test, &tests_passed);
	assert(x++ == 4, &current_test, &tests_passed);
	assert(x == 5, &current_test, &tests_passed);

	float f = 3.0f;
	int i = (int)(f + 2.9f);
	assert(i == 5, &current_test, &tests_passed);

	int* p = &a;
	assert(*p == 53, &current_test, &tests_passed);
	assert(*(p + 0) == 53, &current_test, &tests_passed);

	assert(square(4) == 16, &current_test, &tests_passed);
	assert(square(5 + 1) == 36, &current_test, &tests_passed);

	assert((a > b) == true, &current_test, &tests_passed);
	assert((a < b) == false, &current_test, &tests_passed);
	assert((a != b) == true, &current_test, &tests_passed);
	assert((a == 53 && b == 21), &current_test, &tests_passed);
	assert((a == 53 || b == 0), &current_test, &tests_passed);

	assert((2 + 3 * 4) == 14, &current_test, &tests_passed);
	assert((8 / 2 + 3) * 2 == 14, &current_test, &tests_passed);
	assert((8 / (2 + 2)) * 2 == 4, &current_test, &tests_passed);
	assert((5 + 3) * (2 + 1) == 24, &current_test, &tests_passed);

	int z = 7;
	int* q = &z;
	*q += 5;
	assert(z == 12, &current_test, &tests_passed);

	*q = *q * 2;
	assert(z == 24, &current_test, &tests_passed);

	int m = 5;
	int n = 10;
	assert(((m + n) * (n - m)) == 75, &current_test, &tests_passed);
	assert((m += 2) == 7, &current_test, &tests_passed);
	
	int check = 0;
	int result = (1 || (++check));  // short-circuit: check is not incremented
	assert(check == 0, &current_test, &tests_passed);
	assert(result == true, &current_test, &tests_passed);

	check = 0;
	result = (0 && (++check));  // also short-circuits: still no increment
	assert(check == 0, &current_test, &tests_passed);
	assert(result == false, &current_test, &tests_passed);

	i = 0;
	if (true) {
		i = 1;
	}
	assert(i == 1, &current_test, &tests_passed);
	if (false) {
	
	} else {
		i = 2;
	}
	assert(i == 2, &current_test, &tests_passed);
	if (false) {
	
	} else if (true) {
		i = 3;
	} else {
	
	}
	assert(i == 3, &current_test, &tests_passed);
	if (true) {
		if (true) {
			i = 4;
		}
	}
	assert(i == 4, &current_test, &tests_passed);
	i = 0;
	for (int j = 0; j < 4; j++) {
		i++;
	}
	assert(i == 4, &current_test, &tests_passed);
	i = 0;
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			i++;
		}
	}
	assert(i == 16, &current_test, &tests_passed);
	f = 4.0f;
	assert(f == 4.0f, &current_test, &tests_passed);
	long l = 67;
	i = 67;
	assert(l == i, &current_test, &tests_passed);
	assert(3.0f == 3.0, &current_test, &tests_passed);
	assert(4294967295 != 4294967295L, &current_test, &tests_passed);
	assert(4 + 1.5 == 5.5, &current_test, &tests_passed);
	assert(5 + true == 6, &current_test, &tests_passed);
	assert(true + true == 2, &current_test, &tests_passed);
	assert(true + 1.5 == 2.5, &current_test, &tests_passed);
	i = 2;
	assert(i-- == 2, &current_test, &tests_passed);
	assert(--i == 0, &current_test, &tests_passed);
	short s = 65537;
	assert(s == 1, &current_test, &tests_passed);

	int ca = 10;
	ca += 5;
	assert(ca == 15, &current_test, &tests_passed);
	ca -= 3;
	assert(ca == 12, &current_test, &tests_passed);
	ca *= 2;
	assert(ca == 24, &current_test, &tests_passed);
	ca /= 4;
	assert(ca == 6, &current_test, &tests_passed);

	i = 6;
	int *p1 = &i;
	int **p2 = &p1;
	assert(**p2 == 6, &current_test, &tests_passed);

	int *p3 = null;
	assert(p3 == null, &current_test, &tests_passed);

	printf("\nPassed %d/%d tests\n", tests_passed, current_test);

	return 0;
}
