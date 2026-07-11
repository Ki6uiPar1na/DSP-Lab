clc;
clear;
close all;

% 1. Define a symmetric time axis centered around 0
n_axis = -3:3; 

% 2. Define your signal x[n] on this axis 
% Let's place [1, 2, 3, 4] starting at n = 0
x = [0, 0, 0, 1, 2, 3, 4]; 

% 3. Create the true time-reversed signal x[-n]
x_rev = fliplr(x); 

% 4. Perform Even and Odd Decomposition
even_com = (x + x_rev) / 2;
odd_com  = (x - x_rev) / 2;

% 5. Reconstruct to verify
reconstructed = even_com + odd_com;

% =========================================================
%                     VISUALIZATION
% =========================================================
figure('Name', 'Even and Odd Decomposition', 'NumberTitle', 'off');

% Original Signal
subplot(3,2,1);
stem(n_axis, x, 'filled', 'LineWidth', 1.5);
title('Original Signal x[n]');
xlabel('n'); ylabel('Amplitude');

% Time-Reversed Signal
subplot(3,2,2);
stem(n_axis, x_rev, 'filled', 'LineWidth', 1.5);
title('Time-Reversed Signal x[-n]');
xlabel('n'); ylabel('Amplitude');

% Even Component (Symmetric around n=0)
subplot(3,2,3);
stem(n_axis, even_com, 'r', 'filled', 'LineWidth', 1.5);
title('Even Component x_{even}[n]');
xlabel('n'); ylabel('Amplitude');

% Odd Component (Anti-symmetric around n=0, value at n=0 is always 0)
subplot(3,2,4);
stem(n_axis, odd_com, 'g', 'filled', 'LineWidth', 1.5);
title('Odd Component x_{odd}[n]');
xlabel('n'); ylabel('Amplitude');

% Reconstructed Signal (Should exactly match original)
subplot(3,2,5);
stem(n_axis, reconstructed, 'm', 'filled', 'LineWidth', 1.5);
title('Reconstructed Signal (Even + Odd)');
xlabel('n'); ylabel('Amplitude');
