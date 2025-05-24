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

float sdf_sphere(float px, float py, float pz, float cx, float cy, float cz, float radius) {
	float dx = px - cx;
	float dy = py - cy;
	float dz = pz - cz;
	return sqrt_approx(dx*dx + dy*dy + dz*dz) - radius;
}

float march_ray(float ox, float oy, float oz, float dx, float dy, float dz) {
	float totalDist = 0.0;
	int steps = 0;
	while (steps < 64 && totalDist < 100.0) {
		float px = ox + dx * totalDist;
		float py = oy + dy * totalDist;
		float pz = oz + dz * totalDist;

		float dist = sdf_sphere(px, py, pz, 0.0, 0.0, 3.0, 1.0); // sphere at (0,0,3), radius 1

		if (dist < 0.001) {
			return totalDist + dist; // hit
		}

		totalDist = totalDist + dist;
		steps = steps + 1;
	}

	return 0.0; // no hit
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
		float hit = march_ray(0.0, 0.0, 0.0, dirX, dirY, dirZ);
		if (hit == 0.0) {
			printf(" ");
		} else if (hit < 2) {
			printf("#");
		} else  if (hit < 5) {
			printf("=");
		} else if (hit < 10) {
			printf("-");
		} else if (hit < 25) {
			printf("'");
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
