%% convert 4 sensor arduino output (class_xx.txt) to .csv for neural net

clear all
alldata = fileread('class_10.txt');
numstr = regexp(alldata, '\d+\.?\d*','match');

A = cellfun(@str2double,numstr);

A(A == 3) = [];
A(A == 4) = [];
%A(end) = [];

B = reshape(A,[5,length(A)/5]);
C = transpose(B)

class_ref = 10;

class_col = class_ref*ones(length(C(:,1)),1)

D = [class_col transpose(B)]

%% Uncomment to display data for quick analysis

% figure(1)
% hold on
% for k = 1:5
%     plot(B(k,:))
% end
% legend()

%% output
writematrix(D,'~/Documents/HRL/testdata/class_10.csv');