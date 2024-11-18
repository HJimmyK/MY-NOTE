---
笔记类: 数学
数学类: 概率论
根叶: 叶
tags:
  - 数学
  - 概率论
  - 伯努利试验
---

# 一、n重伯努利试验直至试验连续成功问题
## 1. 问题描述
### 1.1. 问题引入

### 1.2. 问题抽象化描述

我们抽象出这样一个问题：我们一直进行伯努利试验，设每次试验成功的概率为 $p$。我们将一直进行实验，直至有 $n$ 次试验连续成功，并定义随机变量 $X$ 为试验的次数。
<br>
我们首先定义概率值 $P_{m,n} = P_n\{X = m\}$，且定义 $q = 1-p$
不难知道，$p_{m,n}$ 有如下性质：
$$
\begin{align*}
    P_{m,n} &= 0,\quad m<n\\
    P_{n,n} &= p^n,\\
    P_{n+1,n} &= q\cdot p^n,
\end{align*}
$$

我们考虑如何求出 $P_{m,n}$ 的递推公式，我们先假定 $m>n$，记 $1$ 为试验成功，$0$ 为不成功。

对于第一次试验：
1. 若为 $0$，则之后的 $m-1$ 次实验也恰好有 $n$ 次实验连续发生，

2. 若为 $1$，则考虑第二次实验:
    + 若为 $0$，则之后的 $m-2$ 次实验也恰好有 $n$ 次实验连续发生，
    + 若为 $1$，则考虑第三次实验，以此类推
    .....

直至第 $n$ 试验，
1. 若为 $0$，则之后的 $m-n$ 次实验也恰好有 $n$ 次实验连续发生，
2. 若为 $1$，不可能。因为 $m>n$ ，若为 $1$ 则说明试验提前终止了。

换句话说，就是：
若第一次的结果为 $0$，那么剩下的任务就是恰好使用 $m-1$ 次投掷得到到连续的 $n$ 个 $1$
若前两次的结果为 $10$，那么剩下的任务就是恰好使用 $m-2$ 次投掷得到到连续的 $n$ 个 $1$
若前三次的结果为 $110$，那么剩下的任务就是恰好使用 $m-3$ 次投掷得到到连续的 $n$ 个 $1$
若前四次的结果为 $1110$， 那么剩下的任务就是恰好使用 $m-4$ 次投掷得到到连续的 $n$ 个 $1$
......
若前 $n-1$ 次的结果为 $11\cdots10(n-2个1)$， 那么剩下的任务就是恰好使用 $1$ 次投掷得到到连续的 $n$ 个 $1$。

那么，我们不难得到这个递推式：
$$
P_{m,n} = \sum_{i=1}^n p^{i-1}q\cdot P_{m-i,n},\tag{1-1}
$$
这个递推式是一个求和形式的，有很多项。我们考虑由此出发，再寻找一个更简单的递推表达式。

$$
\begin{align*}
    P_{m,n} &= \sum_{i=1}^n p^{i-1}q\cdot P_{m-i,n}\\
    &=p^0qP_{m-1,n}+p^1qP_{m-2,n}+\cdots+p^{n-1}qP_{m-n,n}
\end{align*}
$$

且

$$
\begin{align*}
    P_{m+1,n} &= \sum_{i=1}^n p^{i-1}q\cdot P_{m+1-i,n}\\
    &=p^0qP_{m,n}+p^1qP_{m-1,n}+\cdots+p^{n-1}qP_{m-n+1,n}
\end{align*}
$$

可以发现，上面的两式中间有相同项，只差了一个系数，使用错位相减，得：

$$
P_{m+1,n} = qP_{m,n}+p\cdot[P_{m,n}-p^{n-1}qP_{m-n,n}]
$$

最后得
$$
P_{m+1,n} = P_{m,n} - p^nqP_{m-n,n},\tag{1-2}
$$

需要注意的是，(2)式中，必须有 $m\ne n$，

我们考虑生成函数 $G(z)$，
设 
$$
G(z) = \sum_{i=0}^{\infty}P_{i,n}\cdot z^i
$$

