function [ ] = get_plot_stuff( M, num, t)
%get_plot_stuff
% input: 
%   M -> dataset from csv file
%   num -> figure numbers
%   t -> title of fall
[Ax, Ay, Az] = get_accelerations(M);
mag = get_mag(Ax, Ay, Az);
jerk = get_jerk(mag);
[Px, Py, Pz] = get_change_in_orientation(M);
P_mag = get_mag(Px, Py, Pz);

len = length(jerk);

figure(num)
X = 1:1:len;
hold on;
plot(X, P_mag, 'm');
plot ([0 len], [ 212 212], 'b');
title(t);
xlabel('Time (1/3 of second)');
ylabel('Change in Orientation(deg/sec)');
legend('\Delta Orientation', 'Threshold');
hold off;

figure(num+100)
X = 1:1:len;
hold on;
plot(X, jerk, 'm');
plot ([0 len], [0.1 0.1], 'b');
plot ([0 len], [-0.1 -0.1], 'b');
title(t);
xlabel('Time (1/3 of second)');
ylabel('Jerk (m/s^2)');
legend('Jerk', 'Threshold');
hold off;
end

