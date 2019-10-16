using System;
using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question4
    {
        [DllImport("native", EntryPoint = "ans4")]
        [SuppressUnmanagedCodeSecurity]
        public static extern int ans4(int[] v, int[] c, int len, int cap);
        public static int Answer(int[] v, int[] c, int mc)
        {
            /*int[][] dp = new int[v.Length + 10][];
            dp[0] = new int[mc + 10];
            for (int i = 1; i <= v.Length; i++)
            {
                dp[i] = new int[mc + 10];
                int cc = c[i - 1], cv = v[i - 1];
                for (int j = 0; j <= mc; j++)
                {
                    if (j < cc) dp[i][j] = dp[i - 1][j];
                    else dp[i][j] = Math.Max(dp[i - 1][j - cc] + cv, dp[i - 1][j]);
                }
            }

            return dp[v.Length][mc];*/
            return ans4(v, c, v.Length, mc);
        }
    }
}