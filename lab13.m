clc;
clear;
close all;

% =========================================================
%    EXPERIMENT 13: STATISTICAL MEASURES OF DISCRETE SIGNALS
% =========================================================

% 1. Generate an Asymmetric Test Signal (e.g., Exponential Decay)
% This provides non-zero values for skewness and kurtosis to test formulas effectively.
t = 0:0.05:2;
x = exp(-2*t) + 0.2*randn(size(t)); 
N = length(x);

% 2. Manual Statistical Implementations (Direct Formulas)
mu_manual    = sum(x) / N;                                 % Mean
var_manual   = sum((x - mu_manual).^2) / N;                % Variance (Biased/Population)
std_manual   = sqrt(var_manual);                           % Standard Deviation
skew_manual  = sum(((x - mu_manual) / std_manual).^3) / N; % Skewness
kurt_manual  = sum(((x - mu_manual) / std_manual).^4) / N; % Kurtosis

% 3. Built-in MATLAB Implementations
mu_builtin   = mean(x);
var_builtin  = var(x, 1);       % '1' specifies population normalization (divided by N)
std_builtin  = std(x, 1);       % '1' specifies population normalization (divided by N)
skew_builtin = skewness(x, 1);  % '1' specifies biased flag matching the standard formula
kurt_builtin = kurtosis(x, 1);  % '1' specifies biased flag matching the standard formula

% 4. Display Results and Verification
fprintf('=====================================================\n');
fprintf('%-20s | %-15s | %-15s\n', 'Metric', 'Manual Formula', 'Built-in Function');
fprintf('=====================================================\n');
fprintf('%-20s | %-15.6f | %-15.6f\n', 'Mean (\mu)', mu_manual, mu_builtin);
fprintf('%-20s | %-15.6f | %-15.6f\n', 'Variance (\sigma^2)', var_manual, var_builtin);
fprintf('%-20s | %-15.6f | %-15.6f\n', 'Std Deviation (\sigma)', std_manual, std_builtin);
fprintf('%-20s | %-15.6f | %-15.6f\n', 'Skewness (\gamma_1)', skew_manual, skew_builtin);
fprintf('%-20s | %-15.6f | %-15.6f\n', 'Kurtosis (\gamma_2)', kurt_manual, kurt_builtin);
fprintf('=====================================================\n');

% 5. Visualization and Analysis
figure('Name', 'Experiment 13: Statistical Signal Distribution', 'NumberTitle', 'off');

% Plot 1: Time Domain Signal View
subplot(2,1,1);
stem(0:N-1, x, 'b', 'filled');
hold on;
plot([0 N-1], [mu_manual mu_manual], 'r--', 'LineWidth', 2); % Draw Mean line
title('Discrete-Time Test Signal Sequence');
xlabel('Sample index (n)');
ylabel('Amplitude');
legend('Signal Samples x[n]', 'Calculated Mean (\mu)', 'Location', 'best');
grid on;

% Plot 2: Histogram Distribution View
subplot(2,1,2);
histogram(x, 10, 'FaceColor', [0.4 0.6 0.8], 'EdgeColor', 'black');
title('Sample Amplitude Distribution Histogram');
xlabel('Amplitude Range');
ylabel('Frequency Count');
grid on;