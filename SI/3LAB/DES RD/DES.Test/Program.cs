using System;

namespace DES.Test {
    public class Program {
        public static void Main(string[] args) {
            Console.ForegroundColor = ConsoleColor.Magenta;
            Console.Write("Input encryption key: ");
            var key = Console.ReadLine();

            Console.Write("Input message to encrypt: ");
            var message = Console.ReadLine();


            Console.ForegroundColor = ConsoleColor.Cyan;
            var encryptedMessage = DES.Encrypt(message, key);
            Console.WriteLine($"\nEncrypted message: {Convert.ToHexString(encryptedMessage)}");

            var decryptedMessage = DES.Decrypt(encryptedMessage, key);
            Console.WriteLine($"Decrypted message: {decryptedMessage}\n\n");
            Console.ForegroundColor = ConsoleColor.White;
        }
    }
}
