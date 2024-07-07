#include "MoveCommand.h"
#include "GeneralsViewModel.h"

MoveCommand::MoveCommand(GeneralsViewModel *p) throw()
    : m_pVM(p), m_player_id(0), m_x(0), m_y(0), m_dx(0), m_dy(0) {}

void MoveCommand::SetParameter(const std::any &param) {
    m_player_id = std::any_cast<int>(param);
    m_x = std::any_cast<int>(param);
    m_y = std::any_cast<int>(param);
    m_dx = std::any_cast<int>(param);
    m_dy = std::any_cast<int>(param);
}

void MoveCommand::Exec() {
    m_pVM->move(m_player_id, m_x, m_y, m_dx, m_dy);
}