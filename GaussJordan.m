function x = GaussJordan(A, B, showSteps)

tolPivot = 1e-12;
tolZero = 1e-14;
tolCond = 1e-14;
numFmt = '%10.6g';

if nargin<2 || nargin>3
    error('Use: GaussJordan(A, B, [showSteps])');
end

if nargin<3
    showSteps = true;
end

if ~ismatrix(A) || size(A, 1) ~= size(A, 2)
    error('A debe ser cuadrada');
end
if ~iscolumn(B)
    error('B debe ser vector columna (n x 1)');
end
if size(A, 1) ~= size(B, 1)
    error('Dimensiones incompatibles A/B');
end
n = size(A, 1);
if rcond(A) < tolCond
    error('A es singular o mal condicionada');
end

if showSteps
    disp('Sistema original [A | B]:');
    printAug(A, B, numFmt);
    fprintf('\nPaso 0: Pivoteo parcial\n');
end

for k = 1:n
    [~, pRel] = max(abs(A(k:n, k)));
    p = pRel + k - 1;
    if p ~= k
        A([k p],:) = A([p k],:);
        B([k p]) = B([p k]);
        if showSteps
            fprintf(' - Fila %d <-> %d\n', k, p);
            printAug(A, B, numFmt);
        end
    end

if abs(A(k, k)) < tolPivot
    error('Pivote ~ 0 en k=%d', k);
end
piv = A(k, k);
if abs(piv - 1) > tolZero
    A(k,:) = A(k,:)/piv;
    B(k) = B(k)/piv;
    if showSteps
        fprintf ('Paso %d: Normalizar fila %d(/%g)\n', k, k, piv);
        printAug(A, B, numFmt);
    end
end

for i = 1:n
    if i==k, continue; end
    f= A(i, k);
    if abs(f) > tolZero
        A(i,:) = A(i,:) - f*A(k,:);
        B(i) = B(i) - f*B(k);
        if abs(A(i, k)) < tolZero, A(i, k) = 0; end
        if showSteps
            fprintf(' Eliminar en fila %d(factor=%g)\n', i, f);
            printAug(A, B, numFmt);
        end
    end
end

end % End each pivot normalization and elimination stage

x = B;
if showSteps
    fprintf('\nMatriz final (≈I) y solución:\n');
    printAug(A, x, numFmt);
    for i = 1:n
        fprintf(['x%d=' numFmt '\n'], i, x(i));
    end
end 

function printAug(M, v, fmt)
    [nr,nc] = size(M); bar ='|';
    for r=1:nr
        for c=1:nc, fprintf([fmt ' '], M(r,c)); end
        fprintf('%s',bar); fprintf([fmt '\n'], v(r));
    end
    fprintf('\n');
end
end

