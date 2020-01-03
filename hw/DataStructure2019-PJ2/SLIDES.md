# Dynamic Shortest Path

<br>

## December 25th, 2019, Xue Zhenliang<br>Department of Computer Science

<img alt="Creative Commons License" class="cc" src="assets/cc4-by-nc-sa.png">

***

###### Overview {: .border-gray}

Fast query on random graphs ($m = 3 \times 10^6$).

* Dense graph: $< 0.05\mathrm{ms}$ ($n = 3000$, typically $20μ\mathrm s$)
* Sparse graph: $< 10\mathrm{ms}$ ($n = 10^6$, typically $5\mathrm{ms}$)

---

<br />

**General Method**: Dijkstra's algorithm with hybrid heuristics.

---

* Bidirectional A\*.
---
* Landmarks [1].
---
* Edge pruning.
---
* Block-cut tree.

***

###### Bidirectional A\* {: .border-aqua}

---

![](assets/astar.png)

----

* All *admissible* heuristic estimates $h$ are acceptable.
    * $h(s → u) + h(u → t) \equiv c$ is not reqiured.
---
* Process each vertex at most once.
    * May overlap in two heaps.

***

###### Landmarks {: .border-blue}

Choose some vertices as landmarks to guide A\* algorithm.

---

**Idea**: triangle inequality.

$$
δ(s→u) + δ(u→v) \geqslant δ(s→v)
$$

---

By symmetric property:

$$
δ(u→v) \geqslant |δ(s→u) - δ(s→v)|
$$

---

Compute shortest paths for each source $s$ in set $S$.

<br />

$$
h(u→v) = \max\limits_{s \in S}\left\{|δ(s→u) - δ(s→v)|\right\}
\tag{1}
$$

<br />

---

**In Practice**: choose $S' \subseteq S$ with best estimates [1].

$10 \leqslant |S| \leqslant 1000$ ⇒ $|S'| \approx 5$.

***

###### Edge Pruning {: .border-red}

Detect long edges during shortest path computation.

---

* Use Tarjan's LCA algorithm to evaluate path lengths.
    * $\mathrm O((n + m) α(n))$.
---
* Effective on dense random graphs.
---
* Not friendly to edge removal.
---
    * \*Multi-level pruning with a probability parameter.

***

###### Block-Cut Tree {: .border-green}

Algorithm instances are only installed on *2-vertex-connected* components.

---

* Aimed to avoid exhausted search between disconnected endpoints.
---
* **QAQ**: Most graphs (random graphs/meshes) have few cut vertices.

***

###### References {: .border-orange}

<div class="before-references"></div>
1. "Efficient Point-to-Point Shortest Path Algorithms". from Princeton University.
2. Pijls, Wim; Post, Henk "Yet another bidirectional algorithm for shortest paths" In *Econometric Institute Report EI 2009-10/Econometric Institute, Erasmus University Rotterdam. Erasmus School of Economics*.