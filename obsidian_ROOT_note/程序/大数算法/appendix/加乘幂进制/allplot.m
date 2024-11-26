%% noname
x = -2:2;

y1 = 1 + x + x .^ 2;
y2 = 1 + 3 .* x + x .^ 2;
y3 = 1 + 4 .* x + 5 .* x .^ 2 + 4 .* x .^ 3 + x .^ 4;

x0 = -3.5:0.001:2.5;

y01 = 1 + x0 + x0 .^ 2;
y02 = 1 + 3 .* x0 + x0 .^ 2;
y03 = 1 + 4 .* x0 + 5 .* x0 .^ 2 + 4 .* x0 .^ 3 + x0 .^ 4;
figure(Color='k')
tiledlayout(1, 3)
nexttile
scatter(x, y1, 'filled', Color = '#845ec2')
hold on
plot(x0, y01, Color = '#845ec2', LineWidth = 1.0)
xlabel("$f(x)=1+x+x^2$", "Interpreter", "latex")
ax1 = gca;
ax1.Color = 'k';
ax1.XColor = 'w'; % 设置 x 轴颜色为白色  
ax1.YColor = 'w'; % 设置 y 轴颜色为白色  
ax1.ZColor = 'w'; % 设置 z 轴颜色为白色  
nexttile
scatter(x, y2, 'filled', Color = '#c34a36')
hold on
plot(x0, y02, Color = '#c34a36', LineWidth = 1)
xlabel("$g(x)=1+3x+x^2$", "Interpreter", "latex")
ax2 = gca;
ax2.Color = 'k';
ax2.XColor = 'w'; % 设置 x 轴颜色为白色  
ax2.YColor = 'w'; % 设置 y 轴颜色为白色  
ax2.ZColor = 'w'; % 设置 z 轴颜色为白色  
nexttile
scatter(x, y3, 'filled', Color = '#00c9a7')
hold on
plot(x0, y03, Color = '#00c9a7', LineWidth = 1)
xlabel("$f\cdot g(x)=1+4x+5x^2+4x^3+x^4$", "Interpreter", "latex")
ax3 = gca;
ax3.Color = 'k';
ax3.XColor = 'w'; % 设置 x 轴颜色为白色  
ax3.YColor = 'w'; % 设置 y 轴颜色为白色  
ax3.ZColor = 'w'; % 设置 z 轴颜色为白色  
clc,clear
%% FFT算法和普通乘法的比较
% 原始数据
clc,clear
time = [5.15e-05  2.29e-05
        5.63e-05  4.1e-05
        9.79e-05  0.0001709
        0.0002005  0.0005055
        0.0005872  0.0032638
        0.0012288  0.0130467
        0.0027013  0.0588864
        0.0053059  0.21249
        0.0100813  0.854725
        0.0214199  3.60004
        0.0423809  14.9355
        0.0945868  59.9784
        0.192964  241.005
        0.347598  1007.06];

time(:,3) = [3.53e-05
            1.69e-05
            2.75e-05
            5.14e-05
            0.0001083
            0.0002351
            0.0005115
            0.0011597
            0.0026408
            0.0056722
            0.0125836
            0.0260346
            0.055025
            0.119687];
time1 = time(:, 1);time2 = time(:, 2);time3=time(:,3);
num = length(time);
t = 2:num + 1;

% 创建图形
figure(Color='k');
% 绘制数据
scatter(t, log10(time1), 80, 'filled', 'MarkerFaceColor', '#1f77b4', 'MarkerEdgeColor', 'k');
hold on
plot(t, log10(time1), 'Color', '#1f77b4', 'LineWidth', 2);

scatter(t, log10(time2), 80, 'filled', 'MarkerFaceColor', '#ff7f0e', 'MarkerEdgeColor', 'k');
hold on
plot(t, log10(time2), 'Color', '#ff7f0e', 'LineWidth', 2);

scatter(t, log10(time3), 80, 'filled', 'MarkerFaceColor', '#2ca02c', 'MarkerEdgeColor', 'k');
hold on
plot(t, log10(time3), 'Color', '#2ca02c', 'LineWidth', 2);


% 设置坐标轴标签
xlabel('log$_{2} l$', 'Interpreter', 'latex', 'FontSize', 14);
ylabel('log$_{10} t$', 'Interpreter', 'latex', 'FontSize', 14);

% 设置标题
title('运行时间和数组长度的对数关系', 'FontSize', 16, 'FontWeight', 'bold');

% 添加图例
legend({'$t_1$', '$t_1$', '$t_2$', '$t_2$','$t_3$', '$t_3$'}, 'Interpreter', 'latex', 'FontSize', 12, 'Location', 'NorthWest');

