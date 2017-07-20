 
// File:   main.cpp
// Author: BUSRA ARSLAN 
// Student No: 131044021
//
// Description :
// Ilk size girilirken 2 ayni deger giriniz. Birisi row diğeri column icin.
// Oyunumda alınan sizelara gore bir board cizilir ilk olarak ekrana o basilir
// Bu size a gore legal hamleleri bulan fonksiyonum legal yerleri belirler.
// ekranda bos hamle bitene kadar ilk olarak legal hamlesi olan user oyunu oynar.
// sonrada legal hamlesi maximum eleman yiyen computer max hamleli yeri alır, oynar.
// oyun bu sekilde devam eder.
// her user-computer oynamasindan sonra ekrana skor tablosu basilir.
// en son oyun bitince de userin kazandı kaybetti ya da berabere yazar.
// alinan inputlarin tipleri cin ile kontrol edildi.
// inputlar her kosulda test edildi.
// userin oynadigi hamle legal midir kontrol edildi.
// user hamle secerken column buyuk harf algilamasi yapildi.

// !!!!!!!!!!!!!!!!NOT : arrayimin ilk elemani row:1 col:1 den baslattim.!!!!!!

#include <iostream>
#include<cstdlib>
#include<cstdio>

using namespace std;

const int MAXSIZE = 300; //global constant
const char user_name = 'O'; 
const char pc_name = 'X';
const char empty = '.'; 
const char legal_hamle_yeri= '?';

/////////////////////////Function Prototype///////////////////////////

//table'nin oyuna baslarken ki ilk hali cizdirildi.
void first_draw_table(int row, int col, char arr[][MAXSIZE]);

//table update oldugunda arrayi ekrana basmak icin kullanildi.
void draw_table(int row, int col, char arr[][MAXSIZE]);

//user ve computerlerin birer hamlesi sonucu skor tablosunu ekrana basar.
//her birer hamle sonu tablodaki user ve pc tas sayisini bulur.
void score_status(int row,int col,int *count_user,int *count_pc,char arr[][MAXSIZE]);

//hem user hem computer hamle yapmadan once yani oyun oynamadan once 
//legal hamlenin yerini bulmak ve oraya '?' koyulup yeri belirlemek icin 
//olusturulmus bir fonksiyon.
void find_legal_cells(char name1,char name2,int row,int col,char arr[][MAXSIZE]);

//usern hamle yapmasi icin kullaniciya row ve column degerleri girmesini istiyor
//alinan row ve col play_game_user fonksiyonuna aktarilip
void get_value_from_user(int *new_row,int *new_col, char arr[][MAXSIZE]);

//legal hamlenin yerleri ekranda '?' ile gosterilmesine karsin yine de legal
//hamle olmayan yer girilirse kullanicidan tekrar hamle girilmesi istenir
void play_game_user(int new_row,int new_col,int row, int col, char arr[][MAXSIZE]);

//Computerin legal hamleler arasinda en cok hamleyi getirecek yeri oynamasi
//icin kullanilan fonksiyondur. Pointer olarak alinan x ve y parametreleri 
//maximum row ve column degerlerini bulup play_game_computer fonksiyonuna 
//aktararak computerin hamle yapmasini saglar.
void max_move_computer(int *x, int *y, int row, int col, char arr[][MAXSIZE]);

//Computerin oyununu  oynayip taslari oynatip yedigi fonksiyondur.  
void play_game_computer(int x, int y, int row, int col, char arr[][MAXSIZE]);


//////////////////////////////////////
/////////////MAIN/////////////////////

