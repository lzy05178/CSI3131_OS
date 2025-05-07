import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {



    private static boolean isPrime(int n) {

        if (n <= 1) {
            return false;
        }
        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
    public static void main(String[] args) {

    while (true){
        try {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter a number: ");
            final int number = scanner.nextInt();

            Thread t = new Thread(new Runnable() {
                @Override
                public void run() {
                    System.out.println("Prime numbers up to " + number + ":");
                    for (int i = 2; i <= number; i++) {
                        if (isPrime(i)) {
                            System.out.println(i);
                        }
                    }
                }
            });
            t.start();
            scanner.close();
            break;

        } catch (InputMismatchException e) {
            System.out.println("Invalid input. Please enter an integer.");
        }
    }


    }

}