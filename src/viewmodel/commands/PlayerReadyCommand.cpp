#include "PlayerReadyCommand.h"
#include "GeneralsViewModel.h"

PlayerReadyCommand::PlayerReadyCommand(GeneralsViewModel *p) throw()
    : m_pVM(p), m_player_id(0) {}

void PlayerReadyCommand::SetParameter(const std::any &param) {
    m_player_id = std::any_cast<int>(param);
}

void PlayerReadyCommand::Exec() {
    m_pVM->playerReady(m_player_id);
}