using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question5
    {

        [DllImport("native/native5", EntryPoint = "ans5"), SuppressUnmanagedCodeSecurity, MethodImpl(MethodImplOptions.Unmanaged)]
        public static extern int Answer(int[] d);

        /*public static unsafe int Answer(int[] input)
        {
            fixed (int* ip = &input[0])
            {
                return ans5(ip);
            }
        }*/
    }
}