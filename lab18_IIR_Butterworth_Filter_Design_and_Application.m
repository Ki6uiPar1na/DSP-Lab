clc;
clear;
close all;

% =========================================================
%       EXPERIMENT 18: IIR FILTER DESIGN COMPARISON
% =========================================================

fs = 1000;                     % Sampling frequency
f_pass = 100;                  % Passband edge frequency (Hz)
f_stop = 150;                  % Stopband edge frequency (Hz)
Rp = 1;                        % Passband ripple allowed (dB)
Rs = 40;                       % Stopband attenuation required (dB)

% Normalize frequencies to Nyquist scale
Wp = f_pass / (fs/2);
Ws = f_stop / (fs/2);

% 1. Design Butterworth Low-Pass Filter
[n_butt, Wn_butt] = buttord(Wp, Ws, Rp, Rs);
[b_butt, a_butt] = butter(n_butt, Wn_butt, 'low');

% 2. Design Chebyshev Type I Low-Pass Filter
[n_cheby, Wn_cheby] = cheb1ord(Wp, Ws, Rp, Rs);
[b_cheby, a_cheby] = cheby1(n_cheby, Rp, Wn_cheby, 'low');

% 3. Frequency Analysis
[H_butt, f] = freqz(b_butt, a_butt, 1024, fs);
[H_cheby, ~] = freqz(b_cheby, a_cheby, 1024, fs);

% 4. Visualization
figure('Name', 'Experiment 18: Butterworth vs Chebyshev', 'NumberTitle', 'off');
plot(f, 20*log10(abs(H_butt)), 'b', 'LineWidth', 1.5); hold on;
plot(f, 20*log10(abs(H_cheby)), 'r', 'LineWidth', 1.5);
title('IIR Magnitude Response Comparison');
xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
legend(['Butterworth (Order ' num2str(n_butt) ')'], ['Chebyshev Type I (Order ' num2str(n_cheby) ')']);
ylim([-60 5]);
grid on;