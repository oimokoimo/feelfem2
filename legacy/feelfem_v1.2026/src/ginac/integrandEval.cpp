/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : integrandEval.cpp
 *  Date     : 2002/02/18
 *  Modified : 2002/09/16    Add userfuncsymbol.hpp
 *  
 *  Purpose  : treat element stiffness mathematical component
 *  
 */

#include <stdio.h>
#include <assert.h>
#include <ginac/ginac.h>
using namespace GiNaC;

#include <strstream.h>

#include "feeldef.hpp"

symbol x("x"),y("y"),z("z");

symbol _m1("_m1");
symbol _m2("_m2");
symbol _m3("_m3");
symbol _m4("_m4");
symbol _m5("_m5");
symbol _m6("_m6"); 
symbol _m7("_m7");
symbol _m8("_m8");
symbol _m9("_m9");
symbol _m10("_m10");
symbol _m11("_m11");
symbol _m12("_m12");
symbol _m13("_m13");
symbol _m14("_m14");
symbol _m15("_m15");
symbol _m16("_m16");
symbol _m17("_m17");
symbol _m18("_m18");
symbol _m19("_m19");
symbol _m20("_m20");
symbol _m21("_m21");
symbol _m22("_m22");
symbol _m23("_m23");
symbol _m24("_m24");
symbol _m25("_m25");
symbol _m26("_m26");
symbol _m27("_m27");
symbol _m28("_m28");
symbol _m29("_m29");
symbol _m30("_m30");
symbol _m31("_m31");
symbol _m32("_m32");
symbol _m33("_m33");
symbol _m34("_m34");
symbol _m35("_m35");
symbol _m36("_m36");
symbol _m37("_m37");
symbol _m38("_m38");
symbol _m39("_m39");
symbol _m40("_m40");
symbol _m41("_m41");
symbol _m42("_m42");
symbol _m43("_m43");
symbol _m44("_m44");
symbol _m45("_m45");
symbol _m46("_m46");
symbol _m47("_m47");
symbol _m48("_m48");
symbol _m49("_m49");
symbol _m50("_m50");
symbol _m51("_m51");
symbol _m52("_m52");
symbol _m53("_m53");
symbol _m54("_m54");
symbol _m55("_m55");
symbol _m56("_m56");
symbol _m57("_m57");
symbol _m58("_m58");
symbol _m59("_m59");
symbol _m60("_m60");
symbol _m61("_m61");
symbol _m62("_m62");
symbol _m63("_m63");
symbol _m64("_m64");
symbol _m65("_m65");
symbol _m66("_m66");
symbol _m67("_m67");
symbol _m68("_m68");
symbol _m69("_m69");
symbol _m70("_m70");
symbol _m71("_m71");
symbol _m72("_m72");
symbol _m73("_m73");
symbol _m74("_m74");
symbol _m75("_m75");
symbol _m76("_m76");
symbol _m77("_m77");
symbol _m78("_m78");
symbol _m79("_m79");
symbol _m80("_m80");
symbol _m81("_m81");
symbol _m82("_m82");
symbol _m83("_m83");
symbol _m84("_m84");
symbol _m85("_m85");
symbol _m86("_m86");
symbol _m87("_m87");
symbol _m88("_m88");
symbol _m89("_m89");
symbol _m90("_m90");
symbol _m91("_m91");
symbol _m92("_m92");
symbol _m93("_m93");
symbol _m94("_m94");
symbol _m95("_m95");
symbol _m96("_m96");
symbol _m97("_m97");
symbol _m98("_m98");
symbol _m99("_m99");
symbol _m100("_m100");
symbol _m101("_m101");
symbol _m102("_m102");
symbol _m103("_m103");
symbol _m104("_m104");
symbol _m105("_m105");
symbol _m106("_m106");
symbol _m107("_m107");
symbol _m108("_m108");
symbol _m109("_m109");
symbol _m110("_m110");
symbol _m111("_m111");
symbol _m112("_m112");
symbol _m113("_m113");
symbol _m114("_m114");
symbol _m115("_m115");
symbol _m116("_m116");
symbol _m117("_m117");
symbol _m118("_m118");
symbol _m119("_m119");
symbol _m120("_m120");
symbol _m121("_m121");
symbol _m122("_m122");
symbol _m123("_m123");
symbol _m124("_m124");
symbol _m125("_m125");
symbol _m126("_m126");
symbol _m127("_m127");
symbol _m128("_m128");
symbol _m129("_m129");
symbol _m130("_m130");
symbol _m131("_m131");
symbol _m132("_m132");
symbol _m133("_m133");
symbol _m134("_m134");
symbol _m135("_m135");
symbol _m136("_m136");
symbol _m137("_m137");
symbol _m138("_m138");
symbol _m139("_m139");
symbol _m140("_m140");
symbol _m141("_m141");
symbol _m142("_m142");
symbol _m143("_m143");
symbol _m144("_m144");
symbol _m145("_m145");
symbol _m146("_m146");
symbol _m147("_m147");
symbol _m148("_m148");
symbol _m149("_m149");
symbol _m150("_m150");
symbol _m151("_m151");
symbol _m152("_m152");
symbol _m153("_m153");
symbol _m154("_m154");
symbol _m155("_m155");
symbol _m156("_m156");
symbol _m157("_m157");
symbol _m158("_m158");
symbol _m159("_m159");
symbol _m160("_m160");
symbol _m161("_m161");
symbol _m162("_m162");
symbol _m163("_m163");
symbol _m164("_m164");
symbol _m165("_m165");
symbol _m166("_m166");
symbol _m167("_m167");
symbol _m168("_m168");
symbol _m169("_m169");
symbol _m170("_m170");
symbol _m171("_m171");
symbol _m172("_m172");
symbol _m173("_m173");
symbol _m174("_m174");
symbol _m175("_m175");
symbol _m176("_m176");
symbol _m177("_m177");
symbol _m178("_m178");
symbol _m179("_m179");
symbol _m180("_m180");
symbol _m181("_m181");
symbol _m182("_m182");
symbol _m183("_m183");
symbol _m184("_m184");
symbol _m185("_m185");
symbol _m186("_m186");
symbol _m187("_m187");
symbol _m188("_m188");
symbol _m189("_m189");
symbol _m190("_m190");
symbol _m191("_m191");
symbol _m192("_m192");
symbol _m193("_m193");
symbol _m194("_m194");
symbol _m195("_m195");
symbol _m196("_m196");
symbol _m197("_m197");
symbol _m198("_m198");
symbol _m199("_m199");
symbol _m200("_m200");
symbol _m201("_m201");
symbol _m202("_m202");
symbol _m203("_m203");
symbol _m204("_m204");
symbol _m205("_m205");
symbol _m206("_m206");
symbol _m207("_m207");
symbol _m208("_m208");
symbol _m209("_m209");
symbol _m210("_m210");
symbol _m211("_m211");
symbol _m212("_m212");
symbol _m213("_m213");
symbol _m214("_m214");
symbol _m215("_m215");
symbol _m216("_m216");
symbol _m217("_m217");
symbol _m218("_m218");
symbol _m219("_m219");
symbol _m220("_m220");
symbol _m221("_m221");
symbol _m222("_m222");
symbol _m223("_m223");
symbol _m224("_m224");
symbol _m225("_m225");
symbol _m226("_m226");
symbol _m227("_m227");
symbol _m228("_m228");
symbol _m229("_m229");
symbol _m230("_m230");
symbol _m231("_m231");
symbol _m232("_m232");
symbol _m233("_m233");
symbol _m234("_m234");
symbol _m235("_m235");
symbol _m236("_m236");
symbol _m237("_m237");
symbol _m238("_m238");
symbol _m239("_m239");
symbol _m240("_m240");
symbol _m241("_m241");
symbol _m242("_m242");
symbol _m243("_m243");
symbol _m244("_m244");
symbol _m245("_m245");
symbol _m246("_m246");
symbol _m247("_m247");
symbol _m248("_m248");
symbol _m249("_m249");
symbol _m250("_m250");
symbol _m251("_m251");
symbol _m252("_m252");
symbol _m253("_m253");


