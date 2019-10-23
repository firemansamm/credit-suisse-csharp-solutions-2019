using System;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{

    public class Question2
    {
        [DllImport("native/native2", EntryPoint = "ans2"), SuppressUnmanagedCodeSecurity]
        public static extern unsafe int ans2(int* t, int* r, int* b, int len);
        
        public static unsafe int Answer(int[] risk, int[] bonus, int[] trader)
        {
            fixed (int* rp = &risk[0])
            fixed (int* bp = &bonus[0])
            fixed (int* tp = &trader[0])
            {
                return ans2(tp, rp, bp, risk.Length);
            }
        }
    }
}