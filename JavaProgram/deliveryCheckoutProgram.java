import java.util.Scanner;

public class deliveryCheckoutProgram{
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);

        String foodName;
        long price, shipcost, express, total;
        int questions;

        System.out.print("Enter a food name: ");
        foodName = sc.nextLine();
        System.out.print("Enter the food price: IDR ");
        price = sc.nextLong();
        System.out.print("Do you want express delivery (0 = no, 1 = yes)? ");
        questions = sc.nextInt();

        express = 25000;

        if(price < 100000){
            shipcost = 20000;
        } else {
            shipcost = 30000;
        }

        if  (questions == 0){
            total = price + shipcost;
        } else {
            total = price + shipcost + express;
        }
        
        System.out.println("RECEIPT");
        System.out.println(foodName + "\tIDR " + price);
        System.out.println("Shipping costs\tRp " + shipcost);
        System.out.println("TOTAL\t\tRp " + total);

    }
}