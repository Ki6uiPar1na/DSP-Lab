% Problem 12: STFT (Spectrogram) Analysis
fs = 1000;              % Sampling frequency (1000 Hz)
t = 0:1/fs:2;           % 2 seconds of time

% --- 1. Stationary Signal (Constant 100 Hz) ---
x_stat = sin(2*pi*100*t);

% --- 2. Non-Stationary Signal (Chirp: 50 Hz to 400 Hz) ---
% A "chirp" is a signal where frequency increases over time
x_nonstat = chirp(t, 50, 2, 400); 

% --- Plotting ---
figure('Color', 'w');

% Plot Stationary Spectrogram
subplot(2, 1, 1);
spectrogram(x_stat, 256, 250, 256, fs, 'yaxis');
title('Spectrogram of Stationary Signal (Constant 100Hz)');
colorbar;

% Plot Non-Stationary Spectrogram
subplot(2, 1, 2);
spectrogram(x_nonstat, 256, 250, 256, fs, 'yaxis');
title('Spectrogram of Non-Stationary Signal (Chirp 50Hz to 400Hz)');
colorbar;