#include "funcdef.hpp"
#include "userfuncsymbol.hpp"



void integrandEval(char *formula)
{
  ex e(formula,lst(x,y,z,_m1,_m2,_m3,_m4,_m5,_m6,_m7,_m8,_m9,_m10,_m11,_m12,_m13,_m14,_m15,_m16,_m17,_m18,_m19,_m20,_m21,_m22,_m23,_m24,_m25,_m26,_m27,_m28,_m29,_m30,_m31,_m32,_m33,_m34,_m35,_m36,_m37,_m38,_m39,_m40,_m41,_m42,_m43,_m44,_m45,_m46,_m47,_m48,_m49,_m50,_m51,_m52,_m53,_m54,_m55,_m56,_m57,_m58,_m59,_m60,_m61,_m62,_m63,_m64,_m65,_m66,_m67,_m68,_m69,_m70,_m71,_m72,_m73,_m74,_m75,_m76,_m77,_m78,_m79,_m80,_m81,_m82,_m83,_m84,_m85,_m86,_m87,_m88,_m89,_m90,_m91,_m92,_m93,_m94,_m95,_m96,_m97,_m98,_m99,_m100,_m101,_m102,_m103,_m104,_m105,_m106,_m107,_m108,_m109,_m110,_m111,_m112,_m113,_m114,_m115,_m116,_m117,_m118,_m119,_m120,_m121,_m122,_m123,_m124,_m125,_m126,_m127,_m128,_m129,_m130,_m131,_m132,_m133,_m134,_m135,_m136,_m137,_m138,_m139,_m140,_m141,_m142,_m143,_m144,_m145,_m146,_m147,_m148,_m149,_m150,_m151,_m152,_m153,_m154,_m155,_m156,_m157,_m158,_m159,_m160,_m161,_m162,_m163,_m164,_m165,_m166,_m167,_m168,_m169,_m170,_m171,_m172,_m173,_m174,_m175,_m176,_m177,_m178,_m179,_m180,_m181,_m182,_m183,_m184,_m185,_m186,_m187,_m188,_m189,_m190,_m191,_m192,_m193,_m194,_m195,_m196,_m197,_m198,_m199,_m200,_m201,_m202,_m203,_m204,_m205,_m206,_m207,_m208,_m209,_m210,_m211,_m212,_m213,_m214,_m215,_m216,_m217,_m218,_m219,_m220,_m221,_m222,_m223,_m224,_m225,_m226,_m227,_m228,_m229,_m230,_m231,_m232,_m233,_m234,_m235,_m236,_m237,_m238,_m239,_m240,_m241,_m242,_m243,_m244,_m245,_m246,_m247,_m248,_m249,_m250,_m251,_m252,_m253));


  char buf[BUFSIZ];
  ostrstream ostr(buf,BUFSIZ);

  //  ostr <<  e.diff(m1);
  //  cout << "buf=[" << buf << "]" << endl;
  //
  //  cout << endl;
  //
  //  ostr << e.diff(m2);
  //  cout << "buf=[" << buf << "]" << endl;  
  
  cerr << "Integrand eval=" << e << endl;

  cerr << "e.diff(_m1)= " << e.diff(_m1) << endl;

  return;
}



