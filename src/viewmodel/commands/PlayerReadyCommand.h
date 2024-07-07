#ifndef PLAYER_READY_COMMAND_H
#define PLAYER_READY_COMMAND_H

#include "etlbase.h"

class GeneralsViewModel;

class PlayerReadyCommand : public ICommandBase {
public:
    PlayerReadyCommand(GeneralsViewModel *p) throw();
    virtual void SetParameter(const std::any &param) override;
    virtual void Exec() override;

private:
    GeneralsViewModel *m_pVM;
    int m_player_id;
};

#endif // PLAYER_READY_COMMAND_H