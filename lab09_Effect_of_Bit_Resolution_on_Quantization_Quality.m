% Problem 9: Bit Resolution Comparison
bits = [2, 4, 8];
figure;
for i = 1:3
    L = 2^bits(i);
    step = (max(x) - min(x)) / (L - 1);
    xq = round(x / step) * step;

    subplot(3, 1, i);
    plot(t, x, 'k--'); hold on;
    plot(t, xq, 'r');
    title([num2str(bits(i)), '-Bit Resolution (', num2str(L), ' levels)']);
    grid on;
end