void integrandDerivative(char *formula , int n , char *buf, int bufsiz)
{
  
  ex e(formula,lst(x,y,z,_m1,_m2,_m3,_m4,_m5,_m6,_m7,_m8,_m9,_m10,_m11,_m12,_m13,_m14,_m15,_m16,_m17,_m18,_m19,_m20,_m21,_m22,_m23,_m24,_m25,_m26,_m27,_m28,_m29,_m30,_m31,_m32,_m33,_m34,_m35,_m36,_m37,_m38,_m39,_m40,_m41,_m42,_m43,_m44,_m45,_m46,_m47,_m48,_m49,_m50,_m51,_m52,_m53,_m54,_m55,_m56,_m57,_m58,_m59,_m60,_m61,_m62,_m63,_m64,_m65,_m66,_m67,_m68,_m69,_m70,_m71,_m72,_m73,_m74,_m75,_m76,_m77,_m78,_m79,_m80,_m81,_m82,_m83,_m84,_m85,_m86,_m87,_m88,_m89,_m90,_m91,_m92,_m93,_m94,_m95,_m96,_m97,_m98,_m99,_m100,_m101,_m102,_m103,_m104,_m105,_m106,_m107,_m108,_m109,_m110,_m111,_m112,_m113,_m114,_m115,_m116,_m117,_m118,_m119,_m120,_m121,_m122,_m123,_m124,_m125,_m126,_m127,_m128,_m129,_m130,_m131,_m132,_m133,_m134,_m135,_m136,_m137,_m138,_m139,_m140,_m141,_m142,_m143,_m144,_m145,_m146,_m147,_m148,_m149,_m150,_m151,_m152,_m153,_m154,_m155,_m156,_m157,_m158,_m159,_m160,_m161,_m162,_m163,_m164,_m165,_m166,_m167,_m168,_m169,_m170,_m171,_m172,_m173,_m174,_m175,_m176,_m177,_m178,_m179,_m180,_m181,_m182,_m183,_m184,_m185,_m186,_m187,_m188,_m189,_m190,_m191,_m192,_m193,_m194,_m195,_m196,_m197,_m198,_m199,_m200,_m201,_m202,_m203,_m204,_m205,_m206,_m207,_m208,_m209,_m210,_m211,_m212,_m213,_m214,_m215,_m216,_m217,_m218,_m219,_m220,_m221,_m222,_m223,_m224,_m225,_m226,_m227,_m228,_m229,_m230,_m231,_m232,_m233,_m234,_m235,_m236,_m237,_m238,_m239,_m240,_m241,_m242,_m243,_m244,_m245,_m246,_m247,_m248,_m249,_m250,_m251,_m252,_m253));


  switch (n) {
  case 1:
    e = e.diff(_m1);
    break;

  case 2:
    e = e.diff(_m2);
    break;

  case 3:
    e = e.diff(_m3);
    break;

  case 4:
    e = e.diff(_m4);
    break;

  case 5:
    e = e.diff(_m5);
    break;

  case 6:
    e = e.diff(_m6);
    break;

  case 7:
    e = e.diff(_m7);
    break;

  case 8:
    e = e.diff(_m8);
    break;

  case 9:
    e = e.diff(_m9);
    break;

  case 10:
    e = e.diff(_m10);
    break;

  case 11:
    e = e.diff(_m11);
    break;

  case 12:
    e = e.diff(_m12);
    break;

  case 13:
    e = e.diff(_m13);
    break;

  case 14:
    e = e.diff(_m14);
    break;

  case 15:
    e = e.diff(_m15);
    break;

  case 16:
    e = e.diff(_m16);
    break;

  case 17:
    e = e.diff(_m17);
    break;

  case 18:
    e = e.diff(_m18);
    break;

  case 19:
    e = e.diff(_m19);
    break;

  case 20:
    e = e.diff(_m20);
    break;

  case 21:
    e = e.diff(_m21);
    break;

  case 22:
    e = e.diff(_m22);
    break;

  case 23:
    e = e.diff(_m23);
    break;

  case 24:
    e = e.diff(_m24);
    break;

  case 25:
    e = e.diff(_m25);
    break;

  case 26:
    e = e.diff(_m26);
    break;

  case 27:
    e = e.diff(_m27);
    break;

  case 28:
    e = e.diff(_m28);
    break;

  case 29:
    e = e.diff(_m29);
    break;

  case 30:
    e = e.diff(_m30);
    break;

  case 31:
    e = e.diff(_m31);
    break;

  case 32:
    e = e.diff(_m32);
    break;

  case 33:
    e = e.diff(_m33);
    break;

  case 34:
    e = e.diff(_m34);
    break;

  case 35:
    e = e.diff(_m35);
    break;

  case 36:
    e = e.diff(_m36);
    break;

  case 37:
    e = e.diff(_m37);
    break;

  case 38:
    e = e.diff(_m38);
    break;

  case 39:
    e = e.diff(_m39);
    break;

  case 40:
    e = e.diff(_m40);
    break;

  case 41:
    e = e.diff(_m41);
    break;

  case 42:
    e = e.diff(_m42);
    break;

  case 43:
    e = e.diff(_m43);
    break;

  case 44:
    e = e.diff(_m44);
    break;

  case 45:
    e = e.diff(_m45);
    break;

  case 46:
    e = e.diff(_m46);
    break;

  case 47:
    e = e.diff(_m47);
    break;

  case 48:
    e = e.diff(_m48);
    break;

  case 49:
    e = e.diff(_m49);
    break;

  case 50:
    e = e.diff(_m50);
    break;

  case 51:
    e = e.diff(_m51);
    break;

  case 52:
    e = e.diff(_m52);
    break;

  case 53:
    e = e.diff(_m53);
    break;

  case 54:
    e = e.diff(_m54);
    break;

  case 55:
    e = e.diff(_m55);
    break;

  case 56:
    e = e.diff(_m56);
    break;

  case 57:
    e = e.diff(_m57);
    break;

  case 58:
    e = e.diff(_m58);
    break;

  case 59:
    e = e.diff(_m59);
    break;

  case 60:
    e = e.diff(_m60);
    break;

  case 61:
    e = e.diff(_m61);
    break;

  case 62:
    e = e.diff(_m62);
    break;

  case 63:
    e = e.diff(_m63);
    break;

  case 64:
    e = e.diff(_m64);
    break;

  case 65:
    e = e.diff(_m65);
    break;

  case 66:
    e = e.diff(_m66);
    break;

  case 67:
    e = e.diff(_m67);
    break;

  case 68:
    e = e.diff(_m68);
    break;

  case 69:
    e = e.diff(_m69);
    break;

  case 70:
    e = e.diff(_m70);
    break;

  case 71:
    e = e.diff(_m71);
    break;

  case 72:
    e = e.diff(_m72);
    break;

  case 73:
    e = e.diff(_m73);
    break;

  case 74:
    e = e.diff(_m74);
    break;

  case 75:
    e = e.diff(_m75);
    break;

  case 76:
    e = e.diff(_m76);
    break;

  case 77:
    e = e.diff(_m77);
    break;

  case 78:
    e = e.diff(_m78);
    break;

  case 79:
    e = e.diff(_m79);
    break;

  case 80:
    e = e.diff(_m80);
    break;

  case 81:
    e = e.diff(_m81);
    break;

  case 82:
    e = e.diff(_m82);
    break;

  case 83:
    e = e.diff(_m83);
    break;

  case 84:
    e = e.diff(_m84);
    break;

  case 85:
    e = e.diff(_m85);
    break;

  case 86:
    e = e.diff(_m86);
    break;

  case 87:
    e = e.diff(_m87);
    break;

  case 88:
    e = e.diff(_m88);
    break;

  case 89:
    e = e.diff(_m89);
    break;

  case 90:
    e = e.diff(_m90);
    break;

  case 91:
    e = e.diff(_m91);
    break;

  case 92:
    e = e.diff(_m92);
    break;

  case 93:
    e = e.diff(_m93);
    break;

  case 94:
    e = e.diff(_m94);
    break;

  case 95:
    e = e.diff(_m95);
    break;

  case 96:
    e = e.diff(_m96);
    break;

  case 97:
    e = e.diff(_m97);
    break;

  case 98:
    e = e.diff(_m98);
    break;

  case 99:
    e = e.diff(_m99);
    break;

  case 100:
    e = e.diff(_m100);
    break;

  case 101:
    e = e.diff(_m101);
    break;

  case 102:
    e = e.diff(_m102);
    break;

  case 103:
    e = e.diff(_m103);
    break;

  case 104:
    e = e.diff(_m104);
    break;

  case 105:
    e = e.diff(_m105);
    break;

  case 106:
    e = e.diff(_m106);
    break;

  case 107:
    e = e.diff(_m107);
    break;

  case 108:
    e = e.diff(_m108);
    break;

  case 109:
    e = e.diff(_m109);
    break;

  case 110:
    e = e.diff(_m110);
    break;

  case 111:
    e = e.diff(_m111);
    break;

  case 112:
    e = e.diff(_m112);
    break;

  case 113:
    e = e.diff(_m113);
    break;

  case 114:
    e = e.diff(_m114);
    break;

  case 115:
    e = e.diff(_m115);
    break;

  case 116:
    e = e.diff(_m116);
    break;

  case 117:
    e = e.diff(_m117);
    break;

  case 118:
    e = e.diff(_m118);
    break;

  case 119:
    e = e.diff(_m119);
    break;

  case 120:
    e = e.diff(_m120);
    break;

  case 121:
    e = e.diff(_m121);
    break;

  case 122:
    e = e.diff(_m122);
    break;

  case 123:
    e = e.diff(_m123);
    break;

  case 124:
    e = e.diff(_m124);
    break;

  case 125:
    e = e.diff(_m125);
    break;

  case 126:
    e = e.diff(_m126);
    break;

  case 127:
    e = e.diff(_m127);
    break;

  case 128:
    e = e.diff(_m128);
    break;

  case 129:
    e = e.diff(_m129);
    break;

  case 130:
    e = e.diff(_m130);
    break;

  case 131:
    e = e.diff(_m131);
    break;

  case 132:
    e = e.diff(_m132);
    break;

  case 133:
    e = e.diff(_m133);
    break;

  case 134:
    e = e.diff(_m134);
    break;

  case 135:
    e = e.diff(_m135);
    break;

  case 136:
    e = e.diff(_m136);
    break;

  case 137:
    e = e.diff(_m137);
    break;

  case 138:
    e = e.diff(_m138);
    break;

  case 139:
    e = e.diff(_m139);
    break;

  case 140:
    e = e.diff(_m140);
    break;

  case 141:
    e = e.diff(_m141);
    break;

  case 142:
    e = e.diff(_m142);
    break;

  case 143:
    e = e.diff(_m143);
    break;

  case 144:
    e = e.diff(_m144);
    break;

  case 145:
    e = e.diff(_m145);
    break;

  case 146:
    e = e.diff(_m146);
    break;

  case 147:
    e = e.diff(_m147);
    break;

  case 148:
    e = e.diff(_m148);
    break;

  case 149:
    e = e.diff(_m149);
    break;

  case 150:
    e = e.diff(_m150);
    break;

  case 151:
    e = e.diff(_m151);
    break;

  case 152:
    e = e.diff(_m152);
    break;

  case 153:
    e = e.diff(_m153);
    break;

  case 154:
    e = e.diff(_m154);
    break;

  case 155:
    e = e.diff(_m155);
    break;

  case 156:
    e = e.diff(_m156);
    break;

  case 157:
    e = e.diff(_m157);
    break;

  case 158:
    e = e.diff(_m158);
    break;

  case 159:
    e = e.diff(_m159);
    break;

  case 160:
    e = e.diff(_m160);
    break;

  case 161:
    e = e.diff(_m161);
    break;

  case 162:
    e = e.diff(_m162);
    break;

  case 163:
    e = e.diff(_m163);
    break;

  case 164:
    e = e.diff(_m164);
    break;

  case 165:
    e = e.diff(_m165);
    break;

  case 166:
    e = e.diff(_m166);
    break;

  case 167:
    e = e.diff(_m167);
    break;

  case 168:
    e = e.diff(_m168);
    break;

  case 169:
    e = e.diff(_m169);
    break;

  case 170:
    e = e.diff(_m170);
    break;

  case 171:
    e = e.diff(_m171);
    break;

  case 172:
    e = e.diff(_m172);
    break;

  case 173:
    e = e.diff(_m173);
    break;

  case 174:
    e = e.diff(_m174);
    break;

  case 175:
    e = e.diff(_m175);
    break;

  case 176:
    e = e.diff(_m176);
    break;

  case 177:
    e = e.diff(_m177);
    break;

  case 178:
    e = e.diff(_m178);
    break;

  case 179:
    e = e.diff(_m179);
    break;

  case 180:
    e = e.diff(_m180);
    break;

  case 181:
    e = e.diff(_m181);
    break;

  case 182:
    e = e.diff(_m182);
    break;

  case 183:
    e = e.diff(_m183);
    break;

  case 184:
    e = e.diff(_m184);
    break;

  case 185:
    e = e.diff(_m185);
    break;

  case 186:
    e = e.diff(_m186);
    break;

  case 187:
    e = e.diff(_m187);
    break;

  case 188:
    e = e.diff(_m188);
    break;

  case 189:
    e = e.diff(_m189);
    break;

  case 190:
    e = e.diff(_m190);
    break;

  case 191:
    e = e.diff(_m191);
    break;

  case 192:
    e = e.diff(_m192);
    break;

  case 193:
    e = e.diff(_m193);
    break;

  case 194:
    e = e.diff(_m194);
    break;

  case 195:
    e = e.diff(_m195);
    break;

  case 196:
    e = e.diff(_m196);
    break;

  case 197:
    e = e.diff(_m197);
    break;

  case 198:
    e = e.diff(_m198);
    break;

  case 199:
    e = e.diff(_m199);
    break;

  case 200:
    e = e.diff(_m200);
    break;

  case 201:
    e = e.diff(_m201);
    break;

  case 202:
    e = e.diff(_m202);
    break;

  case 203:
    e = e.diff(_m203);
    break;

  case 204:
    e = e.diff(_m204);
    break;

  case 205:
    e = e.diff(_m205);
    break;

  case 206:
    e = e.diff(_m206);
    break;

  case 207:
    e = e.diff(_m207);
    break;

  case 208:
    e = e.diff(_m208);
    break;

  case 209:
    e = e.diff(_m209);
    break;

  case 210:
    e = e.diff(_m210);
    break;

  case 211:
    e = e.diff(_m211);
    break;

  case 212:
    e = e.diff(_m212);
    break;

  case 213:
    e = e.diff(_m213);
    break;

  case 214:
    e = e.diff(_m214);
    break;

  case 215:
    e = e.diff(_m215);
    break;

  case 216:
    e = e.diff(_m216);
    break;

  case 217:
    e = e.diff(_m217);
    break;

  case 218:
    e = e.diff(_m218);
    break;

  case 219:
    e = e.diff(_m219);
    break;

  case 220:
    e = e.diff(_m220);
    break;

  case 221:
    e = e.diff(_m221);
    break;

  case 222:
    e = e.diff(_m222);
    break;

  case 223:
    e = e.diff(_m223);
    break;

  case 224:
    e = e.diff(_m224);
    break;

  case 225:
    e = e.diff(_m225);
    break;

  case 226:
    e = e.diff(_m226);
    break;

  case 227:
    e = e.diff(_m227);
    break;

  case 228:
    e = e.diff(_m228);
    break;

  case 229:
    e = e.diff(_m229);
    break;

  case 230:
    e = e.diff(_m230);
    break;

  case 231:
    e = e.diff(_m231);
    break;

  case 232:
    e = e.diff(_m232);
    break;

  case 233:
    e = e.diff(_m233);
    break;

  case 234:
    e = e.diff(_m234);
    break;

  case 235:
    e = e.diff(_m235);
    break;

  case 236:
    e = e.diff(_m236);
    break;

  case 237:
    e = e.diff(_m237);
    break;

  case 238:
    e = e.diff(_m238);
    break;

  case 239:
    e = e.diff(_m239);
    break;

  case 240:
    e = e.diff(_m240);
    break;

  case 241:
    e = e.diff(_m241);
    break;

  case 242:
    e = e.diff(_m242);
    break;

  case 243:
    e = e.diff(_m243);
    break;

  case 244:
    e = e.diff(_m244);
    break;

  case 245:
    e = e.diff(_m245);
    break;

  case 246:
    e = e.diff(_m246);
    break;

  case 247:
    e = e.diff(_m247);
    break;

  case 248:
    e = e.diff(_m248);
    break;

  case 249:
    e = e.diff(_m249);
    break;

  case 250:
    e = e.diff(_m250);
    break;

  case 251:
    e = e.diff(_m251);
    break;

  case 252:
    e = e.diff(_m252);
    break;

  case 253:
    e = e.diff(_m253);
    break;
  }

  //  ostrstream ostr(buf,BUFSIZ);
  ostrstream ostr(buf,bufsiz);

  *buf = '\0';
  ostr << e << '\0';

  int stringLength(const char *);
  assert(stringLength(buf)+1 < bufsiz);
  
  void funcSymbolConvert_ginac(char *);
  funcSymbolConvert_ginac( buf );         // _n1(x,y,z) -> _n1 etc.

  return;
}

