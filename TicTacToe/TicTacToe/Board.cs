using System;
using System.Collections.Generic;
using System.Text;

using System.IO;

namespace TicTacToe
    {
    public class Board
        {
        string[,] theBoard = new string[3 , 3];

        public Board()
            {
            for ( int loop = 0; loop < 3; loop++ )
                {
                theBoard[0 , loop] = " ";
                theBoard[1 , loop] = " ";
                theBoard[2 , loop] = " ";
                }
            }

        public bool SetPosition( string num , string character )
            {
            switch ( num )
                {
                //==== top row ====
                case "1":
                        {
                        if ( theBoard[0 , 0] == " " )
                            {
                            theBoard[0 , 0] = character;
                            return false;
                            }
                        break;
                        }
                case "2":
                        {
                        if ( theBoard[1 , 0] == " " )
                            {
                            theBoard[1 , 0] = character;
                            return false;
                            }
                        break;
                        }
                case "3":
                        {
                        if ( theBoard[2 , 0] == " " )
                            {
                            theBoard[2 , 0] = character;
                            return false;
                            }
                        break;
                        }
                //==== middle row ====
                case "4":
                        {
                        if ( theBoard[0 , 1] == " " )
                            {
                            theBoard[0 , 1] = character;
                            return false;
                            }
                        break;
                        }
                case "5":
                        {
                        if ( theBoard[1 , 1] == " " )
                            {
                            theBoard[1 , 1] = character;
                            return false;
                            }
                        break;
                        }
                case "6":
                        {
                        if ( theBoard[2 , 1] == " " )
                            {
                            theBoard[2 , 1] = character;
                            return false;
                            }
                        break;
                        }
                //==== middle row ====
                case "7":
                        {
                        if ( theBoard[0 , 2] == " " )
                            {
                            theBoard[0 , 2] = character;
                            return false;
                            }
                        break;
                        }
                case "8":
                        {
                        if ( theBoard[1 , 2] == " " )
                            {
                            theBoard[1 , 2] = character;
                            return false;
                            }
                        break;
                        }
                case "9":
                        {
                        if ( theBoard[2 , 2] == " " )
                            {
                            theBoard[2 , 2] = character;
                            return false;
                            }
                        break;
                        }
                }


            return true;
            }

        public void DisplayBoard()
            {
            TextWriter tOut = Console.Out;

            tOut.WriteLine( "" );
            tOut.WriteLine( "1" + "|" + "2" + "|" + "3" );
            tOut.WriteLine( "-" + "+" + "-" + "+" + "-" );
            tOut.WriteLine( "4" + "|" + "5" + "|" + "6" );
            tOut.WriteLine( "-" + "+" + "-" + "+" + "-" );
            tOut.WriteLine( "7" + "|" + "8" + "|" + "9" );

            tOut.WriteLine( "" );
            tOut.WriteLine( theBoard[0 , 0] + "|" + theBoard[1 , 0] + "|" + theBoard[2 , 0] );
            tOut.WriteLine( "-" + "+" + "-" + "+" + "-" );
            tOut.WriteLine( theBoard[0 , 1] + "|" + theBoard[1 , 1] + "|" + theBoard[2 , 1] );
            tOut.WriteLine( "-" + "+" + "-" + "+" + "-" );
            tOut.WriteLine( theBoard[0 , 2] + "|" + theBoard[1 , 2] + "|" + theBoard[2 , 2] );
            }

        private void DisplayWinner( Players player )
            {
            TextWriter tOut = Console.Out;

            tOut.WriteLine( "" );
            tOut.WriteLine( "Tic, Tac, Toe, Three in a row" );
            tOut.WriteLine( player.Name + " WINS" );
            tOut.WriteLine( "" );
            }

        public bool HaveWinner( Players[] players )
            {
            TextWriter tOut = Console.Out;

            #region accross
            if ( theBoard[0 , 0] == theBoard[1 , 0] && theBoard[1 , 0] == theBoard[2 , 0] &&
               !theBoard[0 , 0].Contains( " " ) && !theBoard[1 , 0].Contains( " " ) && !theBoard[2 , 0].Contains( " " ) )
                {
                if ( players[0].Character == theBoard[0 , 0] )
                    DisplayWinner( players[0] );
                else
                    DisplayWinner( players[1] );
                return true;
                }

            if ( theBoard[0 , 1] == theBoard[1 , 1] && theBoard[1 , 1] == theBoard[2 , 1] &&
               !theBoard[0 , 1].Contains( " " ) && !theBoard[1 , 1].Contains( " " ) && !theBoard[2 , 1].Contains( " " ) )
                {
                if ( players[0].Character == theBoard[0 , 1] )
                    DisplayWinner( players[0] );
                else
                    DisplayWinner( players[1] );

                return true;
                }

            if ( theBoard[0 , 2] == theBoard[1 , 2] && theBoard[1 , 2] == theBoard[2 , 2] &&
               !theBoard[0 , 2].Contains( " " ) && !theBoard[1 , 2].Contains( " " ) && !theBoard[2 , 2].Contains( " " ) )
                {
                if ( players[0].Character == theBoard[0 , 2] )
                    DisplayWinner( players[0] );
                else
                    DisplayWinner( players[1] );

                return true;

                }
            #endregion accross

            #region down
            if ( theBoard[0 , 0] == theBoard[0 , 1] && theBoard[0 , 1] == theBoard[0 , 2] &&
               !theBoard[0 , 0].Contains( " " ) && !theBoard[0 , 1].Contains( " " ) && !theBoard[0 , 2].Contains( " " ) )
                {
                if ( players[0].Character == theBoard[0 , 0] )
                    DisplayWinner( players[0] );
                else
                    DisplayWinner( players[1] );

                return true;
                }

            if ( theBoard[1 , 0] == theBoard[1 , 1] && theBoard[1 , 1] == theBoard[1 , 2] &&
               !theBoard[1 , 0].Contains( " " ) && !theBoard[1 , 1].Contains( " " ) && !theBoard[1 , 2].Contains( " " ) )
                {
                if ( players[0].Character == theBoard[1 , 0] )
                    DisplayWinner( players[0] );
                else
                    DisplayWinner( players[1] );

                return true;
                }

            if ( theBoard[2 , 0] == theBoard[2 , 1] && theBoard[2 , 1] == theBoard[2 , 2] &&
               !theBoard[2 , 0].Contains( " " ) && !theBoard[2 , 1].Contains( " " ) && !theBoard[2 , 2].Contains( " " ) )
                {
                if ( players[0].Character == theBoard[0 , 2] )
                    DisplayWinner( players[0] );
                else
                    DisplayWinner( players[1] );

                return true;
                }
            #endregion down

            #region diag
            if ( theBoard[0 , 0] == theBoard[1 , 1] && theBoard[1 , 1] == theBoard[2 , 2] &&
               !theBoard[0 , 0].Contains( " " ) && !theBoard[1 , 1].Contains( " " ) && !theBoard[2 , 2].Contains( " " ) )
                {
                if ( players[0].Character == theBoard[0 , 0] )
                    DisplayWinner( players[0] );
                else
                    DisplayWinner( players[1] );

                return true;
                }

            if ( theBoard[2 , 0] == theBoard[1 , 1] && theBoard[1 , 1] == theBoard[0 , 2] &&
               !theBoard[2 , 0].Contains( " " ) && !theBoard[1 , 1].Contains( " " ) && !theBoard[0 , 2].Contains( " " ) )
                {
                if ( players[0].Character == theBoard[2 , 0] )
                    DisplayWinner( players[0] );
                else
                    DisplayWinner( players[1] );

                return true;
                }

            #endregion diag

            #region CAT
            for ( int loop1 = 0; loop1 < 3; loop1++ )
                for ( int loop2 = 0; loop2 < 3; loop2++ )
                    {
                    if ( theBoard[loop1 , loop2] == " " )
                        return false;
                    }
            #endregion CAT

            tOut.WriteLine( "" );
            tOut.WriteLine( "No one WINS, cat game" );
            tOut.WriteLine( "" );

            return true;
            }
        }

    }