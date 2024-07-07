#ifndef GENERALS_VIEW_MODEL_SINK_H
#define GENERALS_VIEW_MODEL_SINK_H

#include "etlbase.h"

class GeneralsViewModel;

class GeneralsViewModelSink : public IPropertyNotification {
public:
    GeneralsViewModelSink(GeneralsViewModel *p) throw();
    virtual void OnPropertyChanged(const std::string& str);

private:
    GeneralsViewModel* m_pVM;
};

#endif // GENERALS_VIEW_MODEL_SINK_H