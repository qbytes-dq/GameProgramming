#region Using directives

using System;
using System.Windows.Forms;

#endregion

namespace StarTrooper
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (StarTrooper starTrooperGame = new StarTrooper())
                starTrooperGame.Run();
        }
    }
}