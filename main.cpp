#include "Incercare.h"
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool player1_turn = true;
bool game_over = false;

int main() {
    PlayerX playerX;
    PlayerO playerO;
    std::vector<char> tabla;

    setupPlayers(playerX, playerO);
    setupTabla(tabla);

    std::jthread t1(playerThread, std::ref(tabla), std::ref(playerX), true);
    std::jthread t2(playerThread, std::ref(tabla), std::ref(playerO), false);

    

    return 0;
}
