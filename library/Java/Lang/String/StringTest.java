package Java.Lang.String;

import static org.junit.Assert.*;
import org.junit.Test;

public class StringTest {

    @Test
    public void testToString() {
    	String actual = "abc";
        assertEquals("abc",actual.toString());
    }

}