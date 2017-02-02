/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cardtest;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.nio.charset.Charset;
import java.sql.Timestamp;

/**
 *
 * @author jmillen
 */
public class CardTest {

    private static void CheckNumber(int[] cardNum)
    {
        int[] reversed = new int[16];
        int odd_accumulator = 0;
        int even_accumulator = 0;

        for (int i = 0, j = 15; i < 16; i++,j--)
        {
            reversed[j] = cardNum[i];
        }

        for (int i = 0; i < 16; i++)
        {
            // Odd/Even processing appears reversed because of 0 based index
            if (i%2 == 0)
            {
                odd_accumulator += reversed[i];
            }
            else
            {
                int even_num = reversed[i] * 2;

                if (even_num > 9)
                {
                    even_num -= 10;
                }

                even_accumulator += even_num;
            }
        }

        if ((odd_accumulator + even_accumulator)%10 > 0)
        {
            System.out.println("FAILURE");
        }
        else
        {
            System.out.println("SUCCESS");
        }
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        File file = new File("/usr/temp.txt");
        Charset encoding = Charset.defaultCharset();
        Timestamp ts = new Timestamp(System.currentTimeMillis());

        try
        {
            InputStream in = new FileInputStream(file);
            Reader reader = new InputStreamReader(in, encoding);
            int readValue;
            int[] cardNum = new int[16];
            int idx = 0;

            while ((readValue = reader.read()) != -1)
            {
                char ch = (char)readValue;

                if (ch == '\n')
                {
                    CheckNumber(cardNum);
                    cardNum = new int[16];
                    idx = 0;
                }
                else
                {
                    int val = Character.getNumericValue(ch);

                    if (val < 0)
                    {
                        val = 0;
                    }
                    if (idx < 16)
                    {
                        cardNum[idx++] = val;
                    }
                }
            }

            if (idx > 0)
            {
                CheckNumber(cardNum);
            }
        }
        catch (Exception e)
        {
            System.out.printf("Exception %s\n", e.toString());
        }

        Timestamp te = new Timestamp(System.currentTimeMillis());
        long diff = te.getTime() - ts.getTime();
        System.out.println(diff);
    }
}
