---
笔记类: 数学
数学类: 分析学
根叶: 叶
tags:
  - 数学
  - 分析学
  - gamma函数
---
# 〇、从阶乘的引入
我们通常认为 $\Gamma$ 函数是阶乘的拓展，而往往，我们初识 $\Gamma$ 函数时，都是先认识的那个复杂无比让人摸不着头脑的[[gamma函数#^8f94ce|无穷积分]]。所以我们这里希望用一种符合直觉，从对阶乘的延拓出发，导出 $\Gamma$ 函数。
我们首先回归阶乘，由阶乘的定义式 $n!=\prod_{i=1}^ni$，不难知道递推式：$(n+1)!=(n+1)\cdot n!$，我们希望寻求的阶乘函数设为 $\Gamma(x)$，我们先设当 $x=n+1$ 时，有 $\Gamma(x)=n!$。同样，我们也要求阶乘函数 $\Gamma(x)$ 也满足这个递推式，即 $\Gamma(x+1)=x\cdot\Gamma(x)$
那么
$$
\begin{align*}\Gamma(x+n+1)&=\Gamma(x)\frac{\Gamma(x+1)}{\Gamma(x)}\frac{\Gamma(x+2)}{\Gamma(x+1)}\cdots\frac{\Gamma(x+n+1)}{\Gamma(x+n)}\\&=\Gamma(x)x(x+1)\cdots(x+n)\\\Gamma(x)&=\frac{\Gamma(x+n+1)}{x(x+1)\cdots(x+n)}
\end{align*}
$$
当 $n$ 很大的时候，我们期望有
$$
\Gamma(x+n+1) = (x+n)!\sim1\cdot2\cdot3\cdots n(n+1)\cdots(n+x)
$$
因此，我们期望
$$
\Gamma(x)\sim\frac{1\cdot2\cdots n}{x(x+1)\cdots(x+n)}(n+1)\cdots(n+x)
$$
如果 $x$ 很小而 $n$ 很大，那么我们可以得到这样的式子：
$$
(n+1)(n+2)\cdots(n+x)\approx n^x
$$
当然，换一个说法就是
$$
\lim\limits_{n\to\infty}\frac{(n+1)(n+2)\cdots(n+x)}{n^x}=1
$$
所以应该有：
$$
\Gamma(x)\approx\frac{1\cdot2\cdots n}{x(x+1)\cdots(x+n)}n^x
$$
更严谨来说，是：
$$
\Gamma(x)=\lim\limits_{n\to\infty}\frac{1\cdot2\cdots n}{x(x+1)\cdots(x+n)}n^x
$$
最终我们就得到了这样的极限表达式，这是符合直觉的。
接下来，我们令 $a_n=\frac{1}{x(x+1)\cdots(x+n)}$
于是，有这样的递推式：
$$
(x+n)a_n=a_{n-1}
$$
根据 $a_n$ 的递推式，我们考虑使用生成函数
我们设出这样的一个函数
$$
f(t)=\sum_{n=0}a_nt^{n+x}
$$
则
$$
f'(t)=x^{x-1}+f(t)
$$
这个微分方程，我们使用常数变易法来求，得到：
$$
f(t)=\int_0^tm^{x-1}e^{t-m}\text{d}m=t^x\int_0^1m^{x-1}e^{t(1-m)}\text{d}m
$$
想要计算 $a_n$，只需计算泰勒展开系数即可
$$
\begin{align*}
a_n & = \frac{1}{n!}\lim\limits_{t\to0}\frac{\text{d}^n}{\text{d}t^n}\int_0^1m^{x-1}e^{t(1-m)}\text{d}m\\
& =\frac{1}{n!}\int_0^1(1-m)^nm^{x-1}\text{d}m
\end{align*}
$$
容易使用分部积分，验证他是成立的。
最后求极限，
>[!warning|aside-r] 一个小问题
>这里的极限是否能放入积分中其实还有问题的，不过这里只想单纯推导 $\Gamma$ 函数的形式，
我们并不要求的那么严格。

$$
\begin{align*}\Gamma(x)&=\lim\limits_{n\to\infty}n!a_nn^x\\&=\lim\limits_{n\to\infty}n!n^x\frac{1}{n!}\int_0^1(1-m)^nm^{x-1}\text{d}m\\&=\lim\limits_{n\to\infty}\int_0^1(1-m)^n(nm)^{x-1}\text{d}(nm)\\&=\lim\limits_{n\to\infty}\int_0^{\infty}(1-\frac tn)^n\cdot t^{x-1}\text{d}t\\&=\int_0^{\infty}t^{x-1}e^{-t}\text{d}t
\end{align*}
$$
那么，最终，我们推导出了 $\Gamma$函数的积分形式：
$$
\Gamma(x)=\int_0^{\infty}t^{x-1}e^{-t}\text{d}t
$$

^8f94ce
![[Pasted image 20241118164633.png]]
# 一、定义
