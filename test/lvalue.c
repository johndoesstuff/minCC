int main() {
	char* b = "hello world";
	printf("%s\n", b);

	*b = 'c';

	printf("%s\n", b);

	return 0;
}
