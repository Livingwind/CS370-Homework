
public class Consumer implements Runnable{
	
	private double buf_total;
	private Buffer buf;
	
	public Consumer( Buffer buf ){
		buf_total = 0;
		this.buf = buf;
	}

	@Override
	public void run() {
		for( int i = 1; i <= 1000000; i++ ){
			buf_total += buf.consume();
			
			if( i % 100000 == 0 )
				System.out.println( "Consumer: Consumed " + i + " items, "
						+ "Cumulative value of consumed items=" + String.format("%.3f",buf_total) );
		}
		
		System.out.println("Consumer: Finished consuming 1,000,000 items");
	}
}
