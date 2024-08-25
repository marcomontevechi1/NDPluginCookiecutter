TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this
#DB += xxx.db

DB_INSTALLS += $(ADCORE)/db/ADBase.template
DB_INSTALLS += $(ADCORE)/db/NDArrayBase.template
DB_INSTALLS += $(ADCORE)/db/NDPluginBase.template
DB_INSTALLS += $(ADCORE)/db/NDStdArrays.template

#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

