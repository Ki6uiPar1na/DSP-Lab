% Define a signal x[n] = [1, 2, 3, 4] starting at n=0
x_orig = [1, 2, 3, 4];
n_orig = 0:3;

% To decompose, we need a symmetric time axis that covers both n and -n
% So we need n from -3 to 3
n = -3:3;
x = zeros(1, length(n));
% Put our original signal into this larger window
% x will be [0, 0, 0, 1, 2, 3, 4] for n = [-3, -2, -1, 0, 1, 2, 3]
x(n >= 0 & n <= 3) = x_orig;

% 1. Reverse the signal: x[-n]
x_rev = fliplr(x);

% 2. Decompose
x_even = (x + x_rev) / 2;
x_odd = (x - x_rev) / 2;

% 3. Verify
x_reconstructed = x_even + x_odd;

% --- Plotting ---
figure('Name', 'Even and Odd Decomposition');

subplot(2, 2, 1);
stem(n, x, 'filled'); title('Original x[n]'); grid on;

subplot(2, 2, 2);
stem(n, x_even, 'filled', 'g'); title('Even Component x_e[n]'); grid on;

subplot(2, 2, 3);
stem(n, x_odd, 'filled', 'r'); title('Odd Component x_o[n]'); grid on;

subplot(2, 2, 4);
stem(n, x_reconstructed, 'filled', 'm'); title('Verified: x_e + x_o'); grid on;