根据 $P_{m,n}$ 的性质，可以容易得到 $G(z)$ 的等效表达式：
$$
\begin{align*}
    G(z)&=\sum_{i=0}^{\infty}P_{n+i,n}\cdot z^{n+i}\\
    &=z^n\sum_{i=0}^{\infty}P_{n+i,n}\cdot z^i \tag{1-3}
\end{align*}
$$

那么
$$
\begin{align*}
    G(z) &= z^n\sum_{i=0}^{\infty}P_{n+i,n}\cdot z^i\\
    &=  z^n\sum_{i=0}^{\infty}P_{n+i,n}\cdot z^i\\
    &=z^nP_{n,n}z^0+z^n\sum_{i=1}^{\infty}P_{n+i,n}\cdot z^i\\
    &=z^nP_{n,n}z^0+z^n\sum_{i=0}^{\infty}P_{n+1+i,n}\cdot z^{i+1}\\
    &=z^nP_{n,n}+z^n\sum_{i=1}^{\infty}P_{n+1+i,n}\cdot z^{i+1} + P_{n+1,n}\cdot z^{n+1}\\
\end{align*}
$$

我们始终只是在玩文字游戏而已，上面的推导纯粹，就是为了凑配出 $P_{n+1+i,n}$ 这一项，为的就是和（2）式结合起来。需要注意的是，（2）式要求 $m\ne n$ 所以 $i$ 必须从 $1$ 开始，所以需要将 $i=0$ 这一项拿出来。

$$
\begin{align*}
    G(z)&=z^nP_{n,n}+z^n\sum_{i=1}^{\infty}P_{n+1+i,n}\cdot z^{i+1} + P_{n+1,n}\cdot z^{n+1}\\
    &=z^nP_{n,n}+z^n\sum_{i=1}^{\infty}[P_{n+i,n} - p^nqP_{i,n}]\cdot z^{i+1} + P_{n+1,n}\cdot z^{n+1}\\
    &=z^nP_{n,n} +z^{n+1}p^nq + z^n\sum_{i=1}^{\infty}P_{n+i,n}\cdot z^{i+1} - z^np^nq\sum_{i=1}^{\infty}P_{i,n}\cdot z^{i+1}\\
    &=z^nP_{n,n} +z^{n+1}p^nq + z^{n+1}\sum_{i=1}^{\infty}P_{n+i,n}\cdot z^i - z^{n+1}p^nq\sum_{i=1}^{\infty}P_{i,n}\cdot z^i\\
\end{align*}
$$

结合 $G(z)$ 得等效表达式，得

$$
\begin{align*}
    G(z)&=z^nP_{n,n} +z^{n+1}p^nq + z^{n+1}\begin{bmatrix*}
        \frac{G(z)}{z^n}-P_{n,n}z^0
    \end{bmatrix*}- z^{n+1}p^nqG(z)\\
    &=z^np^n + z^{n+1}p^nq +z^{1}G(z)-z^{n+1}p^n- z^{n+1}p^nqG(z)\\
\end{align*}
$$

那么

$$
\begin{align*}
    \begin{bmatrix*}1-z+z^{n+1}p^nq\end{bmatrix*}G(z)&=z^np^n+z^{n+1}p^n(q-1)\\
    &=z^np^n - z^{n+1}p^{n+1}\\
    G(z)&=\frac{z^np^n(1-pz)}{1-z+z^{n+1}p^nq}
\end{align*}
$$

至此，我们就得到了 $G(z)$ 的完整表达式：

$$
  G(z)=\frac{z^np^n(1-pz)}{1-z+z^{n+1}p^nq}     \tag{1-4}
$$

那么，我们可以求出期望 $E_n$ 和方差 $D_n$，

$$
\begin{align*}
    E_n&=G'_n(1)\\
    &=p^n\frac{[n-p(n+1)](p^n q) - [-1+(n+1)p^nq](1- p)}{(p^nq)^2}\\
    &=\frac{np^nq-(n+1)p^{n+1}q+q-(n+1)p^nq^2}{p^nq^2}\\
    &=\frac{np^nq^2 - p^{n+1}q-(n+1)p^nq^2+q}{p^nq^2}\\
    &=\frac{q-p^{n+1}q-p^nq^2}{p^nq^2}\\
    &=\frac{1}{p^nq}-\frac{1}{q}\\
