#include <iostream>
#include <cmath>
using namespace std;

int kontrola_hodnoty(int degree)
{
    // bohuzel jsem nebyl schopen osetrit kdyz nekdo zada neco jineho nez cislo,
    // v takovem pripade program spadne
    if (degree < 2) //zkontroluje jestli je kladne a vetsi nez 1
    {   int degree0;
        cout << "Musíte zadat přirozené číslo vetší než jedna\n";
        cin >> degree0;
        kontrola_hodnoty(degree0);
    }
    else
    {
        cout << "Zadaná hodnota je v pořádku, při zadávání matice nezapomeňte, že musí být regulární.\n";

        return degree;
    }
}

long double** vytvor_matici(int degree)
{
    //vytvori pointer na pointer a pak vytvori n pointru,
    // co ukazuje na pointry ktery kazdy z nich ukazuje na n prvku → n*n prvku v poli
    long double**matrix = new long double*[degree];
    for(int i = 0; i < degree; ++i)
    {
        matrix[i] = new long double[degree];
    }
    return matrix;
}

long double** vytvor_jednotkovou_matici(int degree)
{
    //vytvori pointer na pointer a pak vytvori n pointru co ukazuje na pointry ktery kazdy z nich ukazuje na n prvku → n*n prvku v poli
    long double**matrix = new long double*[degree];
    for(int i = 0; i < degree; ++i) {
        matrix[i] = new long double[degree];
    }

    // jdi postupne po radcich a sloupcich a davej hodnoty, jednicek na diagonaluj a 0 jinde
    for (int row = 0; row < degree; row++) {
        for (int col = 0; col < degree; col++) {
            if (row==col)
            {
                matrix[row][col] = 1;
            }
            else
            {
                matrix[row][col] = 0;
            }
        }

    }
    return matrix;
}

void vypln_matici(long double**matrix, int degree)
{// jdi postupne po radcich a sloupcich a davej hodnoty
    for (int row = 0; row < degree; row++) {
        for (int col = 0; col < degree; col++) {
            cout << "A_" << row + 1 << col + 1 << "=";
            cin >> matrix[row][col];
            cout << "\n";
        }

    }
}

void vypis_matici(long double**matrix, int degree)
{// jdi postupne po radcich a sloupcich a vypis co v tom prvku je
    cout << "Vaše matice je:\n\n";
    for (int row = 0; row < degree ; row++)
    {
        cout << "\n";
        for (int col = 0; col < degree ; col++)
        {
            cout << matrix[row][col] << "\t"; //zarovnai kvuli citelnosti
        }
    }
    cout << "\n\n";
}

void vydel_radek_cislem_z_nej(long double**matrix, int degree, int row, int col)
{// urcili jsme si jakou matici, kolik ma clenu v radku, jaky radek to je a jakym cislem z toho radku bud delit
    int a=matrix[row][col]; // urcim si cim delim protoze se mi pak zmeni na jednicku
    for (int col0 = 0; col0 < degree; ++col0)
    {
        matrix[row][col0] =  matrix[row][col0]/a;
    }
}

void vydel_radek_cislem(long double**matrix, int degree, int row, int num)

{// urcili jsme si jakou matici, kolik ma clenu v radku, jaky radek to je a jakym cislem se deli v parametru
    for (int col0 = 0; col0 < degree; ++col0)
    {
        matrix[row][col0] =  matrix[row][col0]/num;
    }
}

void odecti_nasob_radek_od_radku(long double**matrix,int degree,int row1, int row2, int num1 = 1, int num2 = 1)
{
    for (int col = 0; col < degree ; ++col)
    {   //num1, num2 jsou koef a do radku row1 se ulozi vysledek rozdilu
        matrix[row1][col]=num1*matrix[row1][col]- num2*matrix[row2][col];
    }
}

