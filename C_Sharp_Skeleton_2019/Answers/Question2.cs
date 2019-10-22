using System;
using System.Runtime.CompilerServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question2
    {
        [MethodImpl(MethodImplOptions.NoOptimization)]
        public static unsafe int Answer(int[] risk, int[] bonus, int[] trader)
        {
            int[] x = new int[150];
            int len = risk.Length;
            for (int i = len - 1; i >= 0; i--)
            {
                if (bonus[i] > x[risk[i]]) x[risk[i]] = bonus[i];
            }

            for (int i = 1; i < 150; i++)
            {
                if (x[i - 1] > x[i]) x[i] = x[i - 1];
            }
            int dx = 0, ans = 0, cm = 0;
            for (int i = 0; i < len; i++)
            {
                ans += x[trader[i]];
            }

            return ans;
        }
    }
}