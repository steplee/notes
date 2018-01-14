# (Spark RDDs)[https://www.usenix.org/system/files/conference/nsdi12/nsdi12-final138.pdfs://www.usenix.org/system/files/conference/nsdi12/nsdi12-final138.pdf]

 - Cache results in memory (MapReduce must write to HDFS)
 - Coarse-grained (not fine-grained like SQL)
 - **Transformations** create RDDs from other RDDs (e.g. through map,filter,etc.)
 - RDDs are first created from objects in *stable storage*, such as HDFS logs.
 - **Actions** are operations that actually force a computation
    - Transformations are lazy.
 - Calling `persist` will cache results to disk
 - `collect` seems to be a strict action that forces computation
 - Using *lineage* RDDs formed by operations can be regenerated from their base RDDs of stable storage.
 - Tailored for coarse-grained writes, data is immutable
 - Tasks are assigned to support data locality
 - Scala represents each closure as an Object. They are serialized and sent to nodes in the cluster to operate on RDDs.
 - RDDs are statically typed.

### Logistic Regression example
```scala
val points = spark.textFile(...)
                  .map(parsePoint).persist()
var w = // random initial vector
for (i <- 1 to ITERATIONS) {
  val gradient = points.map{ p =>
    p.x * (1/(1+exp(-p.y*(w dot p.x)))-1)*p.y
  }.reduce((a,b) => a+b)
  w -= gradient
}
```

### PageRank example
```scala
val links = spark.textFile(...).map(...).persist()
var ranks = ... // RDD of (URL, rank) pairs
for (i <- 1 to ITERATIONS) {
  // Build an RDD of (targetURL, float) pairs
  // with the contributions sent by each page
  val contribs = links.join(ranks).flatMap {
    (url, (links, rank)) =>
      links.map(dest => (dest, rank/links.size))
  }
// Sum contributions by URL and get new ranks
ranks = contribs.reduceByKey((x,y) => x+y)
                 .mapValues(sum => a/N + (1-a)*sum)
}
```
 - In a job with many iterations, `ranks` should be replicated to avoid failure recomputations.
    - This can be done with `persist` with `RELIABLE` flag
 - **Partitioning** intelligently is important to performance.
    - The thing to optimize in this case is the call to `join`
    - In this PR example, we could have partition on a hash of the `links` and `ranks`.
    - Also could have partitioned by domain name since they are more likely to link to eachother.
    - Can use `partitionBy(func)`

## Representing RDDs
 1. Partitions
 2. Dependencies
 	a. Narrow dependencies (e.g. `map`, `filter`)
	b. Wide dependencies (e.g. `join`, `groupBy`)
 3. A function to compute the RDD given parents
 4. Metadata about partitioning and data placement

## Job Scheduling
 - Runs on top of Mesos
 - Build DAG with Actions at leaves
 - Maximize reuse of RDDs in local memory

## Memory
 1. Java objects
 2. Serialized data
 3. Serialized on-disk data

 RDDs in memory are evicted according to an LRU policy.
