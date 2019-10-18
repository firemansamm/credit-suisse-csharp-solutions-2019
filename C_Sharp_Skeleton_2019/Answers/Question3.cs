using System;
using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question3
    {
        [DllImport("native", EntryPoint = "ans3")]
        [SuppressUnmanagedCodeSecurity]
        public static extern unsafe int ans3(int* s, int sl, int* y, int yl);
        public static unsafe int Answer(int[] scores, int[] alice)
        {
            fixed (int* sp = &scores[0])
            fixed (int* yp = &alice[0])
            {
                return ans3(sp, scores.Length, yp, alice.Length);
            }
        }
    }
}