/************************************************************************/
/*                                                                      */
/* View ver 1.0 1994.5.17                                               */
/* viewcont.c                                                           */
/* Copy rights - all rights reserved by NEC                             */
/*                                                                      */
/************************************************************************/

#include "view.h"

void    ViewContour(p,att,n,v,cid,id)
Vpoint_struct   *p;
float           *v;
int             n,att,id;
int             *cid;
{
    int             i,j,k;
    int             fg;
    int             dn,dc;
    int             fp0[3],fp1[3],fp2[3];
    Vpoint_struct   pp0[3],pp1[3],pp2[3];
    Vpoint          dr[6];

    float           pp;

    fg = 0;

    for (i = 0;i < n;i ++) {

        for (j = 0;j < 3;j ++) {
            fp0[j] = 0;
            fp1[j] = 0;
            fp2[j] = 0;
        }

        if (ViewUtilCheckLine(&p[0],&p[1],v[i],&pp0[0],att) > 0) fp0[0] = 1;
        if (ViewUtilCheckLine(&p[1],&p[2],v[i],&pp0[1],att) > 0) fp0[1] = 1;
        if (ViewUtilCheckLine(&p[2],&p[0],v[i],&pp0[2],att) > 0) fp0[2] = 1;

        if (i != n - 1) {
            if (ViewUtilCheckLine(&p[0],&p[1],v[i+1],&pp1[0],att) > 0) 
				fp1[0] = 1;
            if (ViewUtilCheckLine(&p[1],&p[2],v[i+1],&pp1[1],att) > 0) 
				fp1[1] = 1;
            if (ViewUtilCheckLine(&p[2],&p[0],v[i+1],&pp1[2],att) > 0) 
				fp1[2] = 1;
        }

        if (i != 0) {
            if (ViewUtilCheckLine(&p[0],&p[1],v[i-1],&pp2[0],att) > 0) 
				fp2[0] = 1;
            if (ViewUtilCheckLine(&p[1],&p[2],v[i-1],&pp2[1],att) > 0) 
				fp2[1] = 1;
            if (ViewUtilCheckLine(&p[2],&p[0],v[i-1],&pp2[2],att) > 0) 
				fp2[2] = 1;
        }


        switch(att) {
            case    0:
                dn = 0;
            	for (j = 0;j < 3;j ++) {
               	    if (fp0[j] == 1) {
		        		ViewUtilVpoint(&dr[dn],&pp0[j]); dn ++;
               	    }
            	}

				fg = 1;

            	if (dn == 2)
               	    ViewSetLine(dr,2,0,cid[i],id);
            	break;

		case	1:
		/*  0-1-2	*/

			/*	0-1	*/
				if (fp0[0] == 1 && fp0[1] == 1) {

					if (p[0].scalar > p[1].scalar) {

						dn = 0;
						if (fp1[0] == 1 && fp1[1] == 1) {
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[0]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
            				ViewSetPolygon(dr,dn,0,cid[i+1],id);
							fg = 1;
						}else if (fp1[1] == 1 && fp1[2] == 1){
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&p[0]);   dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
            				ViewSetPolygon(dr,dn,0,cid[i+1],id);
							fg = 1;
						}else if (fp1[2] == 1 && fp1[0] == 1){
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&p[2]);   dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[0]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
            				ViewSetPolygon(dr,dn,0,cid[i+1],id);
							fg = 1;
						}else{
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&p[2]);   dn ++;
							ViewUtilVpoint(&dr[dn],&p[0]);   dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
            				ViewSetPolygon(dr,dn,0,cid[i+1],id);
							fg = 1;
						}

						dn = 0;
						if (fp2[0] == 1 && fp2[1] == 1) {
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp2[0]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp2[1]); dn ++;
            				ViewSetPolygon(dr,dn,0,cid[i],id);
							fg = 1;
						}else{
							ViewUtilVpoint(&dr[dn],&p[1]);   dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
            				ViewSetPolygon(dr,dn,0,cid[i],id);
							fg = 1;
						}

					}else{

						dn = 0;
						if (fp1[0] == 1 && fp1[1] == 1) {
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[0]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[1]); dn ++;
            				ViewSetPolygon(dr,dn,0,cid[i+1],id);
							fg = 1;
						}else{
							ViewUtilVpoint(&dr[dn],&p[1]);   dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
            				ViewSetPolygon(dr,dn,0,cid[i+1],id);
							fg = 1;
						}

						dn = 0;
                        if (fp2[0] == 1 && fp2[1] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }else if (fp2[1] == 1 && fp2[2] == 1){
                            ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[0]);   dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }else if (fp2[2] == 1 && fp2[0] == 1){
                            ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[2]);   dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }else{
                            ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }

					}
				/*	1-2	*/
				}else if (fp0[1] == 1 && fp0[2] == 1) {

					if (p[1].scalar > p[2].scalar) {

						dn = 0;
						if (fp1[1] == 1 && fp1[2] == 1) {
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[1]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
						}else if (fp1[2] == 1 && fp1[0] == 1) {
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[0]); dn ++;
							ViewUtilVpoint(&dr[dn],&p[1]);   dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
						}else if (fp1[0] == 1 && fp1[1] == 1) {
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&p[0]);   dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[0]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[1]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
						}else{
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&p[0]);   dn ++;
							ViewUtilVpoint(&dr[dn],&p[1]);   dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
						}

						dn = 0;
						if (fp2[1] == 1 && fp2[2] == 1) {
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp2[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp2[1]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
						}else{
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&p[2]);   dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
						}

					}else{

						dn = 0;
						if (fp1[1] == 1 && fp1[2] == 1) {
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp1[1]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
						}else{
							ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
							ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
							ViewUtilVpoint(&dr[dn],&p[2]);   dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
						}

                        dn = 0;
                        if (fp2[1] == 1 && fp2[2] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[1]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }else if (fp2[2] == 1 && fp2[0] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[1]);   dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }else if (fp2[0] == 1 && fp2[1] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[0]);   dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[1]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }else{
                            ViewUtilVpoint(&dr[dn],&pp0[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[0]);   dn ++;
                            ViewUtilVpoint(&dr[dn],&p[1]);   dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }
					}
				/*	2-0	*/
				}else if (fp0[2] == 1 && fp0[0] == 1) {

					if (p[2].scalar > p[0].scalar) {

						dn = 0;
						if (fp1[2] == 1 && fp1[0] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp1[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp1[2]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
						}else if (fp1[0] == 1 && fp1[1] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp1[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp1[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[2]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
						}else if (fp1[1] == 1 && fp1[2] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp1[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp1[2]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
						}else{
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[2]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
						}

						dn = 0;
						if (fp2[2] == 1 && fp2[0] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[2]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
						}else{
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[0]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
						}

					}else{

                        dn = 0;
                        if (fp1[2] == 1 && fp1[0] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp1[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp1[2]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
                        }else{
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[0]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i+1],id);
                            fg = 1;
                        }

                        dn = 0;
                        if (fp2[2] == 1 && fp2[0] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[2]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }else if (fp2[0] == 1 && fp2[1] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[2]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }else if (fp2[1] == 1 && fp2[2] == 1) {
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp2[2]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }else{
                            ViewUtilVpoint(&dr[dn],&pp0[2]); dn ++;
                            ViewUtilVpoint(&dr[dn],&pp0[0]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[1]); dn ++;
                            ViewUtilVpoint(&dr[dn],&p[2]); dn ++;
                            ViewSetPolygon(dr,dn,0,cid[i],id);
                            fg = 1;
                        }
					}
				}
					
		}
	}

	if (fg == 0) {

/*
		pp = ViewUtilMax(p[0].scalar,p[1].scalar);
		pp = ViewUtilMax(pp         ,p[2].scalar);
*/
		pp = (p[0].scalar + p[1].scalar + p[2].scalar) / 3.0;

		if (pp < 0.0) {
			dc = 0;

			if (v[0] > pp) {
				dc = 0;
			}else{
				for (k = 0;k < n - 1;k ++) {
					if (v[k] <= pp && v[k+1] > pp) { 
						dc = k + 1;
						break;
					}
				}
				if (v[n - 1] <= pp) {
					dc = n;
				}
			}

		}else{

			if (v[0] >= pp) {
				dc = 0;
			}else{
				for (k = 0;k < n - 1;k ++) {
					if (v[k] < pp && v[k+1] >= pp) { 
						dc = k + 1;
						break;
					}
				}
				if (v[n - 1] < pp) {
					dc = n;
				}
			}
		}

		dn = 0;
   		ViewUtilVpoint(&dr[dn],&p[0]); dn ++;
   		ViewUtilVpoint(&dr[dn],&p[1]); dn ++;
   		ViewUtilVpoint(&dr[dn],&p[2]); dn ++;
   		ViewSetPolygon(dr,dn,0,cid[dc],id);

	}
}
