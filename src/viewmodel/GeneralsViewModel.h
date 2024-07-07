#ifndef GENERALS_VIEW_MODEL_H
#define GENERALS_VIEW_MODEL_H

#include "GeneralsDataModel.h"

#include "GeneralsViewModelSink.h"

class GeneralsViewModel : public Proxy_CommandNotification<GeneralsViewModel>,
                          public Proxy_PropertyNotification<GeneralsViewModel> {
public:
    GeneralsViewModel();

    void SetModel(const std::shared_ptr<GeneralsDataModel>& model);

    // std::shared_ptr

private:
    std::shared_ptr<GeneralsDataModel> m_GeneralsModel;
};

#endif // GENERALS_VIEW_MODEL_H