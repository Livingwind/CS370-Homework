Written by: Christopher William Westerman

runnable using:
    make
    java ProducerConsumer

ProducerConsumer.java: Driver for the program, creates producer and consumer threads.
Producer.java: Produces a random number and places into the circular buffer.
Consumer.java: Consumes values placed into the circular buffer.
Buffer.java: Data structure for Producer and Consumer to interact with.  Maintains a circular
    buffer of 1000 doubles.
