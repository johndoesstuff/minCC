int x = 1;
int y = 1;
int z = 5;
while (z > 0) {
	x = x + y;
	y = x + y;
	z = z - 1;
}
return y;
