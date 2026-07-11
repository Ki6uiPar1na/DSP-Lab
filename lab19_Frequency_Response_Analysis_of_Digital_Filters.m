clc;
clear;
close all;

% =========================================================
%     EXPERIMENT 19: FILTER COEFFS & STRUCTURAL FILTERING
% =========================================================

% Define an arbitrary transfer function: H(z) = (1 + 0.5z^-1) / (1 - 0.7z^-1 + 0.12z^-2)
b = [1, 0.5];
a = [1, -0.7, 0.12];

% Generate an impulse input signal to look at structure output
N = 30;
x = [1, zeros(1, N-1)];

% Filter implementation using MATLAB's standard direct form implementation
y = filter(b, a, x);

% Visualization
figure('Name', 'Experiment 19: Filter Realization Output', 'NumberTitle', 'off');
subplot(2,1,1);
stem(0:N-1, y, 'b', 'filled');
title('Filter Impulse Response h[n]');
xlabel('Sample Index (n)');
ylabel('Amplitude');
grid on;

subplot(2,1,2);
zplane(b, a);
title('Pole-Zero Constellation Mapping');
grid on;