// Implementacion incorrecta de del problema productor/consumidor
class Q {
 int n;
 synchronized int get () {
 System.out.println("Consume: "+n);
 return n;
 }
 synchronized void put (int n) {
 this.n=n;
 System.out.println("Produce: "+n);
 }
}
class Producer implements Runnable {
 Q q;
 Producer(Q q) {
 this.q=q;
 new Thread(this,"Productor").start();
 }
 public void run() {
 int i;
 for (i = 0; i < 10; i++) q.put(i);
 }
}
class Consumer implements Runnable {
 Q q;
 Consumer(Q q) {
 this.q=q;
 new Thread(this,"Consumidor").start();
 }
 public void run() {
 int i;
 for (i = 0; i < 10; i++) q.get();
 }
 }
class PC {
 public static void main(String args[]) {
 Q q = new Q();
 new Producer(q);
 new Consumer(q);
 }
}
