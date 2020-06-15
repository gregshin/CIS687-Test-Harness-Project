using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;

namespace testHarnessGui
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        static public class dllObj
        {
            static public Queue<string> fileList = new Queue<string>();
            static public Queue<string> resultsList = new Queue<string>();
        }

        // net client class
        public class netClient
        {
            public static void StartClient()
            {
                // Data buffer for incoming data.  
                byte[] bytes = new byte[1024];

                // Connect to a remote device.  
                try
                {
                    // new socket
                    Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                    // add IP address
                    System.Net.IPAddress ipAdd = System.Net.IPAddress.Parse("127.0.0.1");
                    System.Net.IPEndPoint remoteEP = new IPEndPoint(ipAdd, 1234);

                    // Connect the socket to the remote endpoint. Catch any errors.  
                    try
                    {
                        // try to connect
                        sender.Connect(remoteEP);

                        Console.WriteLine("Socket connected to {0}",
                            sender.RemoteEndPoint.ToString());

                        byte[] msg;
                        int bytesSent;
                        int bytesRec;

                        foreach (String filePath in App.dllObj.fileList)
                        { 
                            // encode message as ascii
                            msg = Encoding.ASCII.GetBytes(filePath);

                            // Send the data through the socket. 
                            Console.WriteLine("sending bytes");
                            bytesSent = sender.Send(msg);
                            Console.WriteLine("receiving bytes");
                            bytesRec = sender.Receive(bytes);
                            Console.WriteLine("Echo: ",
                                Encoding.ASCII.GetString(bytes, 0, bytesRec));
                        }

                        // Release the socket.  
                        sender.Shutdown(SocketShutdown.Both);
                        sender.Close();
                    }
                    catch (ArgumentNullException ane)
                    {
                        Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
                    }
                    catch (SocketException se)
                    {
                        Console.WriteLine("SocketException : {0}", se.ToString());
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine("Unexpected exception : {0}", e.ToString());
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }
            }

            public static void StartServer()
            {
                // Establish the local endpoint  
                // for the socket. Dns.GetHostName 
                // returns the name of the host  
                // running the application. 
                IPHostEntry ipHost = Dns.GetHostEntry(Dns.GetHostName());
                IPAddress ipAddr = System.Net.IPAddress.Parse("127.0.0.1");
                IPEndPoint localEndPoint = new IPEndPoint(ipAddr, 1234);

                // Creation TCP/IP Socket using  
                // Socket Class Costructor 
                Socket listener = new Socket(ipAddr.AddressFamily,
                             SocketType.Stream, ProtocolType.Tcp);

                try
                {

                    // Using Bind() method we associate a 
                    // network address to the Server Socket 
                    // All client that will connect to this  
                    // Server Socket must know this network 
                    // Address 
                    listener.Bind(localEndPoint);

                    // Using Listen() method we create  
                    // the Client list that will want 
                    // to connect to Server 
                    listener.Listen(10);

                    Console.WriteLine("Waiting for Results ... ");

                    // Suspend while waiting for 
                    // incoming connection Using  
                    // Accept() method the server  
                    // will accept connection of client 
                    Socket clientSocket = listener.Accept();

                    // Data buffer 
                    byte[] bytes = new Byte[1024];
                    string data = null;
                    int numByte;

                    do
                    {

                        numByte = clientSocket.Receive(bytes);
                        if (numByte > 0)
                        {
                            data = Encoding.ASCII.GetString(bytes,
                                                        0, numByte);
                            Console.WriteLine("Received:" + data); // receives data

                            dllObj.resultsList.Enqueue(data); // enqueues results in global queue

                            clientSocket.Send(Encoding.ASCII.GetBytes("ack"));
                        }

                    } while (numByte > 0);

                    clientSocket.Shutdown(SocketShutdown.Both);
                    clientSocket.Close();
                }

                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }
            }
        }

        public static void ServerRecive(Socket receiveSocket)
        {
            Socket s = receiveSocket.Accept();
            Console.WriteLine("Connection accepted from " + s.RemoteEndPoint);
        } 

    }
}
