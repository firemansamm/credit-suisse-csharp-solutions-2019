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
        public static int Answer(double initialLevelOfDebt, double interestPercentage, double repaymentPercentage)
        {
            double r = initialLevelOfDebt * repaymentPercentage / 100.0, p = initialLevelOfDebt / 10.0;
            double sf = r * 100.0 / interestPercentage,
                ll = initialLevelOfDebt - sf,
                ii = (interestPercentage + 100.0) / 100.0;
            double fl = 0.0;
            for (; ll > r - sf; ll *= ii)
            {
                fl += r; 
            }

            return (int)Math.Round(fl + p + ll + sf);
        }
    }
}
