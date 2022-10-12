import java.util.Scanner;

public class calculatorForCashier {
    public static void main(String[] args) {
        
        Scanner input = new Scanner(System.in);

        double itemA, qtyA, itemB, qtyB, itemC, qtyC, to1, to2, to3, total1, total2, dis1, dis2, dis3, disc;
        String discount;

        System.out.print("Input price item A = ");
        itemA = input.nextDouble();
        System.out.print("Input quantity of item A = ");
        qtyA = input.nextDouble();
        System.out.print("Input price item B = ");
        itemB = input.nextDouble();
        System.out.print("Input quantity of item B = ");
        qtyB = input.nextDouble();
        System.out.print("Input price item C = ");
        itemC = input.nextDouble();
        System.out.print("Input quantity of item C = ");
        qtyC = input.nextDouble();

        to1 = itemA * qtyA;
        to2 = itemB * qtyB;
        to3 = itemC * qtyC;
        total1 = to1 + to2 + to3;
        dis1 = 0.02; //diskon 2%
        dis2 = 0.05; //diskon 5%
        dis3 = 0.1; //diskon 10%

        if(total1 > 200000 && total1 < 500000){
            disc = dis1 * total1; 
            discount = "2%";
        } else if(total1 > 500000 && total1 < 1000000){
            disc = dis2 * total1;
            discount = "5%";
        } else {
            disc = dis3 * total1;
            discount = "10%";
        }

        total2 = total1 - disc;
        
        System.out.print("-----------------------------------------\n");
        System.out.print("\t\tNote Struct\t\t\n");
        System.out.print("-----------------------------------------\n");
        System.out.print("Name items | Price | Quantity | Total\n ");
        System.out.print(String.format("Item A\t\t%s %s \t%s\n", itemA, qtyA, to1));
        System.out.print(String.format(" Item B\t\t%s %s \t%s\n", itemB, qtyB, to2));
        System.out.print(String.format(" Item C\t\t%s %s \t%s\n", itemC, qtyC, to3));
        System.out.println("\tTotal\t\t: " + total1);
        System.out.println("========================================== Get a Discount " + discount);
        System.out.println("\tDiscount\t: " + disc);
        System.out.println("\tTotal to Pay\t: " + total2);
    }
}