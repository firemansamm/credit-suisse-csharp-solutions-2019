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
        private static bool w4 = false;
        public static int Answer(int[] v, int[] c, int mc)
        {
            if (w4)
            {
                return ans4(v, c, v.Length, mc);
            }

            w4 = true;
            int[] dp4 = new int[10050];
            int len = c.Length;
            for (int i = len - 1; i >= 0; i--)
            {
                int cc = c[i], cv = v[i];
                for (int j = mc; j >= cc; j--)
                {
                    int a = dp4[j - cc] + cv;
                    if (a > dp4[j]) dp4[j] = a;
                }
            }

            return dp4[mc];
            //return ans4(v, c, v.Length, mc);
        }
    }
}