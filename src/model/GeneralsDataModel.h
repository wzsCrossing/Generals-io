#ifndef GENERALS_DATA_MODEL_H
#define GENERALS_DATA_MODEL_H

#include "etlbase.h"
#include "MapInfo.h"
#include "GameInfo.h"

class GeneralsDataModel : public Proxy_PropertyNotification<GeneralsDataModel> {
public:
    GeneralsDataModel();
    bool playerConnect(int player_id);
    bool playerDisconnect(int player_id);
    bool playerReady(int player_id);
    bool chat(int player_id, const std::string &msg);
    bool move(int player_id, int x, int y, int dx, int dy);
    bool surrender(int player_id);

private:
    std::shared_ptr<GameInfo> m_GameInfo;
};

#endif // GENERALS_DATA_MODEL_H