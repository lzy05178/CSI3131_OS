//
//
//import java.util.Arrays;
//import java.util.Scanner;
//public class a {
//    public static void main(String[] args) throws InterruptedException {
//        while (true){
//            try {
//                Scanner scanner = new Scanner(System.in);
//                System.out.print("Enter the number of Fibonacci numbers to generate: ");
//                final int number = scanner.nextInt();
//                int[] array = new int[number + 1];
//                scanner.close();
//                Thread t = new Thread(new Runnable() {
//                    @Override
//                    public void run() {
//                        for (int i = 0; i < array.length; i++) {
//                            if (i == 0) {
//                                array[i] = 0;
//                            } else if (i == 1) {
//                                array[i] = 1;
//                            } else {
//                                array[i] = array[i - 1] + array[i - 2];
//                            }
//                        }
//                    }
//                });
//                t.start();
//                t.join();
//                System.out.println(Arrays.toString(array));
//                break;
//            } catch (Exception e) {
//                System.out.println("Invalid input. Please enter an integer.");
//            }
//        }
//
//    }
//}
