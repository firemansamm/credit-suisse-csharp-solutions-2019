using System;
using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question3
    {
        [DllImport("native.so", EntryPoint = "ans3")]
        [SuppressUnmanagedCodeSecurity]
        public static extern int NativeAnswer(int[] s, int sl, int[] y, int yl);

        public static int Answer(int[] scores, int[] alice)
        {
            return NativeAnswer(scores, scores.Length, alice, alice.Length);
        }
    }
}