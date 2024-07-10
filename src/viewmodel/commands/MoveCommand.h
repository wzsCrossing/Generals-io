#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "etlbase.h"
#include "PlayerInfo.h"

class GeneralsViewModel;

class MoveCommand : public ICommandBase {
public:
    MoveCommand(GeneralsViewModel *p) throw();
    virtual void SetParameter(const std::any &param) override;
    virtual void Exec() override;

private:
    GeneralsViewModel *m_pVM;
    int m_x, m_y;
    Direction m_dir;
    bool m_half;
};

#endif // MOVE_COMMAND_H