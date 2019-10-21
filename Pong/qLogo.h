//g_bBackGround = false;

//outside walls
	a_list.line_wall (0,0,1024-16,0,g_pDDSwall);	
	a_list.line_wall (0,768-16,1024-16,768-16,g_pDDSwall);
	a_list.line_wall (0,16,0,768-32,g_pDDSwall);
	a_list.line_wall (1024-16,16,1024-16,768-16,g_pDDSwall);

// add paddle
	a_list.add_paddle (  50, 50,g_pDDSpaddle);  
