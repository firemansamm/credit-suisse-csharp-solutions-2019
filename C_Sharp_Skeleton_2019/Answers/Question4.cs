using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question4
    {
        [DllImport("native", EntryPoint = "ans4"), SuppressUnmanagedCodeSecurity]
        public static extern unsafe int ans4(int* v, int* c, int len, int cap);
        public static unsafe int Answer(int[] v, int[] c, int mc)
        {
            /*fixed (int* vp = &v[0])
            fixed (int* cp = &c[0])
            {
                return ans4(vp, cp, v.Length, mc);
            }*/
            int ans1 = 0, cc1 = 0;
            for (int i = 0; i < v.Length; i++)
            {
                if (cc1 + c[i] > mc) continue;
                if (v[i] == 0) continue;
                ans1 += v[i];
                cc1 += c[i];
            }

            if (ans1 == 0) return 0;
            int ans2 = 0, cc2 = 0;
            for (int i = v.Length - 1; i >= 0; i--)
            {
                if (cc2 + c[i] > mc) continue;
                if (v[i] == 0) continue;
                ans2 += v[i];
                cc2 += c[i];
            }

            return ans2 > ans1 ? ans2 : ans1;
        }
    }
}