% 优化坐标轴
grid on; % 加入网格
% 设置坐标轴颜色  
ax = gca;   
ax.XColor = 'w'; % 设置 x 轴颜色为白色  
ax.YColor = 'w'; % 设置 y 轴颜色为白色  
ax.ZColor = 'w'; % 设置 z 轴颜色为白色  

ax.FontSize = 12; % 坐标轴字体大小
xlim([1 num + 2]); % 设置x轴范围
ylim([min(log10(time(:))) - 0.5, max(log10(time(:))) + 0.5]); % 设置y轴范围

% 美化背景和边框
set(gca, 'Color', 'k'); % 设置背景为白色
box on; % 显示边框

% 调整窗口大小
set(gcf, 'Units', 'Normalized', 'Position', [0.1, 0.1, 0.8, 0.6]);

% zp = BaseZoom();
% zp.run();

%% 两种FFT的比较
clc,clear
% 原始数据
time = [5.83e-05  2.02e-05
        7.78e-05  1.63e-05
        0.0001431  2.64e-05
        0.0002891  5.32e-05
        0.0005865  0.0001106
        0.0011849  0.000229
        0.0023656  0.0004932
        0.0048099  0.0011071
        0.0097873  0.0024233
        0.0197357  0.0053013
        0.0455701  0.0125612
        0.0861035  0.0250461
        0.186795  0.0546579
        0.348621  0.118942
        0.735378  0.260676
        1.44339  0.58597
        3.03761  1.12802
        6.10756  2.47913
        12.5192  5.91147
        25.5337  11.0323
        50.7693  23.4071];

time1 = time(:, 1); time2 = time(:, 2); 
num = length(time);
t = 2:num + 1;

% 创建图形
figure(Color='k');
% 绘制数据
scatter(t, log10(time1), 80, 'filled', 'MarkerFaceColor', '#1f77b4', 'MarkerEdgeColor', 'k');
hold on
plot(t, log10(time1), 'Color', '#1f77b4', 'LineWidth', 2);

scatter(t, log10(time2), 80, 'filled', 'MarkerFaceColor', '#ff7f0e', 'MarkerEdgeColor', 'k');
hold on
plot(t, log10(time2), 'Color', '#ff7f0e', 'LineWidth', 2);
hold on
ax = gca;
ax.FontSize = 12; % 坐标轴字体大小  
ax.Color = 'k'; % 设置坐标轴背景颜色为黑色  
ax.XColor = 'w'; % 设置 x 轴颜色为白色  
ax.YColor = 'w'; % 设置 y 轴颜色为白色  
ax.ZColor = 'w'; % 设置 z 轴颜色为白色  

% 设置坐标轴标签
xlabel('log$_{2} l$', 'Interpreter', 'latex', 'FontSize', 14);
ylabel('log$_{10} t$', 'Interpreter', 'latex', 'FontSize', 14);

% 设置标题
title('运行时间和数组长度的对数关系', 'FontSize', 16, 'FontWeight', 'bold');


% 优化坐标轴
grid on; % 加入网格

xlim([1 num + 2]); % 设置x轴范围
ylim([min(log10(time(:))) - 0.5, max(log10(time(:))) + 0.5]); % 设置y轴范围

box on; % 显示边框

% 调整窗口大小
set(gcf, 'Units', 'Normalized', 'Position', [0.1, 0.1, 0.8, 0.6]);

x = 2^t(1,1):0.5:2^t(1,end);
y1 = 10^(-6).*x.*log(x);
plot(log2(x), log10(y1), 'Color', '#2ca02c', 'LineWidth', 1.5,'LineStyle','--');
x = 2^t(1,1):0.1:2^t(1,end);
y1 = 10^(-6.5).*x.*log(x);
plot(log2(x), log10(y1), 'Color', '#2ca02c', 'LineWidth', 1.5,'LineStyle','--');

% 添加图例
legend({'t$_1$', 't$_1$', 't$_2$', 't$_2$', 'Asymptotic line$_1$','Asymptotic line$_2$'}, ...
    'Interpreter', 'latex', 'FontSize', 12, 'Location', 'NorthWest');

% 
% zp = BaseZoom();
% zp.run();

%% MSVC和gcc编译器的朴素乘法和FFT乘法的对比
clc,clear
time_msvc1 = readmatrix("D:\NoteBook\obsidian_note\obsidian_ROOT_note\程序\大数算法\appendix\加乘幂进制\CSVfile\timeMSVCpl.csv");
time_msvc2 = readmatrix("D:\NoteBook\obsidian_note\obsidian_ROOT_note\程序\大数算法\appendix\加乘幂进制\CSVfile\timeMSVCfft.csv");
range_msvc = 10:10:1000;
time_gcc1 = readmatrix("D:\NoteBook\obsidian_note\obsidian_ROOT_note\程序\大数算法\appendix\加乘幂进制\CSVfile\timeGccpl.csv");
time_gcc2 = readmatrix("D:\NoteBook\obsidian_note\obsidian_ROOT_note\程序\大数算法\appendix\加乘幂进制\CSVfile\timeGccfft.csv");

