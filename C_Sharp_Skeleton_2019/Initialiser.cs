using System;
using System.Collections.Generic;
using System.Text;
using C_Sharp_Challenge_Skeleton.Answers;

namespace C_Sharp_Skeleton_2019
{
    public static class Initialiser
    {
        public static unsafe void Run()
        {
            // warms up the methods
            Question2.ans2(null, null, null, 0);
            Question3.ans3(null, 0, null, 0);
            Question4.ans4(null, null, 0, 0);
            Question5.Answer(new int[] {0});
        }
    }
}
