int kontrola_hodnoty(int degree);

long double** vytvor_matici(int degree);

long double** vytvor_jednotkovou_matici(int degree);

void vypln_matici(long double**matrix, int degree);

void vypis_matici(long double**matrix, int degree);

void vydel_radek_cislem_z_nej(long double**matrix, int degree, int row, int col);

void vydel_radek_cislem(long double**matrix, int degree, int row, int num);

void odecti_nasob_radek_od_radku(long double**matrix,int degree,int row1, int row2, int num1 = 1, int num2 = 1);

void prohod_dva_radky (int row1, int row2, long double**matrix, int degree);

void prohozeni_vsech_radku_pod(int row, long double**matrix,int degree);

long double** zkopirovani_matice(long double**A, int degree);

long double** kontrola_inverzni_matice(long double **matrix, long double**I, int degree, int counter);

long double** inverzni_matice(long double **matrix, int degree);

long double** soucin_matic(long double**A, long double**B, int degree);

long double determinant (long double **matrix, int degree, long double k = 1);

void vypis_vec (long double * vec, int degree);

long double* vytvor_vec (int degree);

long double* cramrule(long double **matrix, long double* vec, int degree);

long double** reduced_matrix (long double** matrix, int degree,int row0, int col0 );

long double doplnek (long double ** matrix, int degree, int row, int col);

long double ** adjung (long double **matrix, int degree);

long double ** alter_inverz(long double **matrix,int degree);

long double ** nova_matice(int degree);

int uvod();

int rozcestnik(int degree, long double ** MATRIX);

long double ** nova_matice(int degree);

int zadani_DIM();
