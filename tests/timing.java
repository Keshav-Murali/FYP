import java.util.SplittableRandom;

public class timing {
    public static void main(String args[]){  
	SplittableRandom g = new SplittableRandom();
	long arr[] = new long[100000000];
	long startTime = System.nanoTime();
	for(int i = 0; i < 100000000; i++) {
	   arr[i] = g.nextLong();
//	g.nextLong();
	}
	long exitTime = System.nanoTime();
	System.out.println("Time taken for SplitMix (earlier algorithm): " + (exitTime - startTime)/1000000);
	System.out.println("Value is: " + arr[50000]);
	System.exit(0);
    }
}
