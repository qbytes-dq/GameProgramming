
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
		//add balls to play
		double i_deg;
		double x99;


		int i_radius;

		for (x99=0 ; x99 < g_iNum_Balls ; x99++)
			{
			i_deg = x99 / (double)g_iNum_Balls;
			i_deg *= 360;
			i_radius = ((g_iNum_Balls-1)*16)/3;
			a_listwall->add_ball(592/2 -8,592/2-8,g_pDDSwall,i_deg, i_radius ); 
			}

		//=========================================================================
		//outside walls
		a_listwall->line_wall (0,	0,		576,	0	,g_pDDSwall);	
		a_listwall->line_wall (0,	576,	576,	576	,g_pDDSwall);
		a_listwall->line_wall (0,	16,		0,		576	,g_pDDSwall);
		a_listwall->line_wall (576,	16,		576,	576	,g_pDDSwall);

		//=========================================================================
		// center
		int num_in_cir;
		int xx1,yy1,xx2,rr1;

		num_in_cir = 10;
		xx1 = 592/2 -8;
		yy1	= 592/2 -8;
		rr1 = 100;

		for (x99=0 ; x99 < num_in_cir ; x99++)
			{
			i_deg = x99 / (double)num_in_cir;
			i_deg *= 360;
			a_listwall->add_circle(xx1			, yy1		,rr1, (int)i_deg, g_pDDSwall);	
			}
		//=========================================================================
		// outside circles

		num_in_cir = 10;
		xx1 = int(16*2.8);
		xx2 = 592-16;
		rr1 = 25;
		// top left
		for (x99=0 ; x99 < num_in_cir ; x99++)
			{
			i_deg = x99 / (double)num_in_cir;
			i_deg *= 360;
			a_listwall->add_circle(xx1			, xx1		,rr1, (int)i_deg, g_pDDSwall);	
			}
		// top right
		for (x99=0 ; x99 < num_in_cir ; x99++)
			{
			i_deg = x99 / (double)num_in_cir;
			i_deg *= 360;
			a_listwall->add_circle(xx2 - xx1	, xx1		,rr1, (int)i_deg, g_pDDSwall);	
			}
		//bottom left
		for (x99=0 ; x99 < num_in_cir ; x99++)
			{
			i_deg = x99 / (double)num_in_cir;
			i_deg *= 360;
			a_listwall->add_circle(xx1			, xx2 - xx1	,rr1, (int)i_deg, g_pDDSwall);	
			}
		//bottom right
		for (x99=0 ; x99 < num_in_cir ; x99++)
			{
			i_deg = x99 / (double)num_in_cir;
			i_deg *= 360;	
			a_listwall->add_circle(xx2 - xx1	, xx2 - xx1	,rr1, (int)i_deg, g_pDDSwall);
			}