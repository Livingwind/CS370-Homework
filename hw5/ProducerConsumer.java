
public class ProducerConsumer {
	public static void main( String[] args ){
		Buffer buf = new Buffer();
		
		Thread t_Producer = new Thread( new Producer(buf) );
		Thread t_Consumer = new Thread( new Consumer(buf) );
		t_Producer.start();
		t_Consumer.start();
		
		try{ t_Producer.join(); }
		catch( InterruptedException e ){}
		try{ t_Consumer.join(); }
		catch( InterruptedException e ){}
		
		System.out.println("Exiting!");
		
	}
	
}
