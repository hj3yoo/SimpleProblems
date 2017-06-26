function test(numiter, maxSizeExp)
% numiter: The value of Pi will be approximated with numiter iteration
% The maxSizeExp: maximum size of the seed will be 10^maxSizeExp

approxPi = zeros(1, maxSizeExp);

for i = 1:numiter
    for e = 1:maxSizeExp
        %Update the average approximation
        approxPi(e) = approxPi(e) + (MonteCarloPi(10^e) - approxPi(e)) / i; 
    end
    
    %redraw plot
    loglog(10.^(1:maxSizeExp), abs(approxPi - pi),'-bs');
    title("Approximation error of \pi using Monte Carlo method Iteration #"+i);
    xlabel("number of coordinates generated");
    ylabel("Avg. error");
    axis([1 10^maxSizeExp 10^-7 1]);
    drawnow;
end