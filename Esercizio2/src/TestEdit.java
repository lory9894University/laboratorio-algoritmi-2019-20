import static org.junit.Assert.*;

import org.junit.Test;
import editdistance.EditDistance;


public class TestEdit {

  @Test(expected = NullPointerException.class)
  public void testNull() {
    EditDistance.editDistanceRecursive(null, null);

  }

  @Test
  public void emptyString() {
    assertEquals("wrong edit distance between two empty strings", EditDistance.editDistanceRecursive("", ""), 0);
    assertEquals("wrong edit distance if the source string is empty", EditDistance.editDistanceRecursive("", "empty"), 5);
    assertEquals("wrong edit distance if the objective string is empty", EditDistance.editDistanceRecursive("empty", ""), 5);
  }

  @Test
  public void peculiarDifferences() {
    assertEquals("wrong insertion", EditDistance.editDistanceRecursive("prova", "prva"), 1);
    assertEquals("wrong deletion", EditDistance.editDistanceRecursive("prova", "proova"), 1);
    assertEquals("the string are the same", EditDistance.editDistanceRecursive("prova", "prova"), 0);
    assertEquals("the strings are completely different", EditDistance.editDistanceRecursive("abcd", "efgh"), 8);

  }

}
