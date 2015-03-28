function [ Ax, Ay, Az ] = get_accelerations( M )

Ax = M(:,1)*2/32756;
Ay = M(:,2)*2/32756;
Az = M(:,3)*2/32756;

end