\end{align*}
$$

$$
D_n = E_n(z^2) - E^2_n(z)
$$

且，$z>0$，则

$$
\begin{align*}
    E_n(z^2) &= \sum_{i=0}^{\infty}i^2\cdot P_{i,n}\\
    &= G''_n(1)+G'_n(1)
\end{align*}
$$

那么

$$
\begin{align*}
    D_n&=G''_n(1)+G'_n(1)-[G'_n(1)]^2\\
\end{align*}
$$

而

$$
\begin{align*}
    G''_n(1) &=\frac{p^n(2(p^nq-1)(qp^n+p-1)-n(5p^nq-3p^n(1+p)q+p^{1+n}q))}{p^{3n}q^3}\\
    &=\frac{2(p^nq-1)(p^n-1)-n(2p^n-2p^{n+1})}{p^{2n}q^2}\\
    &=\frac{2(p^nq-1)(p^n-1)-2np^nq}{p^{2n}q^2}\\
\end{align*}
$$

则

$$
\begin{align*}
    D_n&=G''_n(1)+G'_n(1)-[G'_n(1)]^2\\
        &=\frac{2(p^nq-1)(p^n-1)-2np^nq}{p^{2n}q^2}+\frac{1-p^n}{p^nq}-\frac{(1-p^n)^2}{p^{2n}q^2}\\
        &=\frac{(1-p^n)(p^n-1+2-2p^nq+p^nq)-2np^nq}{p^{2n}q^2}\\
        &=\frac{(1-p^n)(p^n+1-p^nq)-2np^nq}{p^{2n}q^2}\\
        &=\frac{(1-p^n)(p^{n+1}+1)-2np^nq}{p^{2n}q^2}\\
        &=\frac{1-p^{2n+1}-p^n+p^{n+1}-2np^nq}{p^{2n}q^2}\\
        &=\frac{1}{p^{2n}q^2}-\frac{1+2n}{p^nq}-\frac{p}{q^2}
\end{align*}
$$

最终，我们得到：

$$
\begin{align*}
    E_n&=\frac{1}{p^nq}-\frac{1}{q}\\
    D_n&=\frac{1}{p^{2n}q^2}-\frac{1+2n}{p^nq}-\frac{p}{q^2}
\end{align*}
$$







# 二、n重伯努利试验的最长成功序列概率问题
## 1.1. 问题描述
### 1.1.1. 问题引入

### 1.1.2. 问题的抽象描述
我们给出这个问题的完整表述：我们进行 $N$ 次伯努利试验，每次试验成功的概率都为 $p$ ，记 $q=1-p$，记随机变量 $X_{m,N}$ 为其中连续成功 $m$ 次的最大值。

比如：（用 1 代表成功）
当 $N=10$ 时，某次的0-1序列为 1001101111，其中最多连续发生 4 次
当 $N=20$ 时，某次的0-1序列为 11000111010011100110，其中最多连续发生 3 次

我们关心的是，在特定的 $N$ 下，连续成功次数的最大值满足什么分布。
<br>
## 2.2. 问题的可行方案
### 2.2.1.马尔可夫链模型
我们使用马尔科夫链前首先需要建立合适的状态机。我们定义如下的状态：
(1). **0状态**：初始（在实验开始前）或前一次为失败且没有出现 $n$ 次及以上连续成功。
(2). **1状态**：当前恰好最大连续成功次数为 1
(3). **2状态**：当前恰好最大连续成功次数为 2
(4). **3状态**：当前恰好最大连续成功次数为 3
   $\cdots$
(n-1). **n-1状态**：当前恰好最大连续成功次数为 n-1
(n). **n状态**：最大连续成功次数大于等于 n

可能很抽象，与我们设想的普通马尔科夫状态不是很一致。我们这里定义的状态其实是一个整体量，即当前序列的装态，而非单次实验的成功与否。比如，对于 $n=3$。 当前序列为 10010101110，其属于 n状态；当前序列为 101011011，其属于 2状态；当前序列为 0010110110，其属于 0状态。

