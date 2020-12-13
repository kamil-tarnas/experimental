precodingMatrix = [1 0 j 0; 0 -1 0 j; 0 1 0 j; 1 0 -j 0]
coefficient = 1/sqrt(2)
x = 0:0.01:4.0*pi % two periods for sin
re = cos(x)
im = sin(x)

plot(x, re, "color","blue")
hold on
plot(x, im, "color","red")

% sample a sin function
