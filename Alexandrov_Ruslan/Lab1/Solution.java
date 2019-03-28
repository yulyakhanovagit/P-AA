package main;

import java.util.ArrayList;

public class Solution {
    private int[][] mainField;
    private ArrayList<Integer> workingSln;
    private ArrayList<Integer> bestSln;
    private int numBest;  // numbers of best squares
    private int numWorking; // numbers of working squares
    private int squareSize;

    private long countComplexity;

    public Solution(int squareSize) {
        this.squareSize = squareSize;
        mainField = new int[squareSize][squareSize];
        numBest = (squareSize * squareSize) + 1;
        workingSln = new ArrayList<>();
        bestSln = new ArrayList<>();
        setThreeSquares();
    }

    private void fillSquare(SquarePoints s, int sideSize) {
        workingSln.add(s.getX());
        workingSln.add(s.getY());
        workingSln.add(sideSize);
        numWorking++;
        for (int x = s.getX(); x < s.getX() + sideSize; x++) {
            for (int y = s.getY(); y < s.getY() + sideSize; y++) {
                mainField[x][y] = 1;
            }
        }
    }

    private void removeFilled(SquarePoints s, int sideSize) {
        workingSln.remove(workingSln.size()-1);
        workingSln.remove(workingSln.size()-1);
        workingSln.remove(workingSln.size()-1);
        numWorking--;
        for (int x = s.getX(); x < s.getX() + sideSize; x++) {
            for (int y = s.getY(); y < s.getY() + sideSize; y++) {
                mainField[x][y] = 0;
            }
        }
    }

    private SquarePoints findEmpty() {
        for (int x = 0; x < squareSize; x++) {
            for (int y = 0; y < squareSize; y++) {
                if (IsEmpty(x,y)) {
                    return new SquarePoints(x,y);
                }
            }
        }
        return new SquarePoints(squareSize + 1, squareSize + 1);
    }

    private boolean IsEmpty(int x, int y) {
        return mainField[x][y] == 0;
    }

    private boolean checkOversize(SquarePoints square) {
        return (square.getX() > squareSize) || (square.getY() > squareSize);
    }

    public void findAllPlaces() {
        for (int i = squareSize -1; i >= 1; i--) {
        countComplexity++;
            var freeSquare = findEmpty();
            if (checkOversize(freeSquare)) {
                if (numWorking < numBest) {
                    bestSln.clear();
                    for (int j = 0; j < numWorking * 3; j++) {
                        bestSln.add(workingSln.get(j));
                    }
                    numBest = numWorking;
                }
                break;
            }
            if (numWorking == (numBest - 1)) break;
            i = getSmallerSize(freeSquare, i);
            var newFreeSquare = findEmpty();
            fillSquare(newFreeSquare, i);
//            System.out.println("Filled");
//            printMainField();
            findAllPlaces();
            removeFilled(freeSquare, i);
//            System.out.println("Removed");
//            printMainField();
        }
    }

    // get such small square as we can use
    private int getSmallerSize(SquarePoints square, int smallSquareSize) {
        int x;
        int y;
        for (x = square.getX(); x < squareSize; x++) {
            if (!IsEmpty(x, square.getY())) {
                break;
            }
        }
        for (y = square.getY(); y < squareSize; y++) {
            if (!IsEmpty(square.getX(), y)) {
                break;
            }
        }
//        System.out.println("Filled");
//        printMainField();
        int diffrenceInX = x - square.getX();
        int diffrenceInY = y - square.getY();
        if (diffrenceInX < smallSquareSize || diffrenceInY < smallSquareSize) {
            if (diffrenceInX > diffrenceInY) {
                smallSquareSize = diffrenceInY;
            } else {
                smallSquareSize = diffrenceInX;
            }
        }
        return smallSquareSize;
    }


    public void printMainField() {
        for (int x = 0; x < squareSize; x++) {
            for (int y = 0; y < squareSize; y++) {
                System.out.print(mainField[x][y] + " ");
            }
            System.out.println();
        }
    }

    public void printAnswer() {
//        System.out.print("Complexity = " + countComplexity);
        System.out.println(numBest);
        for (int i = 0; i < numBest * 3; i++) {
            System.out.print(bestSln.get(i) + 1);
            System.out.print(" ");
            System.out.print(bestSln.get(++i) + 1);
            System.out.print(" ");
           System.out.print(bestSln.get(++i));
          System.out.println();
        }
    }
    public void setThreeSquares() {
        int firstSetting;
        int secondSetting;
        if (squareSize % 2 == 0) {
            firstSetting = squareSize /2;
            secondSetting = squareSize /2;
        } else if (squareSize % 3 == 0) {
            firstSetting = (2 * squareSize) / 3;
            secondSetting = squareSize / 3;
        } else  if (squareSize % 5 == 0) {
            firstSetting = (3 * squareSize) / 5;
            secondSetting = (2 * squareSize) / 5;
        } else {
            firstSetting = (squareSize / 2) + 1;
            secondSetting = squareSize - ((squareSize / 2) + 1);
        }
        fillSquare(new SquarePoints(), firstSetting);
        var bottomSquare = new SquarePoints();
        bottomSquare.setX(firstSetting);
        var rightSquare = new SquarePoints();
        rightSquare.setY(firstSetting);
        fillSquare(bottomSquare, secondSetting);
        fillSquare(rightSquare, secondSetting);
    }
}

