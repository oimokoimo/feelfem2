// feelfem2 v0.1 DSL prototype
// Author: Fujio Hidehiro & Chappy
// Purpose: Minimal educational FEM DSL for 2D Poisson problems

fem u[p1], v[p1];

solve[u; v] {
  quadrature gauss2;

  weq:
    integral( dx(u)*dx(v) + dy(u)*dy(v) )
  = integral( f * v );

  dbc:
    u = 0, on boundary;
}
