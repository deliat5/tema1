
#include <iostream>
#include <string>
#include <list>
#include <vector>

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
    double pret;
    std::string produseIndisponibile;
public:
    friend std::istream& operator>>(std::istream& is, Stoc& stoc) {
        std::cout << "Introduceti numele florii: ";
        is >> stoc.nume;
        return is;
    }
    const double& getPret() const {
        return pret;
    }


};

class Comanda {
private:
    std::list<Stoc> flori;
    double total_plata;

public:
    Comanda(std::list<Stoc> flori={}, double total_plata=0.0): flori(flori), total_plata(total_plata) {
        this->flori = flori;
        this->total_plata = total_plata;
    }

    Comanda(const Comanda &other) {
        this->flori = other.flori;
        this->total_plata = other.total_plata;
    }

    Comanda& operator=(const Comanda &other) {
        if (this == &other)
            return *this;
        this->flori = other.flori;
        this->total_plata = other.total_plata;
        return *this;
    }

    void ComandaFlori(const Stoc &floare) {
        flori.push_back(floare);
    }
    double calculTotalPlata() {
        double total = 0.0;
        for (const auto& floare : flori) {
            total += floare.getPret();
        }
        return total;
    }

    friend std::ostream& operator<<(std::ostream& os, const Comanda& comanda);
    friend std::istream& operator>>(std::istream& is, const Comanda& comanda);
};

std::ostream& operator<<(std::ostream& os, const Comanda& comanda) {
    os << "Numarul de flori cumparate este: " << comanda.flori.size()<<std::endl;
}
std::istream& operator>>(std::istream& is, Comanda& comanda) {
    std::cout << "Introduceti numarul de flori pentru comanda: ";
    int numar_flori;
    is >> numar_flori;
    std::cout<<"\n";
    for (int i=0; i<numar_flori;i++) {
        Stoc floare;
        comanda.ComandaFlori(floare);
    }
    return is;
}
int main() {
    Client c;
    std::cin>>c;
    std::vector<Comanda> comenzi;
    int n;
    std::cout << "Introduceti numarul de comenzi: ";
    std::cin >> n;
    Stoc stoc;
    std::cin>>stoc;
    for (int i = 0; i < n; i++) {
        Comanda comanda;
        std::cin >> comanda;
        comenzi.push_back(comanda);
    }

    for (const auto& comanda : comenzi) {
        std::cout << comanda << std::endl;
    }

    return 0;
}
