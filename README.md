# RingBuffer

#### Background
One of the most common data structures “queue” implements the FIFO principle of managing elements — first input/first output. Queues are ubiquitous in IT when the number of incoming tasks exceeds the bandwidth of a component processing them. In this case, tasks are buffered, that is, they are queued for execution. The order of their execution must correspond to the order of placing them in the queue. A task that remains in a queue longer than the others must be executed first, as soon as the resources of the processing component are released for that.
The Queue ADT can have different internal implementations, depending on its scope. One such possible implementation is the Ring Buffer. A circular buffer is an array of elements, the end of which is logically connected to the beginning, that is, together they represent a continuous sequence of elements. In reality, a circular buffer is represented using an ordinary array of a given length, however, when operating with it using a pointer, when the end of the buffer is reached, the pointer moves to the beginning, as if there were no gap between the first and last elements of the array.

#### Installation
Simply copy ```ringbuffer.h``` to your project/include directory and include it.
