clc;
clear;
close all;

n = -10:10;

u = double(n >= 0);
delta = double(n == 0);
ramp = n .* (n >= 0);
t = 0:0.01:1;
f = 5;
sine_wave = sin(2*pi*f*t);
cos_wave = cos(2*pi*f*t);

figure(1);
stem(n, u, "filled");
grid on;

figure(2);
stem(n, delta);
grid on;

figure(3);
stem(n, ramp);
grid on;


figure(4);
plot(t, sine_wave);
grid on;