range_gcc = 50:50:5000;
len = length(time_msvc2);

colors = ["#ed4545";"#0059cb"];

figure(Color='k')
for i=1:len
    scatter3(range_msvc,range_msvc(i).*ones(1,len),time_msvc1(i,:),1,'filled','MarkerEdgeColor',colors(1),'MarkerFaceColor',colors(1))
    hold on 
    scatter3(range_msvc,range_msvc(i).*ones(1,len),time_msvc2(i,:),1,'filled','MarkerEdgeColor',colors(2),'MarkerFaceColor',colors(2))
    hold on 
end
ax = gca;   
ax.Color = 'k'; % 设置坐标轴背景颜色为黑色  
ax.XColor = 'w'; % 设置 x 轴颜色为白色  
ax.YColor = 'w'; % 设置 y 轴颜色为白色  
ax.ZColor = 'w'; % 设置 z 轴颜色为白色  
xlabel('len', 'Color', 'w', 'FontName', 'Times New Roman'); % 设置标签字体颜色为白色  
ylabel('len', 'Color', 'w', 'FontName', 'Times New Roman');  
zlabel('time', 'Color', 'w', 'FontName', 'Times New Roman');  
legend({'朴素乘法','FFT乘法'},"Color",'k','Location','northwest','TextColor','w')
set(gcf, 'Units', 'Normalized', 'Position', [0.15, 0.15, 0.6, 0.7]);


figure(Color='k')
for i=1:len
    scatter3(range_gcc,range_gcc(i).*ones(1,len),time_gcc1(i,:),1,'filled','MarkerEdgeColor',colors(1),'MarkerFaceColor',colors(1))
    hold on 
    scatter3(range_gcc,range_gcc(i).*ones(1,len),time_gcc2(i,:),1,'filled','MarkerEdgeColor',colors(2),'MarkerFaceColor',colors(2))
    hold on 
end
ax = gca;   
ax.Color = 'k'; % 设置坐标轴背景颜色为黑色  
ax.XColor = 'w'; % 设置 x 轴颜色为白色  
ax.YColor = 'w'; % 设置 y 轴颜色为白色  
ax.ZColor = 'w'; % 设置 z 轴颜色为白色  
xlabel('len', 'Color', 'w', 'FontName', 'Times New Roman'); % 设置标签字体颜色为白色  
ylabel('len', 'Color', 'w', 'FontName', 'Times New Roman');  
zlabel('time', 'Color', 'w', 'FontName', 'Times New Roman');  
legend({'朴素乘法','FFT乘法'},"Color",'k','Location','northwest','TextColor','w')
set(gcf, 'Units', 'Normalized', 'Position', [0.15, 0.15, 0.6, 0.7]);


%% 幂运算
clc,clear
time1 = readmatrix("D:\NoteBook\obsidian_note\obsidian_ROOT_note\程序\大数算法\appendix\加乘幂进制\CSVfile\pow2time_1.csv");
time2 = readmatrix("D:\NoteBook\obsidian_note\obsidian_ROOT_note\程序\大数算法\appendix\加乘幂进制\CSVfile\pow2time_2.csv");
time3 = readmatrix("D:\NoteBook\obsidian_note\obsidian_ROOT_note\程序\大数算法\appendix\加乘幂进制\CSVfile\pow2time_3.csv");

time1_log = log2(time1);
time2_log = log2(time2);
time3_log = log2(time3);
index = 10:1000:(199*1000+10);
colors = ["#e8ef53";"#00e8ff";"#ff6f8f"];


figure(Color='k')
scatter(index,time1_log,3,'filled','MarkerEdgeColor',colors(1),'MarkerFaceColor',colors(1))
hold on
scatter(index,time2_log,3,'filled','MarkerEdgeColor',colors(2),'MarkerFaceColor',colors(2))
hold on
scatter(index,time3_log,3,'filled','MarkerEdgeColor',colors(3),'MarkerFaceColor',colors(3))
hold on

ax = gca;   
ax.Color = 'k'; % 设置坐标轴背景颜色为黑色  
ax.XColor = 'w'; % 设置 x 轴颜色为白色  
ax.YColor = 'w'; % 设置 y 轴颜色为白色  
ax.ZColor = 'w'; % 设置 z 轴颜色为白色  
set(gcf, 'Units', 'Normalized', 'Position', [0.1, 0.1, 0.6, 0.6]);
xlabel('index', 'Color', 'w', 'FontName', 'Times New Roman'); % 设置标签字体颜色为白色  
ylabel('log_2(time)', 'Color', 'w', 'FontName', 'Times New Roman');  
legend({'朴素算法','递归算法','迭代算法'},"Color",'k','Location','northwest','TextColor','w')


