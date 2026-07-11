% Parameters
f = 10;               % Signal frequency (10 Hz)
fs_nyquist = 2 * f;   % Nyquist Rate (20 Hz)
t_cont = 0:0.001:0.5; % "Continuous" time for reference
x_cont = sin(2*pi*f*t_cont);

% 1. Above Nyquist (fs = 100 Hz)
fs_above = 100;
n_above = 0:1/fs_above:0.5;
x_above = sin(2*pi*f*n_above);

% 2. At Nyquist (fs = 20 Hz)
fs_at = 20;
n_at = 0:1/fs_at:0.5;
x_at = sin(2*pi*f*n_at);

% 3. Below Nyquist (fs = 12 Hz) - Expect Aliasing!
fs_below = 12;
n_below = 0:1/fs_below:0.5;
x_below = sin(2*pi*f*n_below);

% --- Plotting ---
figure('Name', 'Sampling and Aliasing');

% Plot 1: Above Nyquist
subplot(3, 1, 1);
plot(t_cont, x_cont, 'k--'); hold on;
stem(n_above, x_above, 'filled', 'b');
title('Over-sampling (Above Nyquist): Excellent Reconstruction');
grid on;

% Plot 2: At Nyquist
subplot(3, 1, 2);
plot(t_cont, x_cont, 'k--'); hold on;
stem(n_at, x_at, 'filled', 'g');
title('Critical Sampling (At Nyquist): Minimum Information');
grid on;

% Plot 3: Below Nyquist
subplot(3, 1, 3);
plot(t_cont, x_cont, 'k--'); hold on;
stem(n_below, x_below, 'filled', 'r');
plot(n_below, x_below, 'r:'); % Draw the "fake" alias wave
title('Under-sampling (Below Nyquist): Aliasing Occurs!');
grid on;