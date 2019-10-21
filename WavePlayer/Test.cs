
using System;
using System.Text;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace WindowsApplication1
{
    class Test
    {
        delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);

        [DllImport("user32.dll")]
        static extern bool EnumChildWindows(IntPtr hwndParent, EnumWindowsProc lpEnumFunc, IntPtr lParam);

        [DllImport("user32.dll")]
        static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

        public void startMain()
        {
            Process[] procs = Process.GetProcessesByName("notepad");
            if (procs.Length == 0)
            {
                Console.WriteLine("MS Access is not currently open");
                return;
            }
            IntPtr hWndParent = procs[0].MainWindowHandle;
            EnumChildWindows(hWndParent, EnumChildren, IntPtr.Zero);
        }

        private bool EnumChildren(IntPtr hWnd, IntPtr lParam)
        {
            StringBuilder lpString = new StringBuilder(256);
            GetWindowText(hWnd, lpString, 256);
            string title = lpString.ToString().Trim();
            int index = -1;
            if ((index = title.IndexOf(" : Database")) > -1)
            {
                title = title.Substring(0, index);
                Console.WriteLine(title + " is open");
            }
            return true;
        }
    }
}