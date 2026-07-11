% Problem 11: Spectrum Analysis
fs = 1000;              % Sample rate
t = 0:1/fs:1-1/fs;      % 1 second of time
% Composite signal: 50Hz and 120Hz
x_comp = sin(2*pi*50*t) + 0.5*sin(2*pi*120*t);

% Compute Magnitude Spectrum
X_mag = abs(fft(x_comp)) / (length(t)/2);
f_axis = (0:length(t)-1) * (fs/length(t));

figure;
plot(f_axis(1:fs/2), X_mag(1:fs/2)); % Plot only positive frequencies
title('Frequency Spectrum');
xlabel('Frequency (Hz)'); ylabel('Magnitude');
grid on;