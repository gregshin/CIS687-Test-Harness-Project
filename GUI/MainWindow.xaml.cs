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

            
        }

        // data member to hold the file list
        //

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
                foreach(string fileName in openFile.FileNames)
                {
                    App.dllObj.fileList.Enqueue(fileName);
                    fileBox.Items.Add(fileName);
                }
            }
        }

        // procedure to create output string
        private void Submit_Click(object sender, RoutedEventArgs e)
        {
            App.netClient.StartClient();
        }
        
    } // end partial class window
}

