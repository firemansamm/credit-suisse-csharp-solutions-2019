using System.Linq;
using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question4
    {
        [DllImport("native", EntryPoint = "ans4")]
        [SuppressUnmanagedCodeSecurity]
        public static extern int NativeAnswer(int[] v, int[] c, int len, int cap);

        public static int Answer(int[] v, int[] c, int mc)
        {
            if (mc >= c.Sum())
            {
                return v.Sum();
            }
            return NativeAnswer(v, c, c.Length, mc);
        }
    }
}