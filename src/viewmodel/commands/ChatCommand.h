#ifndef CHAT_COMMAND_H
#define CHAT_COMMAND_H

#include "etlbase.h"
#include <string>

class GeneralsViewModel;

class ChatCommand : public ICommandBase {
public:
    ChatCommand(GeneralsViewModel *p) throw();
    virtual void SetParameter(const std::any &param) override;
    virtual void Exec() override;

private:
    GeneralsViewModel *m_pVM;
    int m_player_id;
    std::string m_msg;
};

#endif // CHAT_COMMAND_H