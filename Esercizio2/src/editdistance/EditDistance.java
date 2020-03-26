package editdistance;

import java.util.stream.IntStream;

public class EditDistance {
  public static int editdDistance(String s1, String s2) {
    int dNop, dIns, dCanc;
    dNop = dIns = dCanc = 0;

    if (s1.length() == 0)
      return s2.length();
    if (s2.length() == 0)
      return s1.length();

    dNop = s1.charAt(0) == s2.charAt(0) ? editdDistance(s1.substring(1), s2.substring(1)) : Integer.MAX_VALUE;

    dCanc = 1 + editdDistance(s1, s2.substring(1));
    dIns = 1 + editdDistance(s1.substring(1), s2);
    return IntStream.of(dNop, dIns, dCanc).min().getAsInt();
  }
}
