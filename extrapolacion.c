#include <stdio.h>

#define MAX_N 20   // Maximo numero de puntos

void calcular_coeficientes_newton(double x[], double y[], double coef[], int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        coef[i] = y[i];
    }

    for (j = 1; j < n; j++) {
        for (i = n - 1; i >= j; i--) {
            coef[i] = (coef[i] - coef[i - 1]) / (x[i] - x[i - j]);
        }
    }
}

double evaluar_newton(double x[], double coef[], int n, double xp) {
    double resultado = coef[n - 1];
    int i;

    for (i = n - 2; i >= 0; i--) {
        resultado = coef[i] + (xp - x[i]) * resultado;
    }

    return resultado;
}

int main(void) {
    int n, i;
    double x[MAX_N], y[MAX_N], coef[MAX_N];
    double xp, yp;
    double xmin, xmax;

    printf("EXTRAPOLACION POLINOMIAL DE NEWTON\n");
    printf("Numero de puntos de datos (max %d): ", MAX_N);
    scanf("%d", &n);

    if (n < 2 || n > MAX_N) {
        printf("Numero de puntos invalido.\n");
        return 1;
    }

    printf("Introduce los pares (x, y):\n");
    for (i = 0; i < n; i++) {
        printf("x[%d] y[%d]: ", i, i);
        scanf("%lf %lf", &x[i], &y[i]);
    }

    // Calculamos el minimo y maximo de x para verificar si xp esta fuera
    xmin = x[0];
    xmax = x[0];
    for (i = 1; i < n; i++) {
        if (x[i] < xmin) xmin = x[i];
        if (x[i] > xmax) xmax = x[i];
    }

    printf("Introduce el valor de x a EXTRAPOLAR: ");
    scanf("%lf", &xp);

    if (xp >= xmin && xp <= xmax) {
        printf("ADVERTENCIA: x esta dentro del rango de datos (seria interpolacion).\n");
    } else {
        printf("Nota: x esta FUERA del rango [%.6f, %.6f] (extrapolacion).\n", xmin, xmax);
    }

    calcular_coeficientes_newton(x, y, coef, n);
    yp = evaluar_newton(x, coef, n, xp);

    printf("P(%.6f) = %.10f (valor extrapolado)\n", xp, yp);

    return 0;
}