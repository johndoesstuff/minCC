int main() {
	int target = 15;  // Change this to find a different nth prime
	int count = 0;
	int num = 2;

	while (true) {
		int i = 2;
		bool isPrime = true;
		while (i * i <= num) {
			if (num % i == 0) {
				isPrime = false;
			}
			i = i + 1;
		}

		if (isPrime) {
			count = count + 1;
			if (count == target) {
				return num;
			}
		}

		num = num + 1;
	}

	return 0;
}
