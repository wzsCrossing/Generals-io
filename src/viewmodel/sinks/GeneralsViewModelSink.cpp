#include "GeneralsViewModelSink.h"
#include "GeneralsViewModel.h"

GeneralsViewModelSink::GeneralsViewModelSink(GeneralsViewModel *p) throw()
    : m_pVM(p) {}

void GeneralsViewModelSink::OnPropertyChanged(const std::string& str) {
    m_pVM->Fire_OnPropertyChanged(str);
}