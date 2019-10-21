using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

namespace TicTacToe
{
    //=======================================================================================
    class Program
    {   
        static void Main(string[] args)
        {
            bool ContinuePlay = true;

            while (ContinuePlay)
            {
                GameLoop game = new GameLoop();

                TextReader tIn = Console.In;
                TextWriter tOut = Console.Out;

                tOut.Write("Play again (Y/N)? ");
                String again = tIn.ReadLine();

                if (again.ToUpper() == "N")
                    ContinuePlay = false;
            }
        }
    }

    //=======================================================================================

    //=======================================================================================

}