int main() 
{
    const int min_row=4, min_col=4;      //constant
    const int max_row=20, max_col=20;    //constant
    char arr[MAXSIZE][MAXSIZE];
    int row, col, i, j;
    int x=0, y=0;
    int new_row=0, new_col=0;
    int count_user=0, count_pc=0;
    
    cout << "Cift sayida row ve column şeklinde 2 integer deger giriniz:";
    cin >> row >> col;
    
    //input(row,column)check
    while(((row %2 != 0)  || (col %2 != 0) ) ||  ((min_row>row || min_col>col) 
                    || (row>max_row || col>max_col)) || (row!=col) || !cin ){
        cout << "Yanlis girdiniz. Tekrar giriniz:" << endl;
        cin.clear();
        cin.ignore(MAXSIZE, '\n');
        cin >> row >> col;
    }
  
    //////////////////////////////
    ////////TEST FUNCTIONS ///////
    cout << "Oyun tablosunun ilk hali" << endl;
    first_draw_table(row, col, arr);
          
    for(i=1; i<=row; ++i)
    {
        for(j=1; j<=col; ++j)
        {
            while(arr[i][j] == empty){
                count_user=0;    count_pc=0;
                cout << "-----------------------------------------------" << endl;
                
                ////////TEST_ARRAY_USER/////////
                
                find_legal_cells(user_name, pc_name, row, col, arr);
    
                draw_table(row, col, arr);
                cout << "Userin oynayabilecegi hamleler '?' leridir." << endl;
                get_value_from_user(&new_row, &new_col, arr);
                play_game_user(new_row, new_col, row, col, arr);
                draw_table(row, col, arr); 


                ////////TEST_ARRAY_COMPUTER/////////
                find_legal_cells(pc_name, user_name, row, col, arr);

                //draw_table(row, col, arr);//
                max_move_computer(&x, &y, row, col, arr);
                cout <<  "Computerin oynadigi  yer "
                     << "row: " << x << " column: " << y << endl;
                cout << "Computer hamlesini oynuyor" << endl;
                play_game_computer(x, y, row, col, arr);
                draw_table(row, col, arr); 
                
                
                ////////SKOR_DURUMU/////////
                score_status(row, col, &count_user, &count_pc, arr);
                cout << "-----------------------------------------------" << endl;                    
            }
        }
    }
    
    if(count_pc < count_user){
       cout << "USER WIN!!!!!!" << endl; 
    }
    else if(count_user < count_pc){
        cout << "USER LOSE !!!" << endl;
    }
    else if(count_user == count_pc){
         cout << "TIE UP !!!" << endl;
    }
    
    
    return 0;
}


/////////////////////////FUNCTIONS/////////////////////////
///////////////////////////////////////////////////////////

void first_draw_table(int row, int col, char arr[][MAXSIZE]) 
{   
    int i, j, k;
    char t = 'a';
    
    cout << "  ";
    for (k = 0; k < col ; k++) 
    {
        cout << " " << t;
        ++t;
    }
    cout << endl;
   
    for (i= 1; i < row+1 ; i++) 
    {
        if (i < 10) {
            cout << " ";
            cout << i;
        } else {
            cout << i;
        }

        for (j = 1; j < col+1 ; j++) 
        {
            if (i == (row/2 )  && j == (col/2))
            {    
                arr[row/2][col/2] = pc_name;
                cout << " " << arr[row/2][col/2];
            }
            else if(i == (row/2)  && j == (col/2)+1)
            {
                arr[row/2][(col/2)+1] = user_name;
                cout << " " << arr[row/2][(col/2)+1]; 
            }
            else if(i == (row/2+1 )  && j == (col/2))
            {
                arr[row/2+1][col/2] = user_name;
                cout << " " <<  arr[row/2+1][col/2];  
            }
            else if(i == (row/2)+1  && j == (col/2)+1)
            {
                arr[(row/2)+1][(col/2)+1] = pc_name;
                cout<< " " << arr[(row/2)+1][(col/2)+1];  
            }
            else 
            {
                arr[i][j] = empty;
                cout << " " << arr[i][j];  
            }
        }
        cout << endl;
    }
    
}

void draw_table(int row, int col, char arr[][MAXSIZE])
{
    int i, j, k;
    char t = 'a';
    
    cout << endl << "  ";
    for (k = 0; k < col ; k++){
        cout << " " << t;
        ++t;
    }
    cout << endl;
   
    for(i=1; i<row+1; ++i)
    {
        if (i < 10) {
            cout << " ";
            cout << i;
        } else {
            cout << i;
        }
        for(j=1; j<col+1; ++j)
            cout << " " << arr[i][j];
        cout << endl;
    }
    cout << endl;
    
}

void score_status(int row,int col,int *count_user,int *count_pc,char arr[][MAXSIZE])
{
    int i, j;
    
    for(i=1; i<=row; ++i)
    {
        for(j=1; j<=col; ++j)
        {
            if(arr[i][j] == user_name)
                (*count_user) += 1;    
            else if(arr[i][j] == pc_name)
                (*count_pc) += 1;
        }
    }
    cout << "---Skor durumu---" << endl
         << "User:" << *count_user << "   "
         << "Computer:" << *count_pc << endl;
    
}


