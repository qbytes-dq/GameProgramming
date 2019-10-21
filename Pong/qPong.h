
//g_bBackGround = false;
    

// inside box
	a_list.line_wall ( (1024/4)*1,(768/4)*1,(1024/4)*3,(768/4)*1,g_pDDSwall);
	a_list.line_wall ( (1024/4)*1,(768/4)*1,(1024/4)*1,(768/4)*3,g_pDDSwall);
	a_list.line_wall ( (1024/4)*1,(768/4)*3,(1024/4)*3,(768/4)*3,g_pDDSwall);
	a_list.line_wall ( (1024/4)*3,(768/4)*1,(1024/4)*3,(768/4)*3,g_pDDSwall);
 
// add ball
	for (x=0;x<1;x++)
	{
		a_list.add_ball ( ((1024/5)*2)+(x*16)-92,(768/4)*2-032,g_pDDSwall);  
	}
