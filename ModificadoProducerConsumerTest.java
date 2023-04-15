public class ModificadoProducerConsumerTest {
    public static void main(String[] args) {
        CubbyHole c = new CubbyHole();
        Producer[] producers = new Producer[5];
        Consumer[] consumers = new Consumer[5];
        for (int i = 0; i < 5; i++) {
            producers[i] = new Producer(c, i + 1);
            consumers[i] = new Consumer(c, i + 1);
        }
        for (int i = 0; i < 5; i++) {
            producers[i].start();
            consumers[i].start();
        }
    }
}
