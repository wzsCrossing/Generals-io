#include "SurrenderCommand.h"
#include "GeneralsViewModel.h"

SurrenderCommand::SurrenderCommand(GeneralsViewModel *p) throw()
    : m_pVM(p), m_player_id(0) {}

void SurrenderCommand::SetParameter(const std::any &param) {
    m_player_id = std::any_cast<int>(param);
}

void SurrenderCommand::Exec() {
    m_pVM->surrender(m_player_id);
}