void prohod_dva_radky (int row1, int row2, long double**matrix, int degree)
{
    long double*field = new long double[degree];//pole na ulozeni radku
    for (int col = 0; col < degree; col++)
    {

        field[row1]=matrix[row1][col];// ulozim puvodni stranou
        matrix[row1][col]=matrix[row2][col];//prepis radek row1
        matrix[row2][col]= field[row1];//zkopiruji puvodni do row2

    }
    delete field;
}

void prohozeni_vsech_radku_pod(int row, long double**matrix,int degree)
{
    if (row > degree-1)//kdyz chyba
    {
    }
    if (row < degree-1)
    {
        for ( int row0=row ; row0 < degree-1; ++row0)//postupne prohozeni dvojic, vzdy nad a po a postupne jdu dolu
        {
            prohod_dva_radky(row0,row0+1,matrix,degree);
        }
    }
    if (row == degree-1)
    {
        prohozeni_vsech_radku_pod(0,matrix,degree);
    }
}

long double** zkopirovani_matice(long double**A, int degree)
{
    long double**B = vytvor_matici(degree);//nova matice, nove pointry
    for (int row = 0; row < degree; row++)
    {
        for (int col = 0; col < degree; col++)
        {
            B[row][col]=A[row][col];//ulozim ji
        }
    }
    return B;
}

long double** kontrola_inverzni_matice(long double **matrix, long double**I, int degree, int counter)
{
    counter++;
    if (counter > 2*degree) //pokud neustale nemuzu zpracovat, vyvod ze je to singular matice
    {
        cout << "\nMatice je singularni\n";
        return nullptr;
    }
    //vstupuji jiz s predim upravenou matici a upravenou jednotkovou matici
    for (int col0 = 0; col0 < degree - 1; col0++)
    {
        int i = 0;
        while (matrix[col0][col0] == 0)
        {   //snada prohazovat radky kde je aktualni sloupec nulovy, dokud nenajdu,
            i++;
            if (i == degree)// nebo neprojdu vsechny, to pak je matice singularni
            {
                cout << "\nMatice je singularni\n";
                return nullptr;
            }
            else
            {
                prohozeni_vsech_radku_pod(col0, I, degree);
                prohozeni_vsech_radku_pod(col0, matrix, degree);
            }

        }
        for (int row = 1 + col0; row < degree; row++)//abych byl vzdy pod diagonalou
        {   //uprava matice, i jednotkove matice postupne delanim pod diagonalou nuly pomoci nasobeni koef,
            // aby byl nejmensi spolecny nasobek
            odecti_nasob_radek_od_radku(I, degree, row, col0, matrix[col0][col0], matrix[row][col0]);
            odecti_nasob_radek_od_radku(matrix, degree, row, col0, matrix[col0][col0], matrix[row][col0]);
        }
    }
    //uplna gaus. eliminace s inverz.
    if (matrix[degree-1][degree-1]!=0)//pokud pravy dolni prvek nenulovy po upravach radku
    {
        for (int col0 = degree-1; col0 > 0 ; col0--)
        {
            for (int row =col0 -1; row >= 0 ; row--)//abych byl vzdy nad diagonalou
            {   //jdu postupne nahopru a opet nuluji sloupec
                odecti_nasob_radek_od_radku(I,degree,row,col0,matrix[col0][col0] ,matrix[row][col0]);
                odecti_nasob_radek_od_radku(matrix,degree,row,col0, matrix[col0][col0] ,matrix[row][col0]);
            }
        }
        for (int row = 0; row < degree ; ++row)
        {   //delani jednicek na diagonale
            vydel_radek_cislem(I,degree,row,matrix[row][row]);
            vydel_radek_cislem_z_nej(matrix,degree,row,row);
        }
    }
    //reseni kdyz na diagonale 0
    if(matrix[degree-1][degree-1]==0)
    {
        for (int row = 0; row < degree ; ++row)
        {
            if(matrix[row][degree-1]!=0) //snaha najit nenulovy prvekv danem sloupci
            {//pokud najdes prohod s poslednim a zacni od zacatku
                prohozeni_vsech_radku_pod(degree-1,I,degree);
                prohozeni_vsech_radku_pod(degree-1, matrix ,degree);
            }
        }
        return kontrola_inverzni_matice(matrix,I,degree,counter);
    }
    else
    {
        cout << "Invezní ";
        vypis_matici(I,degree);
        return I;
    }
}

