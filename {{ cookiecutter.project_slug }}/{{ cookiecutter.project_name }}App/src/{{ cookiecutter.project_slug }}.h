{% if cookiecutter.author != "None" %}
/*{{ cookiecutter.project_slug.upper() }}_H
 *
 * Authors: {{ cookiecutter.author }}
 *
 */
{% endif %}
#pragma once

#include <cstring>

#include <epicsTypes.h>
#include <shareLib.h>

#include "NDPluginDriver.h"

/* Param definitions */
class epicsShareClass {{ cookiecutter.project_slug }} : public NDPluginDriver {
public:
    {{ cookiecutter.project_slug }}(const char *portName, int queueSize, int blockingCallbacks,
                 const char *NDArrayPort, int NDArrayAddr,
                 int maxBuffers, size_t maxMemory,
                 int priority, int stackSize);

    virtual void processCallbacks(NDArray *pArray);
    virtual asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);

protected:

    int myParam;
    #define FIRST_{{ cookiecutter.project_slug.upper() }}_PARAM myParam

};

// Example parameter.
#define {{ cookiecutter.project_name }}MyParamString      "MY_PARAM"
