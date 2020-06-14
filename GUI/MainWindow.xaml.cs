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
            // init main window component
            InitializeComponent();

        } // end main window

        private void BrowseButton_Click(object sender, RoutedEventArgs e)
        {
            // Create OpenFileDialog
            OpenFileDialog openFile = new Microsoft.Win32.OpenFileDialog();
            // multiselect true
            openFile.Multiselect = true;
            // set what files it can accept
            openFile.Filter = "dll files (*.dll)|*.dll|All files (*.*)|*.*";
            // set initial file directory
            openFile.InitialDirectory = System.AppDomain.CurrentDomain.BaseDirectory;

            // add opened files to the fileList and filebox
            if (openFile.ShowDialog() == true)
            {
                foreach (string fileName in openFile.FileNames)
                {
                    App.dllObj.fileList.Enqueue(fileName);
                    fileBox.Items.Add(fileName);
                }
            }
        } // end browse button click event handler

        // procedure to create output string
        private void Submit_Click(object sender, RoutedEventArgs e)
        {
            App.netClient.StartClient();
            App.netClient.StartServer();

            DisplayResults();

            //public string resultsHolder = App.dllObj.resultsList.Dequeue();

            //verify.Items.Add(App.dllObj.resultsList.Dequeue);

            //fileBox.App.dllObj.resultsList.

        } // end submit click event handler

        private void DisplayResults()
        {

            while (App.dllObj.resultsList.Count != 0)
            {

                resultsBox.Items.Add("==========");
                string[] resultSingle = App.dllObj.resultsList.Dequeue().Split(',');
                //resultSingle.Replace(",", "\n");
                //MessageBox.Show("results replaced");

                using (StreamWriter s = File.AppendText("log.txt"))
                {
                    s.WriteLine("==========");
                    s.WriteLine("File Path:\t" + resultSingle[0]);
                    s.WriteLine("Start Time:\t" + resultSingle[1]);
                    s.WriteLine("End Time:\t" + resultSingle[2]);
                    s.WriteLine("Result:\t\t" + resultSingle[3]);

                    if (resultSingle.Length == 5)
                    {
                        resultsBox.Items.Add("Exception\t" + resultSingle[3]);
                    }

                }

                resultsBox.Items.Add("File Path:\t\t" + resultSingle[0]);
                resultsBox.Items.Add("Start Time:\t" + resultSingle[1]);
                resultsBox.Items.Add("End Time:\t" + resultSingle[2]);
                resultsBox.Items.Add("Result:\t\t" + resultSingle[3]);

                if (resultSingle.Length == 5)
                {
                    resultsBox.Items.Add("Exception\t" + resultSingle[3]);
                }
            }

            resultsBox.Items.Add("==========\n");
        }

        private void Clear_Click(object sender, RoutedEventArgs e)
        {
            fileBox.Items.Clear();
            App.dllObj.fileList.Clear();
        }
    } // end partial class window
} // end namespace

