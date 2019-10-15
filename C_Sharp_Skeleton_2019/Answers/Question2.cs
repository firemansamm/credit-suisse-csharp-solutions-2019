using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question2
    {
        [DllImport("native", EntryPoint = "ans2")]
        [SuppressUnmanagedCodeSecurity]
        public static extern int ans2(int[] t, int tl, int[] r, int[] b, int len);
        public static int Answer(int[] risk, int[] bonus, int[] trader)
        {
            return ans2(trader, trader.Length, risk, bonus, bonus.Length);
        }
    }
}