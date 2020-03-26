package exampleapp;

import editdistance.EditDistance;

public class ExampleApp {
  public static void main(String[] args) {
    int distance;
    distance = EditDistance.editDistanceRecursive("ciao", "caio");
    System.out.println(distance);
  }
}
