#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>

using std::string;
using std::vector;

extern std::mutex mtx;
extern std::condition_variable cv;
extern bool player1_turn;
extern bool game_over;


class Player {
protected:
    string nume;

public:
    Player() = default;
    Player(const string& nume);

    virtual char getCaracter() const = 0;

    virtual ~Player();

    void set_nume(const string& nume);
    string get_nume() const;
};

class PlayerX : public Player {
public:
    static constexpr char caracter = 'X';

    PlayerX();
    PlayerX(const string& nume);

    char getCaracter() const override;
};

class PlayerO : public Player {
public:
    static constexpr char caracter = 'O';

    PlayerO();
    PlayerO(const string& nume);

    char getCaracter() const override;
};

// Funcții legate de joc
void setupPlayers(PlayerX& playerX, PlayerO& playerO);

void setupTabla(vector<char>& tabla);

void afiseazaTabla(const vector<char>& tabla);

bool mutare(vector<char>& tabla, int pozitie, const Player& player);

void afiseazaHartaPozitii();

bool verificaCastigator(const std::vector<char>& tabla, char simbol);

bool remiza(const std::vector<char>& tabla);

void playerThread(std::vector<char>& tabla, Player& player, bool isPlayer1);

