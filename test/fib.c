//target fib number
int target = 10;

int a = 0;
int b = 1;
while (target > 0) {
	int tmp = a;
	a = a + b;
	b = tmp;
	target = target - 1;
}
return a;