那么我们可以很容易的知道转移概率：从非 0和n状态到 0状态只需当前失败即可，进入 n状态后你就无法跳出（我们通常称之为“吸收”），从非 n状态到其后一个状态只需当前成功即可。那么我们可以得到这样的矩阵：
$$
A_{n+1} = \begin{bmatrix*}
    q&q&\cdots&q&0\\
    p\\
    &p&&&\vdots\\
    &&\ddots&&0\\
    &&&p&1
\end{bmatrix*}
$$
比如：
$$
A_{4} = \begin{bmatrix*}
    q&q&q&0\\
    p&0&0&0\\
    0&p&0&0\\
    0&0&p&1\\
\end{bmatrix*}
$$
那么，我们就能够根据状态转移矩阵来确定 $N$ 次后，最终出现最大连正次数 $n$ 及以上的概率，我们将其记作 $P_{N,n^+}\quad(n>0)$，其可由下面的方程确定。
$$
\begin{bmatrix*}
    P_{0}\\
    P_{N,1^+}\\
    \vdots\\
    P_{N,n^+}
\end{bmatrix*}=
\begin{bmatrix*}
    q&q&\cdots&q&0\\
    p\\
    &p&&&\vdots\\
    &&\ddots&&0\\
    &&&p&1
\end{bmatrix*}_{n+1}^N
\begin{bmatrix*}
    1\\
    0\\
    \vdots\\
    0
\end{bmatrix*}\tag{2-1}
$$

我们记 $P_{N,n}$ 表示出现最大连正次数 $n$ 的概率。很显然，我们只要 $P_{N,n} = P_{N,n^+}-P_{N,n+1^+}$ 这样计算即可。

我们肯定有这样的想法，就是能不能将 $A_{n+1}$ 矩阵进行相似对角化，这样就能求出其任意次方了。当然，这样的算法也显然适合计算机来计算。
<br>
我们写出 $A_n$ 的特征方程：
$$
det(\lambda I-A_{n+1})=
\begin{vmatrix*}
    \lambda-q&-q&\cdots&-q&0\\
    -p&\lambda&\\
    &-p&\ddots&&\vdots\\
    &&\ddots&\lambda&0\\
    &&&-p&\lambda -1
\end{vmatrix*}=0
$$
我们将其拉普拉斯展开，不难得到下面的方程：
$$
(\lambda-1)(\lambda^{n}-q\sum_{i=0}^{n-1}p^i\lambda^{n-1-i})=0
$$
<br>

### 2.2.2. 生成函数模型 
#### 2.2.2.1. 递推表达式
虽然马尔科夫链本身就是一种递推公式，但我们想从另一个角度得到一个更简单的递推公式，进而使用生成函数。我们依旧采用上面的记号，记 $P_{N,n}$ 表示出现最大连正次数 $n$ 的概率，记 $P_{N,n^+}\quad(n>0)$ 为最大连正次数大于等于 $n$ 的概率。
不难得到，$P_{N,n^+}$ 的一些性质：
$$
\begin{align*}
    P_{i,n^+}& = 0\qquad i<n\\
    P_{n,n^+} &= p^n\\
    P_{n+1,n^+}&=(2-p)p^n
\end{align*}
$$

我们希望将 $P_{N,n^+}$ 与 $P_{N+1,n^+}$ 联系起来。显然，后者的概率是要更高的。我们假设，有这样的一个方程 $P_{i+1,n^+}=P_{i,n^+}+p(x)$，其中的 $p(x)$ 表示“前 $i$ 次都没有出现，但恰好在抛第 $i+1$ 次才首次出现连续成功 $n$ 次”。

