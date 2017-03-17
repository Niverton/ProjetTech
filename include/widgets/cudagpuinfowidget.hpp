#ifndef CUDAGPUINFO_HPP
#define CUDAGPUINFO_HPP

#include <QWidget>

class QLabel;

class CudaGPUInfoWidget : public QWidget
{
    Q_OBJECT

public:
    CudaGPUInfoWidget();
    ~CudaGPUInfoWidget();

protected:
    /*!
     * \brief Reimplemented methods in order to ensure self deletion.
     * \param event Close event.
     */
    void closeEvent(QCloseEvent* event);
};

#endif // CUDAGPUINFO_HPP
