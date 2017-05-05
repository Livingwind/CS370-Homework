
public class Buffer {
	private int buf_itemcount;
	private int buf_index;
	private double[] buf_array;
	
	public Buffer(){
		buf_itemcount = 0;
		buf_index = 0;
		buf_array = new double[1000];
	}
	
	public synchronized void produce( double item ){
		try{
			while( full() )
				wait();
		}
		catch(InterruptedException e){}
		
		if( buf_index == 1000 )
			buf_index = 0;
			
		buf_array[ buf_index ] = item;
		buf_itemcount++;
		buf_index++;
		
		notify();
	}
	
	public synchronized double consume( ){
		try{
			while( empty() )
				wait();
		}
		catch(InterruptedException e){}
		
		if( buf_index == 0 )
			buf_index = 1000;
		
		buf_index--;
		buf_itemcount--;
		double ret = buf_array[ buf_index ];
		
		notify();
		return ret;
	}
	
	public boolean empty(){
		return buf_itemcount == 0;
	}
	
	public boolean full(){
		return buf_itemcount == 1000;
	}
}
