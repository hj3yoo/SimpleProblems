function approxPi = MonteCarloPi(seedSize)
% Generate a random coordinate between (-1, -1) and (1, 1)
seed1 = rand([1, seedSize]) * 2 - 1;
seed2 = rand([1, seedSize]) * 2 - 1;

% Check if the coordinate fits within the circle of radius 1
% ie. check if it has a distance of 1 or less from the origin
inCircle = sqrt(seed1.^2 + seed2.^2) <= 1;

% Pi can be approximated by counting the number of points inside the circle
approxPi = sum(inCircle) / seedSize * 4;