double sqrt_approx(double x) {
	if (x < 0.0) {
		return -1.0;
	}
	if (x == 0.0) {
		return 0.0;
	}

	double guess = x / 2.0;
	double epsilon = 0.00001;

	for (int i = 0; i < 20; i++) {
		double next = 0.5 * (guess + x / guess);
		if (guess - next < epsilon && guess - next > -epsilon) {
			i = 20;
		} else {
			guess = next;
		}
	}

	return guess;
}

double sdf_sphere(double px, double py, double pz, double cx, double cy, double cz, double radius) {
	double dx = px - cx;
	double dy = py - cy;
	double dz = pz - cz;
	return sqrt_approx(dx*dx + dy*dy + dz*dz) - radius;
}

double sdf(double px, double py, double pz) {
	double spacing = 3.0; //distance between spheres

	double rx = fmod(px + spacing * 0.5, spacing);
	if (rx < 0.0) {
		rx += spacing;
	}
	rx -= spacing * 0.5;

	double ry = fmod(py + spacing * 0.5, spacing);
	if (ry < 0.0) {
		ry += spacing;
	}
	ry -= spacing * 0.5;

	double rz = fmod(pz + spacing * 0.5, spacing) - spacing * 0.5;
	//double rx = px;
	//double rz = pz;

	return sdf_sphere(rx, ry, rz, 0.0, 0.0, 0.0, 1.0);
}

double march_ray(double ox, double oy, double oz, double dx, double dy, double dz) {
	double totalDist = 0.0;
	for (int steps = 0; steps < 35 && totalDist < 100.0; steps++) {
		double px = ox + dx * totalDist;
		double py = oy + dy * totalDist;
		double pz = oz + dz * totalDist;

		double dist = sdf(px, py, pz);

		if (dist < 0.001) {
			return totalDist + dist; //hit
		}

		totalDist += dist;
	}

	return 0.0; //no hit
}


printf("Basic Raymarcher with Sphere SDF:\n\n");

int width = 100;
int height = 50;

char* charset = "@&%QWNM0gB$#DR8mHXKAUbGOpV4d9h6PkqwSE2]ayjxY5Zoen[ult13If}C{iF|(7J)vTLs?z/*cr!+<>;=^,_:'-.`";

double cameraZ = 4.0;

//iterate each character on screen
for (int y = 0; y < height; y++) {
	for (int x = 0; x < width; x++) {
		//normalize screen position to direction
		double dirX = x * (1.0/width) - 0.5;
		double dirY = y * (1.0/height) - 0.5;
		double dirZ = 1.0;

		//normalize vector
		double norm = sqrt_approx(dirX*dirX + dirY*dirY + dirZ*dirZ);
		dirX = dirX / norm;
		dirY = dirY / norm;
		dirZ = dirZ / norm;

		//printf("%f", dirX);
		double hit = march_ray(0.0, 0.0, -cameraZ, dirX, dirY, dirZ);
		if (hit == 0.0) {
			printf(" ");
		} else {
			int charset_len = 91;
			int index = (int)((hit / 20.0) * (charset_len - 1));
			if (index >= charset_len) {
				printf(" ");
			} else {
				printf("%f: %d ", (hit / 20.0) * (charset_len - 1), index);
				//printf("%c", *(charset + index));
			}
		}

	}
	printf("\n");
}

printf("\n");

return 0;
