function [  Px, Py, Pz ] = get_change_in_orientation( M )
Px = M(:,4)*250/32756;
Py = M(:,5)*250/32756;
Pz = M(:,6)*250/32756;

end

