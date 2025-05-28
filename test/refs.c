int main() {
	int x = 42;
	int* p = &x;       // address-of
	int y = *p;        // dereference

	int* q = &x;
	int z = *(&x);     // should also be 42

	return x + y + z;  // should return 42 + 42 + 42 = 126
}
