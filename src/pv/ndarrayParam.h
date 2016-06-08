#ifndef NDARRAYPARAM_H
#define NDARRAYPARAM_H

#include <pv/ntndarray.h>
#include <pv/pvData.h>
#include <pv/pvDatabase.h>
#include <pv/recordProcessor.h>

namespace epics { namespace pvPortDriver {

class NDArrayParam;
typedef std::tr1::shared_ptr<NDArrayParam> NDArrayParamPtr;

class epicsShareClass NDArrayParam :  public epics::pvDatabase::PVRecord
{
private:
    NDArrayParam (std::string const & name,
            epics::pvData::PVStructurePtr const & pvStructure,
            epics::pvPortDriver::RecordProcessor * processor);

    epics::pvPortDriver::RecordProcessor * mProcessor;
    epics::nt::NTNDArrayPtr mArray;

public:
    POINTER_DEFINITIONS(NDArrayParam);

    ~NDArrayParam (void);

    static NDArrayParamPtr create (std::string const & name,
            epics::pvPortDriver::RecordProcessor * processor);

    bool init (void);
    void destroy (void);
    void process (void);
    void put (epics::nt::NTNDArrayPtr array);
    epics::nt::NTNDArrayPtr get (void);
};

}}

#endif //NDARRAYPARAM_H