void GetRightHandSide( char *formula, int totalDOF, int *coeffSblNoVec,
		       char *buf,     int bufsiz                         )
{
  ex e(formula,lst(x,y,z,_m1,_m2,_m3,_m4,_m5,_m6,_m7,_m8,_m9,_m10,_m11,_m12,_m13,_m14,_m15,_m16,_m17,_m18,_m19,_m20,_m21,_m22,_m23,_m24,_m25,_m26,_m27,_m28,_m29,_m30,_m31,_m32,_m33,_m34,_m35,_m36,_m37,_m38,_m39,_m40,_m41,_m42,_m43,_m44,_m45,_m46,_m47,_m48,_m49,_m50,_m51,_m52,_m53,_m54,_m55,_m56,_m57,_m58,_m59,_m60,_m61,_m62,_m63,_m64,_m65,_m66,_m67,_m68,_m69,_m70,_m71,_m72,_m73,_m74,_m75,_m76,_m77,_m78,_m79,_m80,_m81,_m82,_m83,_m84,_m85,_m86,_m87,_m88,_m89,_m90,_m91,_m92,_m93,_m94,_m95,_m96,_m97,_m98,_m99,_m100,_m101,_m102,_m103,_m104,_m105,_m106,_m107,_m108,_m109,_m110,_m111,_m112,_m113,_m114,_m115,_m116,_m117,_m118,_m119,_m120,_m121,_m122,_m123,_m124,_m125,_m126,_m127,_m128,_m129,_m130,_m131,_m132,_m133,_m134,_m135,_m136,_m137,_m138,_m139,_m140,_m141,_m142,_m143,_m144,_m145,_m146,_m147,_m148,_m149,_m150,_m151,_m152,_m153,_m154,_m155,_m156,_m157,_m158,_m159,_m160,_m161,_m162,_m163,_m164,_m165,_m166,_m167,_m168,_m169,_m170,_m171,_m172,_m173,_m174,_m175,_m176,_m177,_m178,_m179,_m180,_m181,_m182,_m183,_m184,_m185,_m186,_m187,_m188,_m189,_m190,_m191,_m192,_m193,_m194,_m195,_m196,_m197,_m198,_m199,_m200,_m201,_m202,_m203,_m204,_m205,_m206,_m207,_m208,_m209,_m210,_m211,_m212,_m213,_m214,_m215,_m216,_m217,_m218,_m219,_m220,_m221,_m222,_m223,_m224,_m225,_m226,_m227,_m228,_m229,_m230,_m231,_m232,_m233,_m234,_m235,_m236,_m237,_m238,_m239,_m240,_m241,_m242,_m243,_m244,_m245,_m246,_m247,_m248,_m249,_m250,_m251,_m252,_m253));

  for(int i=0;i<totalDOF;i++) {
    
    switch(coeffSblNoVec[i]) {
    case 1:
    e = e.subs(_m1 == 0);
    break;

  case 2:
    e = e.subs(_m2 == 0);
    break;

  case 3:
    e = e.subs(_m3 == 0);
    break;

  case 4:
    e = e.subs(_m4 == 0);
    break;

  case 5:
    e = e.subs(_m5 == 0);
    break;

  case 6:
    e = e.subs(_m6 == 0);
    break;

  case 7:
    e = e.subs(_m7 == 0);
    break;

  case 8:
    e = e.subs(_m8 == 0);
    break;

  case 9:
    e = e.subs(_m9 == 0);
    break;

  case 10:
    e = e.subs(_m10 == 0);
    break;

  case 11:
    e = e.subs(_m11 == 0);
    break;

  case 12:
    e = e.subs(_m12 == 0);
    break;

  case 13:
    e = e.subs(_m13 == 0);
    break;

  case 14:
    e = e.subs(_m14 == 0);
    break;

  case 15:
    e = e.subs(_m15 == 0);
    break;

  case 16:
    e = e.subs(_m16 == 0);
    break;

  case 17:
    e = e.subs(_m17 == 0);
    break;

  case 18:
    e = e.subs(_m18 == 0);
    break;

  case 19:
    e = e.subs(_m19 == 0);
    break;

  case 20:
    e = e.subs(_m20 == 0);
    break;

  case 21:
    e = e.subs(_m21 == 0);
    break;

  case 22:
    e = e.subs(_m22 == 0);
    break;

  case 23:
    e = e.subs(_m23 == 0);
    break;

  case 24:
    e = e.subs(_m24 == 0);
    break;

  case 25:
    e = e.subs(_m25 == 0);
    break;

  case 26:
    e = e.subs(_m26 == 0);
    break;

  case 27:
    e = e.subs(_m27 == 0);
    break;

  case 28:
    e = e.subs(_m28 == 0);
    break;

  case 29:
    e = e.subs(_m29 == 0);
    break;

  case 30:
    e = e.subs(_m30 == 0);
    break;

  case 31:
    e = e.subs(_m31 == 0);
    break;

  case 32:
    e = e.subs(_m32 == 0);
    break;

  case 33:
    e = e.subs(_m33 == 0);
    break;

  case 34:
    e = e.subs(_m34 == 0);
    break;

  case 35:
    e = e.subs(_m35 == 0);
    break;

  case 36:
    e = e.subs(_m36 == 0);
    break;

  case 37:
    e = e.subs(_m37 == 0);
    break;

  case 38:
    e = e.subs(_m38 == 0);
    break;

  case 39:
    e = e.subs(_m39 == 0);
    break;

  case 40:
    e = e.subs(_m40 == 0);
    break;

  case 41:
    e = e.subs(_m41 == 0);
    break;

  case 42:
    e = e.subs(_m42 == 0);
    break;

  case 43:
    e = e.subs(_m43 == 0);
    break;

  case 44:
    e = e.subs(_m44 == 0);
    break;

  case 45:
    e = e.subs(_m45 == 0);
    break;

  case 46:
    e = e.subs(_m46 == 0);
    break;

  case 47:
    e = e.subs(_m47 == 0);
    break;

  case 48:
    e = e.subs(_m48 == 0);
    break;

  case 49:
    e = e.subs(_m49 == 0);
    break;

  case 50:
    e = e.subs(_m50 == 0);
    break;

  case 51:
    e = e.subs(_m51 == 0);
    break;

  case 52:
    e = e.subs(_m52 == 0);
    break;

  case 53:
    e = e.subs(_m53 == 0);
    break;

  case 54:
    e = e.subs(_m54 == 0);
    break;

  case 55:
    e = e.subs(_m55 == 0);
    break;

  case 56:
    e = e.subs(_m56 == 0);
    break;

  case 57:
    e = e.subs(_m57 == 0);
    break;

  case 58:
    e = e.subs(_m58 == 0);
    break;

  case 59:
    e = e.subs(_m59 == 0);
    break;

  case 60:
    e = e.subs(_m60 == 0);
    break;

  case 61:
    e = e.subs(_m61 == 0);
    break;

  case 62:
    e = e.subs(_m62 == 0);
    break;

  case 63:
    e = e.subs(_m63 == 0);
    break;

  case 64:
    e = e.subs(_m64 == 0);
    break;

  case 65:
    e = e.subs(_m65 == 0);
    break;

  case 66:
    e = e.subs(_m66 == 0);
    break;

  case 67:
    e = e.subs(_m67 == 0);
    break;

  case 68:
    e = e.subs(_m68 == 0);
    break;

  case 69:
    e = e.subs(_m69 == 0);
    break;

  case 70:
    e = e.subs(_m70 == 0);
    break;

  case 71:
    e = e.subs(_m71 == 0);
    break;

  case 72:
    e = e.subs(_m72 == 0);
    break;

  case 73:
    e = e.subs(_m73 == 0);
    break;

  case 74:
    e = e.subs(_m74 == 0);
    break;

  case 75:
    e = e.subs(_m75 == 0);
    break;

  case 76:
    e = e.subs(_m76 == 0);
    break;

  case 77:
    e = e.subs(_m77 == 0);
    break;

  case 78:
    e = e.subs(_m78 == 0);
    break;

  case 79:
    e = e.subs(_m79 == 0);
    break;

  case 80:
    e = e.subs(_m80 == 0);
    break;

  case 81:
    e = e.subs(_m81 == 0);
    break;

  case 82:
    e = e.subs(_m82 == 0);
    break;

  case 83:
    e = e.subs(_m83 == 0);
    break;

  case 84:
    e = e.subs(_m84 == 0);
    break;

  case 85:
    e = e.subs(_m85 == 0);
    break;

  case 86:
    e = e.subs(_m86 == 0);
    break;

  case 87:
    e = e.subs(_m87 == 0);
    break;

  case 88:
    e = e.subs(_m88 == 0);
    break;

  case 89:
    e = e.subs(_m89 == 0);
    break;

  case 90:
    e = e.subs(_m90 == 0);
    break;

  case 91:
    e = e.subs(_m91 == 0);
    break;

  case 92:
    e = e.subs(_m92 == 0);
    break;

  case 93:
    e = e.subs(_m93 == 0);
    break;

  case 94:
    e = e.subs(_m94 == 0);
    break;

  case 95:
    e = e.subs(_m95 == 0);
    break;

  case 96:
    e = e.subs(_m96 == 0);
    break;

  case 97:
    e = e.subs(_m97 == 0);
    break;

  case 98:
    e = e.subs(_m98 == 0);
    break;

  case 99:
    e = e.subs(_m99 == 0);
    break;

  case 100:
    e = e.subs(_m100 == 0);
    break;

  case 101:
    e = e.subs(_m101 == 0);
    break;

  case 102:
    e = e.subs(_m102 == 0);
    break;

  case 103:
    e = e.subs(_m103 == 0);
    break;

  case 104:
    e = e.subs(_m104 == 0);
    break;

  case 105:
    e = e.subs(_m105 == 0);
    break;

  case 106:
    e = e.subs(_m106 == 0);
    break;

  case 107:
    e = e.subs(_m107 == 0);
    break;

  case 108:
    e = e.subs(_m108 == 0);
    break;

  case 109:
    e = e.subs(_m109 == 0);
    break;

  case 110:
    e = e.subs(_m110 == 0);
    break;

  case 111:
    e = e.subs(_m111 == 0);
    break;

  case 112:
    e = e.subs(_m112 == 0);
    break;

  case 113:
    e = e.subs(_m113 == 0);
    break;

  case 114:
    e = e.subs(_m114 == 0);
    break;

  case 115:
    e = e.subs(_m115 == 0);
    break;

  case 116:
    e = e.subs(_m116 == 0);
    break;

  case 117:
    e = e.subs(_m117 == 0);
    break;

  case 118:
    e = e.subs(_m118 == 0);
    break;

  case 119:
    e = e.subs(_m119 == 0);
    break;

  case 120:
    e = e.subs(_m120 == 0);
    break;

  case 121:
    e = e.subs(_m121 == 0);
    break;

  case 122:
    e = e.subs(_m122 == 0);
    break;

  case 123:
    e = e.subs(_m123 == 0);
    break;

  case 124:
    e = e.subs(_m124 == 0);
    break;

  case 125:
    e = e.subs(_m125 == 0);
    break;

  case 126:
    e = e.subs(_m126 == 0);
    break;

  case 127:
    e = e.subs(_m127 == 0);
    break;

  case 128:
    e = e.subs(_m128 == 0);
    break;

  case 129:
    e = e.subs(_m129 == 0);
    break;

  case 130:
    e = e.subs(_m130 == 0);
    break;

  case 131:
    e = e.subs(_m131 == 0);
    break;

  case 132:
    e = e.subs(_m132 == 0);
    break;

  case 133:
    e = e.subs(_m133 == 0);
    break;

  case 134:
    e = e.subs(_m134 == 0);
    break;

  case 135:
    e = e.subs(_m135 == 0);
    break;

  case 136:
    e = e.subs(_m136 == 0);
    break;

  case 137:
    e = e.subs(_m137 == 0);
    break;

  case 138:
    e = e.subs(_m138 == 0);
    break;

  case 139:
    e = e.subs(_m139 == 0);
    break;

  case 140:
    e = e.subs(_m140 == 0);
    break;

  case 141:
    e = e.subs(_m141 == 0);
    break;

  case 142:
    e = e.subs(_m142 == 0);
    break;

  case 143:
    e = e.subs(_m143 == 0);
    break;

  case 144:
    e = e.subs(_m144 == 0);
    break;

  case 145:
    e = e.subs(_m145 == 0);
    break;

  case 146:
    e = e.subs(_m146 == 0);
    break;

  case 147:
    e = e.subs(_m147 == 0);
    break;

  case 148:
    e = e.subs(_m148 == 0);
    break;

  case 149:
    e = e.subs(_m149 == 0);
    break;

  case 150:
    e = e.subs(_m150 == 0);
    break;

  case 151:
    e = e.subs(_m151 == 0);
    break;

  case 152:
    e = e.subs(_m152 == 0);
    break;

  case 153:
    e = e.subs(_m153 == 0);
    break;

  case 154:
    e = e.subs(_m154 == 0);
    break;

  case 155:
    e = e.subs(_m155 == 0);
    break;

  case 156:
    e = e.subs(_m156 == 0);
    break;

  case 157:
    e = e.subs(_m157 == 0);
    break;

  case 158:
    e = e.subs(_m158 == 0);
    break;

  case 159:
    e = e.subs(_m159 == 0);
    break;

  case 160:
    e = e.subs(_m160 == 0);
    break;

  case 161:
    e = e.subs(_m161 == 0);
    break;

  case 162:
    e = e.subs(_m162 == 0);
    break;

  case 163:
    e = e.subs(_m163 == 0);
    break;

  case 164:
    e = e.subs(_m164 == 0);
    break;

  case 165:
    e = e.subs(_m165 == 0);
    break;

  case 166:
    e = e.subs(_m166 == 0);
    break;

  case 167:
    e = e.subs(_m167 == 0);
    break;

  case 168:
    e = e.subs(_m168 == 0);
    break;

  case 169:
    e = e.subs(_m169 == 0);
    break;

  case 170:
    e = e.subs(_m170 == 0);
    break;

  case 171:
    e = e.subs(_m171 == 0);
    break;

  case 172:
    e = e.subs(_m172 == 0);
    break;

  case 173:
    e = e.subs(_m173 == 0);
    break;

  case 174:
    e = e.subs(_m174 == 0);
    break;

  case 175:
    e = e.subs(_m175 == 0);
    break;

  case 176:
    e = e.subs(_m176 == 0);
    break;

  case 177:
    e = e.subs(_m177 == 0);
    break;

  case 178:
    e = e.subs(_m178 == 0);
    break;

  case 179:
    e = e.subs(_m179 == 0);
    break;

  case 180:
    e = e.subs(_m180 == 0);
    break;

  case 181:
    e = e.subs(_m181 == 0);
    break;

  case 182:
    e = e.subs(_m182 == 0);
    break;

  case 183:
    e = e.subs(_m183 == 0);
    break;

  case 184:
    e = e.subs(_m184 == 0);
    break;

  case 185:
    e = e.subs(_m185 == 0);
    break;

  case 186:
    e = e.subs(_m186 == 0);
    break;

  case 187:
    e = e.subs(_m187 == 0);
    break;

  case 188:
    e = e.subs(_m188 == 0);
    break;

  case 189:
    e = e.subs(_m189 == 0);
    break;

  case 190:
    e = e.subs(_m190 == 0);
    break;

  case 191:
    e = e.subs(_m191 == 0);
    break;

  case 192:
    e = e.subs(_m192 == 0);
    break;

  case 193:
    e = e.subs(_m193 == 0);
    break;

  case 194:
    e = e.subs(_m194 == 0);
    break;

  case 195:
    e = e.subs(_m195 == 0);
    break;

  case 196:
    e = e.subs(_m196 == 0);
    break;

  case 197:
    e = e.subs(_m197 == 0);
    break;

  case 198:
    e = e.subs(_m198 == 0);
    break;

  case 199:
    e = e.subs(_m199 == 0);
    break;

  case 200:
    e = e.subs(_m200 == 0);
    break;

  case 201:
    e = e.subs(_m201 == 0);
    break;

  case 202:
    e = e.subs(_m202 == 0);
    break;

  case 203:
    e = e.subs(_m203 == 0);
    break;

  case 204:
    e = e.subs(_m204 == 0);
    break;

  case 205:
    e = e.subs(_m205 == 0);
    break;

  case 206:
    e = e.subs(_m206 == 0);
    break;

  case 207:
    e = e.subs(_m207 == 0);
    break;

  case 208:
    e = e.subs(_m208 == 0);
    break;

  case 209:
    e = e.subs(_m209 == 0);
    break;

  case 210:
    e = e.subs(_m210 == 0);
    break;

  case 211:
    e = e.subs(_m211 == 0);
    break;

  case 212:
    e = e.subs(_m212 == 0);
    break;

  case 213:
    e = e.subs(_m213 == 0);
    break;

  case 214:
    e = e.subs(_m214 == 0);
    break;

  case 215:
    e = e.subs(_m215 == 0);
    break;

  case 216:
    e = e.subs(_m216 == 0);
    break;

  case 217:
    e = e.subs(_m217 == 0);
    break;

  case 218:
    e = e.subs(_m218 == 0);
    break;

  case 219:
    e = e.subs(_m219 == 0);
    break;

  case 220:
    e = e.subs(_m220 == 0);
    break;

  case 221:
    e = e.subs(_m221 == 0);
    break;

  case 222:
    e = e.subs(_m222 == 0);
    break;

  case 223:
    e = e.subs(_m223 == 0);
    break;

  case 224:
    e = e.subs(_m224 == 0);
    break;

  case 225:
    e = e.subs(_m225 == 0);
    break;

  case 226:
    e = e.subs(_m226 == 0);
    break;

  case 227:
    e = e.subs(_m227 == 0);
    break;

  case 228:
    e = e.subs(_m228 == 0);
    break;

  case 229:
    e = e.subs(_m229 == 0);
    break;

  case 230:
    e = e.subs(_m230 == 0);
    break;

  case 231:
    e = e.subs(_m231 == 0);
    break;

  case 232:
    e = e.subs(_m232 == 0);
    break;

  case 233:
    e = e.subs(_m233 == 0);
    break;

  case 234:
    e = e.subs(_m234 == 0);
    break;

  case 235:
    e = e.subs(_m235 == 0);
    break;

  case 236:
    e = e.subs(_m236 == 0);
    break;

  case 237:
    e = e.subs(_m237 == 0);
    break;

  case 238:
    e = e.subs(_m238 == 0);
    break;

  case 239:
    e = e.subs(_m239 == 0);
    break;

  case 240:
    e = e.subs(_m240 == 0);
    break;

  case 241:
    e = e.subs(_m241 == 0);
    break;

  case 242:
    e = e.subs(_m242 == 0);
    break;

  case 243:
    e = e.subs(_m243 == 0);
    break;

  case 244:
    e = e.subs(_m244 == 0);
    break;

  case 245:
    e = e.subs(_m245 == 0);
    break;

  case 246:
    e = e.subs(_m246 == 0);
    break;

  case 247:
    e = e.subs(_m247 == 0);
    break;

  case 248:
    e = e.subs(_m248 == 0);
    break;

  case 249:
    e = e.subs(_m249 == 0);
    break;

  case 250:
    e = e.subs(_m250 == 0);
    break;

  case 251:
    e = e.subs(_m251 == 0);
    break;

  case 252:
    e = e.subs(_m252 == 0);
    break;

  case 253:
    e = e.subs(_m253 == 0);
    break;

    default:

      cerr << "switch = " << coeffSblNoVec[i];
      assert(1==0);
    }
  }

  ostrstream ostr(buf,bufsiz);
  *buf = '\0';
  e = -1.0 * e;
  ostr << e << '\0';                            // minus ! 020306

  //  cerr << "RHS  = " << buf << endl;
  void funcSymbolConvert_ginac(char *);
  funcSymbolConvert_ginac( buf );         // _n1(x,y,z) -> _n1 etc.

  return;
}

