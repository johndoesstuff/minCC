printf("Basic Raymarcher with Sphere SDF:\n\n");

int width = 100;
int height = 50;

//iterate each character on screen
int y = 0;
while (y < height) {
	int x = 0;
	while (x < width) {
		//normalize screen position to direction
		float dirX = x * (1.0/width) - 0.5;
		float dirY = y * (1.0/height) - 0.5;

		//printf("%f", dirX);
		if (dirX > 0) {
			printf("X");
		} else {
			printf(".");
		}
		x = x + 1;
	}
	printf("\n");
	y = y + 1;
}

printf("\n");

return 0;
