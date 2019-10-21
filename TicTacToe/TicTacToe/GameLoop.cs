using System;
using System.Collections.Generic;
using System.Text;

using System.IO;


namespace TicTacToe
    {
    public class GameLoop
        {
        private bool WinnerFound = false;
        private Players[] players = new Players[2];
        private Board brd = new Board();

        public GameLoop()
            {
            players[0] = new Players( "X" );
            players[1] = new Players( "O" );


            brd.DisplayBoard();

            int playerup = 0;

            while ( !WinnerFound )
                {
                DoMove( playerup );

                playerup++;
                if ( playerup > 1 )
                    playerup = 0;

                WinnerFound = brd.HaveWinner( players );
                }
            }

        private void DoMove( int playerUP )
            {
            bool TryMove = true;

            while ( TryMove )
                {
                TextReader tIn = Console.In;
                TextWriter tOut = Console.Out;

                tOut.Write( players[playerUP].Name + " what Position? " );
                String pos = tIn.ReadLine();

                TryMove = brd.SetPosition( pos , players[playerUP].Character );
                }
            brd.DisplayBoard();
            }
        }

    }