long double** inverzni_matice(long double **matrix, int degree)
{
    long double **I = vytvor_jednotkovou_matici(degree);
    //gaus eliminace. a to stejne pro jednotkovou
    for (int col0 = 0; col0 < degree - 1; col0++)
    {
        int i = 0;
        while (matrix[col0][col0] == 0)
        {//snada prohazovat radky kde je aktualni sloupec nulovy, dokud nenajdu,
            i++;
            if (i == degree)// nebo neprojdu vsechny, to pak je matice singularni
            {
                cout << "Matice je singularni\n";
                return nullptr;
            }
            else
            {
                prohozeni_vsech_radku_pod(col0, I, degree);
                prohozeni_vsech_radku_pod(col0, matrix, degree);
            }
        }
        for (int row = 1 + col0; row < degree; row++)//abych byl vzdy pod diagonalou
        {
            //uprava matice, i jednotkove matice postupne delanim pod diagonalou nuly pomoci nasobeni koef,
            // aby byl nejmensi spolecny nasobek
            odecti_nasob_radek_od_radku(I, degree, row, col0, matrix[col0][col0], matrix[row][col0]);
            odecti_nasob_radek_od_radku(matrix, degree, row, col0, matrix[col0][col0], matrix[row][col0]);
        }
    }
    //uplna gaus. eliminace s inverz. nahoru
    if (matrix[degree-1][degree-1]!=0)
    {
        for (int col0 = degree-1; col0 > 0 ; col0--)
        {
            for (int row =col0 -1; row >= 0 ; row--)//abych byl vzdy pod diagonalou
            {   //jdu postupne nahopru a opet nuluji sloupec
                odecti_nasob_radek_od_radku(I,degree,row,col0,matrix[col0][col0] ,matrix[row][col0]);
                odecti_nasob_radek_od_radku(matrix,degree,row,col0, matrix[col0][col0] ,matrix[row][col0]);
            }
        }
        for (int row = 0; row < degree ; ++row)
        {   //delani jednicek na diagonale
            vydel_radek_cislem(I,degree,row,matrix[row][row]);
            vydel_radek_cislem_z_nej(matrix,degree,row,row);
        }
    }
    //reseni kdyz na diagonale 0
    if(matrix[degree-1][degree-1]==0)
    {
        for (int row = 0; row < degree ; ++row)
        {
            if(matrix[row][degree-1]!=0)//snaha najit nenulovy prvekv danem sloupci
            {
                prohozeni_vsech_radku_pod(degree-1,I,degree);
                prohozeni_vsech_radku_pod(degree-1, matrix ,degree);
            }
        }
    }
    return kontrola_inverzni_matice(matrix,I,degree,0); //pokracuj na kontrolu v cyklu
}

long double** soucin_matic(long double**A, long double**B, int degree)
{
    long double**matrix = new long double*[degree];//kam novou matici ulozim
    for(int i = 0; i < degree; ++i) {
        matrix[i] = new long double[degree];
    }

    for (int row = 0; row < degree; row++)
    {
        for (int col = 0; col < degree; col++)
        {
            matrix[row][col]=0;//vychazim z nuly
            for (int index = 0; index < degree; ++index)
            {
                matrix[row][col] += A[row][index] * B[index][col];//def mat. soucin.
            }
        }

    }
    return matrix;
}

