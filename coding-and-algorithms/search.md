# Search
## 2D Binary Search
[Dijkstra on Saddleback Search](http://www.cs.utexas.edu/users/EWD/ewd09xx/EWD934.PDF)
[Book](https://c51ed804-a-62cb3a1a-s-sites.googlegroups.com/site/algoxy/home/elementary-algorithms.pdf?attachauth=ANoY7cr5mK_QBMyPlXchjHeEcUyCzpNSLd3afw_M3hmRcfB6iI7hskPuiPcmoNXsfwk3TnZyp2aF0bIA9qbZo0sWmxWECzV5pp0b1g9irROSWzdboiV3AsaIm-7Erl6IdyLEmlF82vxdWWslL32PUeAP-6f-PlHhQQBE1EuC-NtmPVC2Q1OcPlcuSXjnxMQ6ezANSKh78OsmxsmDrSnCqXKGqMTnqNC0-MuQHm5EWKishDS3pR0LcPc%3D&attredirects=0)

Given sorted 2D array.
Given strictly increasing f( x,y )
Want to accumulate solutions to some predicate of f(.,.)

Brute-force on all x,y pairs is O(n^2)

### Saddleback search

let array be z-by-z.
Start at top-left : pt = (0,z)
if f(p,q) < z : eliminate all points in vertical line below (p,q) i.e. all (p,y)
if f(p,q) > z : eliminate all points in horizont line right (p,q) i.e. all (x,q)

```Haskell
solve f z = search 0 z where
	search p q | p > z | | q < 0 = []
  		   | z' < z = search (p + 1) q
		   | z' > z = search p (q - 1)
		   | otherwise = (p, q) : search (p + 1) (q - 1)
         	where z' = f p q

```
Since every iteartion we advance one of p or q, it is 2(z+1) running time.
It walks down in a diagonal manner.

#### Improving it
Add binary search when considering next query point
````Haskell
bsearch f y (l, u) | u <= l = l
		   | f m  y = if f (m + 1)  y
			      then bsearch f y (m + 1, u) else m
		   | otherwise = bsearch f y (l, m-1)
	where m = (l + u) div 2
```


