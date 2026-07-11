clc;
clear;
close all;

% =========================================================
%         EXPERIMENT 21: LMS ADAPTIVE FILTER NOISE CANCEL
% =========================================================

N = 500;
n = 1:N;
% Primary input: Desired speech/audio model path
desired = sin(2*pi*0.02*n);

% Interference noise reference
noise_ref = randn(1, N);
% Channel distortion model path adding noise to primary node
noise_interference = filter([1, 0.5, -0.2], 1, noise_ref);
primary_signal = desired + noise_interference;

% Initialize LMS variables
filter_order = 4;
w = zeros(1, filter_order);
mu = 0.01; % LMS step-size parameter
output_y = zeros(1, N);
error_e = zeros(1, N);

% Adaptive Filtering Loop
for i = filter_order:N
    x_vector = noise_ref(i:-1:i-filter_order+1);
    output_y(i) = w * x_vector';
    error_e(i)  = primary_signal(i) - output_y(i);
    w = w + 2 * mu * error_e(i) * x_vector; % Update weights
end

% Visualization
figure('Name', 'Experiment 21: Adaptive System Output', 'NumberTitle', 'off');
subplot(3,1,1);
plot(primary_signal, 'r'); title('Noisy Combined Input Signal');
grid on;
subplot(3,1,2);
plot(error_e, 'b'); title('LMS Output Error Signal (Recovered Signal)');
grid on;
subplot(3,1,3);
plot(desired, 'k--'); title('Original Ground-Truth Reference Signal');
grid on;