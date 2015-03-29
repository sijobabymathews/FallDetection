function [ jerk, jerk4 ] = get_jerk( mag )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

    jerk = zeros(length(mag)-1,1);
    jerk4 = zeros(length(mag)-4,1);
    
    for i = 2:1:length(mag)
        jerk(i) = mag(i) - mag(i-1);
    end
    
    for i = 5:1:length(mag)
        jerk4(i) = mag(i) - mag(i-4);
    end
end

