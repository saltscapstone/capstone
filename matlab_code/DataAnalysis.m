clear;
clf;
file = 'TNK2.mat';
ansrawdata = open(file);
rawdata = ansrawdata.output;

dr = 2E9; %sample rate

totalfft = abs(fft(rawdata(:,2)));
totalfft = totalfft(1:round(end/2));
totalfft =(totalfft/length(totalfft));
totalxvals = (dr/2)*linspace(0,1,length(totalfft));

%ghetto spectrogram
lines = 10;
pointsper = round(length(rawdata(1:500,2))/lines);
for n = 1:lines
   arrayfft(n,:) = abs(fft(rawdata((n-1)*pointsper+1:n*pointsper)));
end
arrayfft = arrayfft(:,1:round(end/2));
arrayfft = (arrayfft/length(arrayfft(1,:)));
arrayxvals = (dr/2)*linspace(0,1,length(arrayfft(1,:)));

%frequency stuff
tmax = .0005;
t = 0:1/dr:tmax;
freqno = 10;
f = linspace(50000,70000,freqno);
sig = cos(2*pi.*f'*t);
for i = 1:freqno
    freqresp(i,:) = conv(rawdata(1:5000,2),sig(i,:));
end
freqrespxvals = (1/dr:1/dr:length(freqresp(1,:))/dr);

subplot(4,1,1)
plot(rawdata(:,1), rawdata(:,2));
title('h')
subplot(4,1,2)
plot(totalxvals, totalfft);
title('FFT of h')
axis([0, 1E5, 0, .05]);
ylim('auto');
subplot(4,1,3)
hold on
for n = 1:lines
    plot(arrayxvals, arrayfft(n,:));
end
axis([0, 1E5, 0, .05]);
ylim('auto');
subplot(4,1,4)
plot(freqrespxvals', freqresp')
axis([.995*tmax, 1.005*tmax, -100, 100])
ylim('auto')