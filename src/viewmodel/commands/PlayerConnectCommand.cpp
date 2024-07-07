#include "PlayerConnectCommand.h"
#include "GeneralsViewModel.h"

PlayerConnectCommand::PlayerConnectCommand(GeneralsViewModel *p) throw()
    : m_pVM(p), m_player_id(0) {}

void PlayerConnectCommand::SetParameter(const std::any &param) {
    m_player_id = std::any_cast<int>(param);
}

void PlayerConnectCommand::Exec() {
    m_pVM->playerConnect(m_player_id);
}