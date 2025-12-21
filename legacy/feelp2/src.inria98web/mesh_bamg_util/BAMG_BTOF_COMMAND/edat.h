typedef struct {
  int     shape;       /* TRIANGLE 3  RECTANGLE 4 */
  int     npmax;
  double *x,*y;
  int    *type;

  int     ne,nx,np;
  int    *ielem;
  int     edge_nodes;
  int     mid_nodes;

  int     org_npmax;
  int    *corresp;     /* old -> new */
  int    *rcorresp;    /* new -> old (for new node, it has 0 entry) */

} FEM_edat;


typedef struct {
  int  max_ne_pn; /* maximum number of elements connecting one node */
  int *ne_pn;     /* number of elements connecting each node */
  int *eno_en;    /* element number array for each node      */
  
  int  max_neg_pn; /* maximum number of edges connecting one node */
  int *neg_pn;     /* number of edges connecting each node        */
  int *nno_en;     /* connecting node number array for each node  */

  int  max_edges;  /* number of edges */
  int *egno_tbl_en;/* edge number table by each node entry */

  int *eg_nnos;    /* edge to number of both nodes correspondance */
  int *ee_egno;    /* element to egno correspondance */

  int *edge_node_no;  /* This block added on 97/07/23 for boundary2D */
  int  edge_nodes;    /* Be careful in case of this is 0             */

} EDGE_2d;


typedef struct {
    int points;            /* Number of total nodes */
    int from;              /* Starting vertex No. in  GEOM vertex No. */
    char *from_name;
    int to;                /* Ending vertex No. in  GEOM vertex No. */
    char *to_name;

    int *node_no;          /* Node number array in pre-ordering No. */
    int mid_points;        /* Not use?     */
    double *mid_address;   /* Not use?     */
    
    int region_no;         /* No data in BAMG  */

} Boundary2Dbamg;

typedef struct {
  int    node_no;    /* Vertex number which on GEdge */
  int    edge_no;    /* Corresponding edge number    */
  double pos;        /* Position parameter on Gedge  */
} VonGEdge;


#define YES 1
#define NO  0

