package edu.cscc;
import java.util.*;
//Anthony Quesenberry 9/19/18 Hello
/*
Anthony Quesenberry
9/19/18
Hello
 */
public class Main {

    private static Scanner input = new Scanner(System.in);

    public static void main(String[] args) {
	// write your code here
        Double area, radius, perimeter;

        //Input
        System.out.println("Circle Program");
        System.out.print("Enter the radius of your circle: ");
        radius = input.nextDouble();

        //Output
        area= Math.PI *Math.pow(radius,2);
        perimeter = Math.PI *radius * 2;

        System.out.println("The area of a circle with the radius of " + radius + " is " + area);
        System.out.println("The perimeter of a circle with a radius of " + radius + " is " + perimeter);

    }
}
