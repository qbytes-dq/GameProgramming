/////////////////////////////////////////////////
void dopathable()
{
	DWORD time_start = timeGetTime();

	int attempts = 0;

	int xLoop = 0;
	int yLoop = 0;
	int zLoop = 0;
	int zzLoop = 0;

	int iKeep = 0;

	int cxb,cxe;
	int cyb,cye;

	// set map up as all hidden
	for( cx = 0 ; cx < width; cx++)
		for( cy = 0 ; cy < height; cy++)
			mapmark[cx][cy]=false;

	// set map edges as unreachable
	for( cx = 0 ; cx < width-1; cx++)
		{
			mappath[cx][0]=999;
			mappath[0][cx]=999;
			mappath[cx][width-1]=999;
			mappath[height-1][cx]=999;
		}
	mappath[height-1][height-1]=999;

	// scan the map
	do
	{
		attempts++;
		// not found yet
		found=false;

		// setup x
		cxb = ptStart.x - attempts;
		cxe = ptStart.x + attempts;

		if (cxb < 0)
			cxb = 0;

		if (cxe > width)
			cxe = width;

		//setup y
		cyb = ptStart.y - attempts;
		cye = ptStart.y + attempts;

		if (cyb < 0)
			cyb = 0;

		if (cye > height)
			cye = height;

		for( cx = cxb ; cx < cxe; cx++)
			for( cy = cyb ; cy < cye; cy++)
			{
				mapmark[cx][cy]=false;
				// make sure it is -1 square
				if(mappath[cx][cy] == -1)
				{
					xLoop ++;
					for ( nx = cx - 1; nx <= cx + 1; nx++)
						for ( ny = cy - 1; ny <= cy + 1 ; ny++)
							{
							yLoop ++;
							// make sure the neighbor is on the map
							//if( nx >= 0 && ny >= 0 && nx < width && ny < height)  // is it on the map
								if (mappath[nx][ny]>=0 && mappath[nx][ny]!=999)   // is it setable
									if (!( nx == cx && ny == cy)) // dont' check myself
										{
										mapmark[cx][cy]=true;
										found=true;
										}
							}
				}
			}
		///////////////////////////////////////////////////
		// now scan the marks
		for( cx = cxb ; cx < cxe; cx++)
			for( cy = cyb ; cy < cye; cy++)
				if (mapmark[cx][cy])
				{
					lowvalue = 999;
					zLoop ++;
					for( nx = cx - 1 ; nx <= cx + 1 ; nx++)
						{
						for( ny = cy - 1 ; ny <= cy + 1 ; ny++)
							{
							zzLoop++;
							if( nx >= 0 && ny >= 0 && nx < width && ny < height)
								if( mappath[nx][ny] >= 0)
									if(mappath[nx][ny] < lowvalue)
										lowvalue = mappath[nx][ny];
							}
						}
						mappath[cx][cy] = lowvalue + 1;
				}

	// this speeds it up
	if (mappath[ptEnd.x][ptEnd.y] != -1)
		if (iKeep++ > 5)
			{
			for (x = 0; x < width;x++)
				for (y = 0 ; y < height; y++)
					if (mappath[x][y] == -1)
						mappath[x][y] = 999;

			DWORD time_end = timeGetTime();
		
			printf("\n dopathable %d\tattempts = %i\txLoop = %i\tyLoop = %i\tzLoop = %i\tzzLoop = %i",time_end - time_start, attempts, xLoop, yLoop, zLoop, zzLoop);

			return;
			}
	}
	while(found);

	DWORD time_end = timeGetTime();
		
	printf("\n dopathable %d\tattempts = %i\txLoop = %i\tyLoop = %i\tzLoop = %i\tzzLoop = %i",time_end - time_start, attempts, xLoop, yLoop, zLoop, zzLoop);
}
