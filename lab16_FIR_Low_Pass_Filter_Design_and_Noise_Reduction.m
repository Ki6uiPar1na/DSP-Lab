clc;
clear;
close all;

% =========================================================
%    EXPERIMENT 16: FIR LOW-PASS FILTER DESIGN & DENOISING
% =========================================================

% 1. Setup Signal Parameters
fs = 2000;                     % Sampling rate (2 kHz)
t = 0:1/fs:0.2;                % Time vector (200 ms duration)

% Generate clean low-frequency base tone (e.g., 10 Hz sinusoid)
f_clean = 10;
clean_signal = sin(2*pi*f_clean*t);

% Generate high-frequency noise interference (e.g., 300 Hz sinusoid)
f_noise = 300;
noise_interference = 0.4 * sin(2*pi*f_noise*t);

% Superimpose to get the noisy composite signal
noisy_signal = clean_signal + noise_interference;

% 2. Design the FIR Low-Pass Filter via Window Method
filter_order = 40;             % 40th-order filter (41 coefficients)
f_cutoff = 50;                 % Cutoff frequency at 50 Hz
Wn = f_cutoff / (fs / 2);      % Normalized cutoff frequency (Nyquist scale)

% Generate filter coefficients (uses Hamming window by default)
b = fir1(filter_order, Wn, 'low');

% 3. Filter Application (Zero-Phase Filtering to prevent group delay shifts)
filtered_signal = filtfilt(b, 1, noisy_signal);

% 4. Frequency Response Analysis
[H, f_axis] = freqz(b, 1, 512, fs);

% 5. Visualizations and Plotting
figure('Name', 'Experiment 16: FIR Low-Pass Performance', 'NumberTitle', 'off');

% Left Panel: Time Domain Waveform Denoising Performance
subplot(2,1,1);
plot(t*1000, noisy_signal, 'r', 'LineWidth', 1.0); hold on;
plot(t*1000, filtered_signal, 'b', 'LineWidth', 2.0);
plot(t*1000, clean_signal, 'k--', 'LineWidth', 1.2);
title('Time Domain Signal Comparison');
xlabel('Time (ms)');
ylabel('Amplitude');
legend('Noisy Input', 'FIR Filtered Output', 'Original Clean Reference', 'Location', 'best');
grid on;

% Right Panel: Filter Magnitude Frequency Profile
subplot(2,1,2);
plot(f_axis, 20*log10(abs(H)), 'm', 'LineWidth', 1.5); hold on;
plot([f_cutoff f_cutoff], [-60 10], 'r--', 'LineWidth', 1.2); % Mark cutoff point
title('Designed FIR Filter Frequency Response');
xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
legend('Filter Transfer Curve', 'Cutoff Boundary (50 Hz)', 'Location', 'best');
ylim([-60 5]);
grid on;