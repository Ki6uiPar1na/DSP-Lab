clc;
clear;
close all;

% =========================================================
%       EXPERIMENT 14: CORRELATION AND COVARIANCE ANALYSIS
% =========================================================

% 1. Setup Input Signals
fs = 1000;                      % Sampling frequency (1 kHz)
t = 0:1/fs:0.1;                 % Time vector (100 ms duration)
f = 50;                         % Signal frequency (50 Hz)

% Signal x[n]: A clean reference sine wave
x = sin(2*pi*f*t);              

% Signal y[n]: A shifted version of x[n] with added White Gaussian Noise
% This simulates a radar/sonar reflection or an echo arriving with a delay.
delay_samples = 25;             % Target delay to find (25 samples = 25 ms)
y = [zeros(1, delay_samples), x(1:end-delay_samples)] + 0.5*randn(size(x));

% 2. Correlation Computation
% xcorr returns a vector of length (2*N - 1) covering both negative and positive lags
[R_xx, lags_xx] = xcorr(x, 'biased');       % Auto-correlation of x
[R_xy, lags_xy] = xcorr(x, y, 'biased');    % Cross-correlation between x and y

% 3. Time Delay Estimation
% Find the lag index where cross-correlation achieves its highest peak
[max_val, peak_idx] = max(R_xy);
estimated_delay = lags_xy(peak_idx);

fprintf('=====================================================\n');
fprintf('True Signal Delay:      %d samples\n', delay_samples);
fprintf('Estimated Delay Peak:   %d samples\n', estimated_delay);
fprintf('=====================================================\n');

% 4. Covariance Computation
% cov() computes the 2x2 covariance matrix between x and y
cov_matrix = cov(x, y);
fprintf('Computed Covariance Matrix [C_xx, C_xy; C_yx, C_yy]:\n');
disp(cov_matrix);

% 5. Visualizations and Plotting
figure('Name', 'Experiment 14: Signal Analysis via Correlation', 'NumberTitle', 'off');

% Subplot 1: Time-Domain Input Signals
subplot(3,1,1);
plot(t*1000, x, 'b', 'LineWidth', 1.5); hold on;
plot(t*1000, y, 'r', 'LineWidth', 1.0);
title('Time Domain Input Sequences');
xlabel('Time (ms)');
ylabel('Amplitude');
legend('Reference x[n]', 'Noisy Echo y[n]', 'Location', 'best');
grid on;

% Subplot 2: Auto-Correlation (Peak always at lag = 0)
subplot(3,1,2);
plot(lags_xx, R_xx, 'b', 'LineWidth', 1.5);
title('Auto-Correlation of x[n] (R_{xx})');
xlabel('Lag (samples)');
ylabel('Correlation Value');
grid on;

% Subplot 3: Cross-Correlation (Peak indicates time-of-arrival delay)
subplot(3,1,3);
plot(lags_xy, R_xy, 'm', 'LineWidth', 1.5); hold on;
plot(estimated_delay, max_val, 'ro', 'MarkerSize', 8, 'LineWidth', 2); % Peak marker
title(['Cross-Correlation (R_{xy}) - Peak Found at Lag: ' num2num(estimated_delay)]);
xlabel('Lag (samples)');
ylabel('Correlation Value');
grid on;