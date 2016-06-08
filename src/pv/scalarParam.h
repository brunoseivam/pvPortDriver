#ifndef SCALARPARAM_H
#define SCALARPARAM_H

#include <pv/ntscalar.h>
#include <pv/pvData.h>
#include <pv/pvDatabase.h>
#include <pv/recordProcessor.h>

namespace epics { namespace pvPortDriver {

template<typename T>
class ScalarParam;

template<typename T>
class epicsShareClass ScalarParam : public epics::pvDatabase::PVRecord
{
private:
    ScalarParam (std::string const & name, epics::pvData::PVStructurePtr const & pvStructure,
            epics::pvPortDriver::RecordProcessor * processor)
    : PVRecord(name, pvStructure), mProcessor(processor) {}

    epics::pvPortDriver::RecordProcessor * mProcessor;
    epics::nt::NTScalarPtr mScalar;

    typedef typename epics::pvData::PVScalarValue<T>::shared_pointer PVTPtr;
    PVTPtr mValue;

public:
    POINTER_DEFINITIONS(ScalarParam);

    ~ScalarParam (void) {}

    static std::tr1::shared_ptr< ScalarParam<T> > create (std::string const & name,
            epics::pvPortDriver::RecordProcessor * processor)
    {
        typedef epics::pvData::PVScalarValue<T> PVT;
        epics::nt::NTScalarPtr scalar(epics::nt::NTScalar::createBuilder()->value(PVT::typeCode)->create());
        std::tr1::shared_ptr< ScalarParam<T> > param(new ScalarParam<T>(name, scalar->getPVStructure(), processor));

        if(!param->init())
            param.reset();

        return param;
    }

    bool init (void)
    {
        initPVRecord();
        mScalar = epics::nt::NTScalar::wrap(getPVStructure());
        mValue = mScalar->getValue<epics::pvData::PVScalarValue<T> >();
        return true;
    }

    void destroy (void)
    {
        PVRecord::destroy();
    }

    void process (void)
    {
        if(mProcessor)
            mProcessor->process(this);
    }

    void put (T value)
    {
        mValue->put(value);
    }

    T get (void)
    {
        return mValue->get();
    }
};

typedef ScalarParam<epics::pvData::boolean> BooleanParam;
typedef ScalarParam<epics::pvData::uint8>   UByteParam;
typedef ScalarParam<epics::pvData::int8>    ByteParam;
typedef ScalarParam<epics::pvData::uint16>  UShortParam;
typedef ScalarParam<epics::pvData::int16>   ShortParam;
typedef ScalarParam<epics::pvData::uint32>  UIntParam;
typedef ScalarParam<epics::pvData::int32>   IntParam;
typedef ScalarParam<epics::pvData::uint64>  ULongParam;
typedef ScalarParam<epics::pvData::int64>   LongParam;
typedef ScalarParam<float>                  FloatParam;
typedef ScalarParam<double>                 DoubleParam;
typedef ScalarParam<std::string>            StringParam;

typedef std::tr1::shared_ptr<BooleanParam>  BooleanParamPtr;
typedef std::tr1::shared_ptr<UByteParam>    UByteParamPtr;
typedef std::tr1::shared_ptr<ByteParam>     ByteParamPtr;
typedef std::tr1::shared_ptr<UShortParam>   UShortParamPtr;
typedef std::tr1::shared_ptr<ShortParam>    ShortParamPtr;
typedef std::tr1::shared_ptr<UIntParam>     UIntParamPtr;
typedef std::tr1::shared_ptr<IntParam>      IntParamPtr;
typedef std::tr1::shared_ptr<ULongParam>    ULongParamPtr;
typedef std::tr1::shared_ptr<LongParam>     LongParamPtr;
typedef std::tr1::shared_ptr<FloatParam>    FloatParamPtr;
typedef std::tr1::shared_ptr<DoubleParam>   DoubleParamPtr;
typedef std::tr1::shared_ptr<StringParam>   StringParamPtr;

}}

#endif
