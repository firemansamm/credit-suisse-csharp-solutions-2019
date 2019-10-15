using System.Security.Cryptography;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question6
    {
        public static int Answer(string[] input)
        {
            var (s, e) = (input[0][0], input[0][input[0].Length - 1]);
            for (int i = input.Length - 1; i > 0; i++)
            {
                if (input[i][0] == s && input[i][input[i].Length - 1] == e)
                {
                    return i;
                }
            }
            return input.Length > 10 ? -1 : 0;
        }
    }
}