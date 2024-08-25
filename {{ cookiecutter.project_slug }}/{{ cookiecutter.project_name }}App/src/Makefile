TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

LIBRARY += {{ cookiecutter.project_slug }}

DBD += {{ cookiecutter.project_slug }}.dbd

# headers are not considered public

# Add all the support libraries needed by this IOC
{{ cookiecutter.project_slug }}_LIBS += NDPlugin ADBase asyn

{{ cookiecutter.project_slug }}_SRCS += {{ cookiecutter.project_slug }}.cpp

# Finally link to the EPICS Base libraries
{{ cookiecutter.project_slug }}_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

