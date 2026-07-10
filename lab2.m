clc; clear; close all;

x = [1, 2, 3, 4];
n = 0:3;

subplot(2, 2, 1);
stem(n, x, 'filled', 'b');
title("Original Signal");

n_shift = n + 2;
subplot(2, 2, 2);
stem(n_shift, x, 'filled', 'r', 'LineWidth', 1.5);
title('Shifted x[n-2]');
xticks(-5:5); grid on;

% --- Reversal Section ---
x_rev = fliplr(x);        % Flips [1 2 3 4] to [4 3 2 1]
n_rev = -fliplr(n);       % Flips [0 1 2 3] and makes them negative: [-3 -2 -1 0]

subplot(2, 2, 3);         % Changed from 3,2,3 to 2,2,3
stem(n_rev, x_rev, 'filled', 'g'); % Swapped n and x
title("Reversal x[-n]");
xticks(-5:5); grid on;

%scalling
x_scale = x(1 : 2 : end);
n_scale = 0 : length(x_scale) - 1;
subplot(2, 2, 4);
stem(n_scale, x_scale, 'filled', 'm');
grid on;
