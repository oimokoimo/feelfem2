/*
 *
 * prototype for avs routines
 *
 *
 *
 */

void put_nth_avs_feel_declare_fp(FILE *,int);
void put_nth_avs_real_name_fp(FILE *,int);
void put_nth_avs_initial_val_fp(FILE *,int);

int how_many_avsoutputs();
void listup_avsoutput_in_sub_fp(FILE *);
void listup_avsoutput_declare_fp(FILE *);
int get_nth_avsoutput_parameters(int);
char *get_ijth_avsoutput_femname(int i,int j);
int get_final_nodes();
int how_many_avsnetworks();
