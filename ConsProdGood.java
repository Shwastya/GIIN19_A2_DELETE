// Implementacion correcta del problema productor/consumidor
class Q {
   int n;
    boolean valueSet=false;
   
   synchronized int get () {
	if (!valueSet)
	   try {
    	          wait();
	   } catch (InterruptedException e ) {
	     	System.out.println("captura la excepcion");
	   }
	System.out.println("Consume: "+n);
	valueSet=false;
	notify();
	return n;
   }

   synchronized void put (int n) {
	if (valueSet)
	   try {
    	          wait();
	   } catch (InterruptedException e ) {
	     	System.out.println("captura la excepcion");
	   }

	this.n=n;
	valueSet=true;
	System.out.println("Produce: "+n);
	notify();
   }
}

class Producer implements Runnable {
   Q q;

   Producer(Q q) {
	this.q=q;
	new Thread(this,"Productor").start();
   }

   public void run() {
	int i=0;
	while(true) q.put(i++);
   }
}

class Consumer implements Runnable {
   Q q;

   Consumer(Q q) {
	this.q=q;
	new Thread(this,"Consumidor").start();
   }

   public void run() {
	while(true) q.get();
   }
}

class PCFijo {
   public static void main(String args[]) {
       Q q = new Q();
for (int x=0;x<5;x++){
      new Producer(q);
      new Consumer(q);
}
       System.out.println("Pulse Ctrl-C para finalizar");
   }
}

