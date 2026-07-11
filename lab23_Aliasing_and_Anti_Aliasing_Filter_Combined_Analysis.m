clc;
clear;
close all;

% =========================================================
%         EXPERIMENT 23: FREQUENCY ALIASING DEMO
% =========================================================

% Test conditions: 60 Hz Analog Frequency modeled tightly
f_analog = 60;

% Case A: Correct Sampling (fs = 200 Hz > 2*f)
fs_high = 200;
t_high = 0:1/fs_high:0.1;
x_high = cos(2*pi*f_analog*t_high);
X_high_fft = abs(fft(x_high, 512));

% Case B: Undersampled Aliased Condition (fs = 80 Hz < 2*f)
fs_low = 80;
t_low = 0:1/fs_low:0.1;
x_low = cos(2*pi*f_analog*t_low);
X_low_fft = abs(fft(x_low, 512));

% Frequency Axes
f_axis_high = (0:511)*(fs_high/512);
f_axis_low  = (0:511)*(fs_low/512);

% Visualization
figure('Name', 'Experiment 23: Aliasing Spectral Effects', 'NumberTitle', 'off');
subplot(2,1,1);
stem(f_axis_high(1:256), X_high_fft(1:256), 'b', 'filled');
title('Spectrum Correctly Sampled (fs = 200 Hz, Peak at 60 Hz)');
xlabel('Frequency (Hz)'); ylabel('Magnitude'); grid on;

subplot(2,1,2);
stem(f_axis_low(1:256), X_low_fft(1:256), 'r', 'filled');
title('Spectrum Undersampled (fs = 80 Hz, Ghost Aliased Peak at 20 Hz)');
xlabel('Frequency (Hz)'); ylabel('Magnitude'); grid on;