恰好在抛第 $i+1$ 次才首次出现连续成功 $n$ 次，显然有以下的要求：
$$
\underbrace{\overbrace{???\cdots???}}^{0\to (i-n)}_{1-P_{i-n,n^+}}\qquad\underbrace{\overbrace{\cdot0\cdot}^{(i-n+1)}}_{1-p}\qquad\underbrace{\overbrace{111\cdots11}^{(i-n+2)\to (i+1)}}_{p^nq}
$$
也就是说，$p(x)$ 对应的事件要发生，必须满足两个条件，
1. 第i-n+1次到i+1次，这n+1次的情况必须是：第i-n+1次为失败，第i-n+2次到i+1次均成功。把这个事件记为 $y$，对应概率记为 $p(y)$，显然 $p(y)=p^nq$
2. 第1次到第i-n次必须没有出现连续n次以上的成功。把这个事件记为 $z$，对应概率记为 $p(z)$。事件 $z$ 的逆事件就是前i-n次至少出现过一次连续n次成功，逆事件的概率就是 $p_{i-n,n^+}$，所以有 $p(z)=1-P_{i-n,n^+}$

因此，$p(x)=p(y)p(z)=(1-P_{i-n,n^+})p^nq$。
综上可得
$$
P_{m+1,n^+}=P_{m,n^+} + (1-P_{m-n,n^+})p^nq,\qquad m>n\tag{2-2}
$$ 
^ba093e

<br>

#### 2.2.2.2. 生成函数
我们考虑生成函数 $G_n(z)$，
设 
$$
G_n(z) = \sum_{i=0}^{\infty}P_{i,n^+}\cdot z^i
$$
根据 $P_{i,n^+}$ 的性质，可以容易得到 $G(z)$ 的等效表达式： 
$$
\begin{align*}
    G_n(z)&=\sum_{i=0}^{\infty}P_{n+i,n^+}\cdot z^{n+i}\\
    &=z^n\sum_{i=0}^{\infty}P_{n+i,n^+}\cdot z^i \tag{2-3}
\end{align*}
$$
^48c076

那么
$$
\begin{align*}
    G_n(z) &= z^n\sum_{i=0}^{\infty}P_{n+i,n^+}\cdot z^i\\
    &=  z^n\sum_{i=0}^{\infty}P_{n+i,n^+}\cdot z^i\\
    &=z^nP_{n,n^+}z^0+z^n\sum_{i=1}^{\infty}P_{n+i,n^+}\cdot z^i\\
    &=z^nP_{n,n^+}z^0+z^n\sum_{i=0}^{\infty}P_{n+1+i,n^+}\cdot z^{i+1}\\
    &=z^nP_{n,n^+}+z^n\sum_{i=1}^{\infty}P_{n+1+i,n^+}\cdot z^{i+1} + P_{n+1,n^+}\cdot z^{n+1}\\
