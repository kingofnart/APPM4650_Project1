dataFile = fopen('data.txt', 'r');
formatSpec = '%f';
A = (fscanf(dataFile, formatSpec))';
tFile = fopen('theta_fiz.txt');
theta_fiz = fscanf(tFile, formatSpec);
c = ones(1,2)*theta_fiz;
x1 = linspace(0,40,101);
x2 = linspace(0,5,13);
x3 = linspace(9,40,2);
s = (early_approx(x2));
hold on
plot(x1,A,'r','LineWidth',2)
plot(x2,s,'g--','LineWidth',2)
plot(x3,c,'b--','LineWidth',2)
title('Fizzle Graph!')
xlabel('\sigma')
ylabel('\theta')
legend('RK-4','Early Approx of \theta(\sigma)','Late Approx of \theta(\sigma)','Location','southeast')

function y = early_approx(x)
y = (1-exp(-2*x/3))/2;
end