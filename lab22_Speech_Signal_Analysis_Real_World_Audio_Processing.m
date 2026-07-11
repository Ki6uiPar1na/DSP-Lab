clc;
clear;
close all;

% =========================================================
%    EXPERIMENT 22: SPEECH SIGNAL PROCESSING ANALYSIS
% =========================================================

% Simulate a vocal frame speech profile sequence
fs = 8000;
t = 0:1/fs:0.5;
speech = sin(2*pi*150*t) .* exp(-10*(t-0.25).^2) + 0.05*randn(size(t));

% Short-Time Energy Window Processing Frame variables
frame_len = floor(0.03 * fs); % 30 ms frame length
hop_size = floor(0.015 * fs); % 15 ms stride overlap
num_samples = length(speech);

num_frames = floor((num_samples - frame_len) / hop_size) + 1;
ste = zeros(1, num_frames);

for f_idx = 1:num_frames
    start_sample = (f_idx-1) * hop_size + 1;
    end_sample = start_sample + frame_len - 1;
    frame = speech(start_sample:end_sample);
    ste(f_idx) = sum(frame.^2); % Calculate Energy
end

% Visualization
figure('Name', 'Experiment 22: Short-Time Analysis', 'NumberTitle', 'off');
subplot(2,1,1);
plot(t, speech, 'b'); title('Synthesized Speech Audio Waveform');
xlabel('Time (s)'); ylabel('Amplitude'); grid on;

subplot(2,1,2);
plot(1:num_frames, ste, 'r', 'LineWidth', 1.5); title('Short-Time Energy (STE) Profile Tracking');
xlabel('Frame Index'); ylabel('Energy'); grid on;