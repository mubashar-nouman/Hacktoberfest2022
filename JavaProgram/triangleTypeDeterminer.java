import java.util.Scanner;

public class triangleTypeDeterminer {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int side1, side2, side3;

        System.out.print("Input the first side of triangle = ");
        side1 = sc.nextInt();
        System.out.print("Input the second side of triangle = ");
        side2 = sc.nextInt();
        System.out.print("Input the third side of triangle = ");
        side3 = sc.nextInt();
        

        if (side1 == side2 && side1 == side2 && side1 == side3) {
            System.out.println("the triangle is equailateral");
        } else if (side1 == side2 || side1 == side3 || side2 == side3) {
            System.out.println("the triangle is isosceles");
        } else {
            System.out.println("the triangle arbitrary");
        }

    }
}