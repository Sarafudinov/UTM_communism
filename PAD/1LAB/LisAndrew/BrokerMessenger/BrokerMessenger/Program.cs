using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Linq;
using System;

namespace BrokerMessenger
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var ip = "127.0.0.1";
            var port = 8080;

            var endPoint = new IPEndPoint(IPAddress.Parse(ip), port);

            var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            socket.Bind(endPoint); // обьединяем 
            socket.Listen(5); // кол-во юзеров

            while (true)
            {
                var listener = socket.Accept();
                var buffer = new byte[256];
                var size = 0;
                var data = new StringBuilder();

                do
                {
                    size = listener.Receive(buffer);
                    data.Append(Encoding.UTF8.GetString(buffer, 0, size));
                }
                while (listener.Available > 0);

                Console.WriteLine(data);

                listener.Send(Encoding.UTF8.GetBytes("Pobeda"));

                listener.Shutdown(SocketShutdown.Both);
                listener.Close();
            }
        }
    }
}
