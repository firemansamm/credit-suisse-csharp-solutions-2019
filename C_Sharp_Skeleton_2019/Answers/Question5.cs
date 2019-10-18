using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question5
    {

        [DllImport("native", EntryPoint = "ans5")]
        [SuppressUnmanagedCodeSecurity]
        public static extern unsafe int ans5(int* d);

        public static unsafe int Answer(int[] input)
        {
            fixed (int* ip = &input[0])
            {
                return ans5(ip);
            }
        }
    }
}