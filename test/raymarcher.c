float sqrt_approx(float x) {
        if (x < 0.0) {
                return -1.0;
        }
        if (x == 0.0) {
                return 0.0;
        }

        float guess = x / 2.0;
        float epsilon = 0.00001;

        int i = 0;
        while (i < 20) {
                float next = 0.5 * (guess + x / guess);
                if (guess - next < epsilon && guess - next > -epsilon) {
                        i = 20;
                } else {
                        guess = next;
                        i = i + 1;
                }
        }

        return guess;
}

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
		float dirZ = 1.0;

		//normalize vector
		float norm = sqrt_approx(dirX*dirX + dirY*dirY + dirZ*dirZ);
		dirX = dirX / norm;
		dirY = dirY / norm;
		dirZ = dirZ / norm;

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
