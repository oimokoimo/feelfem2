/*
 *
 *    FEM triangle
 *
 */

#define abs(x)                        ((x)>=0 ? (x) : -(x))

#define TWO_SAME_POINTS   1
#define NORMAL_TYPE      2

static double area2;
static double a1,a2;
static double b1,b2;
static double c1,c2;

fem_triangle_dot_plane(x1,y1,x2,y2,x3,y3,d1,d2,d3)
     int x1,y1;
     int x2,y2;
     int x3,y3;
     double d1,d2,d3;
{
    int xo1,yo1,xo2,yo2,xo3,yo3;
    int type;
    int x,y,xs,xe;
    int y_sign,x_sign;

    area2 = (x1-x3)*(y2-y3) - ( x2-x3)*(y1-y3);
    a1    = y2 - y3;
    b1    = -(x2 - x3);
    c1    = x2*y3 - x3*y2;
    a2    = y3 - y1;
    b2    = -(x3-x1);
    c2    = x3*y1 - x1 * y3;

    xo1 = x1; xo2 = x2; xo3 = x3;
    yo1 = y1; yo2 = y2; yo3 = y3;
    
    if(y1 == y2) {

	type = TWO_SAME_POINTS;
    }
    else if(y1 == y3) {
	int_var_swap(&x2,&x3);
	int_var_swap(&y2,&y3);
	type = TWO_SAME_POINTS;
    }
    else if(y2 == y3) {
	int_var_swap(&x1,&x3);
	int_var_swap(&y1,&y3);
	type = TWO_SAME_POINTS;
    }
    else if((y3-y2)*(y2-y1) > 0) {
	/* y2 is mid point */
	type = NORMAL_TYPE;
    }
    else if((y1-y3)*(y3-y2) > 0) {
	/* y3 is mid point */
	int_var_swap(&x2,&x3);
	int_var_swap(&y2,&y3);
	type = NORMAL_TYPE;
    }
    else if((y2-y1)*(y1-y3) > 0) {
	/* y1 is mid point */
	int_var_swap(&x1,&x2);
	int_var_swap(&y1,&y2);
	type = NORMAL_TYPE;
    }
    else {
	printf("OH MY GOD!\n");
	exit(1);
    }

    if(type == TWO_SAME_POINTS) {
	y_sign = y3-y1;
	y_sign = y_sign/abs(y_sign);

	y = y1;
	while(y != y3) {
	    xs = cross_point(y,x1,y1,x3,y3);
	    xe = cross_point(y,x2,y2,x3,y3);
	    if(xs<xe) {
		for(x = xs; x <= xe; x++) {
		    fem_contour_dot(x,y,xo1,yo1,xo2,yo2,xo3,yo3,d1,d2,d3);
		}
	    }
	    else {
		for(x = xe; x <= xs; x++) {
		    fem_contour_dot(x,y,xo1,yo1,xo2,yo2,xo3,yo3,d1,d2,d3);
		}
	    }
	    y+= y_sign;
	}
	fem_contour_dot(x3,y3,xo1,yo1,xo2,yo2,xo3,yo3,d1,d2,d3);
    }

    else {
	y_sign = y2-y1;
	y_sign = y_sign/abs(y_sign);
	
	y = y1;
	while( y!= y2) {
	    xs = cross_point(y,x1,y1,x2,y2);
	    xe = cross_point(y,x1,y1,x3,y3);
	    if(xs<xe) {
		for(x = xs; x <= xe; x++) {
		    fem_contour_dot(x,y,xo1,yo1,xo2,yo2,xo3,yo3,d1,d2,d3);
		}
	    }
	    else {
		for(x = xe; x <= xs; x++) {
		    fem_contour_dot(x,y,xo1,yo1,xo2,yo2,xo3,yo3,d1,d2,d3);
		}
	    }
	    y+= y_sign;
	}

	y = y2;
	while( y!= y3) {
	    xs = cross_point(y,x2,y2,x3,y3);
	    xe = cross_point(y,x1,y1,x3,y3);
	    if(xs<xe) {
		for(x = xs; x <= xe; x++) {
		    fem_contour_dot(x,y,xo1,yo1,xo2,yo2,xo3,yo3,d1,d2,d3);
		}
	    }
	    else {
		for(x = xe; x <= xs; x++) {
		    fem_contour_dot(x,y,xo1,yo1,xo2,yo2,xo3,yo3,d1,d2,d3);
		}
	    }
	    y+= y_sign;
	}
	fem_contour_dot(x3,y3,xo1,yo1,xo2,yo2,xo3,yo3,d1,d2,d3);
    }
    
    return;
}

int_var_swap( a , b)
     int *a,*b;
{
    int c;
    c = *a;
    *a = *b;
    *b = c;

    return;
}

int cross_point(y,x1,y1,x2,y2)
     int y,x1,y1,x2,y2;
{
    /* y1 never equals to y2 */
    
    int x;

    if(x1 == x2) return(x1);  /* caution y always on the line y1-y2 */

    x = (y - y1)*(x2-x1) / (y2 -y1) + x1;

    return(x);
}



fem_contour_dot(x,y,x1,y1,x2,y2,x3,y3,d1,d2,d3)
     int x,y;
     int x1,y1,x2,y2,x3,y3;
     double d1,d2,d3;
{
    double d;
    double xi_1,xi_2,xi_3;

    xi_1 = (a1* x + b1 * y + c1) / area2;
    xi_2 = (a2* x + b2 * y + c2) / area2;
    xi_3 = 1.0 - xi_1 - xi_2;

    d = xi_1 * d1 + xi_2 * d2 + xi_3 * d3;

/*    printf(" %f %f %f  -> %f  \n",d1,d2,d3,d); */

    fem_raw_point(x,y,d);
    return;
}
