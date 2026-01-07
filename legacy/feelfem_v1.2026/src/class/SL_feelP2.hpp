/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_feelP2.hpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : feelP2 library generate class
 *
 */


#ifndef FEM_CLASS_SL_FEELP2
#define FEM_CLASS_SL_FEELP2

#include "PM_feelP2.hpp"

class SL_feelP2
  :  public PM_feelP2 {

public:
  SL_feelP2() { return; } // do nothing
  ~SL_feelP2(){ return; } // do nothing

  void SL_diskio(int);
  void SL_zero(int);
  void SL_set(int);
  void SL_filset(int);
  void SL_closefil(int);
  void SL_dat_edat(int);
  void SL_dat_node(int);
  void SL_dat_nodeset(int);
  void SL_dat_num(int);
  void SL_dat_ip(int);
  void SL_datinp(int);
  void SL_get_ielem(int);
  void SL_get_inset(int);
  void SL_inpdat_wrt(int);
  void SL_report(int);
  void SL_ipd_make(int);
  void SL_ipd_nonode(int);
  void SL_ipf_nfree(int);
  void SL_f_alloc(int);
  void SL_f_free(int);
  void SL_feelget(int);
  void SL_getdate(int);
  void SL_cptime(int);

  void generateLibrary(void) {

    SL_diskio(1);
    SL_zero(1);
    SL_set(1);
    SL_filset(1);
    SL_closefil(5);
    SL_dat_edat(2);
    SL_dat_node(2);
    SL_dat_nodeset(2);
    SL_dat_num(2);
    SL_dat_ip(2);
    SL_datinp(5);
    SL_get_ielem(10);
    SL_get_inset(10);
    SL_inpdat_wrt(10);
    SL_report(10);
    SL_ipd_make(1);
    SL_ipd_nonode(1);
    SL_ipf_nfree(1);
    SL_f_alloc(1);
    SL_f_free(5);
    SL_feelget(5);
    SL_getdate(1);
    SL_cptime(1);

    return;
  }


};

#endif