\end{align*}
$$
我们始终只是在玩文字游戏而已，上面的推导纯粹，就是为了凑配出 $P_{n+1+i,n^+}$ 这一项，为的就是和[[n重伯努利试验相关问题#^ba093e|（2-2）式]]结合起来。需要注意的是，（2-2）式要求 $m > n$ 所以 $i$ 必须从 $1$ 开始，所以需要将 $i=0$ 这一项拿出来。
$$
\begin{align*}
    G_n(z)&=z^nP_{n,n^+}+z^n\sum_{i=1}^{\infty}P_{n+1+i,n^+}\cdot z^{i+1} + P_{n+1,n^+}\cdot z^{n+1}\\
    &=z^nP_{n,n^+}+z^n\sum_{i=1}^{\infty}[P_{n+i,n^+} - p^nqP_{i,n^+}+p^nq]\cdot z^{i+1} + P_{n+1,n^+}\cdot z^{n+1}\\
    &=z^np^n +z^{n+1}p^n(2-p) + z^n\sum_{i=1}^{\infty}P_{n+i,n^+}\cdot z^{i+1} - z^np^nq\sum_{i=1}^{\infty}P_{i,n^+}\cdot z^{i+1}\\ & \qquad\qquad +z^{n+1}\sum_{i=1}^{\infty}p^nqz^{i}\\
    &=z^np^n +z^{n+1}p^n(2-p) + z^{n+1}\sum_{i=1}^{\infty}P_{n+i,n^+}\cdot z^i - z^{n+1}p^nq\sum_{i=1}^{\infty}P_{i,n^+}\cdot z^i\\
      & \qquad\qquad + z^{n+1}p^nq\cdot\frac{z}{1-z}
\end{align*}
$$
结合 $G_n(z)$ 得[[n重伯努利试验相关问题#^48c076|等效表达式]] ，得
$$
\begin{align*}
    G_n(z)&=z^np^n +z^{n+1}p^n(2-p) + z^{n+1}\begin{bmatrix*}
        \frac{G(z)}{z^n}-P_{n,n^+}z^0
    \end{bmatrix*}- z^{n+1}p^nqG(z)\\ 
    &\qquad\qquad + z^{n+1}p^nq\cdot\frac{z}{1-z}\\
    &=z^np^n + z^{n+1}p^n(2-p) +z^{1}G(z)-z^{n+1}p^n- z^{n+1}p^nqG(z)\\&\qquad\qquad + z^{n+1}p^nq\cdot\frac{z}{1-z}\\
\end{align*}
$$
那么
$$
\begin{align*}
    \begin{bmatrix*}1-z+z^{n+1}p^nq\end{bmatrix*}G_n(z)&=z^np^n+z^{n+1}p^n(1-p)+ z^{n+1}p^nq\cdot\frac{z}{1-z}\\
    &=z^np^n + z^{n+1}p^{n}q+ z^{n+1}p^nq\cdot\frac{z}{1-z}\\
    &=\frac{z^np^n-z^{n+1}p^n+z^{n+1}p^nq-z^{n+2}p^nq+z^{n+2}p^nq}{1-z}\\
    &=\frac{z^np^n(1-z+zq)}{1-z}\\
    G_n(z)&=\frac{z^np^n(1-pz)}{(1-z+z^{n+1}p^nq)(1-z)}
\end{align*}
$$
至此，我们就得到了 $G_n(z)$ 的完整表达式：
$$
  G_n(z)=\frac{z^np^n(1-pz)}{(1-z+z^{n+1}p^nq)(1-z)},\quad n>1     \tag{2-4}
$$

<br>

当然，事实上，我们更关心的是 $P_{i,n}$，利用 $P_{i,n} = P_{i,n^+}-P_{i,n+1^+}$
设 
$$
F_n(z) = \sum_{i=0}^{\infty}P_{i,n}\cdot z^i
$$
那么，
$$
\begin{align*}
  F_n(z)&=\sum_{i=0}^{\infty}(P_{i,n^+}-P_{i,n+1^+})\cdot z^i\\
  &=G_n(z) - G_{n+1}(z)\\
  &=\frac{z^np^n(1-pz)}{(1-z+z^{n+1}p^nq)(1-z)}-\frac{z^{n+1}p^{n+1}(1-pz)}{(1-z+z^{n+2}p^{n+1}q)(1-z)}\\
  &=\frac{z^np^n(1-pz)}{1-z}\cdot \frac{(1-z+z^{n+2}p^{n+1}q)-(1-z+z^{n+1}p^nq)zp}{(1-z+z^{n+1}p^nq)(1-z+z^{n+2}p^{n+1}q)}\\
  &=\frac{z^np^n(1-pz)}{1-z}\cdot \frac{(1-z)(1-pz)}{(1-z+z^{n+1}p^nq)(1-z+z^{n+2}p^{n+1}q)}\\
  &=\frac{z^np^n(1-pz)^2}{(1-z+z^{n+1}p^nq)(1-z+z^{n+2}p^{n+1}q)}
\end{align*}
$$
即
$$
F_n(z)=\frac{z^np^n(1-pz)^2}{(1-z+z^{n+1}p^nq)(1-z+z^{n+2}p^{n+1}q)}\quad n>1\tag{5}
$$
#### 2.2.2.3. 概率求和式


$$
P_{m,n^+} = \sum_{j=1}^{\lfloor m/n\rfloor} (-1)^{j+1}  q^{j-1}p^{jn} \binom{m-jn}{j-1} \begin{pmatrix*}
  \frac{q(1+m-jn)}{j}+p
\end{pmatrix*}
$$

## 2.3. 编程验证


<br>
<br>

## 2.4. 参考
[来自Wikipedia的参考：combinatorics - Probability for the length of the longest run in $n$ Bernoulli trials - Mathematics Stack Exchange](https://math.stackexchange.com/questions/59738/probability-for-the-length-of-the-longest-run-in-n-bernoulli-trials/59749#59749)
