#include "widgets/cudagpuinfowidget.hpp"

#include "utils/cudartgpuinfodl.hpp"

#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>

#include <iostream>

#include <dlfcn.h>

CudaGPUInfoWidget::CudaGPUInfoWidget() : QWidget(nullptr)
{
    setWindowTitle("GPU Properties");
    setMinimumSize(300, 400);
    setWindowFlags(Qt::WindowCloseButtonHint);

    QFile file(":/styles/cudagpuinfowidget/cudagpuinfowidget.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QString styleSheet = file.readAll();
    setStyleSheet(styleSheet);
    file.close();

    /*void* handle;
    typedef cudaError_t(*CudaRunTimeVersion)(int*);
    typedef cudaError_t(*CudaVersion)(int*);
    typedef cudaError_t(*CudaDeviceProperties)(cudaDeviceProp*,int);
    handle = dlopen("libcudart.so", RTLD_LAZY);

    if(!handle)
    {
        std::cerr << dlerror() << "\n";
        std::exit(-1);
    }

    dlerror();

    CudaRunTimeVersion getCudaRunTimeVersion;
    getCudaRunTimeVersion = (CudaRunTimeVersion)dlsym(handle, "cudaRuntimeGetVersion");

    if(!getCudaRunTimeVersion)
    {
        std::cerr << dlerror() << "\n";
        std::exit(-1);
    }

    dlerror();

    CudaVersion getCudaVersion;
    getCudaVersion = (CudaVersion)dlsym(handle, "cudaDriverGetVersion");

    if(!getCudaVersion)
    {
        std::cerr << dlerror() << "\n";
        std::exit(-1);
    }

    dlerror();

    CudaDeviceProperties getCudaDeviceProperties;
    getCudaDeviceProperties = (CudaDeviceProperties)dlsym(handle, "cudaGetDeviceProperties");

    if(!getCudaDeviceProperties)
    {
        std::cerr << dlerror() << "\n";
        std::exit(-1);
    }*/

    CudaRTGPUInfoDL cuIndoDL;
    int rtVer = cuIndoDL.getCudaRunTimeVersion();
    int cuVer = cuIndoDL.getCudaDriverVersion();
    CudaRTGPUInfoDL::Properties dProp = cuIndoDL.getCudaDeviceProperties();

    QVBoxLayout* mainVbox = new QVBoxLayout();

    QHBoxLayout* hBoxDeviceName = new QHBoxLayout();
    QHBoxLayout* hBoxDeviceMemory = new QHBoxLayout();
    QHBoxLayout* hBoxSharedMemoryPerBlock = new QHBoxLayout();
    QHBoxLayout* hBoxRegistersPerBlock = new QHBoxLayout();
    QHBoxLayout* hBoxWarpSize = new QHBoxLayout();
    QHBoxLayout* hBoxMaxPitch = new QHBoxLayout();
    QHBoxLayout* hBoxMaxThreadsPerBlock = new QHBoxLayout();
    QHBoxLayout* hBoxMaxThreadsDimension = new QHBoxLayout();
    QHBoxLayout* hBoxMaxThreadsDimensionValues = new QHBoxLayout();
    QHBoxLayout* hBoxMaxGridSize = new QHBoxLayout();
    QHBoxLayout* hBoxMaxGridSizeValues = new QHBoxLayout();
    QHBoxLayout* hBoxClockFrq = new QHBoxLayout();
    QHBoxLayout* hBoxConstMem = new QHBoxLayout();
    QHBoxLayout* hBoxMinimumRevisionComputeCapablity = new QHBoxLayout();
    QHBoxLayout* hBoxMaximumRevisionComputeCapablity = new QHBoxLayout();
    QHBoxLayout* hBoxTextureAlignment = new QHBoxLayout();
    QHBoxLayout* hBoxDeviceOverlap = new QHBoxLayout();
    QHBoxLayout* hBoxStreamingMultiprocessors = new QHBoxLayout();
    QHBoxLayout* hBoxKernelRunTimeLimit = new QHBoxLayout();
    QHBoxLayout* hBoxIntegratedDevice = new QHBoxLayout();
    QHBoxLayout* hBoxMapHostMem = new QHBoxLayout();
    QHBoxLayout* hBoxComputeMode = new QHBoxLayout();
    QHBoxLayout* hBoxConcurrentKernels = new QHBoxLayout();
    QHBoxLayout* hBoxECC = new QHBoxLayout();
    QHBoxLayout* hBoxPCIBusID = new QHBoxLayout();
    QHBoxLayout* hBoxPCIDeviceID = new QHBoxLayout();
    QHBoxLayout* hBoxTCCDriver = new QHBoxLayout();
    QHBoxLayout* hBoxCudaRunTimeVersion = new QHBoxLayout();
    QHBoxLayout* hBoxCudaVersion = new QHBoxLayout();

    /*int rtVer;
    getCudaRunTimeVersion(&rtVer);

    int cuVer;
    getCudaVersion(&cuVer);

    cudaDeviceProp dProp;
    getCudaDeviceProperties(&dProp, 0);*/

    QLabel* deviceNameLabel = new QLabel("Device:", this);
    deviceNameLabel->setObjectName("DeviceNameLabel");
    QLabel* deviceNameValueLabel = new QLabel(QString::fromUtf8(dProp.name), this);
    hBoxDeviceName->addWidget(deviceNameLabel, 0, Qt::AlignLeft);
    hBoxDeviceName->addWidget(deviceNameValueLabel, 0, Qt::AlignRight);

    QLabel* deviceMemoryLabel = new QLabel("Memory:", this);
    deviceMemoryLabel->setObjectName("DeviceMemoryLabel");
    QLabel* deviceMemoryValueLabel = new QLabel(QString::number((dProp.totalGlobalMem / 1024) / 1024) + " MB", this);
    hBoxDeviceMemory->addWidget(deviceMemoryLabel, 0, Qt::AlignLeft);
    hBoxDeviceMemory->addWidget(deviceMemoryValueLabel, 0, Qt::AlignRight);

    QLabel* sharedMemoryPerBlockLabel = new QLabel("Shared Memory Per Block:", this);
    sharedMemoryPerBlockLabel->setObjectName("SharedMemoryPerBlockLabel");
    QLabel* sharedMemoryPerBlockValueLabel = new QLabel(QString::number(dProp.sharedMemPerBlock / 1024) + " KB", this);
    hBoxSharedMemoryPerBlock->addWidget(sharedMemoryPerBlockLabel, 0, Qt::AlignLeft);
    hBoxSharedMemoryPerBlock->addWidget(sharedMemoryPerBlockValueLabel, 0, Qt::AlignRight);

    QLabel* registersPerBlockLabel = new QLabel("Registers Per Block:", this);
    registersPerBlockLabel->setObjectName("RegistersPerBlockLabel");
    QLabel* registersPerBlockValueLabel = new QLabel(QString::number(dProp.regsPerBlock), this);
    hBoxRegistersPerBlock->addWidget(registersPerBlockLabel, 0, Qt::AlignLeft);
    hBoxRegistersPerBlock->addWidget(registersPerBlockValueLabel, 0, Qt::AlignRight);

    QLabel* warpSizeLabel = new QLabel("Warp Size:", this);
    warpSizeLabel->setObjectName("WarpSizeLabel");
    QLabel* warpSizeValueLabel = new QLabel(QString::number(dProp.warpSize), this);
    hBoxWarpSize->addWidget(warpSizeLabel, 0, Qt::AlignLeft);
    hBoxWarpSize->addWidget(warpSizeValueLabel, 0, Qt::AlignRight);

    QLabel* maxPitchLabel = new QLabel("Maximum Memory Pitch:", this);
    maxPitchLabel->setObjectName("MaxPitchLabel");
    QLabel* maxPitchValueLabel = new QLabel(QString::number((dProp.memPitch / 1024) / 1024) + " MB" , this);
    hBoxMaxPitch->addWidget(maxPitchLabel, 0, Qt::AlignLeft);
    hBoxMaxPitch->addWidget(maxPitchValueLabel, 0, Qt::AlignRight);

    QLabel* maxThreadsPerBlockLabel = new QLabel("Maximum Threads Per Block:", this);
    maxThreadsPerBlockLabel->setObjectName("MaxThreadsPerBlockLabel");
    QLabel* maxThreadsPerBlockValueLabel = new QLabel(QString::number(dProp.maxThreadsPerBlock) , this);
    hBoxMaxThreadsPerBlock->addWidget(maxThreadsPerBlockLabel, 0, Qt::AlignLeft);
    hBoxMaxThreadsPerBlock->addWidget(maxThreadsPerBlockValueLabel, 0, Qt::AlignRight);

    QLabel* maxThreadsDimensionLabel = new QLabel("Maximum Threads Dimensions:", this);
    maxThreadsDimensionLabel->setObjectName("MaxThreadsDimensionLabel");
    QString values = "<ul><li>X: ";
    values += QString::number(dProp.maxThreadsDim[0]);
    values += "</li><li>Y: ";
    values += QString::number(dProp.maxThreadsDim[1]);
    values += "</li><li>Z: ";
    values += QString::number(dProp.maxThreadsDim[2]);
    values += "</li></ul>";
    QLabel* maxThreadsDimensionValueLabel = new QLabel(values, this);
    hBoxMaxThreadsDimension->addWidget(maxThreadsDimensionLabel, 0, Qt::AlignLeft);
    hBoxMaxThreadsDimensionValues->addWidget(maxThreadsDimensionValueLabel, 0, Qt::AlignLeft);

    QLabel* maxGridSizeLabel = new QLabel("Maximum Grid Size:", this);
    maxGridSizeLabel->setObjectName("MaxGridSizeLabel");
    values = "<ul><li>X: ";
    values += QString::number(dProp.maxGridSize[0]);
    values += "</li><li>Y: ";
    values += QString::number(dProp.maxGridSize[1]);
    values += "</li><li>Z: ";
    values += QString::number(dProp.maxGridSize[2]);
    values += "</li></ul>";
    QLabel* maxGridSizeValueLabel = new QLabel(values , this);
    hBoxMaxGridSize->addWidget(maxGridSizeLabel, 0, Qt::AlignLeft);
    hBoxMaxGridSizeValues->addWidget(maxGridSizeValueLabel, 0, Qt::AlignLeft);

    QLabel* clockFrqLabel = new QLabel("Clock Frequency:", this);
    clockFrqLabel->setObjectName("ClockFrqLabel");
    QLabel* clockFrqValueLabel = new QLabel(QString::number(dProp.clockRate / 1000) + " Mhz" , this);
    hBoxClockFrq->addWidget(clockFrqLabel, 0, Qt::AlignLeft);
    hBoxClockFrq->addWidget(clockFrqValueLabel, 0, Qt::AlignRight);

    QLabel* constMemLabel = new QLabel("Constant Available Memory:", this);
    constMemLabel->setObjectName("ConstMemLabel");
    QLabel* constMemValueLabel = new QLabel(QString::number(dProp.totalConstMem / 1024) + " KB" , this);
    hBoxConstMem->addWidget(constMemLabel, 0, Qt::AlignLeft);
    hBoxConstMem->addWidget(constMemValueLabel, 0, Qt::AlignRight);

    QLabel* minimumRevisionComputeCapabilityLabel = new QLabel("Min. Rev. Compute Capability:", this);
    minimumRevisionComputeCapabilityLabel->setObjectName("MinimumRevisionComputeCapabilityLabel");
    QLabel* minimumRevisionComputeCapabilityValueLabel = new QLabel(QString::number(dProp.minor), this);
    hBoxMinimumRevisionComputeCapablity->addWidget(minimumRevisionComputeCapabilityLabel, 0, Qt::AlignLeft);
    hBoxMinimumRevisionComputeCapablity->addWidget(minimumRevisionComputeCapabilityValueLabel, 0, Qt::AlignRight);

    QLabel* maximumRevisionComputeCapabilityLabel = new QLabel("Max. Rev. Compute Capability:", this);
    maximumRevisionComputeCapabilityLabel->setObjectName("MaximumRevisionComputeCapabilityLabel");
    QLabel* maximumRevisionComputeCapabilityValueLabel = new QLabel(QString::number(dProp.major), this);
    hBoxMaximumRevisionComputeCapablity->addWidget(maximumRevisionComputeCapabilityLabel, 0, Qt::AlignLeft);
    hBoxMaximumRevisionComputeCapablity->addWidget(maximumRevisionComputeCapabilityValueLabel, 0, Qt::AlignRight);

    QLabel* textureAlignmentLabel = new QLabel("Texture Alignment:", this);
    textureAlignmentLabel->setObjectName("TextureAlignmentLabel");
    QLabel* textureAlignmentValueLabel = new QLabel(QString::number(dProp.textureAlignment) + " B", this);
    hBoxTextureAlignment->addWidget(textureAlignmentLabel, 0, Qt::AlignLeft);
    hBoxTextureAlignment->addWidget(textureAlignmentValueLabel, 0, Qt::AlignRight);

    QLabel* deviceOverlapLabel = new QLabel("Device Overlap:", this);
    deviceOverlapLabel->setObjectName("DeviceOverlapLabel");
    QLabel* deviceOverlapValueLabel = new QLabel(this);

    if(dProp.deviceOverlap)
    {
        deviceOverlapValueLabel->setText(QString("Yes"));
    }
    else
    {
        deviceOverlapValueLabel->setText(QString("No"));
    }

    hBoxDeviceOverlap->addWidget(deviceOverlapLabel, 0, Qt::AlignLeft);
    hBoxDeviceOverlap->addWidget(deviceOverlapValueLabel, 0, Qt::AlignRight);

    QLabel* streamingMultiprocessorsLabel = new QLabel("Streaming Multiprocessors:", this);
    streamingMultiprocessorsLabel->setObjectName("StreamingMultiprocessorsLabel");
    QLabel* streamingMultiprocessorsValueLabel = new QLabel(QString::number(dProp.multiProcessorCount), this);
    hBoxStreamingMultiprocessors->addWidget(streamingMultiprocessorsLabel, 0, Qt::AlignLeft);
    hBoxStreamingMultiprocessors->addWidget(streamingMultiprocessorsValueLabel, 0, Qt::AlignRight);

    QLabel* kernelRunTimeLimitLabel = new QLabel("Kernels Run Time Limit:", this);
    kernelRunTimeLimitLabel->setObjectName("KernelRunTimeLimitLabel");
    QLabel* kernelRunTimeLimitValueLabel = new QLabel(this);

    if(dProp.kernelExecTimeoutEnabled)
    {
        kernelRunTimeLimitValueLabel->setText(QString("Yes"));
    }
    else
    {
        kernelRunTimeLimitValueLabel->setText(QString("No"));
    }

    hBoxKernelRunTimeLimit->addWidget(kernelRunTimeLimitLabel, 0, Qt::AlignLeft);
    hBoxKernelRunTimeLimit->addWidget(kernelRunTimeLimitValueLabel, 0, Qt::AlignRight);

    QLabel* integratedDeviceLabel = new QLabel("Integrated Device:", this);
    integratedDeviceLabel->setObjectName("IntegratedDeviceLabel");
    QLabel* integratedDeviceValueLabel = new QLabel(this);

    if(dProp.integrated)
    {
        integratedDeviceValueLabel->setText(QString("Yes"));
    }
    else
    {
        integratedDeviceValueLabel->setText(QString("No"));
    }

    hBoxIntegratedDevice->addWidget(integratedDeviceLabel, 0, Qt::AlignLeft);
    hBoxIntegratedDevice->addWidget(integratedDeviceValueLabel, 0, Qt::AlignRight);

    QLabel* mapHostMemLabel = new QLabel("Host Memory Mapping:", this);
    mapHostMemLabel->setObjectName("MapHostMemLabel");
    QLabel* mapHostMemValueLabel = new QLabel(this);

    if(dProp.canMapHostMemory)
    {
        mapHostMemValueLabel->setText(QString("Yes"));
    }
    else
    {
        mapHostMemValueLabel->setText(QString("No"));
    }

    hBoxMapHostMem->addWidget(mapHostMemLabel, 0, Qt::AlignLeft);
    hBoxMapHostMem->addWidget(mapHostMemValueLabel, 0, Qt::AlignRight);

    QLabel* computeModeLabel = new QLabel("Compute Mode:", this);
    computeModeLabel->setObjectName("ComputeModeLabel");
    QLabel* computeModeValueLabel = new QLabel(this);

    switch(dProp.computeMode)
    {
        /*case cudaComputeModeDefault:
        {
            computeModeValueLabel->setText("Default");
            break;
        }

        case cudaComputeModeExclusive:
        {
            computeModeValueLabel->setText("Exclusive");
            break;
        }

        case cudaComputeModeProhibited:
        {
            computeModeValueLabel->setText("Prohibited");
            break;
        }

        default:
        {
            computeModeValueLabel->setText("Unknown");
            break;
        }*/
    }

    hBoxComputeMode->addWidget(computeModeLabel, 0, Qt::AlignLeft);
    hBoxComputeMode->addWidget(computeModeValueLabel, 0, Qt::AlignRight);

    QLabel* concurrentKernelsLabel = new QLabel("Concurrent Kernels:", this);
    concurrentKernelsLabel->setObjectName("ConcurrentKernelsLabel");
    QLabel* concurrentKernelsValueLabel = new QLabel(this);

    if(dProp.concurrentKernels)
    {
        concurrentKernelsValueLabel->setText("Yes");
    }
    else
    {
        concurrentKernelsValueLabel->setText("No");
    }

    hBoxConcurrentKernels->addWidget(concurrentKernelsLabel, 0, Qt::AlignLeft);
    hBoxConcurrentKernels->addWidget(concurrentKernelsValueLabel, 0, Qt::AlignRight);

    QLabel* ECCLabel = new QLabel("ECC:", this);
    ECCLabel->setObjectName("ECCLabel");
    QLabel* ECCValueLabel = new QLabel(this);

    if(dProp.ECCEnabled)
    {
        ECCValueLabel->setText("Yes");
    }
    else
    {
        ECCValueLabel->setText("No");
    }

    hBoxECC->addWidget(ECCLabel, 0, Qt::AlignLeft);
    hBoxECC->addWidget(ECCValueLabel, 0, Qt::AlignRight);

    QLabel* PCIBusIDLabel = new QLabel("PCI Bus ID:", this);
    PCIBusIDLabel->setObjectName("PCIBusIDLabel");
    QLabel* PCIBusIDValueLabel = new QLabel(QString::number(dProp.pciBusID), this);
    hBoxPCIBusID->addWidget(PCIBusIDLabel, 0, Qt::AlignLeft);
    hBoxPCIBusID->addWidget(PCIBusIDValueLabel, 0, Qt::AlignRight);

    QLabel* PCIDeviceLabel = new QLabel("PCI Device ID:", this);
    PCIDeviceLabel->setObjectName("PCIDeviceLabel");
    QLabel* PCIDeviceValueLabel = new QLabel(QString::number(dProp.pciDeviceID), this);
    hBoxPCIDeviceID->addWidget(PCIDeviceLabel, 0, Qt::AlignLeft);
    hBoxPCIDeviceID->addWidget(PCIDeviceValueLabel, 0, Qt::AlignRight);

    QLabel* TCCDriverLabel = new QLabel("TCC Driver:", this);
    TCCDriverLabel->setObjectName("TCCDriverLabel");
    QLabel* TCCDriverValueLabel = new QLabel(this);

    if(dProp.tccDriver)
    {
        TCCDriverValueLabel->setText("Yes");
    }
    else
    {
        TCCDriverValueLabel->setText("No");
    }

    hBoxTCCDriver->addWidget(TCCDriverLabel, 0, Qt::AlignLeft);
    hBoxTCCDriver->addWidget(TCCDriverValueLabel, 0, Qt::AlignRight);

    QLabel* cudaRunTimeVersionLabel = new QLabel("Cuda Run Time Ver.:", this);
    cudaRunTimeVersionLabel->setObjectName("CudaRunTimeVersion");
    QLabel* cudaRunTimeVersionValueLabel = new QLabel(QString::number(rtVer), this);
    hBoxCudaRunTimeVersion->addWidget(cudaRunTimeVersionLabel, 0, Qt::AlignLeft);
    hBoxCudaRunTimeVersion->addWidget(cudaRunTimeVersionValueLabel, 0, Qt::AlignRight);

    QLabel* cudaVersionLabel = new QLabel("Cuda Ver.:", this);
    cudaVersionLabel->setObjectName("CudaVersionLabel");
    QLabel* cudaVersionValueLabel = new QLabel(QString::number(cuVer), this);
    hBoxCudaVersion->addWidget(cudaVersionLabel, 0, Qt::AlignLeft);
    hBoxCudaVersion->addWidget(cudaVersionValueLabel, 0, Qt::AlignRight);

    mainVbox->addLayout(hBoxDeviceName);
    mainVbox->addLayout(hBoxDeviceMemory);
    mainVbox->addLayout(hBoxSharedMemoryPerBlock);
    mainVbox->addLayout(hBoxRegistersPerBlock);
    mainVbox->addLayout(hBoxWarpSize);
    mainVbox->addLayout(hBoxMaxPitch);
    mainVbox->addLayout(hBoxMaxThreadsPerBlock);
    mainVbox->addLayout(hBoxMaxThreadsDimension);
    mainVbox->addLayout(hBoxMaxThreadsDimensionValues);
    mainVbox->addLayout(hBoxMaxGridSize);
    mainVbox->addLayout(hBoxMaxGridSizeValues);
    mainVbox->addLayout(hBoxClockFrq);
    mainVbox->addLayout(hBoxConstMem);
    mainVbox->addLayout(hBoxMinimumRevisionComputeCapablity);
    mainVbox->addLayout(hBoxMaximumRevisionComputeCapablity);
    mainVbox->addLayout(hBoxTextureAlignment);
    mainVbox->addLayout(hBoxDeviceOverlap);
    mainVbox->addLayout(hBoxStreamingMultiprocessors);
    mainVbox->addLayout(hBoxKernelRunTimeLimit);
    mainVbox->addLayout(hBoxIntegratedDevice);
    mainVbox->addLayout(hBoxMapHostMem);
    mainVbox->addLayout(hBoxComputeMode);
    mainVbox->addLayout(hBoxConcurrentKernels);
    mainVbox->addLayout(hBoxECC);
    mainVbox->addLayout(hBoxPCIBusID);
    mainVbox->addLayout(hBoxPCIDeviceID);
    mainVbox->addLayout(hBoxTCCDriver);
    mainVbox->addLayout(hBoxCudaRunTimeVersion);
    mainVbox->addLayout(hBoxCudaVersion);

    setLayout(mainVbox);

    move((QApplication::desktop()->screenGeometry().width() / 2) - (size().width() / 2),
         (QApplication::desktop()->screenGeometry().height() / 2) - (size().height() / 2));
}

CudaGPUInfoWidget::~CudaGPUInfoWidget() {}

/**************************************************************
 **************************************************************
 *
 * Close event..
 *
 **************************************************************/
void CudaGPUInfoWidget::closeEvent(QCloseEvent* event)
{
    QWidget::closeEvent(event);
    deleteLater();
}
