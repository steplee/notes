# Tensorflow notes
Not recording the basics...

[Stanford](http://web.stanford.edu/class/cs20si/lectures/

## [Queues](https://blog.metaflow.fr/tensorflow-how-to-optimise-your-input-pipeline-with-queues-and-multi-threading-e7c3874157e0)
Allow asynchronous, native data pipelining.
**Python is a bottleneck if used to feed data**

Basic example worflow:
```
x_input_data = tf.random_normal([3], mean=-1, stddev=4)
q = tf.FIFOQueue(capacity=3, dtypes=tf.float32)
enqueue_op = q.enqueue_many(x_input_data) 
input = q.dequeue() # Use input as an input tensor, every sess.run(.) call will dequeue the next element
# BUT: when q is empty, the program will hang, waiting for more inputs
```
The above example demonstrates the API, but is useless as it is not async.

The **QueueRunner** and **coordinator** facilitate synchronization and queue management.
> *You must add your QueueRunner to the TF collection 'QUEUE_RUNNERS'*

