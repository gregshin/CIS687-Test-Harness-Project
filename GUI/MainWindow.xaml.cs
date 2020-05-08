using System;
using System.IO;
using System.Collections.Generic;
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
        
    }
}
