import static org.junit.Assert.*;

import org.junit.Test;
import editdistance.EditDistance;


public class TestEdit {

  /**both strings null**/
  @Test(expected = NullPointerException.class)
  public void testNull() {
    EditDistance.editDistanceRecursive(null, null);
    EditDistance.editDistanceDyn(null, null);

  }

  /**both strings empty**/
  @Test
  public void bothEmptyString() {
    assertEquals("wrong edit distance between two empty strings", EditDistance.editDistanceRecursive("", ""), 0);
    assertEquals("wrong edit distance between two empty strings", EditDistance.editDistanceDyn("", ""), 0);
  }

  /**first string empty**/
  @Test
  public void firstEmptyString() {
    assertEquals("wrong edit distance if the source string is empty", EditDistance.editDistanceRecursive("", "empty"), 5);
    assertEquals("wrong edit distance if the source string is empty", EditDistance.editDistanceDyn("", "empty"), 5);
  }
  /**second string empty**/
  @Test
  public void secondEmptyString() {
    assertEquals("wrong edit distance if the objective string is empty", EditDistance.editDistanceRecursive("empty", ""), 5);
    assertEquals("wrong edit distance if the objective string is empty", EditDistance.editDistanceDyn("empty", ""), 5);
  }
  @Test
  public void wrongInsertion() {
    assertEquals("wrong insertion", EditDistance.editDistanceRecursive("prova", "prva"), 1);
    assertEquals("wrong insertion", EditDistance.editDistanceDyn("prova", "prva"), 1);
  }

  @Test
  public void wrongDeletion() {
    assertEquals("wrong deletion", EditDistance.editDistanceRecursive("prova", "proova"), 1);
    assertEquals("wrong deletion", EditDistance.editDistanceDyn("prova", "proova"), 1);
  }
  @Test
  public void sameString() {
    assertEquals("the string are the same", EditDistance.editDistanceRecursive("prova", "prova"), 0);
    assertEquals("the string are the same", EditDistance.editDistanceDyn("prova", "prova"), 0);
  }

  @Test
  public void noCommonCharacter() {
    assertEquals("the strings are completely different", EditDistance.editDistanceRecursive("abcd", "efgh"), 8);
    assertEquals("the strings are completely different", EditDistance.editDistanceDyn("abcd", "efgh"), 8);
  }

  /**first string is a substring of second**/
  @Test
  public void SubstringFirst() {
    assertEquals("there should be 2 added character", EditDistance.editDistanceRecursive("av", "java"), 2);
    assertEquals("there should be 2 added character", EditDistance.editDistanceDyn("av", "java"), 2);

  }

  /**second string is a substring of first**/
  @Test
  public void SubstringSecond() {
    assertEquals("there should be 11 deletion", EditDistance.editDistanceRecursive("iReallyLikeJava", "like"), 11);
    assertEquals("there should be 11 deletion", EditDistance.editDistanceDyn("iReallyLikeJava", "like"), 11);
  }

}
