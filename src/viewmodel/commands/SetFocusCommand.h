#ifndef SET_FOCUS_COMMAND_H
#define SET_FOCUS_COMMAND_H

#include "etlbase.h"

class GeneralsViewModel;

class SetFocusCommand : public ICommandBase {
public:
    SetFocusCommand(GeneralsViewModel *p) throw();
    virtual void SetParameter(const std::any &param) override;
    virtual void Exec() override;

private:
    GeneralsViewModel *m_pVM;
    int m_x, m_y;
};

#endif // SET_FOCUS_COMMAND_H