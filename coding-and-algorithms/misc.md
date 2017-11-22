# Stuff

#### C++ priority queue from multiset
```
if( Q.size() < K ) Q.insert(s);
else if(*Q.begin() < s) {
  Q.erase(Q.begin());
  Q.insert(s);
}
```
