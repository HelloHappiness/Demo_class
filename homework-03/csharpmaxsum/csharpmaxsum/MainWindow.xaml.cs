using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Data;
using System.IO;
using System.Threading;
using System.Collections.ObjectModel;
using System.Media;
using System.Xml;
using System.Windows.Markup;
using System.Runtime.InteropServices;

namespace csharpmaxsum
{
    public class datacell
    {
        public int CellContent { get; set; }
        public SolidColorBrush CellBackColor { get; set; }
    }
    public class items : ObservableCollection<item> { }
    public class item
    {
        public int Value { get; set; }
        public string Back { get; set; }
    }
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport("libmaxsum.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int main_flow(int select, string filename);
        private int width, length;
        private int select=0;
        private int op=0;
        private int lb, le, wb, we;
        private int[,] data = new int[100, 100];
        private bool[,] map = new bool[100, 100];
        private int maxsum;
        private string filename; 
        public ObservableCollection<items> CollectionSource { get; set; }
       
        public MainWindow()
        {
            InitializeComponent();
        }
       
        private void generateMap()
        {
            FileStream aFile = new FileStream("ouput.txt", FileMode.Open);
            StreamReader sr = new StreamReader(aFile);
            if (op == 0)
            {
                string tmp = sr.ReadLine();
                string[] line = tmp.Split(' ');
                width = Convert.ToInt32(line[0]);
                length = Convert.ToInt32(line[1]);

                for (int i = 1; i <= width; i++)
                {
                    tmp = sr.ReadLine();
                    line = tmp.Split(' ');
                    for (int j = 1; j <= length; j++)
                    {
                        data[i, j] = Convert.ToInt32(line[j - 1]);
                    }
                }
                maxsum = Convert.ToInt32(sr.ReadLine());
                lb = Convert.ToInt32(sr.ReadLine());
                le = Convert.ToInt32(sr.ReadLine());
                wb = Convert.ToInt32(sr.ReadLine());
                we = Convert.ToInt32(sr.ReadLine());
                ResultTextBox.Text = Convert.ToString(maxsum);
                for (int i = 1; i <= width; i++)
                    for (int j = 1; j <= length; j++)
                    {
                        if (wb <= we)
                        {
                            if (i <= we && i >= wb)
                            {
                                if (lb <= le)
                                {
                                    if (j >= lb && j <= le)
                                        map[i, j] = true;
                                    else
                                        map[i, j] = false;
                                }
                                else
                                {
                                    if (j > le && j < lb)
                                        map[i, j] = false;
                                    else
                                        map[i, j] = true;
                                }
                            }
                            else map[i, j] = false;
                        }
                        else
                        {
                            if (i <= we || i >= wb)
                            {
                                if (lb <= le)
                                {
                                    if (j >= lb && j <= le)
                                        map[i, j] = true;
                                    else
                                        map[i, j] = false;
                                }
                                else
                                {
                                    if (j > le && j < lb)
                                        map[i, j] = false;
                                    else
                                        map[i, j] = true;
                                }
                            }
                            else map[i, j] = false;
                        }
                    }
                //cankao
                CollectionSource = new ObservableCollection<items>();
                CollectionSource.Clear();

                for (int i = 0; i < width; i++)
                {
                    items dr = new items();
                    dr.Clear();
                    for (int j = 0; j < length; j++)
                    {

                        item ttt = new item { Back = "White", Value = data[i+1,j+1] };
                        dr.Add(ttt);
                        if (map[i+1, j+1]) dr[j].Back = "LightSkyBlue";

                    }
                    CollectionSource.Add(dr);
                }

                datagrid.ItemsSource = null;
                datagrid.ItemsSource = CollectionSource;
                datagrid.Visibility = Visibility.Visible;
            }

            else if (op == -1)
            {
                string tmp = sr.ReadLine();
                MessageBox.Show(tmp);
            }
        }

        private void Button_Click_SelectDataFile(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.FileName = "Document"; 
            dlg.DefaultExt = ".txt"; 
            dlg.Filter = "Text documents (.txt)|*.txt"; 
            Nullable<bool> result = dlg.ShowDialog();
            if (result == true)
            {
                filename = dlg.FileName;
            }
        }

        private void Button_Clik_Result(object sender, RoutedEventArgs e)
        {
            op = main_flow(select, filename);
            generateMap();
        }

        private void CheckBox_Checked_Normal(object sender, RoutedEventArgs e)
        {
            select = 0;
        }

        private void CheckBox_Checked_Vertical(object sender, RoutedEventArgs e)
        {
            select = 1;
        }

        private void CheckBox_Checked_Horizontal(object sender, RoutedEventArgs e)
        {
            select = 2;
        }

        private void datagrid_AutoGeneratingColumn(object sender, DataGridAutoGeneratingColumnEventArgs e)
        {
            (sender as DataGrid).Columns.Clear();
            for (int columnIndex = 0; columnIndex < this.CollectionSource[0].Count; columnIndex++)
            {
                DataGridTemplateColumn column = new DataGridTemplateColumn();
                XmlTextReader sr = new XmlTextReader(
                  new StringReader(
                    "<DataTemplate xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\" xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">" +
                      "<TextBlock Background=\"{Binding [" + columnIndex + "].Back}\" Text=\"{Binding [" + columnIndex + "].Value}\"  TextAlignment=\"Center\"  Foreground=\"Black\"/>" +
                    "</DataTemplate>"));

                column.CellTemplate = (DataTemplate)XamlReader.Load(sr);

                (sender as DataGrid).Columns.Add(column);
            }
            e.Column = null;
        }

        private void datagrid_AutoGeneratedColumns(object sender, EventArgs e)
        {
            for (int i = 0; i < datagrid.Columns.Count; i++)
            {
                datagrid.Columns[i].Header = (i + 1).ToString();

            }
        }


    }
}
