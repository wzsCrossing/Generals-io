#include "StartGameCommand.h"
#include "GeneralsViewModel.h"

StartGameCommand::StartGameCommand(GeneralsViewModel *p) throw()
    : m_pVM(p), m_nickname("") {}

void StartGameCommand::SetParameter(const std::any &param) {
    m_nickname = std::any_cast<QString>(param);
}

void StartGameCommand::Exec() {
    m_pVM->startGame(m_nickname);
}