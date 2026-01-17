/************************************************************************/
/*                                                                      */
/* View ver 1.0 1994.5.17                                               */
/* viewutil.c                                                           */
/* Copy rights - all rights reserved by NEC                             */
/*                                                                      */
/************************************************************************/

#include "view.h"

void	ViewUtilVector(r,p)
Vpoint	*r,*p;
{
	float	l;

	l = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);
	
	if (p->x != 0.0 || p->y != 0.0 || p->z != 0.0) {
		r->x = p->x / l;
		r->y = p->y / l;
		r->z = p->z / l;
	}else{
		r->x = 0.0;
		r->y = 0.0;
		r->z = 0.0;
	}
}

void	ViewUtilRotateXYZ(r,p,ax,ay,az)
Vpoint	*r,*p;
float	ax,ay,az;
{
	float   x1,x2,x3,y1,y2,y3,z1,z2,z3;

    x1 =   p->x * cos((double)ay) + p->z * sin((double)ay);
    y1 =   p->y;
    z1 = - p->x * sin((double)ay) + p->z * cos((double)ay);	
    x2 =   x1;
    y2 =   y1   * cos((double)ax) - z1   * sin((double)ax);
    z2 =   y1   * sin((double)ax) + z1   * cos((double)ax);
    x3 =   x2   * cos((double)az) - y2   * sin((double)az);
    y3 =   x2   * sin((double)az) + y2   * cos((double)az);
    z3 =   z2;

	r->x = x3;
	r->y = y3;
	r->z = z3;
}

float	ViewUtilDistance(p0,p1)
Vpoint	*p0,*p1;
{
    float   length;

    length = sqrt((double)(p0->x - p1->x) * (double)(p0->x - p1->x)
            	+ (double)(p0->y - p1->y) * (double)(p0->y - p1->y)
            	+ (double)(p0->z - p1->z) * (double)(p0->z - p1->z));

    return(length);
}

float	ViewUtilMax(p1,p2)
float	p1,p2;
{
	if (p1 > p2) 	return(p1);
	else			return(p2);
}

float	ViewUtilMin(p1,p2)
float	p1,p2;
{
	if (p1 < p2) 	return(p1);
	else			return(p2);
}

float	ViewUtilInnerAngle(p1,p2)
Vpoint	*p1,*p2;
{
	float   inner,length1,length2;

    length1 = sqrt(p1->x * p1->x + p1->y * p1->y + p1->z * p1->z);
    length2 = sqrt(p2->x * p2->x + p2->y * p2->y + p2->z * p2->z);

    inner = (p1->x * p2->x + p1->y * p2->y + p1->z * p2->z)
          / (length1 * length2);

    return(inner);
}

float	ViewUtilInnerProduct(p1,p2)
Vpoint	*p1,*p2;
{
	float	inner;

    inner = p1->x * p2->x + p1->y * p2->y + p1->z * p2->z;

	return(inner);
}

void	ViewUtilNormal(p0,r0)
Vpoint	*p0,*r0;
{
    Vpoint 	pp[3],rp;
    int     i;
    float   length;

    for (i = 0;i < 3;i ++) {
        pp[i].x = p0->x;
        pp[i].y = p0->y;
        pp[i].z = p0->z;
        p0 ++;
    }
    rp.x = (pp[0].y - pp[1].y) * (pp[0].z + pp[1].z)
         + (pp[1].y - pp[2].y) * (pp[1].z + pp[2].z)
         + (pp[2].y - pp[0].y) * (pp[2].z + pp[0].z);
    rp.y = (pp[0].z - pp[1].z) * (pp[0].x + pp[1].x)
         + (pp[1].z - pp[2].z) * (pp[1].x + pp[2].x)
         + (pp[2].z - pp[0].z) * (pp[2].x + pp[0].x);
    rp.z = (pp[0].x - pp[1].x) * (pp[0].y + pp[1].y)
         + (pp[1].x - pp[2].x) * (pp[1].y + pp[2].y)
         + (pp[2].x - pp[0].x) * (pp[2].y + pp[0].y);
    length = sqrt(rp.x * rp.x + rp.y * rp.y + rp.z * rp.z);

    r0->x = rp.x / length;
    r0->y = rp.y / length;
    r0->z = rp.z / length;
}

void	ViewUtilQuickSort(num,len,first,last)
int		*num;
float	*len;
int		first,last;
{
	int		i,j;
	float	av;
	float	l;
	int		n;

	i = first;
	j = last;

	av = len[(i + j) / 2];

	for(;;) {
		while(len[i] > av) {
			i ++;
		}

		while(len[j] < av) {
			j --;
		}
		if (i >= j) break;

		l = len[i];
		n = num[i];

		len[i] = len[j];
		num[i] = num[j];

		len[j] = l;
		num[j] = n;

		i ++;
		j --;
	}

	if (first < i - 1) ViewUtilQuickSort(num,len,first,i - 1);
	if (j + 1 < last ) ViewUtilQuickSort(num,len,j + 1,last );
	
}

