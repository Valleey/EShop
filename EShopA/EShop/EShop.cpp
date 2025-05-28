#include <iostream>
#include <fstream>
#include <string>
class Shop
{
private:
    std::string p;
    float l;
    int c;
public:
    virtual void cantitate() = 0; // Verificator cantitate produse
    
};

class Admin
{
    //Aceasta clasa va sterge/ adauga / modifica produsele disponibile si stocul lor, cat si pretul acestora.
};

class CosDeCumparaturi 
{
    // Cosul de cumparaturi
};
class Checkout : public CosDeCumparaturi
{
    //Pagina de checkout, daca clientul nu este autentificat, aceasta ii va afisa optiunea de a face cumpararea cu sau fara cont, si il
   //va redirectiona spre optiunile de plata sau pagina de login.
};
class Client 
{
    //Clientul care face cumparaturile, acesta va adauga sau sterge din cosul de cumparaturi
};
int Welcome()
{
    int n;
    std::fstream in_file("CosDeCumparaturi.txt", std::ios::in, std::ios::_Nocreate);
    std::fstream out_file("CosDeCumparaturi.txt", std::ios::out, std::ios::_Nocreate);
    if (!in_file)
    {
        std::cout << "Fisierul nu a putut fi deschis.";
        return 1;
    }
    if (!out_file)
    {
        std::cout << "Fisierul nu a putut fi inchis.";
        return 2;
    }
    switch (n)
    {
    case 1:
    {
        //Oferte 

    };
    case 2:
    {
        //Alege dupa categorie
    }

    case 3:
    {
        //Cos de cumparaturi
    }
    case 4:
    {
        //Pagina de login
    }
    }
    
            return 0;
}
int main()
{
    std::cout << "Alegeti optiunea dorita: 1.Oferte\n2.Alege dupa categorie\n3.Cos de cumparaturi\n4.Login\n0.Exit";
    Welcome();
   
  
    
  
    
}
//----------------

// 
//8. Sistem de Magazin Online
//Enunț: Dezvoltă un proiect de magazin online utilizând limbajul C++.Proiectul are ca scop crearea unui magazin online numit Eshop.
// Acesta va permite utilizatorilor să comande produse și oferte printr - un simplu click.
// Programul va facilita cumpărăturile online, permițând utilizatorilor să navigheze prin diferite categorii de produse, 
// să adauge articole în coșul de cumpărături, și să finalizeze achizițiile printr - un proces de checkout.
//Programul va începe prin afișarea unui mesaj de bun venit, urând utilizatorului 
// bun venit la Eshop și solicitându - i să aleagă între zona de oferte sau să 
// cumpere după categorie.Dacă utilizatorul alege zona de oferte, se vor afișa toate 
// ofertele disponibile și va putea începe cumpărăturile.
// Dacă utilizatorul alege să cumpere după categorie, se va afișa un meniu cu categorii 
// precum cărți, mobile și tablete, calculatoare și accesorii.Utilizatorul va introduce 
// opțiunea dorită și se vor afișa produsele corespunzătoare pe baza selecției.
//Produsele vor fi citite dintr - un fișier extern pentru a facilita actualizarea 
// catalogului de produse.Odată ce utilizatorul a selectat un articol, 
// va avea opțiunea să - l adauge în coș sau să continue cumpărăturile.După ce utilizatorul a selectat toate produsele dorite, poate proceda la meniul de checkout sau tranzacții, unde poate adăuga articole în coș, edita articolele deja adăugate sau ieși din program.La checkout, utilizatorul trebuie să se autentifice dacă este un utilizator nou sau cumpără pentru prima dată cu Eshop, sau să se înregistreze și să creeze un cont.După autentificare, utilizatorul poate alege metoda de plată, precum plata cu cardul de credit, cardul de debit sau plata la livrare.După confirmarea plății, programul se va încheia cu un mesaj de mulțumire.
// 
// 
// 
//Cerințe :
//    Citirea produselor dintr - un fișier extern.
//    Afișarea unui meniu de bun venit și a opțiunilor de navigare.
//    Funcționalități pentru adăugarea și gestionarea articolelor din coșul de cumpărături.
//    Meniu de checkout cu autentificare și opțiuni de plată.
//    Generarea de rapoarte privind achizițiile și stocurile disponibile.
//    Interfață prietenoasă pentru utilizator, cu meniuri și opțiuni clare.
// 
// 
//    Abilități Dezvoltate :
//Manipularea fișierelor
//Managementul bazelor de date
//Programare orientată pe obiecte
//Implementarea algoritmilor de autentificare și securitate
//Concepte C++ :
//    Clase și Obiecte
//    File I / O
//    STL(Standard Template Library : vector, map)
//    Funcții și Recursivitate
//    Moștenire și Polimorfism
//    Funcții Virtuale
//    Manipularea Erorilor
//    Pointers și Memorie Dinamică
//
//    Cerințe comune pentru toate proiectele
//    Pentru toate proiectele de C++ prezentate, se impun următoarele cerințe comune :
//Urcarea proiectului pe GitHub :
//Proiectul trebuie să fie gestionat folosind un repository GitHub public.
//Repository - ul trebuie să includă un istoric clar de commit - uri, reflectând progresul dezvoltării proiectului.
//Lucrul cu branch - uri și commit - uri * :
//    Dezvoltarea trebuie să fie organizată folosind branch - uri pentru diferite funcționalități și etape ale proiectului.
//    Toate modificările semnificative trebuie să fie documentate prin mesaje de commit descriptive și concise.
//    Readme :
//    Repository - ul GitHub trebuie să conțină un fișier README.md bine structurat care să includă :
//Descrierea proiectului : Explicații clare privind scopul și funcționalitățile proiectului.
//Funcționalități : O listă detaliată a funcționalităților implementate în proiect.
//Screenshot - uri : Imagini relevante care să ilustreze interfața utilizatorului și principalele funcționalități.
