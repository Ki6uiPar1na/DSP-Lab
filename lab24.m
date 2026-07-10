clc;
clear;
close all;

% =========================================================
%      EXPERIMENT 24: COMPLETE INTEGRATED DSP PIPELINE
% =========================================================

% Step 1: Signal Creation
fs = 1000;
t = 0:1/fs:0.5;
x_base = sin(2*pi*5*t);
x_noise = 0.5*sin(2*pi*120*t);
x_noisy = x_base + x_noise;

% Step 2: Denoise utilizing simple Moving Average FIR Structure Filter
window_size = 10;
b = ones(1, window_size) / window_size;
x_clean = filter(b, 1, x_noisy);

% Step 3: Statistical Property Extraction
mean_val = mean(x_clean);
var_val = var(x_clean);

% Step 4: FFT Transformation Mapping
X_mag = abs(fft(x_clean, 256));
freq_axis = (0:255)*(fs/256);

% Step 5: Master Visualization Display Setup
figure('Name', 'Experiment 24: End-to-End DSP Pipeline', 'NumberTitle', 'off');
subplot(3,1,1);
plot(t, x_noisy, 'r'); title('Pipeline Stage 1: Noisy Composite Signal Input');
grid on;

subplot(3,1,2);
plot(t, x_clean, 'b', 'LineWidth', 1.5); title(['Pipeline Stage 2: Filtered Output (Mean: ' num2str(mean_val, 2) ')']);
grid on;

subplot(3,1,3);
plot(freq_axis(1:128), X_mag(1:128), 'm', 'LineWidth', 1.5); title('Pipeline Stage 3: Frequency Profile Spectrum View');
xlabel('Frequency (Hz)'); grid on;