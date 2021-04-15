clear;
clc;
TF=load('FTmotor.mat');
TF=TF.FTmotor;
ADCATmega328=10;%input
%% Open Loop
num=cell2mat(TF.numerator);
den=cell2mat(TF.denominator);
G=tf(num,den)

t = 0:1e-3:100;       % time vector
u = ones(length(t),1)*ADCATmega328; % unit step input vector
y = lsim(G,u,t);       % system response  
figure;
plot(t,y);
%% Test PID control
%load('C.mat')
Tref = getPIDLoopResponse(C,G,"closed-loop");
hold on;
y1 = lsim(Tref*mean(y),u/ADCATmega328,t);       % system response  
plot(t,y1);
legend("Open Loop","Closed Loop");