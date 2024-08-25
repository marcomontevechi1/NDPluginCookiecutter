#!../../bin/linux-x86_64/test

#- You may have to change test to something else
#- everywhere it appears in this file

< envPaths

epicsEnvSet("PREFIX", "TEST:")
epicsEnvSet("PORT", "SIM")
epicsEnvSet("PLUGIN_PORT", "{{ cookiecutter.project_name }}")
epicsEnvSet("EPICS_DB_INCLUDE_PATH", "$(TOP)/db")

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/test.dbd"
test_registerRecordDeviceDriver pdbbase

simDetectorConfig("$(PORT)", 255, 255, 1, 100, 0)
dbLoadRecords("$(ADSIMDETECTOR)/db/simDetector.template","P=$(PREFIX),R=cam:,PORT=$(PORT),ADDR=0,TIMEOUT=1")

ND{{ cookiecutter.project_name }}Configure("$(PLUGIN_PORT)", 20, 0, "$(PORT)", 0, 0, 0)
dbLoadRecords("{{ cookiecutter.project_slug }}.template", "P=$(PREFIX),R={{ cookiecutter.project_name }}:,PORT=$(PLUGIN_PORT),ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT)")

NDStdArraysConfigure("Image1", 20, 0, "$(PORT)", 0, 0, 0, 0, 0, 5)
dbLoadRecords("NDStdArrays.template", "P=$(PREFIX),R=image1:,PORT=Image1,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT),TYPE=Int8,FTVL=UCHAR,NELEMENTS=12000000")

NDStdArraysConfigure("Image2", 20, 0, "$(PORT)", 0, 0, 0, 0, 0, 5)
dbLoadRecords("NDStdArrays.template", "P=$(PREFIX),R=image2:,PORT=Image2,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PLUGIN_PORT),TYPE=Int8,FTVL=UCHAR,NELEMENTS=12000000")

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncxxx,"user=marco"
