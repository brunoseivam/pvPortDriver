#include <pv/ndarrayParam.h>
#include <pv/ntndarray.h>
#include <pv/pvData.h>
#include <pv/pvDatabase.h>
#include <pv/recordProcessor.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::nt;
using namespace epics::pvPortDriver;

NDArrayParam::NDArrayParam (string const & name, PVStructurePtr const & pvStructure,
        RecordProcessor * processor)
: PVRecord(name, pvStructure), mProcessor(processor) {}

NDArrayParam::~NDArrayParam (void) {}

NDArrayParamPtr NDArrayParam::create (string const & name,
        RecordProcessor * processor)
{
    NTNDArrayPtr array(NTNDArray::createBuilder()->addTimeStamp()->create());
    NDArrayParamPtr record(new NDArrayParam(name, array->getPVStructure(), processor));

    if(!record->init())
        record.reset();

    return record;
}

bool NDArrayParam::init (void)
{
    initPVRecord();
    mArray = NTNDArray::wrap(getPVStructure());
    return true;
}

void NDArrayParam::destroy (void)
{
    PVRecord::destroy();
}

void NDArrayParam::process (void)
{
    if(mProcessor)
        mProcessor->process(this);
}

void NDArrayParam::put (NTNDArrayPtr array)
{
    lock();
    beginGroupPut();

    mArray->getUniqueId()->put(array->getUniqueId()->get());
    mArray->getCompressedDataSize()->put(array->getCompressedDataSize()->get());
    mArray->getUncompressedDataSize()->put(array->getUncompressedDataSize()->get());
    mArray->getValue()->set(array->getValue()->getSelectedIndex(), array->getValue()->get());
    mArray->getDimension()->copy(*array->getDimension());
    mArray->getAttribute()->copy(*array->getAttribute());
    mArray->getDataTimeStamp()->copy(*array->getDataTimeStamp());
    mArray->getTimeStamp()->copy(*array->getTimeStamp());

    endGroupPut();
    unlock();
}

NTNDArrayPtr NDArrayParam::get (void)
{
    return mArray;
}

