using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.NetworkInformation;
using System.Runtime.InteropServices;
using System.Security;
using System.Threading.Tasks;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question1
    {
        [DllImport("native", EntryPoint = "ans1")]
        [SuppressUnmanagedCodeSecurity]
        public static extern int ans1(double d, double ip, double rp);
        public static int Answer(double initialLevelOfDebt, double interestPercentage, double repaymentPercentage)
        {
            return ans1(initialLevelOfDebt, interestPercentage, repaymentPercentage);
        }
    }
}
