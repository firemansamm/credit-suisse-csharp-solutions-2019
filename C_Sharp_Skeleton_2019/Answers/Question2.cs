using System;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{

    public class Question2
    {
        [DllImport("native", EntryPoint = "ans2"), SuppressUnmanagedCodeSecurity]
        public static extern unsafe int ans2(int* t, int* r, int* b, int len);
        
        public static unsafe int Answer(int[] risk, int[] bonus, int[] trader)
        {
            fixed (int* rp = &risk[0])
            fixed (int* bp = &bonus[0])
            fixed (int* tp = &trader[0])
            {
                return ans2(tp, rp, bp, risk.Length);
            }
            /*int* x = stackalloc int[125];
            int len = risk.Length, ans = 0;
            for (int i = len - 1; i >= 0; i--)
            {
                if (bonus[i] > x[risk[i]]) x[risk[i]] = bonus[i];
            }

            for (int i = 1; i < 125; i++)
            {
                if (x[i - 1] > x[i]) x[i] = x[i - 1];
            }
            for (int i = 0; i < len; i++)
            {
                ans += x[trader[i]];
            }

            return ans;*/
        }
    }
}