void esetDerivative(char *formula , int type , char *buf, int bufsiz)
{
  ex e(formula,lst(x,y,z,_m1,_m2,_m3,_m4,_m5,_m6,_m7,_m8,_m9,_m10,_m11,_m12,_m13,_m14,_m15,_m16,_m17,_m18,_m19,_m20,_m21,_m22,_m23,_m24,_m25,_m26,_m27,_m28,_m29,_m30,_m31,_m32,_m33,_m34,_m35,_m36,_m37,_m38,_m39,_m40,_m41,_m42,_m43,_m44,_m45,_m46,_m47,_m48,_m49,_m50,_m51,_m52,_m53,_m54,_m55,_m56,_m57,_m58,_m59,_m60,_m61,_m62,_m63,_m64,_m65,_m66,_m67,_m68,_m69,_m70,_m71,_m72,_m73,_m74,_m75,_m76,_m77,_m78,_m79,_m80,_m81,_m82,_m83,_m84,_m85,_m86,_m87,_m88,_m89,_m90,_m91,_m92,_m93,_m94,_m95,_m96,_m97,_m98,_m99,_m100,_m101,_m102,_m103,_m104,_m105,_m106,_m107,_m108,_m109,_m110,_m111,_m112,_m113,_m114,_m115,_m116,_m117,_m118,_m119,_m120,_m121,_m122,_m123,_m124,_m125,_m126,_m127,_m128,_m129,_m130,_m131,_m132,_m133,_m134,_m135,_m136,_m137,_m138,_m139,_m140,_m141,_m142,_m143,_m144,_m145,_m146,_m147,_m148,_m149,_m150,_m151,_m152,_m153,_m154,_m155,_m156,_m157,_m158,_m159,_m160,_m161,_m162,_m163,_m164,_m165,_m166,_m167,_m168,_m169,_m170,_m171,_m172,_m173,_m174,_m175,_m176,_m177,_m178,_m179,_m180,_m181,_m182,_m183,_m184,_m185,_m186,_m187,_m188,_m189,_m190,_m191,_m192,_m193,_m194,_m195,_m196,_m197,_m198,_m199,_m200,_m201,_m202,_m203,_m204,_m205,_m206,_m207,_m208,_m209,_m210,_m211,_m212,_m213,_m214,_m215,_m216,_m217,_m218,_m219,_m220,_m221,_m222,_m223,_m224,_m225,_m226,_m227,_m228,_m229,_m230,_m231,_m232,_m233,_m234,_m235,_m236,_m237,_m238,_m239,_m240,_m241,_m242,_m243,_m244,_m245,_m246,_m247,_m248,_m249,_m250,_m251,_m252,_m253));


  switch (type) {
  case TYPE_DIFF_X:
    e = e.diff(_m1);
    break;

  case TYPE_DIFF_Y:
    e = e.diff(_m2);
    break;

  case TYPE_DIFF_Z:
    e = e.diff(_m3);
    break;

  default:
    assert(1==0);
  }

  
  ostrstream ostr(buf,bufsiz);

  *buf = '\0';
  ostr << e << '\0';

  return;
}


