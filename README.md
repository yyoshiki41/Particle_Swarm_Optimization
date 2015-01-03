# Particle Swarm Optimization
==============
粒子群最適化


## Contributor 
Yoshiki Nakagawa

## Example
![Image of PSO](https://https://github.com/yyoshiki41/Paticle_Swarm_Optimization.png)


## Benchmark functions
- 2n-minima
<pre>
// 2変数
f(x, y) = (x^4 - 16*x^2 + 5*x) + (y^4 - 16*y^2 + 5*y)
// 多変数
f(x_n) = Σ {(x_n)^4 - 16*(x_n)^2 + 5*(x_n)}
</pre>
- rosenbrock
<pre>
// 2変数
f(x, y) = (1-x)^2 + 100*(y - x^2)^2
// 多変数
f(x_n) = Σ {(1-(x_n)^2 + 100*((x_n+1) - (x_n)^2)^2}
</pre>
