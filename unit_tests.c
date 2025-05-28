void assert(bool condition, int* current, int* passed) {
	if (condition) {
		printf("Test Passed\n");
	} else {
		printf("Test Failed\n");
	}
}

int main() {
	printf("Running Unit Tests...\n\n");
	int current_test = 0;
	int tests_passed = 0;

	int a = 53;
	assert(a == 53);
	int b = 21 + a;
	assert(b == 74);

	return 0;
}
