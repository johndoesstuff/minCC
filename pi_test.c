int i = 0;
int iterations = 1000;
int sign = 1;            // 1 or -1
int denom = 1;
int scale = 1000000;     // fixed-point scaling factor
int term = 0;
int sum = 0;

while (i < iterations) {
    // term = scale / denom
    term = scale / denom;

    // if sign is positive, add term; else, subtract
    if (sign > 0) {
        sum = sum + term;
    } else {
        sum = sum - term;
    }

    // Flip sign: sign = -sign
    sign = sign * -1;

    // denom = denom + 2
    denom = denom + 2;

    // i = i + 1
    i = i + 1;
}

// pi_approx = 4 * sum
int pi_approx = 4 * sum;

// Now pi_approx / scale is the integer part, and pi_approx % scale is fractional
return pi_approx;
