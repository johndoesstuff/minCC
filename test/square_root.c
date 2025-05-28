double sqrt_approx(double x) {
	if (x < 0.0) {
		return -1.0;
	}
	if (x == 0.0) {
		return 0.0;
	}

	double guess = x / 2.0;
	double epsilon = 0.00001;

	int i = 0;
	while (i < 20) {
		double next = 0.5 * (guess + x / guess);
		if (guess - next < epsilon && guess - next > -epsilon) {
			i = 20;
		} else {
			guess = next;
			i = i + 1;
		}
	}

	return guess;
}

int main() {
	printf("Sqrt 2 is approximately %f\n", sqrt_approx(2.0));

	return 0;
}
