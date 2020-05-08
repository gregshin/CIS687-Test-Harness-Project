using System;
using System.IO;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;

namespace testHarnessGui
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        public List<string> fileList = new List<string>();

        private void BrowseButton_Click(object sender, RoutedEventArgs e)
        {
            // Create OpenFileDialog
            OpenFileDialog openFile = new Microsoft.Win32.OpenFileDialog();
            openFile.Multiselect = true;
            openFile.Filter = "dll files (*.dll)|*.dll|All files (*.*)|*.*";
            openFile.InitialDirectory = System.AppDomain.CurrentDomain.BaseDirectory;
            
            if (openFile.ShowDialog() == true)
            {
                foreach(string fileName in openFile.FileNames)
                {
                    fileList.Add(fileName);
                    fileBox.Items.Add(fileName);
                }
            }

            foreach (string name in fileList)
            {
                Console.WriteLine(name + "\n");
            }
        }

        private void Submit_Click(object sender, RoutedEventArgs e)
        {
            string jsonOutput = "{'files':[";

            if (fileList.Count == 0)
            {
                // need error message here
            }
            else
            {
                foreach (string name in fileList)
                {
                    jsonOutput += "'";
                    jsonOutput += name;
                    jsonOutput += "',";
                }
            }

            jsonOutput += "]}";

            verify.Items.Add(jsonOutput);
        }
        
    } // end partial class window

    public class netClient
    {
        public static void StartClient()
        {
            // Data buffer for incoming data.  
            byte[] bytes = new byte[1024];

            // Connect to a remote device.  
            try
            {
                Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                System.Net.IPAddress ipAdd = System.Net.IPAddress.Parse("127.0.0.1");
                System.Net.IPEndPoint remoteEP = new IPEndPoint(ipAdd, 1234);

                // Connect the socket to the remote endpoint. Catch any errors.  
                try
                {
                    sender.Connect(remoteEP);

                    Console.WriteLine("Socket connected to {0}",
                        sender.RemoteEndPoint.ToString());

                    int numOfMessages = 3;

                    byte[] msg = Encoding.ASCII.GetBytes("3");

                    // Send the data through the socket.  
                    int bytesSent = sender.Send(msg);

                    // Receive the response from the remote device.  
                    int bytesRec = sender.Receive(bytes);
                    Console.WriteLine("Echoed test = {0}",
                        Encoding.ASCII.GetString(bytes, 0, bytesRec));

                    for (int i = 0; i < numOfMessages; i++)
                    {
                        msg = Encoding.ASCII.GetBytes("/ExamplePath" + (i + 1));

                        // Send the data through the socket.  
                        bytesSent = sender.Send(msg);
                        bytesRec = sender.Receive(bytes);
                        Console.WriteLine("Echoed test = {0}",
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

        static void Main(string[] args)
        {
            StartClient();
        }
    }

}