figure(Color='k')
scatter(index,time1,3,'filled','MarkerEdgeColor',colors(1),'MarkerFaceColor',colors(1))
hold on
ax = gca;   
ax.Color = 'k'; % 设置坐标轴背景颜色为黑色  
ax.XColor = 'w'; % 设置 x 轴颜色为白色  
ax.YColor = 'w'; % 设置 y 轴颜色为白色  
ax.ZColor = 'w'; % 设置 z 轴颜色为白色  
set(gcf, 'Units', 'Normalized', 'Position', [0.1, 0.1, 0.6, 0.6]);
xlabel('index', 'Color', 'w', 'FontName', 'Times New Roman'); % 设置标签字体颜色为白色  
ylabel('time', 'Color', 'w', 'FontName', 'Times New Roman');  
legend({'朴素算法'},"Color",'k','Location','northwest','TextColor','w')



figure(Color='k')
scatter(index,time2,3,'filled','MarkerEdgeColor',colors(2),'MarkerFaceColor',colors(2))
hold on
scatter(index,time3,3,'filled','MarkerEdgeColor',colors(3),'MarkerFaceColor',colors(3))
hold on
ax = gca;   
ax.Color = 'k'; % 设置坐标轴背景颜色为黑色  
ax.XColor = 'w'; % 设置 x 轴颜色为白色  
ax.YColor = 'w'; % 设置 y 轴颜色为白色  
ax.ZColor = 'w'; % 设置 z 轴颜色为白色  
set(gcf, 'Units', 'Normalized', 'Position', [0.1, 0.1, 0.6, 0.6]);
xlabel('index', 'Color', 'w', 'FontName', 'Times New Roman'); % 设置标签字体颜色为白色  
ylabel('time', 'Color', 'w', 'FontName', 'Times New Roman');  
legend({'递归算法','迭代算法'},"Color",'k','Location','northwest','TextColor','w')




%% 优化的二进制转十进制
clc,clear
mat = readmatrix("D:\Jimmy\program\my_math_demo\times.csv");
len = 100:10:1090;

mat = log2(mat);
color1 = "#845ec2";
color2 = "#ffc75f";
% 创建图形  
figure('Color', 'k'); % 设置背景颜色为黑色  
plot(len,mat(1,:),"Color",color2,"LineWidth",1.2)
hold on
plot(len,mat(2,:),"Color",color1,"LineWidth",1.2)
hold on
scatter(len,mat(1,:),5,"MarkerEdgeColor",color2,"MarkerFaceColor",color2)
hold on

scatter(len,mat(2,:),5,"MarkerEdgeColor",color1,"MarkerFaceColor",color1)
hold on

% 添加标签  
xlabel('length', 'Color', 'w', 'FontName', 'Times New Roman'); % 设置标签字体颜色为白色  
ylabel('log_2(time)', 'Color', 'w', 'FontName', 'Times New Roman');  

% 设置坐标轴颜色  
ax = gca;   
ax.Color = 'k'; % 设置坐标轴背景颜色为黑色  
ax.XColor = 'w'; % 设置 x 轴颜色为白色  
ax.YColor = 'w'; % 设置 y 轴颜色为白色  
ax.ZColor = 'w'; % 设置 z 轴颜色为白色  

legend({'10to2','2to10'},"Color",'k','Location','northwest','TextColor','w')





%% 优化的二进制转十进制
clc,clear
mat = readmatrix("D:\Jimmy\program\homework2\advacned_times.csv");
len = 100:10:1090;

mat = log2(mat);
color1 = "#845ec2";
color2 = "#ffc75f";
% 创建图形  
figure('Color', 'k'); % 设置背景颜色为黑色  
plot(len,mat(1,:),"Color",color2,"LineWidth",1.2)
hold on
plot(len,mat(2,:),"Color",color1,"LineWidth",1.2)
hold on
scatter(len,mat(1,:),5,"MarkerEdgeColor",color2,"MarkerFaceColor",color2)
hold on

scatter(len,mat(2,:),5,"MarkerEdgeColor",color1,"MarkerFaceColor",color1)
hold on

% 添加标签  
xlabel('length', 'Color', 'w', 'FontName', 'Times New Roman'); % 设置标签字体颜色为白色  
ylabel('log_2(time)', 'Color', 'w', 'FontName', 'Times New Roman');  

% 设置坐标轴颜色  
ax = gca;   
ax.Color = 'k'; % 设置坐标轴背景颜色为黑色  
ax.XColor = 'w'; % 设置 x 轴颜色为白色  
ax.YColor = 'w'; % 设置 y 轴颜色为白色  
ax.ZColor = 'w'; % 设置 z 轴颜色为白色  

legend({'优化方法1','优化方法2'},"Color",'k','Location','northwest','TextColor','w')






