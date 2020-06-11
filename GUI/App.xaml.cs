﻿using System;
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

                        MessageBox.Show("Socket connected");

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
                            bytesSent = sender.Send(msg);
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
        }

        public static void ServerRecive(Socket receiveSocket)
        {
            Socket s = receiveSocket.Accept();
            Console.WriteLine("Connection accepted from " + s.RemoteEndPoint);
        } 
    }
}
