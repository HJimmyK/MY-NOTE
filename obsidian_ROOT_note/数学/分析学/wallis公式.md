---
笔记类: 数学
数学类: 分析学
根叶: 叶
tags:
  - 数学
  - 分析学
  - wallis公式
  - pi的渐进式
  - beta函数
---

**沃利斯**
<br>
定义如下的表达式：
$$
A_{p,q} = \int_0^1 (1-x^{\frac 1 p})^q\text{d}x  
$$

我们先计算几个$A_{p,q}$的值，得到以下的一些结果：
$$
\begin{align*}
    A_{0,0} &= 1;\\
    A_{p,0} &= 1,\quad
    A_{p,1} = \frac{1}{p+1},\quad p\in N;\\
    A_{1,q} &= \frac{1}{q+1},\quad q\in N\\
    A_{2,3} &= \frac{1}{10};\quad
    A_{3,5} = \frac{1}{56};  
\end{align*}
$$

我们试试从另一个角度开始：
$$
A_{p,q}=\int_0^1 (1-x^{\frac 1 p})^q\text{d}x  \\
$$
从另一个角度，使用分部积分可得：
$$
\begin{align*}
  A_{p,q}&=\left.x(1-x^{\frac 1 p})^q\right|_0^1- \int_0^1 x \text{d}(1-x^{\frac 1 p})^q  \\  
  &= 0 - \int_0^1 x\cdot q\cdot \frac{1}{p}(-x^{\frac{1}{p}-1})(1-x^{\frac 1 p})^{q-1}\text{d}x \\
  &= \frac{q}{p}\int_0^1  (x^{\frac{1}{p}})(1-x^{\frac 1 p})^{q-1}\text{d}x \\
\end{align*}\\
$$

且：
$$
\begin{align*}
    A_{p,q}&=\int_0^1 (1-x^{\frac 1 p})^q\text{d}x \\
    &= \int_0^1 (1-x^{\frac 1 p})(1-x^{\frac 1 p})^{q-1}\text{d}x \\
    &=\int_0^1 (1-x^{\frac 1 p})^{q-1}\text{d}x - \int_0^1 (x^{\frac 1 p})(1-x^{\frac 1 p})^{q-1}\text{d}x \\
    &=A_{p,q-1} - \frac{p}{q}A_{p,q}
\end{align*}\\
$$


我们便可以得到：
$$
A_{p,q}\cdot \frac{q+p}{q} = A_{p,q-1},\quad q\ne 0
$$
我们使用递推连乘相消：
$$
\begin{align*}
    A_{p,q}&=A_{p,1}\cdot \frac{A_{p,2}}{A_{p,1}}\cdot \frac{A_{p,3}}{A_{p,2}}\cdots \frac{A_{p,q}}{A_{p,q-1}}\\
    &=\frac{1}{1+p}\cdot \frac{2}{2+p}\cdot \frac{3}{3+p}\cdots \frac{q}{q+p}\\
    &=\frac{p!q!}{(p+q)!}\\
    &=\frac{1}{\begin{pmatrix*}p+q\\ p \end{pmatrix*}}
\end{align*}
$$
我们可以得到这样的方程：
$$
A_{p,q} = \frac{p!q!}{(p+q)!}=\frac{1}{\begin{pmatrix*}p+q\\ p \end{pmatrix*}}, \quad p,q\in N
$$

令 $t = 1-x^{\frac 1 p}$，则 $x = (1-t)^{p}$
那么
$$
\begin{align*}
    A_{p,q} &= \int_0^1 (1-x^{\frac 1 p})^q\text{d}x \\
            &= \int_0^1 t^q\text{d} (1-t)^p\\
            &= \int_1^0 t^q\cdot(-p)(1-t)^{p-1}\text{d}t\\
            &= p\int_0^1 t^q\cdot (1-t)^{p-1}\text{d}t\\
            &= p\cdot \beta(q+1,p)
\end{align*}
$$



我们根据这个式子
$$
A_{p,q}\cdot \frac{q+p}{q} = A_{p,q-1},\quad q\ne 0
$$
当 $q$ 趋于无穷时，两式近似相等，
$$
\lim\limits_{m\to+\infty}\frac{A_{\frac 1 2,m+\frac 1 2}}{A_{\frac 1 2,m-\frac 1 2}}=\lim\limits_{m\to+\infty}\frac{m+\frac12}{1+m}=1
$$
那么由此式：
$$
A_{\frac{1}{2},m-\frac 1 2}>A_{\frac{1}{2},m}>A_{\frac{1}{2},m+\frac 1 2}
$$
结合夹逼定理，得：
$$
A_{\frac 1 2,m+\frac 1 2}=A_{\frac 1 2,m},\quad m\to +\infty
$$
而
$$
\begin{align*}
    A_{\frac12,m}&=A_{\frac12,0}\cdot \frac{A_{\frac12,1}}{A_{\frac12,0}}\cdot \frac{A_{\frac12,2}}{A_{\frac12,1}}\cdots \frac{A_{\frac12,m}}{A_{\frac12,m-1}}\\
    &=1\cdot\frac{1}{\frac12+1}\cdot \frac{2}{\frac12+2}\cdots \frac{m}{\frac12+m}\\
    &=\frac{m!2^m}{3\cdot5\cdots(1+2m)}\\
    &=\frac{(2m)!!}{(1+2m)!!}
\end{align*}\\
$$
$$
\begin{align*}
    A_{\frac12,m+\frac12}&=A_{\frac12,\frac12}\cdot \frac{A_{\frac12,1+\frac12}}{A_{\frac12,0+\frac12}}\cdot \frac{A_{\frac12,2+\frac12}}{A_{\frac12,1+\frac12}}\cdots \frac{A_{\frac12,m+\frac12}}{A_{\frac12,m-1+\frac12}}\\
    &=A_{\frac12,\frac12}\cdot\frac{\frac12+1}{2}\cdot \frac{\frac12+2}{3}\cdots \frac{\frac12+m}{m+1}\\
    &=A_{\frac12,\frac12}\frac{3\cdot5\cdots(1+2m)}{(m+1)!2^m}\\
    &=A_{\frac12,\frac12}\frac{2\cdot(1+2m)!!}{(2m+2)!!}
\end{align*}
$$
那么，我们就得
$$
\frac{(2m)!!}{(1+2m)!!}=A_{\frac12,\frac12}\frac{2\cdot(1+2m)!!}{(2m+2)!!},\quad m\to+\infty
$$
结合 $A_{\frac12,\frac12}=\frac{\pi}{4}$，得
$$
\lim\limits_{m\to+\infty}\frac{(2m)!!\cdot(2m+2)!!}{(1+2m)!!(1+2m)!!} = \frac{\pi}{2}
$$
当然，如果我们利用的是 $\lim\limits_{m\to+\infty}A_{\frac12,m}=\lim\limits_{m\to+\infty}A_{\frac12,m-\frac12}$，就会得到更被我们熟知的沃利斯公式的形式：
$$
\lim\limits_{m\to+\infty}\left\{
    \frac{(2m)!!\cdot(2m)!!}{(2m-1)!!\cdot(2m+1)!!}
 \right\}= \frac{\pi}{2}
$$


