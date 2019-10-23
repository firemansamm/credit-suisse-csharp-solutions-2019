﻿using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Security;

namespace C_Sharp_Challenge_Skeleton.Answers
{
    public class Question4
    {
        [DllImport("native/native4", EntryPoint = "ans4"), SuppressUnmanagedCodeSecurity]
        public static extern unsafe int ans4(int* v, int* c, int len, int cap);
        public static unsafe int Answer(int[] v, int[] c, int mc)
        {
            /*fixed (int* vp = &v[0])
            fixed (int* cp = &c[0])
            {
                return ans4(vp, cp, v.Length, mc);
            }*/
            int ans = 0, cc = 0;
            for (int i = 0; i < v.Length; i++)
            {
                if (cc + c[i] > mc) continue;
                if (v[i] == 0) continue;
                ans += v[i];
                cc += c[i];
            }

            return ans;
        }
    }
}