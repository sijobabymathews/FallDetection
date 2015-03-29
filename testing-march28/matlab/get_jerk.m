function [ jerk ] = get_jerk( mag )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

    jerk = zeros(length(mag),1);

    for i = 2:length(mag)
        jerk(i) = mag(i) - mag(i-1);
    end
end

