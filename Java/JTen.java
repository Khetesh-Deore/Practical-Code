// File: ProducerConsumerDemo.java

class SharedBuffer {
    int data;
    boolean hasData = false;

    // Producer puts data into the buffer
    synchronized void produce(int value) throws InterruptedException {
        while (hasData) {
            wait(); // Wait if data is already there
        }
        data = value;
        System.out.println("Produced: " + data);
        hasData = true;
        notify(); // Notify the consumer
    }

    // Consumer consumes data from the buffer
    synchronized void consume() throws InterruptedException {
        while (!hasData) {
            wait(); // Wait until there is data
        }
        System.out.println("Consumed: " + data);
        hasData = false;
        notify(); // Notify the producer
    }
}

class Producer extends Thread {
    SharedBuffer buffer;

    Producer(SharedBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        try {
            for (int i = 1; i <= 10; i++) {
                buffer.produce(i);
                Thread.sleep(500); // Simulate time delay
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Consumer extends Thread {
    SharedBuffer buffer;

    Consumer(SharedBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        try {
            for (int i = 1; i <= 10; i++) {
                buffer.consume();
                Thread.sleep(500); // Simulate time delay
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

public class JTen {
    public static void main(String[] args) {
        SharedBuffer buffer = new SharedBuffer();
        Producer p = new Producer(buffer);
        Consumer c = new Consumer(buffer);
        p.start();
        c.start();
    }
}
