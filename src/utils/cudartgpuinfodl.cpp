#include "utils/cudartgpuinfodl.hpp"

#include "except/cudartnotfoundexception.hpp"
#include "except/cudartresolveexception.hpp"

CudaRTGPUInfoDL::CudaRTGPUInfoDL()
{
    library.setFileName("cudart");

    if(!library.load())
    {
        throw CudaRTNotFoundException("Cuda Run Time Library not found!");
    }

    cuDriverVer = (CudaDriverVersion)library.resolve("cudaDriverGetVersion");

    if(!cuDriverVer)
    {
        throw CudaRTResolveException(library.errorString().toUtf8().constData());
    }

    cuRTVer = (CudaRunTimeVersion)library.resolve("cudaRuntimeGetVersion");

    if(!cuRTVer)
    {
        throw CudaRTResolveException(library.errorString().toUtf8().constData());
    }

    cuDeviceProp = (CudaDeviceProperties)library.resolve("cudaGetDeviceProperties");

    if(!cuDeviceProp)
    {
        throw CudaRTResolveException(library.errorString().toUtf8().constData());
    }
}

CudaRTGPUInfoDL::~CudaRTGPUInfoDL()
{
    library.unload();
}

int CudaRTGPUInfoDL::getCudaDriverVersion()
{
    int dVer;

    if(cuDriverVer(&dVer) > 0)
    {
        return -1;
    }

    return dVer;
}

int CudaRTGPUInfoDL::getCudaRunTimeVersion()
{
    int rtVer;

    if(cuRTVer(&rtVer) > 0)
    {
        return -1;
    }

    return rtVer;
}

const CudaRTGPUInfoDL::Properties& CudaRTGPUInfoDL::getCudaDeviceProperties()
{
    cuDeviceProp(reinterpret_cast<cudaDeviceProp*>(&properties), 0);
    return properties;
}

bool CudaRTGPUInfoDL::cudaRunTimeDetected()
{
    QLibrary lib("cudart");

    if(!lib.load())
    {
        return false;
    }

    lib.unload();
    return true;
}
