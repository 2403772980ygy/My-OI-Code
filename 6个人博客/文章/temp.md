由于莫队的时间复杂度分析比较玄学，我们先感性理解一下

设块大小为x，区间端点移动一次为基本运算，是O(1)的

考虑左端点的移动距离，对于每个询问，由于我们排了序，左端点最多从前一个块移动到当前块,移动距离为$O(x)$，总时间复杂度为$O(mx)$

再考虑右端点，对于一个块内的所有询问，右端点最多从前一个块的最后一个询问的右端点n,移动回该块起点，然后由于排序完r单调递增，又移动回n.移动距离为$O(\frac{n}{x} \times n)=O(\frac{n^2}{x})​$

总时间复杂度为$O(mx+\frac{n^2}{x})$

根据均值不等式,当$x=\sqrt{\frac{n^2}{m}}=\frac{n}{\sqrt{m}}$时有最小值$O(n\sqrt{m})$

我们发现，块的个数是$\sqrt{m}$而不是通常时候的$\sqrt{n}$



