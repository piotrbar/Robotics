import java.util.*;

public class Covariance {
    public static void main (String [] args) {
        
        /* Our values in cm:
           x        y 
          -1      -0,5
          -0,6    0,6
          -0,3    1,2
          0,2     1,2
          0,3     1,7
          0,3     0,4
          0,4     0,6
          0,7     1,3
          0,8     0,4
          1,3     0,7
        */

        Scanner in = new Scanner(System.in);
        System.out.println("Give number of measurements: ");
        int numOfLocations = in.nextInt();
        double [] xs = new double [20];
        double [] ys = new double [20];

        System.out.println("Give x and y in centimeters: ");
        for(int i=0; i<numOfLocations; ++i) {
            xs[i] = in.nextDouble();
            ys[i] = in.nextDouble();
        }

        //Calculating mean for x and y.
        double xMean = 0.0;
        double yMean = 0.0;
        double xSum = 0.0;
        double ySum = 0.0;
        for(int i=0; i<numOfLocations; ++i) {
            xSum+=xs[i];
            ySum+=ys[i];
        }
        xMean = xSum/numOfLocations;
        yMean = ySum/numOfLocations;

        //Calculating covariance matrix.
        //First value.
        double sum = 0;
        for(int i=0; i<numOfLocations; ++i) {
            sum+=(xs[i]-xMean)*(xs[i]-xMean);
        }    
        double firstValue = sum/numOfLocations;

        //Diagonal values.
        sum = 0;
        for(int i=0; i<numOfLocations; ++i) {
            sum+=(xs[i]-xMean)*(ys[i]-yMean);
        }
        double diagonalValues = sum/numOfLocations;

        //Forth value.
        sum = 0;
        for(int i=0; i<numOfLocations; ++i) {
            sum+=(ys[i]-yMean)*(ys[i]-yMean);;
        }
        double forthValue = sum/numOfLocations;

        System.out.println("Covariance matrix: ");
        System.out.println(firstValue + " " + diagonalValues);
        System.out.println(diagonalValues + " " + forthValue);
    }
}
