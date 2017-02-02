using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace CardTest
{
	class MainClass
	{
		private static IList<List<int>> _numbers = new List<List<int>>();
		public static void Main()
		{
			var start = DateTime.Now;

		    using (var reader = new StreamReader(@"../temp.txt"))
		    {
		        var keepGoing = true;
		        while (keepGoing)
		        {
		            int szRead;
		            var line = ReadNumber(reader, out szRead);

		            if (szRead < 16)
		            {
		                keepGoing = false;
		            }
		            else
		            {
		                reverseNumbers(line);
		            }
		        }
		    }

			processNumbers();
			var end = DateTime.Now;

			var diff = end - start;
			Console.WriteLine(diff);
		}

	    private static string ReadNumber(TextReader reader, out int szRead)
	    {
	        var builder = new StringBuilder();
	        var numCharsInNumber = 0;

	            szRead = 0;
	        var keepReading = true;

	        do
	        {
	            if (reader.Peek() < 0)
	            {
	                keepReading = false;
	            }
	            else
	            {
	                var character = (char) reader.Read();
	                numCharsInNumber++;

	                if (character == '\n')
	                {
	                    keepReading = false;
	                }
	                else if (numCharsInNumber > 16)
	                {
	                    keepReading = false;
	                    do
	                    {
	                        if (reader.Peek() < 0)
	                        {
	                            character = (char) reader.Read();
	                        }
	                        else
	                        {
	                            character = '\n';
	                        }

	                    } while (character != '\n');
	                }
	                else
	                {
	                    builder.Append(character);
	                    szRead++;
	                }
	            }

	        } while (keepReading);

	        return builder.ToString();
	    }

		private static void reverseNumbers(string cardNum)
		{
			var reversed = new List<int>();
			int strLength = cardNum.Length;
			for (int i = strLength - 1; i >= 0; i--)
			{
				var asInt = 0;
				var str = cardNum[i].ToString();
				int.TryParse(str, out asInt);
				reversed.Add(asInt);
			}

			_numbers.Add(reversed);
		}

		private static void processNumbers()
		{
			foreach (var number in _numbers)
			{
				var oddAcc = 0;
				var evenAcc = 0;

				for (var i = 0; i < 16; i++)
				{
					if (i%2 == 0)
					{
						oddAcc += number[i];
					}
					else
					{
						int even_num = number[i] * 2;

						if (even_num > 9)
						{
							even_num -= 10;
						}

						evenAcc += even_num;
					}
				}
				if ((oddAcc + evenAcc) % 10 > 0)
				{
					Console.WriteLine("Fail");
				}
				else
				{
					Console.WriteLine("Success");
				}
			}
		}
	}
}
