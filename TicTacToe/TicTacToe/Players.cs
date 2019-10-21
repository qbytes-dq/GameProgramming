using System;
using System.Collections.Generic;
using System.Text;

using System.IO;


namespace TicTacToe
    {
    public class Players
        {
        public string Name = "";
        public string Character = "";

        public Players( string num )
            {
            Character = num;

            TextReader tIn = Console.In;
            TextWriter tOut = Console.Out;

            tOut.Write( Character.ToString() + " What is your name: " );
            Name = tIn.ReadLine();
            }
        }

    }
