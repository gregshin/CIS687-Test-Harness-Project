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
            string filePath = System.AppDomain.CurrentDomain.BaseDirectory;
            string directoryName = "";
            for (int i = 0; i < 5; i++)
            {
                directoryName = System.IO.Path.GetDirectoryName(filePath);
                filePath = directoryName;
                if (i == 1)
                {
                    filePath = directoryName + @"\";
                }
            }
            openFile.InitialDirectory = directoryName;

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
            MessageBox.Show("Starting Send");
            App.netClient.StartClient();
            MessageBox.Show("Waiting for results");
            App.netClient.StartServer();
            MessageBox.Show("Displaying Results");
            DisplayResults();

            //public string resultsHolder = App.dllObj.resultsList.Dequeue();

            //verify.Items.Add(App.dllObj.resultsList.Dequeue);

            //fileBox.App.dllObj.resultsList.

        } // end submit click event handler

        // method to display results
        private void DisplayResults()
        {
            // while the resultslist is not empty
            while (App.dllObj.resultsList.Count != 0)
            {
                // prep the results box
                resultsBox.Items.Add("==========");
                // dequeue from the results list and split
                string[] resultSingle = App.dllObj.resultsList.Dequeue().Split(',');

                // save results to file
                using (StreamWriter s = File.AppendText("log.txt"))
                {
                    s.WriteLine("==========");
                    s.WriteLine("File Path:\t" + resultSingle[0]);
                    s.WriteLine("Start Time:\t" + resultSingle[1]);
                    s.WriteLine("End Time:\t" + resultSingle[2]);
                    s.WriteLine("Result:\t\t" + resultSingle[3]);

                    if (resultSingle.Length == 5)
                    {
                        s.WriteLine("Exception:\t" + resultSingle[4]);
                    }

                }
                // display results in the results box
                resultsBox.Items.Add("File Path:\t\t" + resultSingle[0]);
                resultsBox.Items.Add("Start Time:\t" + resultSingle[1]);
                resultsBox.Items.Add("End Time:\t" + resultSingle[2]);
                resultsBox.Items.Add("Result:\t\t" + resultSingle[3]);

                if (resultSingle.Length == 5)
                {
                    resultsBox.Items.Add("Exception:\t" + resultSingle[4]);
                }
            }
        }

        // method to clear the dll list box on click event
        private void Clear_Click(object sender, RoutedEventArgs e)
        {
            fileBox.Items.Clear();
            App.dllObj.fileList.Clear();
        }

        private void RemoveDll_Click(object sender, RoutedEventArgs e)
        {
            fileBox.Items.Remove(fileBox.SelectedItem);
        }

        private void ClearResults_Click(object sender, RoutedEventArgs e)
        {
            resultsBox.Items.Clear();
        }
    } // end partial class window
} // end namespace