/////////////Legal Hamle Yeri Belirleme Fonksiyonu////////////////
void find_legal_cells(char name1,char name2,int row,int col,char arr[][MAXSIZE])
{
    int m, n, i,j;
    
    for(m=1; m<row+1; ++m)
    {
        for(n=1; n<col+1; ++n)
        {
            if(arr[m][n] == name1)
            {
                //cout <<  arr[i][j] << endl;
                i=m;    j=n;
                while(arr[i+1][j] ==name2 && i<row-1)
                {
                    if(arr[i+2][j] == empty)
                        arr[i+2][j] = legal_hamle_yeri;  
                    ++i;
                }
                i=m;    j=n;
                while(arr[i-1][j] == name2 && i>2)
                {
                    if(arr[i-2][j] == empty)
                       arr[i-2][j] = legal_hamle_yeri;
                    --i;
                }
                i=m;    j=n;
                while(arr[i][j+1] == name2 && j<col-1)
                {
                    if(arr[i][j+2] == empty)
                        arr[i][j+2] = legal_hamle_yeri;
                    ++j;
                }
                i=m;    j=n;
                while(arr[i][j-1] == name2 && j>2)
                {
                    if(arr[i][j-2] == empty)
                        arr[i][j-2] = legal_hamle_yeri;
                    --j;
                }

                /////CAPRAZLAR/////
                i=m;    j=n;
                while(arr[i+1][j+1] == name2 && i<row-1 && j<col-1)
                {
                    if(arr[i+2][j+2] == empty)
                        arr[i+2][j+2] = legal_hamle_yeri;          
                    ++i;    ++j;
                }
                i=m;    j=n;
                while(arr[i+1][j-1] == name2 && i<row-1 && j>2)
                {
                    if(arr[i+2][j-2] == empty)
                        arr[i+2][j-2] = legal_hamle_yeri;                   
                    ++i;    --j;
                }
                i=m;    j=n;
                while(arr[i-1][j+1] == name2 && i>2 && j<col-1)
                {
                    if(arr[i-2][j+2] == empty)
                        arr[i-2][j+2] = legal_hamle_yeri;
                    --i;    ++j;
                }
                i=m;    j=n;
                while(arr[i-1][j-1] == name2 && i>2 && j>2)
                {
                    if(arr[i-2][j-2] == empty)
                        arr[i-2][j-2] = legal_hamle_yeri;
                    --i;    --j;
                }
            }
        }
    }
    
}
  
///////////////USER//////////////
void get_value_from_user(int *new_row,int *new_col, char arr[][MAXSIZE])
{
    int w, q, z, r=1;
    const int max= 20;
    char harf_column, h= 'a', arr_harf[max];
    int arr_rakam[max]; 
    
    for(w=0; w<max; ++w){
        arr_harf[w]= h;
        ++h;
    }
    for(q=0; q<max; ++q){
        arr_rakam[q]= r;
        ++r;
    }
    
    cout << "Istediginiz '?' li yerin row ve columnunu giriniz:  ";
    cin >> *new_row >> harf_column;
    harf_column= tolower(harf_column); //buyuk harf girerse de kabul ediyor
    
    //char kontrol//
    while(!cin){
        cout << "yanlis girdiniz .Tekrar giriniz" << endl;
        cin.clear();
        cin.ignore(MAXSIZE, '\n');
        cin >> *new_row >> harf_column;
    }

    
    for(z=0; z<max; ++z)
    {
        if(harf_column == arr_harf[z])
            *new_col = arr_rakam[z];
    }
    
    //CHECK//
    /////Legal Hamle Kontrolu/////
    while(arr[*new_row][*new_col] != legal_hamle_yeri)
    {
        cout << "Lutfen legal hamle giriniz:" << endl;
        cin >> *new_row >> harf_column;
        harf_column= tolower(harf_column); 
        
        for(z=0; z<max; ++z)
        {
            if(harf_column == arr_harf[z])
                *new_col = arr_rakam[z];
        } 
    }       
    
}


