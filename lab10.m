clc;
clear;
close all;

% =========================================================
%  EXPERIMENT 10: DISCRETE FOURIER TRANSFORM (DFT) COMPARISON
% =========================================================

% 1. Define Test Signal Parameters
N = 64;                                    % Number of samples (DFT points)
n = 0:N-1;                                 % Discrete time index vector
f1 = 5;                                    % First frequency component (Hz)
f2 = 12;                                   % Second frequency component (Hz)
x = sin(2*pi*f1*n/N) + 0.5*sin(2*pi*f2*n/N); % Composite test signal

% 2. Manual DFT Implementation (Direct Mathematical Summation)
X_manual = zeros(1, N);
for k = 0:N-1
    for n_idx = 0:N-1
        X_manual(k+1) = X_manual(k+1) + x(n_idx+1) * exp(-1j*2*pi*k*n_idx/N);
    end
end

% 3. Built-in FFT Implementation (Fast Fourier Transform)
X_fft = fft(x);

% 4. Verify Numerical Equivalence
max_diff = max(abs(X_manual - X_fft));
fprintf('Maximum absolute difference: %e\n', max_diff);

% 5. Visualization and Plotting
figure('Name', 'Experiment 10: DFT vs FFT Comparison', 'NumberTitle', 'off');

% Top Plot: Original Input Signal
subplot(3,1,1);
plot(n, x, 'b.-', 'LineWidth', 1.5);
title('Original Test Signal x[n]');
xlabel('Sample index (n)');
ylabel('Amplitude');
grid on;

% Middle Plot: Manual DFT Spectrum
subplot(3,1,2);
stem(n, abs(X_manual), 'r', 'filled');
title('Magnitude Spectrum (Manual DFT Implementation)');
xlabel('Frequency bin (k)');
ylabel('|X[k]|');
grid on;

% Bottom Plot: Built-in FFT Spectrum
subplot(3,1,3);
stem(n, abs(X_fft), 'm', 'filled');
title('Magnitude Spectrum (Built-in FFT Routine)');
xlabel('Frequency bin (k)');
ylabel('|X[k]|');
grid on;