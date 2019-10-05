using System;
using System.Collections.Generic;
using System.Linq;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question6
    {
        public static int Answer(string[] input)
        {
            var x = new HashSet<(char, char)>();
            var ans = -1;
            for (var i = 0; i < input.Length; i++)
            {
                var k = input[i];
                var g = (k[0], k[k.Length - 1]);
                if (x.Contains(g))
                {
                    ans = i;
                }

                x.Add(g);
            }

            return ans;
        }
    }
}