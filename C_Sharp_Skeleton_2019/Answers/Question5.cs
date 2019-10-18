using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question5
    {

        [DllImport("native", EntryPoint = "ans5")]
        [SuppressUnmanagedCodeSecurity]
        public static extern int ans5(int[] d);

        public static int Answer(int[] input)
        {
            return ans5(input);
        }
    }
}