int		ViewUtilArcCenter(rp,rd,p)
Vpoint	*rp,*p;
float	*rd;
{
	Vpoint	p1,p2,p3;
	Vpoint	a0,b0;
	Vpoint	r0;
	float	aa,bb,ab,dt;
	float	s,t;

	p1.x = p[0].x; p1.y = p[0].y; p1.z = p[0].z;
	p2.x = p[1].x; p2.y = p[1].y; p2.z = p[1].z;
	p3.x = p[2].x; p3.y = p[2].y; p3.z = p[2].z;

	a0.x = p1.x - p2.x;
	a0.y = p1.y - p2.y;
	a0.z = p1.z - p2.z;

	b0.x = p3.x - p2.x;
	b0.y = p3.y - p2.y;
	b0.z = p3.z - p2.z;

	aa = a0.x * a0.x + a0.y * a0.y + a0.z * a0.z;
	bb = b0.x * b0.x + b0.y * b0.y + b0.z * b0.z;

	ab = a0.x * b0.x + a0.y * b0.y + a0.z * b0.z;

	dt = aa * bb - ab * ab;

	if (dt < 1.0e-10) return( -1 );

  	s = (bb * (aa / 2.0) - ab * (bb / 2.0)) / dt;
  	t = (aa * (bb / 2.0) - ab * (aa / 2.0)) / dt;

	r0.x = s * a0.x + t * b0.x;
	r0.y = s * a0.y + t * b0.y;
	r0.z = s * a0.z + t * b0.z;
		
	rp->x = r0.x + p2.x;
	rp->y = r0.y + p2.y;
	rp->z = r0.z + p2.z;

	*rd = ViewUtilDistance(&p1,rp);

	return( 1 );
}

int		ViewUtilCheckLine(p0,p1,value,pp,att)
Vpoint_struct	*p0,*p1,*pp;
float			value;
int				att;
{
    float   max,min;
    float  	dist[2],ratio[2];
    Vpoint 	unit;

	if (att != 1) {
		if (fabs(p0->scalar - value) < 1.0e-08 
     	 && fabs(p1->scalar - value) < 1.0e-08) {

        	pp->point.x = p0->point.x;
        	pp->point.y = p0->point.y;
        	pp->point.z = p0->point.z;
        	pp->scalar  = value;

        	return( 1 );
		}
	}

	if ((p0->scalar <= value && p1->scalar > value) || 
		(p0->scalar >= value && p1->scalar < value)) {

        dist[0] = fabs(value - p0->scalar);
        dist[1] = fabs(value - p1->scalar);

		if (fabs(dist[0] + dist[1]) < 1.0e-08) {
			ratio[0] = 0.0;
			ratio[1] = 0.0;
		}else{
       		ratio[0] = dist[0] / (dist[0] + dist[1]);
       		ratio[1] = dist[1] / (dist[0] + dist[1]);
		}

        unit.x = fabs(p1->point.x - p0->point.x);
        unit.y = fabs(p1->point.y - p0->point.y);
        unit.z = fabs(p1->point.z - p0->point.z);

		if (p0->point.x < p1->point.x) 
        	pp->point.x = p0->point.x + ratio[0] * unit.x;
		else
        	pp->point.x = p1->point.x + ratio[1] * unit.x;

		if (p0->point.y < p1->point.y) 
        	pp->point.y = p0->point.y + ratio[0] * unit.y;
		else
        	pp->point.y = p1->point.y + ratio[1] * unit.y;

		if (p0->point.z < p1->point.z) 
        	pp->point.z = p0->point.z + ratio[0] * unit.z;
		else
        	pp->point.z = p1->point.z + ratio[1] * unit.z;

        pp->scalar  = value;

        return( 1 );

	}

	return( - 1 );

}

void	ViewUtilVpoint(vp,vsp)
Vpoint			*vp;
Vpoint_struct	*vsp;
{
	vp->x = vsp->point.x;
	vp->y = vsp->point.y;
	vp->z = vsp->point.z;
}

float	ViewUtilLagrange(x,n,fx,fy)
float   x,*fx,*fy;
int     n;
{
    int     i,j;
    float   s,p;

    s = 0.0;
    for (i = 0;i < n;i ++) {
        p = fy[i];
        for (j = 0;j < n;j ++) {
            if (i != j) {
                p *= (x - fx[j]) / (fx[i] - fx[j]);
            }
        }
        s += p;
    }
    return( s );
}







	
