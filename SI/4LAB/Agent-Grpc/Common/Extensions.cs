using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Common.Extensions
{
    public static class Extensions
    {
        public static string EncryptionRSA(this string content, int e, int mod, bool enable = true)
        {
            if (enable == false) return content;
            byte[] asc = Encoding.ASCII.GetBytes(content);
            var res = new int[asc.Length];
            string strResult = "";

            for (int i = 0; i < asc.Length; i++)
            {
                int c = 1;
                int a = 0;
                int ASCII = (asc[i]);

                while (a < e)
                {
                    c = c * ASCII;
                    c = c % mod;
                    a++;
                }
                //Console.WriteLine($"{content[i]} = {ASCII}; {ASCII} ^ {e} % {mod} = {c}");   - проверка
                res[i] = c;
                strResult += $"{c}";
                if (i - 1 == asc.Length) break;
                strResult += " ";
            }
            strResult = strResult.Remove(strResult.Length - 1);


            return strResult;
        }


        public static string DecryptionRSA(this string content, int d, int mod, bool enable = true)
        {
            if (enable == false) return content;
            string[] splittedString = content.Split(" ");
            var encryptedText = new int[splittedString.Length];
            var dec = new int[encryptedText.Length];
            string res = "";

            for (int i = 0; i < encryptedText.Length; i++)
            {
                encryptedText[i] = int.Parse(splittedString[i]);
            }

            for (int i = 0; i < encryptedText.Length; i++)
            {
                int m = 1;
                int a = 0;

                while (a < d)
                {
                    m = m * encryptedText[i];
                    m = m % mod;
                    a++;
                }
                dec[i] = m;
            }

            for (int i = 0; i < dec.Length; i++)
            {
                res += (char)dec[i];
            }

            return res;
        }


    }
}
