/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   modulef_def.h
 *      Date:   1998/11/02
 *   
 *   Purpose:   Definitions for Modulef
 *              
 */

/* Parameters */
#define MF_DEFAULT_IMPRE  -1

#define MF_MAX_FILES    256

/* Installation dependent path names, etc. */
#define MF_LIBRALY_DIRECTORY  "/home/fujio/modulef/linux/sta/lib"



/* File names */

/* Modulef data file name */
#define MF_FNAME_FEELMAIL   "solve%d.MAIL"
#define MF_FNAME_FEELCOOR   "solve%d.COOR"
#define MF_FNAME_FEELTAE    "solve%d.TAE"
#define MF_FNAME_FEELMUA    "solve%d.MUA"


/* FCODE=2  solve routine*/
/* FCODE=1  first file   */
/* FCODE=0  library file */
#define MF_FNAME_FEELMF    "feelmf.f"
#define MF_FCODE_FEELMF    1

#define MF_FNAME_FEELMAIN  "feelmain.f"
#define MF_FCODE_FEELMAIN  1

#define MF_FNAME_PNRAID    "pnraid.f"
#define MF_FCODE_PNRAID    1

#define MF_FNAME_DOBPER    "dobper.f"
#define MF_FCODE_DOBPER    1


#define MF_FNAME_SOLVE     "solve%d.f"
#define MF_NOM77_SOLVE     "solve%d"
#define MF_FCODE_SOLVE     1

#define MF_FNAME_SOLVE_MACO  "solve%dmaco.f"
#define MF_NOM77_SOLVE_MACO  "solve%dmaco"
#define MF_FCODE_SOLVE_MACO  1

#define MF_FNAME_SOLVE_MILI  "solve%dmili.f"
#define MF_NOM77_SOLVE_MILI  "solve%dmili"
#define MF_FCODE_SOLVE_MILI  1

#define MF_FNAME_ELEM_PR     "prs%s.f"
#define MF_NOM77_ELEM_PR     "prs%s"
#define MF_FCODE_ELEM_PR     1



#define MF_FNAME_SOLVE_TAE  "solve%dtae.f"
#define MF_NOM77_SOLVE_TAE  "solve%dtae"
#define MF_FCODE_SOLVE_TAE  1

/* Library modules */
#define MF_FNAME_FEELNOPO  "feelnopo.f"
#define MF_FCODE_FEELNOPO  0

#define MF_FNAME_ALLOCFEMV "allocfemv.f"
#define MF_FCODE_ALLOCFEMV 0



/* MODULEF LIBRARY NAME */
#define MF_FNAME_RAID    "pd%s.f"
#define MF_NOM77_RAID    "pd"
#define MF_FCODE_RAID    1

#define MF_FNAME_MILIEU  "milieu%d.f"
#define MF_NOM77_MILIEU  "MILIEU%d"
#define MF_FCODE_MILIEU  1


/* Function declarations */

FILE *mfFileWriteOpen();
char *zerozeronum();





