# Makefile for the pvPortDriver library

TOP = ..
include $(TOP)/configure/CONFIG

PVPORTDRIVER_SRC = $(TOP)/src


LIBRARY += pvPortDriver

INC += pv/recordProcessor.h
INC += pv/scalarParam.h
INC += pv/enumParam.h
INC += pv/ndarrayParam.h
INC += pv/pvPortDriver.h

include $(PVPORTDRIVER_SRC)/portDriver/Makefile

pvPortDriver_LIBS += nt pvDatabase pvAccess pvData Com 
pvPortDriver_LIBS += $(EPICS_BASE_IOC_LIBS)

# shared library ABI version.
#SHRLIB_VERSION ?= 4.2


include $(TOP)/configure/RULES

