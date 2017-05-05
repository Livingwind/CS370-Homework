import java.util.Random;

public class Producer implements Runnable{
	private double buf_total;
	private Buffer buf;
	
	public Producer( Buffer buf ){
		buf_total = 0;
		this.buf = buf;
	}
	
	@Override
	public void run() {
		Double value;
		Random random = new Random();
		for( int i = 1; i <= 1000000; i++ ){
			value = random.nextDouble() * 100.0;
			buf.produce( value );
			buf_total += value;
			
			if( i % 100000 == 0 )
				System.out.println( "Producer: Produced " + i + " items, "
						+ "Cumulative value of generated items=" + String.format("%.3f",buf_total) );
		}
		System.out.println("Producer: Finished generating 1,000,000 items");
	}
}
