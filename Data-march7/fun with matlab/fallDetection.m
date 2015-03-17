% Load data from Melissa Fall back 1
M = load('fall1R.csv');
f_Ax = M(:,1)*2/32756;
f_Ay = M(:,2)*2/32756;
f_Az = M(:,3)*2/32756;
f_A_mag = sqrt(f_Ax.^2 + f_Ay.^2 +f_Az.^2);
f_jerk = zeros(length(f_A_mag),1);

for i = 2:length(f_A_mag)
    f_jerk(i) = f_A_mag(i) - f_A_mag(i-1);
end
M = load('ADL.csv');
Ax = M(:,1)*2/32756;
Ay = M(:,2)*2/32756;
Az = M(:,3)*2/32756;
A_mag = sqrt(Ax.^2 + Ay.^2 +Az.^2);
jerk = zeros(length(A_mag),1);

for i = 2:length(A_mag)
    jerk(i) = A_mag(i) - A_mag(i-1);
end

boxplot([f_jerk, jerk]);