/*
   FEEL p2  MAKE FORTRAN LIBRARY   cal_ht
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

#define FNAME "cal_ht.f"
void lib_cal_ht()
{
   FILE *fp;
   StoreMakefile(FNAME,SYSTEM_LIBRARY);
   if(LIMIT_FILE == 1) return;
   fp = OpenFileToWrite( FNAME );
   F77("      subroutine cal_ht_a(ielem,neelem,nenode,KHa,npmax)\n");
   F77("*---------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*---------------------------------------------------------------------\n");
   F77("*  Purpose: スカイライン行列の列の高さを計算する補助プログラム\n");
   F77("*           要素内の最小節点番号を探し出す\n");
   F77("*\n");
   F77("*        KHaは、各節点における接続最小節点番号\n");
   F77("*\n");
   F77("*  注意: KHaは、0クリアされているはず\n");
   F77("*\n");
   F77("*---------------------------------------------------------------------\n");
   F77("      dimension ielem(nenode,neelem),KHa(*)\n");
   F77("*---\n");
   F77("      do 10 i=1,npmax\n");
   F77("         KHa(i) = npmax + 1\n");
   F77(" 10   continue\n");
   F77("*---\n");
   F77("      do 100 i=1,neelem\n");
   F77("         \n");
   F77("         ip_min = ielem(1,i)\n");
   F77("\n");
   F77("*---  各要素内の最小節点番号を求める\n");
   F77("         do 120 j=2,nenode\n");
   F77("            if(ip_min .gt. ielem(j,i)) ip_min = ielem(j,i)\n");
   F77(" 120     continue\n");
   F77("         \n");
   F77("         do 130 j=1,nenode\n");
   F77("            if(KHa(ielem(j,i)) .gt. ip_min) KHa(ielem(j,i)) = ip_min\n");
   F77(" 130     continue\n");
   F77("         \n");
   F77(" 100  continue\n");
   F77("\n");
   F77("c      do 200 j=1,468\n");
   F77("c       write(*,*) 'KHa(',j,')= ',kha(j)\n");
   F77("c 200  continue\n");
   F77("*---\n");
   F77("      return\n");
   F77("      end\n");
   F77("      subroutine cal_ht(KHa,KH,IPF,IPD,npmax,neq)\n");
   F77("*---------------------------------------------------------------------\n");
   F77("*  FEEL P2 System Subroutine\n");
   F77("*---------------------------------------------------------------------\n");
   F77("*  Purpose: スカイライン行列の列の高さを計算するプログラム\n");
   F77("*\n");
   F77("*  注意: 配列KHaの0は、未使用節点の意味\n");
   F77("*\n");
   F77("*  変数: KHa(npmax)     各節点に関連する最小節点番号\n");
   F77("*        KH (neq)       スカイライン行列の列の高さ、対角のみの場合の0から始める\n");
   F77("*        IPF(npmax)     節点毎自由度\n");
   F77("*        IPD(npmax)     累積節点自由度\n");
   F77("*        npmax      入  総節点数\n");
   F77("*        neq        入  方程式の本数(連立一次方程式の連立の数)\n");
   F77("*---------------------------------------------------------------------\n");
   F77("      dimension KHa(npmax),KH(neq),IPF(npmax),IPD(npmax)\n");
   F77("*---\n");
   F77("      do 100 i=1,npmax\n");
   F77("         \n");
   F77("         if(IPF(i) .eq. 0) goto 100\n");
   F77("*\n");
   F77("* min_np は節点 i における最小 関連方程式番号\n");
   F77("*\n");
   F77("         min_np  = IPD( KHa(i) )\n");
   F77("         ip_base = IPD( i )\n");
   F77("*---\n");
   F77("         do 200 j=1,IPF(i)\n");
   F77("            KH( ip_base + j - 1) = min_np \n");
   F77(" 200     continue\n");
   F77("*---\n");
   F77(" 100  continue\n");
   F77("*---\n");
   F77("      do 300 i=1,neq\n");
   F77("         KH(i) = i - KH(i)\n");
   F77("C         write(*,*) 'KH(',i,') = ',kh(i)\n");
   F77(" 300  continue\n");
   F77("      return\n");
   F77("      end\n");
   F77("\n");
 CloseFile(fp);
 return;
}
