#include <pv/enumParam.h>
#include <pv/ntenum.h>
#include <pv/pvData.h>
#include <pv/pvDatabase.h>
#include <pv/recordProcessor.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::nt;
using namespace epics::pvPortDriver;

EnumParam::EnumParam (string const & name, PVStructurePtr const & pvStructure,
        RecordProcessor * processor)
: PVRecord(name, pvStructure), mProcessor(processor) {}

EnumParam::~EnumParam (void) {}

EnumParamPtr EnumParam::create (string const & name,
        vector<string> const & choices, RecordProcessor * processor)
{
    NTEnumPtr e(NTEnum::createBuilder()->addTimeStamp()->create());
    EnumParamPtr param(new EnumParam(name, e->getPVStructure(), processor));

    if(!param->init())
        param.reset();
    else
        param->setChoices(choices);

    return param;
}

bool EnumParam::init (void)
{
    initPVRecord();
    NTEnumPtr ntEnum(NTEnum::wrap(getPVStructure()));
    return mEnum.attach(ntEnum->getValue());
}

void EnumParam::destroy (void)
{
    PVRecord::destroy();
}

void EnumParam::process (void)
{
    if(mProcessor)
        mProcessor->process(this);
}

void EnumParam::put (int32 index)
{
    mEnum.setIndex(index);
}

int32 EnumParam::get (void)
{
    return mEnum.getIndex();
}

string EnumParam::getChoice (void)
{
    return mEnum.getChoice();
}

void EnumParam::setChoices (vector<string> const & choices)
{
    mEnum.setChoices(choices);
}




