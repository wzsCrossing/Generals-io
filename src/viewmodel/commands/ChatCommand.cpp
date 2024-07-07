#include "ChatCommand.h"
#include "GeneralsViewModel.h"

ChatCommand::ChatCommand(GeneralsViewModel *p) throw()
    : m_pVM(p), m_player_id(0), m_msg("") {}

void ChatCommand::SetParameter(const std::any &param) {
    m_player_id = std::any_cast<int>(param);
    m_msg = std::any_cast<std::string>(param);
}

void ChatCommand::Exec() {
    m_pVM->chat(m_player_id, m_msg);
}