#include "SetFocusCommand.h"
#include "GeneralsViewModel.h"

SetFocusCommand::SetFocusCommand(GeneralsViewModel *p) throw()
    : m_pVM(p), m_x(0), m_y(0) {}

void SetFocusCommand::SetParameter(const std::any &param) {
    m_x = std::any_cast<int>(param);
    m_y = std::any_cast<int>(param);
}

void SetFocusCommand::Exec() {
    m_pVM->setFocus(m_x, m_y);
}