# Numerical Methods

Academic exercises by Yoltzin Daniel Figueroa Urzua, Electrical-Electronic Engineering student at UAEM.

## Files

- `interpolacion.c`: Newton polynomial interpolation with divided differences and nested evaluation.
- `extrapolacion.c`: the same polynomial method for evaluation outside the data interval; prints a warning for an in-range point.
- `GaussJordan.m`: MATLAB function with partial pivoting and optional printed row operations.

## C programs

Compile separately with a C compiler, for example:

```sh
gcc -std=c11 -Wall -Wextra interpolacion.c -o interpolacion
gcc -std=c11 -Wall -Wextra extrapolacion.c -o extrapolacion
```

Enter 2 to 20 data points, all with distinct x coordinates. Example: (0,0), (1,1), (2,4). Evaluating x=1.5 gives 2.25; extrapolating x=3 gives 9. These are mathematical reference examples, not a claim of compiler execution in this review.

The original C exercises are preserved. They do not validate every scanf result or reject repeated x coordinates. Use numeric input and distinct x values. High-degree interpolation and especially extrapolation can be numerically unstable; this is academic code.

## MATLAB

Place `GaussJordan.m` on the MATLAB path:

```matlab
A = [0 2; 1 3]; B = [4; 7];
x = GaussJordan(A, B, false);
assert(norm(A*x-B, inf) < 1e-10); % Expected x = [1; 2]
```

### Portfolio correction

The local original closed the pivot loop before normalization and elimination, so those stages only ran for the final column. In this portfolio copy those stages run inside each pivot iteration. A pivot-error format argument was also corrected. The source file on the user's MATLAB Drive was left intact. Shape and conditioning checks use fixed tolerances and this is not a production replacement for MATLAB's built-in linear solvers.

Validation: static review of loop placement and independent numerical checks of the corrected algorithm. MATLAB execution has not been performed during this portfolio preparation. MATLAB skill level: basic academic use.
