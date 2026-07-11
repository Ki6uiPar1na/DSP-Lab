clc;
clear;
close all;

% =========================================================
%    EXPERIMENT 17: FIR HIGH-PASS FILTER DESIGN & FILTERING
% =========================================================

% 1. Setup Signal Parameters
fs = 1000;                     % Sampling rate (1 kHz)
t = 0:1/fs:1;                  % Time vector (1 second duration)

% Generate clean high-frequency signal (e.g., 60 Hz tone)
f_signal = 60;
clean_signal = sin(2*pi*f_signal*t);

% Generate low-frequency baseline wander drift (e.g., 1.5 Hz drift)
f_drift = 1.5;
drift = 1.5 * sin(2*pi*f_drift*t);

% Superimpose to form the drifted signal
drifted_signal = clean_signal + drift;

% 2. Design the FIR High-Pass Filter via Window Method
filter_order = 60;             % 60th-order filter
f_cutoff = 10;                 % Cutoff frequency at 10 Hz
Wn = f_cutoff / (fs / 2);      % Normalized cutoff frequency

% Generate high-pass filter coefficients
b = fir1(filter_order, Wn, 'high');

% 3. Filter Application (Zero-Phase Filtering)
filtered_signal = filtfilt(b, 1, drifted_signal);

% 4. Visualization
figure('Name', 'Experiment 17: High-Pass Filtering', 'NumberTitle', 'off');

subplot(2,1,1);
plot(t, drifted_signal, 'r', 'LineWidth', 1.0); hold on;
plot(t, filtered_signal, 'b', 'LineWidth', 1.5);
title('Time Domain Signal: Baseline Wander Removal');
xlabel('Time (s)');
ylabel('Amplitude');
legend('Drifted Input', 'High-Pass Filtered Output', 'Location', 'best');
grid on;

subplot(2,1,2);
[H, f_axis] = freqz(b, 1, 512, fs);
plot(f_axis, 20*log10(abs(H)), 'm', 'LineWidth', 1.5);
title('Designed High-Pass Filter Magnitude Response');
xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
grid on;