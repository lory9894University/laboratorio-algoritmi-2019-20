package exampleapp;

import editdistance.EditDistance;

import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class ExampleApp {
  ArrayList<String> toCorrect = null;
  private ArrayList<String> dictionary = null;

  public ExampleApp(String toBeCorrected, String dictionary) {

    try (BufferedReader in = new BufferedReader(new FileReader(toBeCorrected))) {
      toCorrect = in.lines().map(x -> x.replaceAll("\\p{Punct}", "").toLowerCase())
          .flatMap((a) -> Stream.of(a.split(" ")))
          .collect(Collectors.toCollection(ArrayList::new));
    } catch (IOException e) {
      System.err.println(e.getMessage());
    }

    try (BufferedReader in = new BufferedReader(new FileReader(dictionary))) {
      this.dictionary = in.lines().collect(Collectors.toCollection(ArrayList::new));
    } catch (IOException e) {
      System.err.println(e.getMessage());
    }

  }

  public static void main(String[] args) {
    ExampleApp autocorrect = new ExampleApp("documents/correctme.txt", "documents/dictionary.txt");
    autocorrect.getCorrection().entrySet().stream().filter(entry -> entry.getValue().get(0).compareTo(entry.getKey()) != 0).forEach(System.out::println);
  }

  private ArrayList<String> fixWord(String word) {
    ArrayList<String> alternatives = new ArrayList<>();
    int minEditDistance = Integer.MAX_VALUE;
    int localEditDistance = 0;

    for (String correctWord : dictionary) {
      localEditDistance = EditDistance.editDistanceDyn(word, correctWord);
      if (localEditDistance < minEditDistance) {
        alternatives.clear();
        minEditDistance = localEditDistance;
      }
      if (localEditDistance == minEditDistance)
        alternatives.add(correctWord);
    }

    return alternatives;
  }

  public HashMap<String, ArrayList<String>> getCorrection() {
    HashMap<String, ArrayList<String>> correction = new HashMap<>();

    for (String word : toCorrect)
      correction.put(word, fixWord(word));
    return correction;
  }
}
