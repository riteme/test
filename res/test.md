# Markdown World
[Jump to Math World](#1)

## Basic Markdown
天灭`Pascal`  
```cpp
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    
    cout << "Hello, world!" << endl;
    
    return 0;
}
```

```python
import sys

if len(sys.argv) > 0:
    print(' '.join(sys.argv)
else:
    print('Nothing in the parameters.')
```

* [ ] Unfinished
* [x] Finished

## Mathjax
$$ 233 \neq 244 \tag{233} $$
行内公式$ 233 \neq 666 = 777 $ 真的是inline  
$dollar

## Link
百毒 is here: [Link][baidu]
[baidu]: http://www.baidu.com/ "Baidu"

## <span id="1"> Math World </span>
我的算法是 $ \Theta (n ^ 2 \log n) $
$$ \sqrt{2} \approx 1.414 \tag{1} $$
$$ \sum_{i = 1}^\infty i = - \frac{1}{12} \tag{1.1} $$
$$ \infty \times \infty = \infty \tag{1.2} $$

已知$ P_1 (x_1, y_1) $和$ P_2 (x_2, y_2) $，求$ |P_1P_2| $：
$$ |P_1P_2| = \sqrt{(x_1 + x_2)^2 + (y_1 + y_2)^2} \tag{1.3} $$

矩阵:
$$
\left[
\begin{matrix}
1 & 2 \\
3 & 4
\end{matrix}
\right]
\times
\left[
\begin{matrix}
1 & 0 \\
0 & 1
\end{matrix}
\right]
=
\left[
\begin{matrix}
1 & 2 \\
3 & 4
\end{matrix}
\right]
\tag{1.4}
$$

文字：
$$ 512\texttt{MB} $$

定理:
$$ l \bot \alpha, \, l \subset \beta \Rightarrow \alpha \bot \beta$$