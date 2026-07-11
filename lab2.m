clc;
clear;
close all;

% =========================================================
%                  ORIGINAL SIGNAL DEFINITION
% =========================================================
n = 0:3;
x = [1 2 3 4];

figure(1);
stem(n, x, 'filled', 'LineWidth', 1.5);
title('Original Signal x[n]');
xlabel('n');
ylabel('Amplitude');
grid on;
axis([-4 7 0 5]);

% =========================================================
%         1. TIME DELAY: x[n - 2] (Shift Right by 2)
% =========================================================
nd = n + 2; % Shift the time axis right: 2 to 5
xd = x;     % Signal amplitudes stay identical

figure(2);
stem(nd, xd, 'filled', 'LineWidth', 1.5);
title('Time Delay x[n - 2]');
xlabel('n');
ylabel('Amplitude');
grid on;
axis([-4 7 0 5]);

% =========================================================
%        2. TIME ADVANCE: x[n + 1] (Shift Left by 1)
% =========================================================
na = n - 1; % Shift the time axis left: -1 to 2
xa = x;     % Signal amplitudes stay identical

figure(3);
stem(na, xa, 'filled', 'LineWidth', 1.5);
title('Time Advance x[n + 1]');
xlabel('n');
ylabel('Amplitude');
grid on;
axis([-4 7 0 5]);

% =========================================================
%         3. TIME REVERSAL: x[-n] (Reflection)
% =========================================================
nr = -fliplr(n); % Flip time axis signs and order: -3 to 0
xr = fliplr(x);  % Reverse amplitude tracking order

figure(4);
stem(nr, xr, 'filled', 'LineWidth', 1.5);
title('Time Reversal x[-n]');
xlabel('n');
ylabel('Amplitude');
grid on;
axis([-4 7 0 5]);

% =========================================================
%         4. TIME COMPRESSION: x[2n] (Downsampling)
% =========================================================
% Keeps every 2nd sample: n=0 (val=1), n=2 (val=3)
nc = 0:floor(max(n)/2); 
xc = x(1:2:end); 

figure(5);
stem(nc, xc, 'filled', 'LineWidth', 1.5);
title('Compression x[2n]');
xlabel('n');
ylabel('Amplitude');
grid on;
axis([-4 7 0 5]);

% =========================================================
%         5. TIME EXPANSION: x[n/2] (Upsampling)
% =========================================================
% Inserts zeros between original samples
ne = 0:(2 * max(n));          % Expanded axis: 0 to 6
xe = zeros(1, length(ne));    % Initialize zero vector
xe(1:2:end) = x;              % Place original values at even slots (0, 2, 4, 6)

figure(6);
stem(ne, xe, 'filled', 'LineWidth', 1.5);
title('Expansion x[n/2]');
xlabel('n');
ylabel('Amplitude');
grid on;
axis([-4 7 0 5]);
