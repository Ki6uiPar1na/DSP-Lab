% Problem 6: Reconstruction
fs = 50;                  % Sampling frequency
t_samples = 0:1/fs:0.2;   % Sampled time
x_samples = sin(2*pi*10*t_samples); % 10Hz Signal

% Reconstruction using Linear Interpolation
t_fine = 0:0.001:0.2;
x_recon = interp1(t_samples, x_samples, t_fine, 'linear');

figure;
plot(t_fine, sin(2*pi*10*t_fine), 'k--'); hold on; % Original
stem(t_samples, x_samples, 'r', 'filled');       % Samples
plot(t_fine, x_recon, 'b', 'LineWidth', 1.5);    % Reconstructed
title('Signal Reconstruction via Interpolation');
legend('Original', 'Samples', 'Reconstructed');
grid on;