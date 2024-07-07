#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "etlbase.h"

class GeneralsViewModel;

class MoveCommand : public ICommandBase {
public:
    MoveCommand(GeneralsViewModel *p) throw();
    virtual void SetParameter(const std::any &param) override;
    virtual void Exec() override;

private:
    GeneralsViewModel *m_pVM;
    int m_player_id;
    int m_x, m_y, m_dx, m_dy;
};

#endif // MOVE_COMMAND_H