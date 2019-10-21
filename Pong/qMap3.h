

	// add paddles first.  they user owner IDs and are passed around
	//=========================================================================
	// inside paddles
	// Team 1 (red)
		if (Player1.i_PlayerType[0] != Open && Player1.i_PlayerType[0] != Closed)
			a_listwall->add_v_paddle ( 592-(16*5),	300 ,	g_pDDSpaddle_V, 0, Player1); 
	// Team 2 (yellow)
		if (Player1.i_PlayerType[1] != Open && Player1.i_PlayerType[1] != Closed)
			a_listwall->add_v_paddle (   (16*4),		300,	g_pDDSpaddle_V, 1, Player1); 
	// Team 3 (blue)
		if (Player1.i_PlayerType[2] != Open && Player1.i_PlayerType[2] != Closed)
			a_listwall->add_h_paddle (  300,			(16*4),		g_pDDSpaddle_H, 2, Player1); 
	// Team 4 (Green)
		if (Player1.i_PlayerType[3] != Open && Player1.i_PlayerType[3] != Closed)
			a_listwall->add_h_paddle (  300,			592-(16*5),	g_pDDSpaddle_H, 3, Player1); 

	//=========================================================================
	// outside paddles
	// Team 1 (red)
		if (Player1.i_PlayerType[4] != Open && Player1.i_PlayerType[4] != Closed)
			a_listwall->add_v_paddle ( 592-(16*4),			300 , g_pDDSpaddle_V, 4, Player1); 
	// Team 2 (yellow)
		if (Player1.i_PlayerType[5] != Open && Player1.i_PlayerType[5] != Closed)
			a_listwall->add_v_paddle (	(16*3)+1,		 300, g_pDDSpaddle_V, 5, Player1); 
	// Team 3 (blue)
		if (Player1.i_PlayerType[6] != Open && Player1.i_PlayerType[6] != Closed)
			a_listwall->add_h_paddle (  300,	(16*3)-1, g_pDDSpaddle_H, 6, Player1); 
	// Team 4 (Green)
		if (Player1.i_PlayerType[7] != Open && Player1.i_PlayerType[7] != Closed)
			a_listwall->add_h_paddle (  300, 592-(16*4)+1, g_pDDSpaddle_H, 7, Player1);

	//=========================================================================
	int xx9 = 592/2 -8;
	//add ball to play
	//add ball

	double i_deg;
	double x99;
	for (x99=0 ; x99 < g_iNum_Balls ; x99++)
		{
		i_deg = x99 / (double)g_iNum_Balls;
		i_deg *= 360;
		a_listwall->add_ball(xx9, xx9, g_pDDSwall, i_deg, 130 ); 
		}

	//outside walls
		a_listwall->line_wall (0,0,600-16,0,g_pDDSwall);	
		a_listwall->line_wall (0,600-16,600-16,600-16,g_pDDSwall);
		a_listwall->line_wall (0,16,0,600-32,g_pDDSwall);
		a_listwall->line_wall (600-16,16,600-16,600-16,g_pDDSwall);

	// corners
		// top left
		a_listwall->line_wall (16,64,64-16,64,g_pDDSwall);	
		a_listwall->line_wall (64,16,64,64,g_pDDSwall);
		// bottom left
		a_listwall->line_wall (64,592-64,64,592-17,g_pDDSwall);	
		a_listwall->line_wall (16,592-80,64,592-80,g_pDDSwall);
		// top right
		a_listwall->line_wall (592-80,64,592-17,64,g_pDDSwall);	
		a_listwall->line_wall (592-80,48,592-80,16,g_pDDSwall);
		// bottom right
		a_listwall->line_wall (592-17,592-80,592-64,592-80,g_pDDSwall);	
		a_listwall->line_wall (592-80,592-32,592-80,592-80,g_pDDSwall);	
