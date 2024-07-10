#ifndef START_GAME_COMMAND_H
#define START_GAME_COMMAND_H

#include "etlbase.h"
#include <QString>

class GeneralsViewModel;

class StartGameCommand : public ICommandBase {
public:
    StartGameCommand(GeneralsViewModel *p) throw();
    virtual void SetParameter(const std::any &param) override;
    virtual void Exec() override;

private:
    GeneralsViewModel *m_pVM;
    QString m_nickname;
};

#endif // START_GAME_COMMAND_H