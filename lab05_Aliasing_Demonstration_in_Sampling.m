% Aliasing Demonstration - Corrected
clear; clc; close all;

% 1. Setup Frequencies
f_sig = 60;             % Original Signal Frequency (60 Hz)
fs = 70;                % Sampling Frequency (70 Hz - Below Nyquist!)

% 2. Create the "Continuous" Reference
% We use a very tiny time step (0.0001) to make it look smooth
t_fine = 0:0.0001:0.1;  
x_cont = sin(2*pi*f_sig * t_fine);

% 3. Create the Sampled Signal
% This represents what the computer "sees" after sampling
t_samp = 0:1/fs:0.1;    
x_samp = sin(2*pi*f_sig * t_samp);

% 4. Calculate the "Alias" Frequency
% The perceived frequency is the difference between signal and sample rate
f_alias = abs(f_sig - fs); 
x_alias = sin(2*pi*f_alias * t_fine);

% --- Plotting ---
figure('Color', 'w', 'Name', 'Aliasing Demonstration');

% Plot 1: The fast original signal (Light Gray)
plot(t_fine, x_cont, 'Color', [0.7 0.7 0.7], 'LineWidth', 1); 
hold on;

% Plot 2: The actual samples taken (Red Dots)
stem(t_samp, x_samp, 'filled', 'r', 'LineWidth', 1.5);

% Plot 3: The "Ghost" Alias wave (Blue Dashed)
% This shows how the dots create a fake low-frequency signal
plot(t_fine, x_alias, 'b--', 'LineWidth', 2);

% --- Formatting ---
title(['Aliasing: ', num2str(f_sig), 'Hz Signal sampled at ', ...
    num2str(fs), 'Hz looks like ', num2str(f_alias), 'Hz']);
xlabel('Time (seconds)');
ylabel('Amplitude');
legend('Original 60Hz Signal', 'Samples (70Hz)', 'Perceived 10Hz Alias');
grid on;