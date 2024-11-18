---
笔记类: 数学
数学类: 分析学
根叶: 叶
tags:
  - 分析学
  - 数学
  - beta函数
---

# 一、定义与变式
## 1.1. 原始定义
对 $\forall p,q>0$，
$$
B(p,q)=\int_0^1x^{p-1}(1-x)^{q-1}\text{d}x \tag{定义1-1}
$$
称为 $B$ 函数
![[Pasted image 20241117174322.png]]
![[Pasted image 20241117174344.png]]
## 1.2. 性质
+ **对称性**
对 $\forall p,q>0$，
$$
B(p,q)=B(q,p)\tag{性质1-1}
$$
>[!note] 对称性证明：
>$$\begin{align*}B(p,q)&=\int_0^1x^{p-1}(1-x)^{q-1}\text{d}x \\&=\int_1^0(1-t)^{p-1}t^{q-1}\text{d}(-t)\\&=\int_0^1t^{q-1}(1-t)^{p-1}\text{d}t\\&=B(q,p)\end{align*}$$


+ **与 $\Gamma$ 函数的关系**
对 $\forall p,q>0$，
$$
B(p,q)=\dfrac{\Gamma(p)\Gamma(q)}{\Gamma(p+q)}\tag{性质1-2}
$$
>[!note] 与 $\Gamma$ 函数关系的证明：
>$$
\begin{aligned}
\Gamma(p) \Gamma(q) & =4 \int_{0}^{+\infty} s^{2 p-1} \mathrm{e}^{-s^{2}} \mathrm{~d} s \int_{0}^{+\infty} t^{2 q-1} \mathrm{e}^{-t^{2}} \mathrm{~d} t \\
& =4 \iint_{\Omega} s^{2 p-1} \mathrm{e}^{-s^{2}} t^{2 q-1} \mathrm{e}^{-t^{2}} \mathrm{~d} s \mathrm{~d} t \\
& =4 \iint_{\substack{0 \leqslant r<+\infty, 0 \leqslant \theta<+\infty}} r^{2(p+q)-1} e^{-r^{2}} \cos ^{2 p-1} \theta \sin ^{2 q-1} \theta \mathrm{~d} r \mathrm{~d} \theta \\
& =\left(2 \int_{0}^{\pi / 2} \cos ^{2 p-1} \theta \sin ^{2 q-1} \theta \mathrm{~d} \theta\right)\left(2 \int_{0}^{+\infty} r^{2(p+q)-1} \mathrm{e}^{-r^{2}} \mathrm{~d} r\right) \\
& =\mathrm{B}(p, q) \Gamma(p+q)
\end{aligned}
> $$
> 其中用到了 $\Gamma$ 函数的[[beta函数#^441841|三角定义]]。
 ^b8bd16
+ **递推式**
对 $\forall p,q>0$，
$$
B(p,q+1)=\dfrac{q}{p+q}B(p,q)\tag{性质1-3}
$$
>[!note] 递推式的证明：
> 由[[beta函数#^b8bd16|性质（1-2）]] $$\begin{align*}\Gamma(p)\Gamma(q+1) &= B(p,q+1)\Gamma(p+q+1)\\\Gamma(p)q\Gamma(q) &= B(p,q+1)(p,q+1)\Gamma(p+q)\\\dfrac{q}{p+q}\dfrac{\Gamma(p)\Gamma(q)}{\Gamma(p+q)}&=B(p,q+1)\\\dfrac{q}{p+q}B(p,q)&=B(p,q+1)\end{align*}$$

## 1.2. 等价定义
### 1.2.1 三角定义
$\forall p,q>-1$，
$$
\int_{0}^{\frac{\pi}{2}}\sin^p\theta\cos^q\theta\cdot\text{d}\theta = \dfrac12B\left(\dfrac{p+1}{2},\dfrac{q+1}{2}\right) \tag{等价定义2-1}
$$

^441841

>[!note] 三角定义证明：
>$$\begin{align*}\int_0^{\frac{\pi}{2}}\sin^p\theta\cos^q\theta \text{d}\theta &=  \int_0^{1}(\sqrt{x})^p (1-x)^{\frac{q-1}{2}} (\frac{1}{2\sqrt{x}}) \text{d}x \\&=\dfrac{1}{2}\int_0^1x^{\frac{p-1}{2}}(1-x)^{\frac{q-1}{2}}\text{d}x\\&=B\left(\dfrac{p+1}{2},\dfrac{q+1}{2}\right)\end{align*}$$

### 1.2.2 幂函数定义
$\forall p,q>-1$，
$$
\int_{0}^1t^p(1-t^{\alpha})^q \text{d}t = \dfrac{1}{\alpha}B\left(\dfrac{p+1}{\alpha},q+1\right) \tag{等价定义2-2}
$$
>[!note] 幂函数定义证明：
>  $$\begin{align*}\int_{0}^1t^p(1-t^{\alpha})^q \text{d}t &= \int_0^1 m^{\frac{p}{\alpha}} (1-m)^q \frac{1}{\alpha}m^{\frac{1}{\alpha}-1}\text{d}m\\&=\frac{1}{\alpha}\int_0^1m^{\frac{p+1}{\alpha}-1}(1-m)^q\text{d}m\\&=\frac{1}{\alpha}B\left(\dfrac{p+1}{\alpha},q+1\right) \end{align*}$$
### 1.2.3 分式线性定义
$\forall p>-1,m+\alpha n<-1$，
$$
\int_0^{+\infty}u^p(u^{\alpha}+1)^q\text{d}u = \frac{1}{\alpha}B\left(\dfrac{p+1}{\alpha},-\dfrac{p+\alpha q+1}{\alpha}\right) \tag{等价定义2-3}
$$
>[!tip] 想法：
>考虑一个由 $[0,1]\to[0,+\infty]$ 的变换：$t=\dfrac{x}{1-x}$，即令 $x=\dfrac{t}{t+1}$
$$\begin{aligned}B(p, q) & =\int_{0}^{+\infty}\left(\frac{t}{t+1}\right)^{p-1}\left(\frac{1}{t+1}\right)^{q-1} \cdot \frac{1}{(t+1)^{2}} \mathrm{~d} t \\& =\int_{0}^{+\infty} t^{p-1}(t+1)^{-p-q} \mathrm{~d} t\end{aligned}$$
进一步地，考虑令 $t=u^{\alpha}(\alpha>0), u \in[0,+\infty)$
$$\begin{aligned}B(p, q) & =\int_{0}^{+\infty}\left(u^{\alpha}\right)^{p-1}\left(u^{\alpha}+1\right)^{-p-q} \cdot \alpha u^{\alpha-1} \mathrm{~d} u \\& =\alpha \int_{0}^{+\infty} u^{\alpha p-1}\left(u^{\alpha}+1\right)^{-p-q} \mathrm{~d} u\end{aligned}$$

^5fac92

### 1.2.4 双曲函数定义
$\forall p>-1,p+q<0$，
$$
\int_{0}^{+\infty} \sinh ^{p} u \cosh ^{q} u \mathrm{~d} u=\frac{1}{2} B\left(\frac{p+1}{2},-\frac{p+q}{2}\right)
$$
>[!note] 双曲函数定义证明：
>根据[[beta函数#^5fac92|等价定义三中的结果]]，令 $t=\sinh^2 u,u \in [0,+\infty)$，
>$$\begin{align*}B(p,q) &=\int_0^{+\infty}(\sinh^2(u))^{p-1}(\cosh^2u)^{-p-q}\cdot 2\sinh u\cosh u\text{d}u\\& = 2\int_0^{+\infty} \sinh^{2p-1}u\cosh^{-2p-2q+1}u\text{d}u\end{align*}$$






关于 $B$ 函数的乘积公式：
$$
B(x,y)=\dfrac{x+y}{xy}\prod_{k=1}^{\infty}\dfrac{1+\frac{x+y}{k}}{(1+\frac{x}{k})(1+\frac{y}{k})}
$$

我们利用 $\Gamma$ 函数的这个无穷乘积表达式：
$$
\Gamma(z)=\dfrac{1}{z}\prod_{k=1}^{\infty}\left[\left(1+\dfrac{z}{k}\right)^{-1}\left(1+\dfrac 1n\right)^z\right]
$$
有：
$$
\begin{align*}
B(x,y)&=\dfrac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\\
&=\dfrac{\dfrac{1}{xy}\prod_{k=1}^{\infty}\left[\left(1+\dfrac{x}{k}\right)^{-1}\left(1+\dfrac 1n\right)^x\right]\left[\left(1+\dfrac{y}{k}\right)^{-1}\left(1+\dfrac 1n\right)^y\right]}{\dfrac{1}{x+y}\prod_{k=1}^{\infty}\left[\left(1+\dfrac{x+y}{k}\right)^{-1}\left(1+\dfrac 1n\right)^{x+y}\right]}\\
&=\dfrac{x+y}{xy}\prod_{k=1}^{\infty}\dfrac{\left(1+\dfrac{x}{k}\right)^{-1}\left(1+\dfrac{y}{k}\right)^{-1}}{\left(1+\dfrac{x+y}{k}\right)^{-1}}\\
&=\dfrac{x+y}{xy}\prod_{k=1}^{\infty}\dfrac{1+\dfrac{x+y}{k}}{\left(1+\dfrac{x}{k}\right)\left(1+\dfrac{y}{k}\right)}
\end{align*}
$$
 

$$
\Gamma(z) = \frac{1}{z} \prod_{n=1}^{\infty} \left( \frac{n+z-1}{n} e^{\frac{z-1}{n}} \right)
$$





















![[Pasted image 20241118213749.png]]




[Beta Function -- from Wolfram MathWorld](https://mathworld.wolfram.com/BetaFunction.html)