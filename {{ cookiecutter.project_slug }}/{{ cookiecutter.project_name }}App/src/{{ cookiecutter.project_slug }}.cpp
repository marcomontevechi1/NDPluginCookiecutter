{% if cookiecutter.author != "None" %}
/*
 * Authors: {{ cookiecutter.author }}
 */

{% endif %}
#include <epicsMath.h>

#include <iocsh.h>
#include <epicsExport.h>

#include <{{ cookiecutter.project_slug }}.h>

static const char *driverName = "{{ cookiecutter.project_slug }}";

{{ cookiecutter.project_slug }}::{{ cookiecutter.project_slug }}(const char *portName, int queueSize, int blockingCallbacks,
             const char *NDArrayPort, int NDArrayAddr,
             int maxBuffers, size_t maxMemory,
             int priority, int stackSize)
    : NDPluginDriver(portName,
                     queueSize,
                     blockingCallbacks,
                     NDArrayPort,
                     NDArrayAddr,
                     1, // maxAddr
                     maxBuffers,
                     maxMemory,
                     asynInt32ArrayMask | asynFloat64ArrayMask | asynOctetMask | asynGenericPointerMask,
                     asynInt32ArrayMask | asynFloat64ArrayMask | asynOctetMask | asynGenericPointerMask,
                     0, // asynFlags
                     1, // autoConnect
                     priority,
                     stackSize,
                     1) // maxThreads
{

    createParam({{ cookiecutter.project_name }}MyParamString,  asynParamInt32, &myParam);

    setIntegerParam(myParam, 0);
    callParamCallbacks();

}

void
{{ cookiecutter.project_slug }}::processCallbacks(NDArray *pArray)
{

    // pArray is borrowed reference.  Caller will release()
    // Never modify pArray. If need to modify, create output array insted.
    NDArray *pOutput = NULL;

    NDPluginDriver::beginProcessCallbacks(pArray);

    pOutput = this->pNDArrayPool->copy(pArray, pOutput, false, true, true);
    memset(pOutput->pData, ((epicsInt8*)(pOutput->pData))[0] + 1, pOutput->dataSize);

    asynPrint(pasynUserSelf, ASYN_TRACE_FLOW,
              "%s:%s: Finished processing.\n", this->portName, __PRETTY_FUNCTION__);

    NDPluginDriver::endProcessCallbacks(pOutput, false, true);

}

asynStatus {{ cookiecutter.project_slug }}::writeInt32(asynUser *pasynUser, epicsInt32 value)
{
    int status = 0;
    int function = pasynUser->reason;

    status |= (int)setIntegerParam(function, value);

    if(function < FIRST_{{ cookiecutter.project_slug.upper() }}_PARAM)
        return NDPluginDriver::writeInt32(pasynUser, value);

    else if(function == myParam){
        asynPrint(pasynUserSelf, ASYN_TRACE_FLOW,
              "%s:%s: Modifying myParam.\n", this->portName, __PRETTY_FUNCTION__);
    }

    callParamCallbacks();

    return (asynStatus)status;
}

extern "C" int ND{{ cookiecutter.project_name }}Configure(const char *portName, int queueSize, int blockingCallbacks,
                                const char *NDArrayPort, int NDArrayAddr,
                                int maxBuffers, size_t maxMemory)
{
    {{ cookiecutter.project_slug }} *pPlugin = new {{ cookiecutter.project_slug }}(portName, queueSize, blockingCallbacks, NDArrayPort, NDArrayAddr,
                     maxBuffers, maxMemory, 0, 2000000);

    return pPlugin->start();
}

/* EPICS iocsh shell commands */
static const iocshArg initArg0 = { "portName",iocshArgString};
static const iocshArg initArg1 = { "frame queue size",iocshArgInt};
static const iocshArg initArg2 = { "blocking callbacks",iocshArgInt};
static const iocshArg initArg3 = { "NDArrayPort",iocshArgString};
static const iocshArg initArg4 = { "NDArrayAddr",iocshArgInt};
static const iocshArg initArg5 = { "maxBuffers",iocshArgInt};
static const iocshArg initArg6 = { "maxMemory",iocshArgInt};
static const iocshArg * const initArgs[] = {&initArg0,
                                            &initArg1,
                                            &initArg2,
                                            &initArg3,
                                            &initArg4,
                                            &initArg5,
                                            &initArg6};
static const iocshFuncDef initFuncDef = {"ND{{ cookiecutter.project_name }}Configure",7,initArgs};
static void initCallFunc(const iocshArgBuf *args)
{
    ND{{ cookiecutter.project_name }}Configure(args[0].sval, args[1].ival, args[2].ival,
                     args[3].sval, args[4].ival, args[5].ival,
                     args[6].ival);
}

static void ND{{ cookiecutter.project_name }}Register(void)
{
    iocshRegister(&initFuncDef,initCallFunc);
}

extern "C" {
epicsExportRegistrar(ND{{ cookiecutter.project_name }}Register);
}
