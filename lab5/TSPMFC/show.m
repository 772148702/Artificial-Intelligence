
cost = load('result.out');
m = 1:length(cost);
m = m';
figure 
plot(m,cost,'r-','LineWidth', 1, 'MarkerSize', 1);
%set(gca,'xtick',[0:100:1000],'ytick',[0:20:1000])
xlabel('代数');
ylabel('每代最优解误差的百分比');