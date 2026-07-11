% Problem 8: Quantization Error
error_sig = x - x_quant;
mse = mean(error_sig.^2);

figure;
subplot(2,1,1);
plot(t, error_sig, 'm');
title(['Quantization Error (Noise). MSE = ', num2str(mse)]);
grid on;

subplot(2,1,2);
histogram(error_sig, 20);
title('Error Distribution');