void play_game_user(int new_row,int new_col,int row,int col,char arr[][MAXSIZE])
{
    int i=0, j=0, m=0, n=0, k=0;
    int temp1=0, temp2=0;
    int s, t;
    
    i=new_row;    j=new_col;
    temp1= new_row;
    while(arr[i+1][j] == pc_name && i<row-1)
    {
        if(arr[i+2][j] == user_name){
            for(k=temp1; k<i+2; ++k)
                arr[k][j]= user_name;
        }
        ++i;
    }
    i=new_row;    j=new_col;
    temp1= new_row;
    while(arr[i-1][j] == pc_name && i>2)
    {
        if(arr[i-2][j] == user_name){
            for(k=temp1; k>i-2; --k)
                arr[k][j]= user_name;
        }
        --i;
    }
    i=new_row;    j=new_col;
    temp1= new_col;
    while(arr[i][j+1] == pc_name && j<col-1)
    {
        if(arr[i][j+2] == user_name){
            for(k=temp1; k<j+2; ++k)
                arr[i][k]= user_name;
        }
        ++j;
    }
    i=new_row;    j=new_col;
    temp1= new_col;
    while(arr[i][j-1] == pc_name && j>2)
    {
        if(arr[i][j-2] == user_name){
            for(k=temp1; k>j-2; --k)
                arr[i][k]= user_name;
        }
        --j;
    }
    
    /////CAPRAZLAR/////
    i=new_row;    j=new_col;
    temp1= new_row;   temp2= new_col;
    while(arr[i+1][j+1] == pc_name && i<row-1 && j<col-1)
    {
        if(arr[i+2][j+2] == user_name){
            for(m=temp1, n=temp2; m<i+2, n<j+2; ++m, ++n)
                arr[m][n]= user_name;
        }
        ++i;    ++j;
    }
    i=new_row;    j=new_col;
    temp1= new_row;   temp2= new_col;
    while(arr[i+1][j-1] == pc_name && i<row-1 && j>2)
    {
        if(arr[i+2][j-2] == user_name){
            for(m=temp1, n=temp2; m<i+2, n>j-2; ++m, --n)
                arr[m][n]= user_name;
        }
        ++i;    --j;
    }
    i=new_row;    j=new_col;
    temp1= new_row;   temp2= new_col;
    while(arr[i-1][j+1] == pc_name && i>2 && j<col-1)
    {
        if(arr[i-2][j+2] == user_name){
            for(m=temp1, n=temp2; m>i-2, n<j+2; --m, ++n)
                arr[m][n]= user_name;
        }
        --i;    ++j;
    }
    i=new_row;    j=new_col;
    temp1= new_row;   temp2= new_col;
    while(arr[i-1][j-1] == pc_name && i>2 && j>2)
    {
        if(arr[i-2][j-2] == user_name){
            for(m=temp1, n=temp2; m>i-2, n>j-2; --m, --n)
                arr[m][n]= user_name;
        }
        --i;    --j;
    }
    
    ///Diger ihtimalleri gosteren soru isaretleri tekrar '.' yapildi.    
    for(s=1; s < row+1; ++s)
    {
        for(t=1; t< col+1; ++t)
        {
            if(arr[s][t] == legal_hamle_yeri)
                arr[s][t] = empty;
        }
    }
    
}

////////////////////////////COMPUTER/////////////////////////////

void max_move_computer(int *x, int *y, int row, int col, char arr[][MAXSIZE])
{
    int i, j, k, m, n, t=0;
    int temp1, temp2, counter=0;
    int a=0, max=0;
    
    for(i=1; i<=row; ++i)
    {
        for(j=1; j<=col; ++j){
            if(arr[i][j] == legal_hamle_yeri)
                ++a;
        }     
    }
    int count_arr[a];
    count_arr[0]= 0;  
    
    for(i=1; i<=row; ++i)
    {
        for(j=1; j<=col; ++j)
        {       
            if(arr[i][j] == legal_hamle_yeri)
            {     
                // cout << i <<"ve"<< j << endl;;
                m=i;    n=j;
                temp1= i;
                while(arr[m+1][n] == user_name && m<row-1)
                {
                    if(arr[m+2][n] == pc_name){
                        for(k=temp1+1; k<m+2; ++k)
                            ++counter;
                    }
                    ++m;
                }
                m=i;    n=j;
                temp1= i;
                while(arr[m-1][n] == user_name && m>2)
                {
                    if(arr[m-2][n] == pc_name){
                        for(k=temp1-1; k>m-2; --k)
                            ++counter;
                    }
                    --m;
                }
                m=i;    n=j;
                temp1= j;
                while(arr[m][n+1] == user_name && n<col-1)
                {
                    if(arr[m][n+2] == pc_name){
                        for(k=temp1+1; k<n+2; ++k)
                            ++counter;
                    }
                    ++n;
                }
                m=i;    n=j;
                temp1= j;
                while(arr[m][n-1] == user_name && n>2)
                {
                    if(arr[m][n-2] == pc_name){
                        for(k=temp1-1; k>n-2; --k)
                            ++counter;
                    }
                    --n;
                }

                /////CAPRAZLAR/////
                int s, p;
                m=i;    n=j;
                temp1= i;   temp2= j;
                while(arr[m+1][n+1] == user_name && m<row-1 && n<col-1)
                {
                    if(arr[m+2][n+2] == pc_name){
                        for(s=temp1+1, p=temp2+1; s<m+2, p<n+2; ++s, ++p)
                            ++counter;
                    }
                    ++m;    ++n;
                }
                m=i;    n=j;
                temp1= i;   temp2= j;
                while(arr[m+1][n-1] == user_name && m<row-1 && n>2)
                {
                    if(arr[m+2][n-2] == pc_name){
                        for(s=temp1+1, p=temp2-1; s<m+2, p>n-2; ++s, --p)
                            ++counter;
                    }
                    ++m;    --n;
                }
                m=i;    n=j;
                temp1= i;   temp2= j;
                while(arr[m-1][n+1] == user_name && m>2 && n<col-1)
                {
                    if(arr[m-2][n+2] == pc_name){
                        for(s=temp1-1, p=temp2+1; s>m-2, p<n+2; --s, ++p)
                            ++counter;
                    }
                    --m;    ++n;
                }
                m=i;    n=j;
                temp1= i;   temp2= j;
                while(arr[m-1][n-1] == user_name && m>2 && n>2)
                {
                    if(arr[m-2][n-2] == pc_name){
                        for(s=temp1-1, p=temp2-1; s>m-2, p>n-2; --s, --p)
                            ++counter;
                    }
                    --m;    --n;
                }
                
                ///////////////////MAX oynama yolu BULMA/////////////////////
                count_arr[t+1]= counter;
                if(count_arr[t]<= count_arr[t+1]  && max<= count_arr[t+1])
                { 
                    max= count_arr[t+1];
                    *x= i;
                    *y= j;
                }
                ++t;
                counter=0;
            }
        }
    }   
    
    // count_arr kontrolu//
    //int w;
    //for(w=1; w<=a; ++w)
    //   cout << " =" << count_arr[w];
    //cout << endl;   
    
}

