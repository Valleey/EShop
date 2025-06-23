#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
void continuare()                    //functie pentru o interfata mai prietenoasa 
{
    std::cout << "\nApasati 'Enter' pentru a continua.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
class Shop
{
private:
    
public:
    virtual void cantitate() = 0; 

};
class Produs
{
public:
    std::string nume;
    float pret;
    int cantitate;
};

class Admin : public Shop            //functiile admin (adaugare si modificare produse, adaugare si modificare oferte)
{
private:
    std::vector<Produs> catalogProduse;

public:
    void cantitate() override {}

    void afiseazaCatalog()
    {
        std::cout << "\nCatalogul de produse:\n";
        for (const auto& p : catalogProduse)
        {
            std::cout << p.nume << " - Pret: " << p.pret << " RON, Cantitate: " << p.cantitate << "\n";
        }
        std::cout << std::endl;
    }

    void adaugaProdus(const std::string& numeProdus, float pret, int cantitate)
    {
        
        for (auto& produs : catalogProduse)
        {
            if (produs.nume == numeProdus)
            {
                produs.cantitate += cantitate;
                produs.pret = pret; 
                std::cout << "Produsul deja exista. Cantitatea a fost actualizata.\n";
                return;
            }
        }

        catalogProduse.push_back({ numeProdus, pret, cantitate });
        std::cout << "Produs adaugat cu succes.\n";
    }

    void modificaProdus(const std::string& numeProdus, float pretNou, int cantitateNoua)
    {
        for (auto& produs : catalogProduse)
        {
            if (produs.nume == numeProdus)
            {
                produs.pret = pretNou;
                produs.cantitate = cantitateNoua;
                std::cout << "Produs modificat cu succes.\n";
                return;
            }
        }
        std::cout << "Produsul nu a fost gasit in catalog.\n";
    }

    const std::vector<Produs>& getCatalog() const
    {
        return catalogProduse;
    }
    void adaugaOferta() 
    {
        std::string tipOferta;
        std::cout << "Selectati tipul ofertei:\n1. Reduceri\n2. Lichidari de stoc\nOptiune: ";
        int optiune;
        std::cin >> optiune;

        if (optiune == 1)                                             //TEST
        {
            tipOferta = "Reduceri:";
        }
        else if (optiune == 2)
        {
            tipOferta = "Lichidari de stoc:";
        }
        else 
        {
            std::cout << "Optiune invalida.\n";
            return;
        }

        std::string numeProdus;
        float pret;
        int cantitate;

        std::cout << "Nume produs: ";
        std::cin >> numeProdus;
        std::cout << "Pret: ";
        std::cin >> pret;
        std::cout << "Cantitate: ";
        std::cin >> cantitate;

       
        std::ifstream in("oferte.txt");
        std::vector<std::string> reducereLines, lichidariLines;
        std::string line;
        enum Sectiune { NONE, REDUCERI, LICHIDARI };
        Sectiune current = NONE;

        while (std::getline(in, line)) 
        {
            if (line == "Reduceri:") 
            {
                current = REDUCERI;
                continue;
            }
            if (line == "Lichidari de stoc:") 
            {
                current = LICHIDARI;
                continue;
            }

            if (current == REDUCERI)
                reducereLines.push_back(line);
            else if (current == LICHIDARI)
                lichidariLines.push_back(line);
        }
        in.close();

        
        std::ostringstream newLine;
        newLine << numeProdus << " " << pret << " " << cantitate;

        if (tipOferta == "Reduceri:")
            reducereLines.push_back(newLine.str());
        else
            lichidariLines.push_back(newLine.str());

        
        std::ofstream out("oferte.txt");
        out << "Reduceri:\n";
        for (const auto& l : reducereLines)
            out << l << "\n";

        out << "\nLichidari de stoc:\n";
        for (const auto& l : lichidariLines)
            out << l << "\n";

        out.close();

        std::cout << "Oferta a fost adaugata cu succes la sectiunea \"" << tipOferta << "\".\n";
    }
};
bool autentificare(const std::string& conturi_ex, const std::string& parola_ex, bool& adminAutf)
{
    std::ifstream in("User_Database.txt");
    if (!in.is_open())
    {
        std::cout << "Fisierul cu utilizatori nu poate fi accesat.\n";
        return 0;
    }
    std::string linie;
    while (std::getline(in, linie))
    {
        std::string userPass = conturi_ex + " " + parola_ex;
        if (linie == userPass)
        {

            if (conturi_ex == "Admin" && parola_ex == "ADMIN")
            {
                adminAutf = true;
                std::cout << "                                 <!>Bun venit, ADMIN, optiuni noi:\n\n9.Adauga sau modifica produse\n\n10.Modifica oferte\n\n";
                return true;
            }
            else
            {
                std::cout << "Autentificare reusita. Bine ai venit, " << conturi_ex << "!\n\n";

            }
            return true;
        }

    }
    std::cout << "Autentificare invalida, verificati datele si incercati din nou.\n";
    return 0;
}
int autf(bool& adminAutf) // functie pentru creare cont si autentificare
{
    int optiune, incercari;
    std::string user, parola, nume;
    std::map<std::string, std::string> conturi;
    std::cout << "Bine ati venit pe pagina de autentificare, alegeti optiunea dorita:\n1.Creare cont\n2.Autentificare" << std::endl;
    std::cin >> optiune;
    switch (optiune)
    {
    case 1:
    {

        std::ifstream in("User_Database.txt");
        std::string conturi_ex, parola_ex;
        while (in >> conturi_ex >> parola_ex)
        {
            conturi[conturi_ex] = parola_ex;
        }
        in.close();
        std::cout << "Introduceti numele contului si parola dorita." << std::endl;
        while (true)
        {
            std::ofstream out("User_Database.txt", std::ios::app);
            std::cout << "Nume: ";
            std::cin >> user;

            if (conturi.find(user) != conturi.end())
            {
                std::cout << "Contul exista deja, incercati un nume diferit.\n";
                continue;
            }

            std::cout << "Parola: ";
            std::cin >> parola;

            if (out.is_open())
            {
                out << user << " " << parola << "\n";
                conturi[user] = parola;
                out.close();
                std::cout << "Cont creat cu succes.\n";
                return 2;
            }
            else
            {
                std::cout << "Fisierul nu a putut fi deschis.\n";
                return 1;
            }
        }


        break;
    }
    case 2:
    {
        void login();
        {
            std::ifstream in("User_Database.txt");
            std::string conturi_ex, parola_ex;
            while (in >> conturi_ex >> parola_ex)
            {
                conturi[conturi_ex] = parola_ex;
            }
            incercari = 3;

            while (incercari > 0)
            {
                std::cout << "Nume: ";
                std::cin >> conturi_ex;
                std::cout << "Parola: ";
                std::cin >> parola_ex;

                if (autentificare(conturi_ex, parola_ex, adminAutf))
                {
                    break;
                }
                else
                {

                    incercari--;
                    if (incercari > 0)
                        std::cout << "Mai aveti " << incercari << " incercari ramase.\n";
                    else
                        std::cout << "Numar maxim de incercari atins. Autentificare blocata.\n";

                }
            }
            in.close();
        }
        break;
    }
    default:
        std::cout << "Optiune invalida.";
        break;
    }
    return 0;
}
void Oferte() 
{     // functia de oferte
    std::ifstream in("Oferte.txt");
    std::string line;
    enum Sectiune { NONE, REDUCERI, LICHIDARI };
    Sectiune sectiune = NONE;

    std::cout << "\n-------- Oferte Speciale --------\n";

    while (std::getline(in, line))
    {
        if (line.empty()) continue;

        if (line == "Reduceri:")
        {
            sectiune = REDUCERI;
            std::cout << "\n### Reduceri disponibile:\n";
            continue;
        }
        else if (line == "Lichidari de stoc:")
        {
            sectiune = LICHIDARI;
            std::cout << "\n### Lichidari de stoc:\n";
            continue;
        }

        size_t lastSpace = line.find_last_of(' ');
        size_t secondLastSpace = line.find_last_of(' ', lastSpace - 1);

        if (lastSpace != std::string::npos && secondLastSpace != std::string::npos)
        {
            
                int cantitate = std::stoi(line.substr(lastSpace + 1));
                float pret = std::stof(line.substr(secondLastSpace + 1, lastSpace - secondLastSpace - 1));
                std::string nume = line.substr(0, secondLastSpace);

                std::cout << "- " << nume << " | Pret: " << pret << " RON | Cantitate: " << cantitate << '\n';
            
            
        }
    }

    std::cout << "----------------------------------\n";
    in.close();
}
class CosDeCumparaturi     //functiile pentru cosul de cumparaturi 
{
private:
    struct Produs
    {
        std::string nume;
        int cantitate;
        float pret;
    };

    std::vector<Produs> cos;

public:
    void adaugaProdus(const Produs& p) 
    {
        for (auto& item : cos) 
        {
            if (item.nume == p.nume) 
            {
                item.cantitate += p.cantitate;
                return;
            }
        }
        cos.push_back(p);
    }
    void afiseazaCos()
    {
        if (cos.empty())
        {
            std::cout << "Cosul de cumparaturi este gol.\n";
            return;
        }

        std::cout << "\nProdusele din cos:\n";
        float total = 0.0f;
        for (const auto& item : cos)
        {
            float subTotal = item.pret * item.cantitate;
            std::cout << "- " << item.nume << " | Pret: " << item.pret << " RON | Cantitate: " << item.cantitate
                << " | Subtotal: " << subTotal << " RON\n";
            total += subTotal;
        }
        std::cout << "Total de plata: " << total << " RON\n";
    }
    
    bool cosGol() const { return cos.empty(); }
    void golesteCos() { cos.clear(); }
    void stergeProdus(const std::string& numeProdus) {}
    void meniuCos()
    {
        std::cout << "----- Cos de cumparaturi -----\n";
        afiseazaCos();
        
    }

    
    const std::vector<Produs>& getContinutCos() const 
    {
        return cos;
    }
};
class Checkout : public CosDeCumparaturi //functiile de checkout
{
public:
    
    void finalizeazaComanda() 
    {
        int o;
        std::string confirmare;
        bool adminAutf = false;  

        if (cosGol()) 
        {
            std::cout << "Cosul este gol. Nu se poate finaliza comanda.\n";
            return;
        }

        std::cout << "\nFinalizare comanda:\n";
        afiseazaCos();
        std::cout << "\nPentru finalizarea comenzii este nevoie de un cont, doriti sa va autentificati? (da/nu): ";
        std::cin >> confirmare;

        if (confirmare == "da") 
        {
            int status = autf(adminAutf);
            if (status == 0) 
            {
                std::cout << "Autentificare esuata sau anulata. Comanda nu poate continua.\n";
                return;
            }
        }
        else 
        {
            std::cout << "Autentificarea este necesara pentru a plasa comanda.\n";
            return;
        }

        std::cout << "Doriti sa plasati comanda? (da/nu): ";
        std::cin >> confirmare;

        if (confirmare == "da") 
        {
            std::cout << "Alegeti optiunea de plata dorita:\n1.Cash\n2.Card de credit\n";
            std::cin >> o;

            switch (o) 
            {
            case 1:
                std::cout << "Ati ales plata cash, multumim pentru ca ati comandat cu EShop!\n";
                golesteCos();
                break;
            case 2:
                std::cout << "Ati ales plata cu cardul de credit. Multumim pentru comanda!\n";
                golesteCos();
                break;
            default:
                std::cout << "Optiune de plata invalida.\n";
            }
        }
        else 
        {
            std::cout << "Comanda anulata.\n";
        }
    }
   
};

void alegeDupaCategorie(CosDeCumparaturi& cos)  
{
    std::ifstream file("produs.txt");
    std::map<std::string, std::vector<Produs>> categorii;
    std::string line, catCu;

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        if (line.rfind("Categorie:", 0) == 0)
        {
            catCu = line.substr(9); 
            catCu.erase(0, catCu.find_first_not_of(" \t")); 
        }
        else
        {
            std::istringstream iss(line);
            std::string nume;
            float pret;
            int cantitate;

            size_t lastSpace = line.find_last_of(' ');
            size_t secondLastSpace = line.find_last_of(' ', lastSpace - 1);

            if (lastSpace != std::string::npos && secondLastSpace != std::string::npos)
            {
                
                    cantitate = std::stoi(line.substr(lastSpace + 1));
                    pret = std::stof(line.substr(secondLastSpace + 1, lastSpace - secondLastSpace - 1));
                    nume = line.substr(0, secondLastSpace);
                    categorii[catCu].push_back({ nume, pret, cantitate });
                
                
            }
        }
    }

    file.close();

    if (categorii.empty())
    {
        std::cout << "Nu exista produse disponibile.\n";
        return;
    }

    std::cout << "\nCategorii disponibile:\n";
    int index = 1;
    std::vector<std::string> categoryList;
    for (const auto& pair : categorii)
    {
        std::cout << index++ << ". " << pair.first << '\n';
        categoryList.push_back(pair.first);
    }

    int op;
    std::cout << "Alege o categorie: ";
    std::cin >> op;

    if (op < 1 || op > categoryList.size())
    {
        std::cout << "Optiune invalida.\n";
        return;
    }

    std::string selectedCategory = categoryList[op - 1];
    std::cout << "\nProduse din categoria \"" << selectedCategory << "\":\n";
    for (const auto& p : categorii[selectedCategory])
    {
        std::cout << p.nume << " - Pret: " << p.pret << " RON, Cantitate: " << p.cantitate << "\n";
    }

    std::string produsAles;
    int cant;

    std::cout << "\nIntroduceti numele produsului dorit: ";
    std::cin >> produsAles;
    std::cout << "Introduceti cantitatea dorita: ";
    std::cin >> cant;

    bool gasit = false;
    for (const auto& p : categorii[selectedCategory])
    {
        if (p.nume == produsAles)
        {
            cos.adaugaProdus({ p.nume, cant, p.pret }); 
            gasit = true;
            break;
        }
    }

    if (!gasit)
    {
        std::cout << "Produsul nu a fost gasit in aceasta categorie.\n";
    }
}




