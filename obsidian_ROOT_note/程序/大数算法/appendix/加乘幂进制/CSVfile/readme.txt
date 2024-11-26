times.csv是进制转换测量的数据文件，第一行是十进制转化二进制，第二行是二进制转化十进制。字符串输入数据从以 10*i + 100 变化，i = 0:1:99
advanced_times.csv是优化后的进制转换的数据文件，，第一行是仅仅优化幂乘方，第二行是采用记录表。字符串输入数据从以 100*i + 100 变化，i = 0:1:99


pow2time_1.csv 朴素算法结果
pow2time_2.csv 递归算法结果
pow2time_3.csv 迭代算法结果
是三种二进制的测量数据文件，计算的指数以 1000*i + 10 变化，i = 0:1:199


timeMSVCfft.csv 和 timeMSVCpl.csv文件是 MSVC 编译器测量的FFT和朴素乘法的运行时间的数据，计算的两个字符串分别以 i , j 变化，i = 10:10:1000 ，j = 10:10:1000
timeMSVCfft.csv 和 timeGccpl.csv文件是 gcc 编译器测量的FFT和朴素乘法的运行时间的数据，计算的两个字符串分别以 i , j 变化，i = 50:50:5000 ，j = 50:50:5000
timeMSVCfft_.csv 和 timeGccpl_.csv文件是第二次测量。