long double determinant (long double **matrix, int degree, long double k = 1)
{
    long double ** A = zkopirovani_matice(matrix,degree);
    //abych si nezmenil puvodni matici a mohl na ni pozdeji provadet jine operace
    long double det =1;
    for (int col0 = 0; col0 < degree - 1; col0++)
    {
        int i = 0;
        while (A[col0][col0] == 0&& i < degree)
        {//snada prohazovat radky kde je aktualni sloupec nulovy, dokud nenajdu,
            i++;
            prohozeni_vsech_radku_pod(col0, A, degree);
            if(col0< degree-1)
            {
                k*=pow(-1,degree-(col0+1)); //meneni znamenka determinantu dle kolika prohozeni radku
            }
            else
            {
                k*=pow(-1,degree-1);
            }

        }
        for (int row = 1 + col0; row < degree; row++)//abych byl vzdy pod diagonalou
        {
            //uprava matice, postupne delanim pod diagonalou nuly pomoci nasobeni koef,
            // aby byl nejmensi spolecny nasobek
            odecti_nasob_radek_od_radku(A, degree, row, col0, A[col0][col0], A[row][col0]);
            k=k*A[col0][col0];
        }
    }
    for (int i = 0; i < degree ; ++i)
    {
        det*=A[i][i];
    }
    if (det==0)
    {
        return 0;
    }

    return det/k;

}

long double* vytvor_vec (int degree)
{
    long double*field = new long double[degree];
    for (int col = 0; col < degree; col++)
    {
        cout << "X_" << col+1 << ":";
        cin >> field[col];// uloz hodnoty
        cout << "\n";
    }
    return field;
}

void vypis_vec (long double * vec, int degree)
{
    for (int i = 0; i <degree ; ++i)
    {
        cout << vec[i] << "\t";
    }
    cout << "\n";
}

long double* cramrule(long double **matrix, long double* vec, int degree)
{
    long double ** A = zkopirovani_matice(matrix,degree);
    long double detA = determinant(A,degree);
    long double*solution = new long double[degree];
    for (int col = 0; col < degree; col++)
    {
        long double ** B = zkopirovani_matice(matrix,degree); //vyzdy jinak poupravim puvodni matici
        for (int row = 0; row < degree; ++row)
        {
            B[row][col] = vec[row];
        }
        solution[col] = ( (determinant(B,degree)) / detA); //cramerovo pravidlo
    }
    return solution;
}

long double** reduced_matrix (long double** matrix, int degree,int row0, int col0 )
{
    long double** reduced = vytvor_matici(degree-1); //vytvor matici o jeden rad mensi
    int row1 =0; // pocitadlo abych dodrzel redukovanou dimenzi
    for (int row = 0; row < degree  ; ++row)
    {

        if (row != row0)  //skrtam jeden radek
        {
            int col1 =0;
            for (int col = 0; col < degree ;++col)
            {

                if(col != col0 && col1!=degree-1) //skrtam jeden sloupec + overeni ze neprekracuji dimenzi
                {
                    reduced[row1][col1]=matrix[row][col];
                    col1++;
                }

            }
            row1++;
        }
    }
    return reduced;
}

long double doplnek (long double ** matrix, int degree, int row, int col)
{
    long double ** A = reduced_matrix(matrix,degree,row,col);
    long double det = determinant(A,degree-1);
    long double D = pow(-1,row+col)*det; //def doplnku
    return D;
}

long double ** adjung (long double **matrix, int degree)
{

    long double** adjung = vytvor_matici(degree);
    for (int row = 0; row < degree ; ++row)
    {
        for (int col = 0; col < degree; ++col)
        {
            adjung[row][col]=doplnek(matrix,degree,col,row); //def adjung matice
        }
    }
    return  adjung;
}

long double ** alter_inverz(long double **matrix,int degree)
{
    long double ** adjungs = adjung(matrix,degree); //udelej si adjung
    for (int row = 0; row < degree ; ++row)
    {
        vydel_radek_cislem(adjungs,degree,row,determinant(matrix,degree));
        //vydel det puvodni → def inverz pomoci adjung
    }
    cout << "Invezní ";
    vypis_matici(adjungs,degree);
    return adjungs;
}

int zadani_DIM()
{
    cout << "Chci zadat matici řádu: ";
    int degree;

    cin >> degree;

    degree = kontrola_hodnoty(degree);
    return degree;
}