void play_game_computer(int x, int y, int row, int col, char arr[][MAXSIZE])
{
    int i, j, m, n, k;
    int temp1, temp2;
    
    //x ve y legal hamlenin koordinatlaridir.
    i=x;    j=y;
    temp1= x;
    while(arr[i+1][j] == user_name && i<row-1)
    {
        if(arr[i+2][j] == pc_name){
            for(k=temp1; k<i+2; ++k)
                arr[k][j]= pc_name;
        }
        ++i;
    }
    i=x;    j=y;
    temp1= x;
    while(arr[i-1][j] == user_name && i>2)
    {
        if(arr[i-2][j] == pc_name){
            for(k=temp1; k>i-2; --k)
                arr[k][j]= pc_name;
        }
        --i;
    }
    i=x;    j=y;
    temp1= y;
    while(arr[i][j+1] == user_name && j<col-1)
    {
        if(arr[i][j+2] == pc_name){
            for(k=temp1; k<j+2; ++k)
                arr[i][k]= pc_name;
        }
        ++j;
    }
    i=x;    j=y;
    temp1= y;
    while(arr[i][j-1] == user_name && j>2)
    {
        if(arr[i][j-2] == pc_name){
            for(k=temp1; k>j-2; --k)
                arr[i][k]= pc_name;
        }
        --j;
    }
    
    /////CAPRAZLAR/////
    i=x;    j=y;
    temp1= x;   temp2= y;
    while(arr[i+1][j+1] == user_name && i<row-1 && j<col-1)
    {
        if(arr[i+2][j+2] == pc_name){
            for(m=temp1, n=temp2; m<i+2, n<j+2; ++m, ++n)
                arr[m][n]= pc_name;
        }
        ++i;    ++j;
    }
    i=x;    j=y;
    temp1= x;   temp2= y;
    while(arr[i+1][j-1] == user_name && i<row-1 && j>2)
    {
        if(arr[i+2][j-2] == pc_name){
            for(m=temp1, n=temp2; m<i+2, n>j-2; ++m, --n)
                arr[m][n]= pc_name;
        }
        ++i;    --j;
    }
    i=x;    j=y;
    temp1= x;   temp2= y;
    while(arr[i-1][j+1] == user_name && i>2 && j<col-1)
    {
        if(arr[i-2][j+2] == pc_name){
            for(m=temp1, n=temp2; m>i-2, n<j+2; --m, ++n)
                arr[m][n]= pc_name;
        }
        --i;    ++j;
    }
    i=x;    j=y;
    temp1= x;   temp2= y;
    while(arr[i-1][j-1] == user_name && i>2 && j>2)
    {
        if(arr[i-2][j-2] == pc_name){
            for(m=temp1, n=temp2; m>i-2, n>j-2; --m, --n)
                arr[m][n]= pc_name;
        }
        --i;    --j;
    }
    
    ///Diger ihtimalleri gosteren soru isaretleri tekrar '.' yapildi.
    int s, t;
    for(s=1; s <row+1; ++s)
    {
        for(t=1; t <col+1; ++t)
        {
            if(arr[s][t] == legal_hamle_yeri)
                arr[s][t] = empty;
        }
    }
    
}
