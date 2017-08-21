function runner(matrix_dim)
% runs the LUD benchmark
%     'matrix_dim' is the size of the square matrix being generated

if nargin < 1
   error('Missing matrix_dim\n');
end

M = rand(matrix_dim, matrix_dim);

tic
[L,U,P] = lu(M);
elapsedTime = toc;

LU = inv(P)*L*U;

fprintf('Largest deviation from the expected result:\n');
max(max(abs(LU-M)))

fprintf('WARNING: Skipping output verification because the lu builtin function finds a different permutation from the other implementations\n')

fprintf(1, '{ \"status\": %d, \"options\": \"matrix_dim %d\", \"time\": %f }\n', 1, matrix_dim, elapsedTime);
end

