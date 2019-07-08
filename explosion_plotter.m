dataFile = fopen('exp_data.txt', 'r');
formatSpec = '%f';
A = (fscanf(dataFile,formatSpec))';
sFile = fopen('sigma_exp.txt');
sigma_exp = fscanf(sFile,formatSpec);
x1 = linspace(0,20,101);
x2 = linspace(0,1,2);
x3 = linspace(1,20,100);
s = early_approx(x2);
c = late_approx(x3, sigma_exp);
hold on
plot(x1,A,'r','LineWidth',2)
plot(x2,s,'g--','LineWidth',2)
plot(x3,c,'b--','LineWidth',2)
title('Explosion Graph!')
xlabel('\theta')
ylabel('\sigma')
legend('RK-4','Early Approx of \sigma(\theta)','Late Approx of \sigma(\theta)','Location','southeast')
hold off

function y = early_approx(x)
y = x;
end

function y = late_approx(x, sigma_exp)
y = sigma_exp-exp(-x);
end