void ewiseQuadEval(char *formula,char *buf,int bufsiz)
{
  ex e(formula,lst(x,y,z,_m1,_m2,_m3,_m4,_m5,_m6,_m7,_m8,_m9,_m10,_m11,_m12,_m13,_m14,_m15,_m16,_m17,_m18,_m19,_m20,_m21,_m22,_m23,_m24,_m25,_m26,_m27,_m28,_m29,_m30,_m31,_m32,_m33,_m34,_m35,_m36,_m37,_m38,_m39,_m40,_m41,_m42,_m43,_m44,_m45,_m46,_m47,_m48,_m49,_m50,_m51,_m52,_m53,_m54,_m55,_m56,_m57,_m58,_m59,_m60,_m61,_m62,_m63,_m64,_m65,_m66,_m67,_m68,_m69,_m70,_m71,_m72,_m73,_m74,_m75,_m76,_m77,_m78,_m79,_m80,_m81,_m82,_m83,_m84,_m85,_m86,_m87,_m88,_m89,_m90,_m91,_m92,_m93,_m94,_m95,_m96,_m97,_m98,_m99,_m100,_m101,_m102,_m103,_m104,_m105,_m106,_m107,_m108,_m109,_m110,_m111,_m112,_m113,_m114,_m115,_m116,_m117,_m118,_m119,_m120,_m121,_m122,_m123,_m124,_m125,_m126,_m127,_m128,_m129,_m130,_m131,_m132,_m133,_m134,_m135,_m136,_m137,_m138,_m139,_m140,_m141,_m142,_m143,_m144,_m145,_m146,_m147,_m148,_m149,_m150,_m151,_m152,_m153,_m154,_m155,_m156,_m157,_m158,_m159,_m160,_m161,_m162,_m163,_m164,_m165,_m166,_m167,_m168,_m169,_m170,_m171,_m172,_m173,_m174,_m175,_m176,_m177,_m178,_m179,_m180,_m181,_m182,_m183,_m184,_m185,_m186,_m187,_m188,_m189,_m190,_m191,_m192,_m193,_m194,_m195,_m196,_m197,_m198,_m199,_m200,_m201,_m202,_m203,_m204,_m205,_m206,_m207,_m208,_m209,_m210,_m211,_m212,_m213,_m214,_m215,_m216,_m217,_m218,_m219,_m220,_m221,_m222,_m223,_m224,_m225,_m226,_m227,_m228,_m229,_m230,_m231,_m232,_m233,_m234,_m235,_m236,_m237,_m238,_m239,_m240,_m241,_m242,_m243,_m244,_m245,_m246,_m247,_m248,_m249,_m250,_m251,_m252,_m253));


  ostrstream ostr(buf,bufsiz);
  *buf = '\0';
  ostr << e << '\0';

  void funcSymbolConvert_ginac(char *);
  funcSymbolConvert_ginac( buf );         // _n1(x,y,z) -> _n1 etc.

  return;
}
