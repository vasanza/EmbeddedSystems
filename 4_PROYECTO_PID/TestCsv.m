00T = csvread('Datos.csv',1,0);
%quitar la primera fila que tiene los fieldnames
title('Datos CSV');
figure;
plot(T(:,1),T(:,2));
hold on;
plot(T(:,1),T(:,3));
legend('input','output');

