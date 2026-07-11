clc;
clear;
close all;

% =========================================================
%         EXPERIMENT 20: ENERGY AND POWER DENSITY
% =========================================================

fs = 500;
t = 0:1/fs:1;
x = 2 * sin(2*pi*15*t) + 3 * cos(2*pi*50*t);
N = length(x);

% 1. Calculate Time-Domain Total Power
total_power_time = sum(x.^2) / N;

% 2. Calculate Frequency Domain Power via FFT (Parseval's Theorem)
X_fft = fft(x);
psd = (1 / (fs * N)) * abs(X_fft).^2;
freq_axis = (0:N-1) * (fs / N);

% 3. Verification & Print
fprintf('Time-Domain Total Power:      %.4f\n', total_power_time);

% 4. Plotting
figure('Name', 'Experiment 20: Spectral Power Evaluation', 'NumberTitle', 'off');
subplot(2,1,1);
plot(t, x, 'b');
title('Time Domain Input Profile');
xlabel('Time (s)'); ylabel('Amplitude');
grid on;

subplot(2,1,2);
plot(freq_axis(1:floor(N/2)), psd(1:floor(N/2)), 'm', 'LineWidth', 1.5);
title('Power Spectral Density (PSD) Plot');
xlabel('Frequency (Hz)'); ylabel('Power / Frequency');
grid on;