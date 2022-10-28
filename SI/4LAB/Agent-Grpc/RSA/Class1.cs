using System.Text;



namespace App
{

    class Program
    {
        private static int _p;
        private static int _q;
        private static int _mod;
        private static int _e;
        private static int _fi;
        private static int _d;

        public static void Main(string[] args)
        {
            string msg = "Hello";
            //Console.WriteLine("Enter your message to encrypt & decrypt: ");
            //msg = Console.ReadLine();
            Console.WriteLine($"---------- Encrypt ----------");
            Console.WriteLine($"Message to encrypt: {msg}");
            var vr1 = Encrypt(13, 197, msg);
            Console.Write($"\nEncrypted message: ");
            Console.ForegroundColor = ConsoleColor.Blue;
            foreach (var item in vr1)
            {
                Console.Write(item + " ");
            }
            Console.ForegroundColor = ConsoleColor.White;



            Console.WriteLine("\n\n---------- Decrypt ----------");
            Console.Write($"Message to decrypt: ");
            string decrypt = Decrypt(vr1);
            Console.Write("Decrypted text: ");
            Console.ForegroundColor = ConsoleColor.Green;
            Console.Write(decrypt + "\n\n");
            Console.ForegroundColor = ConsoleColor.White;







            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine($"\n[Data: P: {_p}, Q: {_q}, Mod: {_mod}, Fi: {_fi}, E: {_e}, D: {_d}]");
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine($"\nPublic Key:  [e, mod] = [{_e}, {_mod}]");
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.WriteLine($"Private Key: [d, mod] = [{_d}, {_mod}]");
            Console.ForegroundColor = ConsoleColor.Black;


        }

        public static int[] Encrypt(int p, int q, string message)
        {
            byte[] asc = Encoding.ASCII.GetBytes(message);
            var res = new int[asc.Length];

            (_p, _q) = (p, q);
            _mod = _p * _q;
            _fi = (_p - 1) * (_q - 1);
            GetE(_fi);

            for (int i = 0; i < asc.Length; i++)
            {
                int c = 1;
                int a = 0;
                int ASCII = (asc[i]);

                while (a < _e)
                {
                    c = c * ASCII;
                    c = c % _mod;
                    a++;
                }
                Console.WriteLine($"{message[i]} = {ASCII}; {ASCII} ^ {_e} % {_mod} = {c}");
                res[i] = c;

            }
            return res;
        }

        public static string Decrypt(int[] encryptedText)
        {
            string output = "\n";
            var arr = new byte[encryptedText.Length];
            var dec = new int[encryptedText.Length];
            string res = "";

            for (int i = 2; i < int.MaxValue; i++)
            {
                if ((i * _e) % _fi == 1)
                {
                    _d = i;
                    break;
                }
            }

            for (int i = 0; i < dec.Length; i++)
            {
                int m = 1;
                int a = 0;



                while (a < _d)
                {
                    m = m * encryptedText[i];
                    m = m % _mod;
                    a++;
                }
                output += $"{encryptedText[i]} ^ {_d} % {_mod} = {m}; {m} = {(char)m}\n";
                dec[i] = m;

            }
            foreach (var item in dec)
            {
                Console.Write(item + " ");
            }

            Console.WriteLine(output);

            for (int i = 0; i < dec.Length; i++)
            {
                res += (char)dec[i];
            }
            return res;
        }

        private static void GeneratePrimes()
        {
            Random rnd = new Random();
            int tmp = 0;
            while (_p == 0 || _q == 0)
            {
                tmp = rnd.Next(1, 1000);
                if (_p == 0)
                {
                    if (IsPrime(tmp)) _p = tmp;
                    continue;
                }
                if (IsPrime(tmp)) _q = tmp;
            }
            Console.WriteLine($"P: {_p}, Q: {_q}");
        }

        private static bool IsPrime(int num)
        {
            if (num == 2 || num == 3 || num == 5 || num == 7) return true;
            double num_sqrt = Math.Sqrt(num);
            int num_fl = Convert.ToInt32(Math.Floor(num_sqrt));
            if (num != 1 && num != 2 && num != 3 && num != 5 && num != 7 && num % 2 > 0 && num % 3 > 0 && num % 5 > 0 && num % 7 > 0)
            {
                for (int i = 11; i <= num_fl; i += 2)
                {
                    if (num % i == 0)
                    {
                        return false;
                    }
                }
            }
            else return false;
            return true;
        }

        private static void GetE(int fi)
        {
            for (int i = 2; i < fi; i++)
            {
                if (fi % i != 0 && IsPrime(i))
                {
                    _e = i;
                    break;
                }
            }
        }
    }
}






