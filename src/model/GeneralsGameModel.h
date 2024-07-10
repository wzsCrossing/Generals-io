#ifndef GANERALS_GAME_MODEL_H
#define GANERALS_GAME_MODEL_H

#include <queue>
#include <cmath>

#include "etlbase.h"
#include "MapInfo.h"
#include "GameInfo.h"

class GeneralsGameModel : public Proxy_PropertyNotification<GeneralsGameModel> {
public:
    GeneralsGameModel();
    std::shared_ptr<MapInfo> getMapInfo() throw();
    bool startGame(const QString &nickname);
    bool setFocus(int x, int y);
    bool move(int x, int y, Direction dir, bool half);
    bool clearMove();
    bool cancelMove();
    bool surrender();
    void addRound();

private:
    const std::pair<int, int> directions[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool gameStarted{}, surrendered{};
    int gameMode{};
    int width, height;

    std::shared_ptr<Focus> focus{};

    QString playerName;
    std::shared_ptr<MapInfo> playerMap;

    std::deque<Move> moveQueue;
};

#endif // GANERALS_GAME_MODEL_H