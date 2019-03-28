package main;

import java.util.Scanner;

public class Runner {

    public static void main(String[] args) {
        var in = new Scanner(System.in);
        System.out.println("Enter size:");
        var size = in.nextInt();
        if (size < 2) {
            System.out.println("N < 2");
            return;
        }

        var solution = new Solution(size);
        solution.findAllPlaces();
        solution.printAnswer();
//        solution.printMainField();
    }
}
