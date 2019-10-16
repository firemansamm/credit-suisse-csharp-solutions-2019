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
            return ans4(v, c, v.Length, mc);
        }
    }
}