long double ** nova_matice(int degree)
{
    long double ** matrix = vytvor_matici(degree);
    vypln_matici(matrix,degree);

    vypis_matici(matrix,degree); //ukazka matice

    return  matrix;
}

int rozcestnik(int degree, long double **MATRIX)
{
    long double**matrix =zkopirovani_matice(MATRIX,degree); //nechci puvodni matici menit a tak pracuji s kopii

    cout << "Jakou operaci si přejete učinit? Zadejte číslo dané volby a postupujte dle instrukcí\n"
            "0. ověření regularity\n"
            "1. výpočet determinantu\n"
            "2. výpočet inverzní matice\n"
            "3. výpočet adjungované matice\n"
            "4. vyřešení soustavy pomoci Cramerova pravidla\n"
            "5. změna zadné matice\n"
            "6. zobraz zadanou matici\n"
            "7. ukončit program\n"
            "Volba: \t";
    int choice;
    cin >> choice;
    cout << "\n";
    if (choice !=0 && choice!=1 && choice!=2 && choice!=3 && choice!=4 && choice!=5 && choice!=6&& choice !=7)
    {
        cout << "\nNezadal jste platné číslo\n";
        rozcestnik(degree,MATRIX);
        return 0;
    }
    switch(choice) //urceni co se bude delat
    {
        case 0:
        {
            int det = determinant(matrix,degree);
            if (det != 0)
            {
                cout << "Matice je regulární\n";
            }
            else
            {
                cout << "Matice je singulární\n";
            }
            break;
        }
        case 1:
        {
            int det =determinant(matrix,degree);
            cout << "Det = " << det << "\n";
            break;
        }
        case 2 :
        {
            cout << "Přejete si výpočet pomocí:\n"
                    "1. úplné gaussovy eliminace\n"
                    "2. adjungované matice\n"
                    "Volba:";
            int choice0;
            cin >> choice0;
            cout << "\n";
            switch (choice0)
            {
                case 1 :
                {
                    inverzni_matice(matrix,degree);
                    break;
                }
                case 2:
                {
                    alter_inverz(matrix,degree);
                    break;
                }
                default: break;
            }
            cout << "\nPokud Vám výpočet nevyšel, zkuste druhou metodu.\n";
            break;
        }
        case 3 :
        {
            long double **A = adjung(matrix,degree);
            vypis_matici(A,degree);
            break;
        }
        case 4 :
        {
            cout << "Zadejte vector pro který soustavu řešíte.\n";

            long double* b = vytvor_vec(degree);

            cout << "Zadal jste:\t";
            vypis_vec(b,degree);

            long double* x = cramrule(matrix,b,degree);
            cout << "Resenim soustavy je: \t";
            vypis_vec(x,degree);
            break;
        }
        case 5:
        {
            int degree0 = zadani_DIM();

            rozcestnik(degree0,nova_matice(degree0));

            return 0;
        }
        case 6:
        {
            vypis_matici(MATRIX,degree);
            rozcestnik(degree,MATRIX);
            return 0;
        }
        case 7 : return 0;
        default: return 1;
    }
    cout << "Chcete ukončit program?\n"
            "[ano = 1 / ne = 0]:\t";
    int answer;
    cin >> answer;
    switch (answer)
    {
        case 0:
        {
            rozcestnik(degree,MATRIX);

        }
        case 1:
        {
            return 0;
        }
        default:  return 1;
    }
}

int uvod()
{
    //uvodni
    cout << "Vítejte v programu pro výpočet inverzních matic, determinantů,\n"
            "soustavy či pro zjištění regulárnosti.\n"
            "Zadejte prosím řád čtvercové matice, kterou chcete zadat,\n"
            "avšak pokud zadáte iracionální číslo, tak bude zaokrouhleno na dolní celou čast,\n"
            "pokud nezadáte číslo program nebude fungovat.\n\n";
    int degree = zadani_DIM();

    return degree;
}

