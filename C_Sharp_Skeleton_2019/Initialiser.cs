using C_Sharp_Challenge_Skeleton.Answers;

namespace C_Sharp_Skeleton_2019
{
    public static class Initialiser
    {
        public static unsafe void Run()
        {
            // warms up the methods
            Question2.Answer(new int[]{}, new int[]{}, new int[]{});
            Question3.Answer(new int[]{}, new int[]{});
            Question4.Answer(new int[]{}, new int[]{}, 0);
            Question5.Answer(new int[] { 0 });
        }
    }
}
