#include <stdio.h>
#include <math.h>

int main() {
    float integral;
    float a,b;
    int n;
    float h;
    float x;
    int i;

    float f(float x); // Function we're integrating.

    printf("Enter limits a,b and number of partitions n.\n");
    scanf("%f %f %d", &a, &b, &n);

    h = (b-a)/n;
    integral = (f(a) + f(b))/2.0;
    x = a;

    for (i=1;i<=n-1;i++) {
        x = x+h;
        integral = integral + f(x);
    }

    integral = integral*h;

    printf("With n = %d trapezoids, our estimate\n",n);
    printf("of the integral from %f to %f = %f\n",a,b,integral);
}

float f(float x) {

    float return_val;

    // Calculate function.

    // Use sin(x).
    return_val = sin(x);

    return return_val;
}