int Welcome(Admin& admin, CosDeCumparaturi& cos)  // interfata de bun venit
{
    bool adminAutf = false;
    while (true)
    {
        std::cout << "                                 --------------Bun venit pe EShop!--------------\n\n\n                                        Alegeti optiunea dorita de mai jos \n\n\n1.Oferte\n -Reduceri si lichidari de stoc.\n\n"
            "2.Alege dupa categorie\n -Cautati mai multe produse? Incercati cautarea dupa categorie! \n\n3.Cos de cumparaturi\n -Verificati produsele adaugate, pretul fiecaruia si pretul total.\n\n"
            "4.Autentificare / Creare cont\n -Creati-va cont pentru a benefica de reduceri si promotii exclusive pentru clientii fideli! \n\n5.Checkout\n" 
            "- Finalizati comanda si selectati optiunile de plata.\n\n"
            "0.Iesire\n -Optiunea de iesire din program.\n\n";
            
        int optiune;
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
        
        std::cin >> optiune;
        switch (optiune)
        {
        case 1:
        {
            Oferte();
            continuare();
            break;
        };
        case 2:
        {
            alegeDupaCategorie(cos);
            continuare();
            break;
        }

        case 3:
        {
            cos.meniuCos();
            continuare();
            break;
        }
        case 4:
        {
            autf(adminAutf);
            continuare();
            break;
        }

        case 5:
        {
            Checkout checkout;
            for (auto& item : cos.getContinutCos()) // you'll need this accessor
                checkout.adaugaProdus(item);
            checkout.finalizeazaComanda();
            continuare();
            break;
        }
        case 6:
        {
            if (!adminAutf)
            {
                std::cout << "Optiune invalida\n";
                continuare();
                break;
            }
            std::string nume;
            int cant;

            std::cout << "Introduceti numele produsului dorit: ";
            std::cin >> nume;
            std::cout << "Introduceti cantitatea dorita: ";
            std::cin >> cant;

            bool gasit = false;
            for (const auto& p : admin.getCatalog())
            {
                if (p.nume == nume)
                {
                    cos.adaugaProdus({ p.nume, cant, p.pret });
                    gasit = true;
                    break;
                }
            }
            if (!gasit)
            {
                std::cout << "Produsul nu exista in catalog.\n";
            }

            break;
        }
        case 9:
        {
            if (!adminAutf) 
            {
                std::cout << "Optiune invalida\n";
                continuare();
                break;
            }
            std::string nume;
            float pret;
            int cantitate;

            std::cout << "Introduceti numele produsului: ";
            std::cin >> nume;
            std::cout << "Introduceti pretul produsului: ";
            std::cin >> pret;
            std::cout << "Introduceti cantitatea produsului: ";
            std::cin >> cantitate;

            admin.adaugaProdus(nume, pret, cantitate);
            continuare();
            break;
        }
        case 10:
        {
            if (!adminAutf) 
            {
                std::cout << "Optiune invalida\n";
                continuare();
                break;    
            }
            admin.adaugaOferta();
            continuare();
            break;
        }
        case 0:
            std::cout << "Iesire din program.\n";
            return 0;
        default:
            std::cout << "Optiune invalida.\n";
            continuare();
        }
        continue;
    }


}
int main()
{
    Admin admin;
    CosDeCumparaturi cos;
    while (true)
    {
        Welcome(admin, cos);

    }


}
//----------------


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
// va avea opțiunea să - l adauge în coș sau să continue cumpărăturile.După ce utilizatorul a selectat toate produsele dorite, poate proceda 
// la meniul de checkout sau tranzacții, unde poate adăuga articole în coș, edita articolele deja adăugate sau ieși din program.
// La checkout, utilizatorul trebuie să se autentifice dacă este un utilizator nou sau cumpără pentru prima dată cu Eshop, 
// sau să se înregistreze și să creeze un cont.După autentificare, utilizatorul poate alege metoda de plată, precum plata cu cardul de credit, 
// cardul de debit sau plata la livrare.După confirmarea plății, programul se va încheia cu un mesaj de mulțumire.
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
