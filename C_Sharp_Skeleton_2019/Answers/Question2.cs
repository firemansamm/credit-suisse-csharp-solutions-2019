using System;
using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question2
    {
        [DllImport("native", EntryPoint = "ans2")]
        [SuppressUnmanagedCodeSecurity]
        public static extern unsafe int ans2(int* t, int* r, int* b, int len);

        private static bool w;
        public static unsafe int Answer(int[] risk, int[] bonus, int[] trader)
        {
            /*if (w)
            {
                fixed (int* tp = &trader[0])
                fixed (int* rp = &risk[0])
                fixed (int* bp = &bonus[0])
                {
                    return ans2(tp, rp, bp, bonus.Length);
                }
            }
            w = true;*/
            int[] x = new int[160];
            int len = risk.Length;
            for (int i = len - 1; i >= 0; i--)
            {
                if (bonus[i] > x[risk[i]]) x[risk[i]] = bonus[i];
            }
            Array.Sort(risk);
            Array.Sort(trader);
            int dx = 0, ans = 0, cm = 0;
            for (int i = 0; i < len; i++)
            {
                while (dx < len && risk[dx] <= trader[i])
                {
                    if (x[risk[dx]] > cm) cm = x[risk[dx]];
                    dx++;
                }

                ans += cm;
            }

            return ans;
        }
    }
}