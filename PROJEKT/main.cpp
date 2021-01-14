#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

int generator_Liczb(int tablica[],int n)//Funkcja generujaca pseudolosowe liczby
{
    ofstream plik("dane.txt"); //Otwarcie pliku "dane.txt" do zapisu
//Generator liczb pseudolosowych
    srand(time(NULL));

    for(int i=0; i<n; i++)
    {
        tablica[i]=rand()%10+1;
        plik<<tablica[i]<<" "; //Zapis wygenerej tablicy do pliku
    }
    return tablica[n]; //Zwrocenie tablicy
}

void wczytanie_z_pliku(int tablica[],int n) //Funkcja wczytujaca dane  z pliku
{
    fstream plik; //zadeklarowanie pliku do odczytu
    plik.open("dane.txt");
    if(plik.good()==false) //Sprawdzenie czy plik istnieje
    {
        cout<<"Taki plik nie istnieje."<<endl;
    }
    for(int i=0; i<n; i++) //Zapis tablicy do pliku
    {
        plik>>tablica[i];
    }
}

void zapis_do_pliku(int tab[],int tab_przedsort[],int n) //Funkcja zapisujaca dane do pliku
{
    ofstream zapis; //Otwarcie pliku zapis "wynik.txt"
    zapis.open("wynik.txt");
    zapis<<"Po sortowaniu: ";
    for(int i=0;i<n;i++) //Wypisanie tablicy po posortowaniu
    {
        zapis<<tab[i];
        zapis<<" ";
    }
    zapis<<endl;
    zapis<<"Przed sortowaniem: ";
    for(int j=0;j<n;j++) //Wypisanie tablicy przed sortowaniem
        zapis<<tab_przedsort[j]<<" ";
}

void sortowanie_przez_wstawianie(int tab[],int p) //Funkcja sortujaca przez wstawianie
{
    int i,j,x;
	for(j=p-2; j>=0; j--)
  {
    x=tab[j];
    i=j+1;
    while((i<p) && (x>tab[i]))
    {
      tab[i-1]=tab[i];
      i++;
    }
    tab[i-1] = x;
  }

// Wyswietlamy wynik sortowania

  cout << "Po sortowaniu: \n\n";
  for(i=0; i<p; i++)
    cout << setw(6) << tab[i];
  cout << endl;
}
void sortowanie_kopcowe( int tab[], int n ) //Funkcja sortujaca poprzez kopcowanie
{
    int i,j,k,x,m;
    //budujemy kopiec
    for(i=2; i<=n; i++)
   {
    j = i;
    k = j/2;
    x = tab[i];
    while((k>0) && (tab[k]<x))
    {
      tab[j] = tab[k];
      j=k;
      k=j/2;
    }
    tab[j] = x;
   }

// Rozbieramy kopiec

  for(i=n; i>1; i--)
  {
    swap(tab[1], tab[i]);
    j=1;
    k=2;
    while(k<i)
    {
      if((k+1<i) && (tab[k+1]>tab[k]))
        m=k+1;
      else
        m=k;
      if(tab[m] <= tab[j])
        break;
      swap(tab[j], tab[m]);
      j=m;
      k=j+j;
    }
  }

// Wyswietlamy wynik sortowania

  cout << "Po sortowaniu: \n\n";
  for(i = 0; i <= n; i++)
    cout << setw(6) << tab[i];
  cout << endl;
}

int main()
{

    DWORD t1, t2;
    int n, *tablica, i, k; //Deklaracja zmiennych

    cout<<"Ile liczb chcesz posortowac?: "<<endl;
    cin>>n;
    tablica=new int[n];

    cout<<"1.Wczytanie liczb z pliku"<<endl;
    cout<<"2.Wygenerowanie liczb i zapisanie ich do pliku"<<endl;
    cin>>k;
    //Wybor jaka metoda chcesz posortowac

    switch(k)
    {
        case 1:
        {
            wczytanie_z_pliku(tablica,n); //Wywolanie funkcji wczytanie_z_pliku
            break;
        }
        case 2:
        {
            generator_Liczb(tablica,n); //Wyowolanie funkcji generator_Liczb
            break;
        }
        default:
            {
                cout<<"Bledny wybor";
                return 0;
            }
    }

    int tablica_przedsort[n];
    for(int j=0;j<=n;j++)
    {
        tablica_przedsort[j]=tablica[j]; //Stoworzenie tablicy z wartosciami tablicy przed posortowaniem
    }
    cout<<"Liczby to :"<<endl; //Wypisanie ciagu
    for(int l=0;l<n;l++)
        {
            cout<<tablica[l]<<" ";
        }
        //Wybor rodzaju sortowania
    cout<<endl<<endl;
    cout<<"Jaka metoda posortowac? \n"<<endl;
    cout<<"1.Wstawianie"<<endl;
    cout<<"2.Kopcowanie"<<endl;
    cout<<endl<<endl;
    int wybor;
    cin>>wybor;
    switch(wybor)
    {
        case 1:
        {
            cout<<"Po posortowaniu przez wstawianie: "<<endl;
            t1=GetTickCount();
            sortowanie_przez_wstawianie(tablica,n); // Wywolanie funkcji sortuj¹cej przez wstawianie
            t2=GetTickCount()-t1;
            cout<<"\nCzas wykonania algorytmu: "<<t2<<" [ms]";
            break;
        }
        case 2:
        {
            cout<<"Po posortowaniu kopcowym: "<<endl;
            t1=GetTickCount();
            sortowanie_kopcowe(tablica,n-1); //Wywolanie funkcji sortujacej przez kopcowanie
            t2=GetTickCount()-t1;
            cout<<"\nCzas wykonania algorytmu: "<<t2<<" [ms]";
            break;
        }
        default:
            {
                cout<<"Bledny wybor";
                return 0;
            }
    }
    zapis_do_pliku(tablica,tablica_przedsort,n); //Wywolanie funkcji zapisujacej dane do pliku
    return 0;
}
