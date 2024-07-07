#include "PlayerDisconnectCommand.h"
#include "GeneralsViewModel.h"

PlayerDisconnectCommand::PlayerDisconnectCommand(GeneralsViewModel *p) throw()
    : m_pVM(p), m_player_id(0) {}

void PlayerDisconnectCommand::SetParameter(const std::any &param) {
    m_player_id = std::any_cast<int>(param);
}

void PlayerDisconnectCommand::Exec() {
    m_pVM->playerDisconnect(m_player_id);
}