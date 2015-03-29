function [if_fall ] = get_if_fall(M)
%get_if_fall
% input: 
%   M -> dataset from csv file
[Ax, Ay, Az] = get_accelerations(M);
mag = get_mag(Ax, Ay, Az);
jerk = get_jerk(mag);
[Px, Py, Pz] = get_change_in_orientation(M);
P_mag = get_mag(Px, Py, Pz);

% get jerks over threshold
j_over = jerk>=0.1;
p_over = P_mag>=212;

% comparitors
if (max(j_over+p_over)>1)
    if_fall = true;
else
    if_fall = false;
end