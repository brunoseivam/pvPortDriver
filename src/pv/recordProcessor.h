#ifndef RECORD_PROCESSOR_H
#define RECORD_PROCESSOR_H

#include <pv/pvDatabase.h>

namespace epics { namespace pvPortDriver {

class epicsShareClass RecordProcessor {
public:
    virtual ~RecordProcessor (void) {}
    virtual void process (epics::pvDatabase::PVRecord const *) = 0;
};

}}

#endif
