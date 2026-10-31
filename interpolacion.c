#include <stdio.h>

#define MAX_N 20   // Máximo número de puntos

void calcular_coeficientes_newton(double x[], double y[], double coef[], int n) {
    int i, j;

    // Inicialmente, los coeficientes son los valores de y
    for (i = 0; i < n; i++) {
        coef[i] = y[i];
    }

    // Diferencias divididas (en sitio)
    for (j = 1; j < n; j++) {
        for (i = n - 1; i >= j; i--) {
            coef[i] = (coef[i] - coef[i - 1]) / (x[i] - x[i - j]);
        }
    }
}

// Evalúa el polinomio de Newton en un punto xp usando Horner generalizado
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

    printf("INTERPOLACION POLINOMIAL DE NEWTON\n");
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

    // Punto a interpolar (se recomienda que este entre x[0] y x[n-1])
    printf("Introduce el valor de x a INTERPOLAR: ");
    scanf("%lf", &xp);

    // Calculamos coeficientes de Newton
    calcular_coeficientes_newton(x, y, coef, n);

    // Evaluamos el polinomio en xp
    yp = evaluar_newton(x, coef, n, xp);

    printf("P(%.6f) = %.10f (valor interpolado)\n", xp, yp);

    return 0;
}