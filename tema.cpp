//Pentru ziua de nastere si luna voiam sa implementez ideea ca daca este ziua de nastere a clientului in data in care da comanda sa aiba o reducere de 10% la comanda

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>

class Client {
private:
    std::string nume;
    std::string adresa;
    int ziua_nasterii;
    int luna_nasterii;

public:
    Client(std::string nume = "", std::string adresa = "", int ziua_nasterii = -1, int luna_nasterii = -1) {
        this->nume = nume;
        this->adresa = adresa;
        this->ziua_nasterii = ziua_nasterii;
        this->luna_nasterii = luna_nasterii;
    }

    Client(const Client &other);

    Client& operator=(const Client &other);

    friend std::ostream& operator<<(std::ostream& os, const Client& c);
    friend std::istream& operator>>(std::istream& is, Client& c);

    const std::string &getNume() const;

};

Client::Client(const Client &other) {
    this->nume = other.nume;
    this->adresa = other.adresa;
    this->ziua_nasterii = other.ziua_nasterii;
    this->luna_nasterii = other.luna_nasterii;
}

Client& Client::operator=(const Client &other) {
    if (this == &other)
        return *this;
    this->nume = other.nume;
    this->adresa = other.adresa;
    this->ziua_nasterii = other.ziua_nasterii;
    this->luna_nasterii = other.luna_nasterii;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Client& c) {
    os << "Client:" << "nume=" << c.nume << "\t" << "adresa=" << c.adresa << "\t" << "ziua nasterii=" << c.ziua_nasterii << "\t" << "luna nasterii=" << c.luna_nasterii << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Client& c) {
    std::cout << "Introduceti numele :";
    getline(is,c.nume);
    std::cout << "Introduceti adresa :";
    getline(is,c.adresa);
    std::cout << "Introduceti ziua de nastere (ziua) :";
    is >> c.ziua_nasterii;
    std::cout << "Introduceti ziua de nastere (luna) :";
    is >> c.luna_nasterii;
    std::cout<<"\n";
    return is;
}

const std::string& Client::getNume() const {
    return nume;
}

class Stoc {
private:
    std::string nume;
    static std::unordered_map<std::string, double> preturi;
public:
    Stoc(const std::string& nume = "") : nume(nume) {}

    static void setPret(const std::string& nume, double pret) {
        preturi[nume] = pret;
    }

    static double getPret(const std::string& nume) {
        return preturi[nume];
    }

    friend std::istream& operator>>(std::istream& is, Stoc& stoc) {
        std::cout << "Introduceti numele florii: ";
        is >> stoc.nume;
        return is;
    }

    const std::string& getNume() const {
        return nume;
    }
};

std::unordered_map<std::string, double> Stoc::preturi;

class Comanda {
private:
    std::list<Stoc> flori;
public:
    Comanda(std::list<Stoc> flori = {}) : flori(flori) {}

    void ComandaFlori(const Stoc &floare) {
        flori.push_back(floare);
    }

    double calculTotalPlata() const {
        double total = 0.0;
        for (const auto& floare : flori) {
            total += Stoc::getPret(floare.getNume());
        }
        return total;
    }

    friend std::ostream& operator<<(std::ostream& os, const Comanda& comanda);
    friend std::istream& operator>>(std::istream& is, const Comanda& comanda);
};

std::ostream& operator<<(std::ostream& os, const Comanda& comanda) {
    os << "Numarul de flori cumparate este: " << comanda.flori.size();
    return os;
}

std::istream& operator>>(std::istream& is, Comanda& comanda) {
    std::cout << "Introduceti numarul de flori pentru comanda: ";
    int numar_flori;
    is >> numar_flori;
    std::cout << "\n";

    if (numar_flori > 3) {
        std::string optiune;
        std::cout << "Doriti ca aceste flori sa fie facute in buchet? (Da/Nu): ";
        is >> optiune;
        if (optiune == "Da" || optiune == "da") {
            std::cout << "Selectati flori pentru buchet:\n";
            for (int i = 0; i < numar_flori; ++i) {
                Stoc floare;
                is >> floare;
                comanda.ComandaFlori(floare);
            }
            return is;
        }
    }

    for (int i=0; i<numar_flori;i++) {
        Stoc floare;
        is >> floare;
        comanda.ComandaFlori(floare);
    }
    return is;
}

int main() {
    std::cout<<"Preturile florilor disponibile: "<<"\n"<<"Trandafir: 10 lei"<<"\n"<<"Crin: 8 lei"<<"\n"<<"Lalea: 6 lei"<<"\n"<<"Bujor: 6 lei"<<"\n";
    Client c;
    std::cin >> c;

    Stoc::setPret("trandafir", 10.0);
    Stoc::setPret("crin", 8.0);
    Stoc::setPret("lalea", 6.0);
    Stoc::setPret("bujor", 6.0);
    Comanda comanda;
    std::cin >> comanda;
    std::cout << comanda << "\n";

    std::cout << "Comanda plasata de " << c.getNume() << " este:\n" << comanda << std::endl;
    double total_plata = comanda.calculTotalPlata();
    std::cout << "Total de plata: " << total_plata << " lei\n";

    return 0;
}

