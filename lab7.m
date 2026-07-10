% Problem 7: Uniform Quantizer
t = 0:0.001:0.1;
x = sin(2*pi*20*t); % Input sine wave

% Quantization Logic (e.g., 8 levels)
levels = 8;
x_min = -1; x_max = 1;
q_step = (x_max - x_min) / (levels - 1);
x_quant = round(x / q_step) * q_step;

figure;
plot(t, x, 'b'); hold on;
plot(t, x_quant, 'r', 'LineWidth', 1.5);
title('Uniform Quantization (8 Levels)');
legend('Analog Signal', 'Quantized Signal');
grid on;