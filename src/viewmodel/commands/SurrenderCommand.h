#ifndef SURRENDER_COMMAND_H
#define SURRENDER_COMMAND_H

#include "etlbase.h"

class GeneralsViewModel;

class SurrenderCommand : public ICommandBase {
public:
    SurrenderCommand(GeneralsViewModel *p) throw();
    virtual void SetParameter(const std::any &param) override;
    virtual void Exec() override;

private:
    GeneralsViewModel *m_pVM;
    int m_player_id;
};

#endif // SURRENDER_COMMAND_H