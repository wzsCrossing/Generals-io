#include "MoveCommand.h"
#include "GeneralsViewModel.h"

MoveCommand::MoveCommand(GeneralsViewModel *p) throw()
    : m_pVM(p), m_x(0), m_y(0), m_half(false) {}

void MoveCommand::SetParameter(const std::any &param) {
    m_x = std::any_cast<int>(param);
    m_y = std::any_cast<int>(param);
    m_dir = std::any_cast<Direction>(param);
    m_half = std::any_cast<bool>(param);
}

void MoveCommand::Exec() {
    m_pVM->move(m_x, m_y, m_dir, m_half);
}