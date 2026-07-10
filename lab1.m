clc; clear; close all;

f1 = 100;  
f2 = 300; 

f_max = max(f1, f2);
fs_nyquist = 2 * f_max;   % 600 Hz

fs1 = fs_nyquist;      % Nyquist
fs2 = 2 * fs_nyquist;  % Above Nyquist
fs3 = 150;             % Below Nyquist (ALIASING)

t_end = 0.05;

% Continuous signal
t = 0:1e-5:t_end;
x = sin(2*pi*f1*t) + 0.5*cos(2*pi*f2*t);

figure;

%% 1. Original signal
subplot(4,1,1);
plot(t, x, 'k', 'LineWidth', 1.5);
title('Original Continuous Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

%% 2. Nyquist sampling (RED)
t1 = 0:1/fs1:t_end;
x1 = sin(2*pi*f1*t1) + 0.5*cos(2*pi*f2*t1);

subplot(4,1,2);
stem(t1, x1, 'r', 'filled');
title(['Nyquist Sampling (', num2str(fs1), ' Hz)']);
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

%% 3. Above Nyquist (BLUE)
t2 = 0:1/fs2:t_end;
x2 = sin(2*pi*f1*t2) + 0.5*cos(2*pi*f2*t2);

subplot(4,1,3);
stem(t2, x2, 'b', 'filled');
title(['Above Nyquist (', num2str(fs2), ' Hz)']);
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

%% 4. Below Nyquist (GREEN - ALIASING)
t3 = 0:1/fs3:t_end;
x3 = sin(2*pi*f1*t3) + 0.5*cos(2*pi*f2*t3);
subplot(4,1,4);

plot(t, x, 'k', 'LineWidth', 1.5); % continuous reference FIRST
hold on;

stem(t3, x3, 'g', 'filled');       % sampled signal

title(['Below Nyquist (', num2str(fs3), ' Hz)']);
xlabel('Time (s)');
ylabel('Amplitude');
legend('Continuous signal','Samples');
grid on;