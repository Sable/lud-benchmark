function runner(matrix_dim, input_directory)
% runs the LUD benchmark
%     'matrix_dim' is the size of the square matrix being generated
%     'input_directory' is the directory containing the inputs

if nargin < 2
   error('Missing matrix_dim and/or input directory\n');
end

input_file_path = fullfile(input_directory, strcat(num2str(matrix_dim), '.csv'));
M = csvread(input_file_path);

fletcherSum(M)

tic;
R = lud_base(M,matrix_dim);
elapsedTime = toc;

FlooredR = floor(100*R);

L = tril(R,-1) + eye(matrix_dim, matrix_dim);
U = triu(R);
LU = L*U;

fprintf('Largest deviation from the expected result:\n');
max(max(abs(LU-M)))

fprintf(1, '{ \"status\": %d, \"options\": \"matrix_dim %d\", \"time\": %f, \"output\": %d }\n', 1, matrix_dim, elapsedTime, fletcherSum(floor(100*R)));
end

