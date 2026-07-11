clc;
clear;
close all;

% =========================================================
%      EXPERIMENT 15: RANDOM SIGNAL ANALYSIS (WGN)
% =========================================================

% 1. Generate White Gaussian Noise (WGN)
fs = 1000;                      % Sampling frequency (1 kHz)
N = 1000;                       % Number of noise samples
n = 0:N-1;                      % Sample index vector
t = n/fs;                       % Time vector

% Generate noise with mean = 0 and variance = 1 (Standard WGN)
rng('default');                 % Reset random seed for reproducibility
noise = randn(1, N);            

% 2. Empirical Statistical Verification
emp_mean = mean(noise);
emp_var  = var(noise, 1);       % Population variance
emp_std  = std(noise, 1);       % Population standard deviation

fprintf('=====================================================\n');
fprintf('Statistical Parameter | Theoretical Value | Empirical\n');
fprintf('=====================================================\n');
fprintf('Mean                  |       0.0000      |   %.4f\n', emp_mean);
fprintf('Variance              |       1.0000      |   %.4f\n', emp_var);
fprintf('Std Deviation         |       1.0000      |   %.4f\n', emp_std);
fprintf('=====================================================\n');

% 3. Frequency and Spectral Properties
% Compute biased Auto-Correlation (WGN auto-correlation should be an impulse at lag 0)
[R_xx, lags] = xcorr(noise, 'biased');

% Estimate Power Spectral Density (PSD) via Periodogram
% (WGN PSD should be flat across the frequency band)
noise_fft = fft(noise);
psd = (1/(fs*N)) * abs(noise_fft).^2;
freq_axis = (0:N-1)*(fs/N);

% 4. Visualization and Plotting
figure('Name', 'Experiment 15: White Gaussian Noise Analysis', 'NumberTitle', 'off');

% Subplot 1: Time Domain Waveform
subplot(2,2,1);
plot(t, noise, 'Color', [0.3 0.3 0.3]);
title('Time Domain Waveform');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

% Subplot 2: Histogram vs. Theoretical Gaussian PDF
subplot(2,2,2);
histogram(noise, 25, 'Normalization', 'pdf', 'FaceColor', [0.4 0.6 0.8]);
hold on;
x_pdf = -4:0.1:4;
y_pdf = (1/sqrt(2*pi)) * exp(-x_pdf.^2 / 2); % Standard normal PDF formula
plot(x_pdf, y_pdf, 'r-', 'LineWidth', 2);
title('Empirical Histogram vs. PDF');
xlabel('Value');
ylabel('Density');
legend('Histogram', 'Theoretical PDF');
grid on;

% Subplot 3: Auto-Correlation Sequence
subplot(2,2,3);
plot(lags, R_xx, 'b', 'LineWidth', 1.5);
title('Auto-Correlation Sequence (R_{xx})');
xlabel('Lag (samples)');
ylabel('Correlation');
grid on;

% Subplot 4: Power Spectral Density (PSD)
subplot(2,2,4);
plot(freq_axis(1:N/2), 10*log10(psd(1:N/2)), 'm'); % One-sided spectrum in dB
title('Power Spectral Density');
xlabel('Frequency (Hz)');
ylabel('Power/Frequency (dB/Hz)');
grid on;