#ifndef ENUMPARAM_H
#define ENUMPARAM_H

#include <pv/pvData.h>
#include <pv/pvEnumerated.h>
#include <pv/pvDatabase.h>
#include <pv/recordProcessor.h>

namespace epics { namespace pvPortDriver {

class EnumParam;
typedef std::tr1::shared_ptr<EnumParam> EnumParamPtr;

class epicsShareClass EnumParam :  public epics::pvDatabase::PVRecord
{
private:
    EnumParam (std::string const & name,
            epics::pvData::PVStructurePtr const & pvStructure,
            epics::pvPortDriver::RecordProcessor * processor);

    epics::pvPortDriver::RecordProcessor * mProcessor;
    epics::pvData::PVEnumerated mEnum;

public:
    POINTER_DEFINITIONS(EnumParam);

    ~EnumParam (void);

    static EnumParamPtr create (std::string const & name,
            std::vector<std::string> const & choices,
            epics::pvPortDriver::RecordProcessor * processor);

    bool init (void);
    void destroy (void);
    void process (void);
    void put (epics::pvData::int32 index);
    epics::pvData::int32 get (void);
    std::string getChoice (void);
    void setChoices (std::vector<std::string> const & choices);
};

}}

#endif //ENUMPARAM_H
