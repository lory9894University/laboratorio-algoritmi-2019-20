package editdistance;

import java.util.Arrays;
import java.util.stream.IntStream;

public class EditDistance {
  /**
   * calculate the necessary number of insertion/deletion of characters to
   * transform s1 in s2, in a recursive manner
   *
   * @param s1 source string
   * @param s2 objective string
   * @return the edit distance between s1 and s2
   **/
  public static int editDistanceRecursive(String s1, String s2) {
    int dNop, dIns, dCanc;
    dNop = dIns = dCanc = 0;

    if (s1.length() == 0)
      return s2.length();
    if (s2.length() == 0)
      return s1.length();

    dNop = s1.charAt(0) == s2.charAt(0) ? editDistanceRecursive(s1.substring(1), s2.substring(1)) : Integer.MAX_VALUE;

    dCanc = 1 + editDistanceRecursive(s1, s2.substring(1));
    dIns = 1 + editDistanceRecursive(s1.substring(1), s2);
    return IntStream.of(dNop, dIns, dCanc).min().getAsInt();
  }

  /**
   * calculate the necessary number of insertion/deletion of characters to
   * transform s1 in s2, using dynamic programming paradigm
   *
   * @param s1 source string
   * @param s2 objective string
   * @return the edit distance between s1 and s2
   **/
  public static int editDistanceDyn(String s1, String s2) {
    int x = s1.length();
    int y = s2.length();
    int[][] matrix = new int[x][y];

    for (int[] arr : matrix) {
      Arrays.fill(arr, -1);
    }
    return calculateDistance(s1, s2, matrix, x - 1, y - 1);
  }

  /**
   * populate the matrix of edit distance of s1 and s2
   *
   * @param s1 source string
   * @param s2 objective string
   * @return the edit distance between s1 and s2
   **/
  private static int calculateDistance(String s1, String s2, int[][] matrix, int i, int j) {
    if (i<0)
      return j + 1;
    if (j<0)
      return i + 1;

    if (matrix[i][j]!=-1)
      return matrix[i][j];

    if (s1.charAt(i) == s2.charAt(j))
      matrix[i][j] = calculateDistance(s1, s2, matrix, i - 1, j - 1);
    else {
      matrix[i][j] = 1 + Math.min(calculateDistance(s1, s2, matrix, i, j - 1), calculateDistance(s1, s2, matrix, i - 1, j));
    }

    return matrix[i][j];
  }
}
