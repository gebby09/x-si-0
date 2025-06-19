#include "Incercare.h"
#include <thread>
#include <mutex>
#include <condition_variable>
// --- Implementare Player ---

Player::Player(const string& nume) : nume(nume) {}

Player::~Player() = default;

void Player::set_nume(const string& nume) {
    this->nume = nume;
}

string Player::get_nume() const {
    return nume;
}

// --- Implementare PlayerX ---

PlayerX::PlayerX() : Player() {}

PlayerX::PlayerX(const string& nume) : Player(nume) {}

char PlayerX::getCaracter() const {
    return caracter;
}

// --- Implementare PlayerO ---

PlayerO::PlayerO() : Player() {}

PlayerO::PlayerO(const string& nume) : Player(nume) {}

char PlayerO::getCaracter() const {
    return caracter;
}

// --- Funcții de joc ---

void setupPlayers(PlayerX& playerX, PlayerO& playerO) {
    char alegere;
    string nume1, nume2;

    std::cout << "Cu ce jucator vrei sa fii? (X/O): ";
    std::cin >> alegere;

    switch (alegere) {
        case 'X':
        case 'x':
            std::cout << "Care este numele jucatorului care foloseste X? ";
            std::cin >> nume1;
            playerX.set_nume(nume1);

            std::cout << "Care este numele jucatorului care foloseste O? ";
            std::cin >> nume2;
            playerO.set_nume(nume2);
            break;

        case 'O':
        case 'o':
            std::cout << "Care este numele jucatorului care foloseste O? ";
            std::cin >> nume1;
            playerO.set_nume(nume1);

            std::cout << "Care este numele jucatorului care foloseste X? ";
            std::cin >> nume2;
            playerX.set_nume(nume2);
            break;

        default:
            std::cout << "Optiune invalida!" << std::endl;
            exit(1);
    }
}

void setupTabla(vector<char>& tabla) {
    tabla.clear();
    tabla.resize(9, ' ');
}

void afiseazaTabla(const vector<char>& tabla) {
    for (int i = 0; i < 9; ++i) {
        std::cout << " " << tabla[i] << " ";
        if ((i + 1) % 3 != 0)
            std::cout << "|";
        else if (i != 8)
            std::cout << "\n---+---+---\n";
    }
    std::cout << std::endl;
}

bool mutare(vector<char>& tabla, int pozitie, const Player& player) {
    if (pozitie < 1 || pozitie > static_cast<int>(tabla.size())) {
        std::cout << "Pozitie invalida! Trebuie intre 1 si 9." << std::endl;
        return false;
    }
    int index = pozitie - 1;
    if (tabla[index] != ' ') {
        std::cout << "Pozitia este deja ocupata!" << std::endl;
        return false;
    }
    tabla[index] = player.getCaracter();
    afiseazaTabla(tabla);
    return true;
}

void afiseazaHartaPozitii() {
    std::cout << "Pozitiile de pe tabla sunt numerotate astfel:\n";
    std::cout << " 1 | 2 | 3 \n";
    std::cout << "---+---+---\n";
    std::cout << " 4 | 5 | 6 \n";
    std::cout << "---+---+---\n";
    std::cout << " 7 | 8 | 9 \n\n";
}

bool verificaCastigator(const std::vector<char>& tabla, char simbol) {
    const int linii[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // Linii
        {0,3,6},{1,4,7},{2,5,8}, // Coloane
        {0,4,8},{2,4,6}          // Diagonale
    };
    for (auto& linie : linii) {
        if (tabla[linie[0]] == simbol &&
            tabla[linie[1]] == simbol &&
            tabla[linie[2]] == simbol)
            return true;
    }
    return false;
}

bool remiza(const std::vector<char>& tabla) {
    for (char c : tabla) {
        if (c == ' ')
            return false;
    }
    return true;
}

void playerThread(std::vector<char>& tabla, Player& player, bool isPlayer1) {
    while (!game_over) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return player1_turn == isPlayer1 || game_over; });

        if (game_over) break;

        afiseazaHartaPozitii();
        std::cout << "Tura lui " << player.get_nume() << " (" << player.getCaracter() << "): ";
        int poz;
        std::cin >> poz;

        if (mutare(tabla, poz, player)) {
            if (verificaCastigator(tabla, player.getCaracter())) {
                afiseazaTabla(tabla);
                std::cout << "Jucatorul " << player.get_nume() << " (" << player.getCaracter() << ") a castigat!\n";
                game_over = true;
                cv.notify_all();
                break;
            }
            if (remiza(tabla)) {
                afiseazaTabla(tabla);
                std::cout << "Remiza!\n";
                game_over = true;
                cv.notify_all();
                break;
            }
            player1_turn = !player1_turn;
            lock.unlock();
            cv.notify_all();
        } else {
            std::cout << "Mutare invalida. Incearca din nou.\n";
        }
    }
}
