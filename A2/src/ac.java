public class ac {
    public static void main(String[] args) {
        int[][]  array = {{1,2,3},{1,2,3}};
        for (int i=0;i<2;i++){
            for (int j=0;j<3;j++){
                System.out.print(array[i][j]+" ");
                System.out.print("空行");
            }
        }
    }
}
