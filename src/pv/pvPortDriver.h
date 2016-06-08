/* pvPortDriver.h */
/**
 * Copyright - See the COPYRIGHT that is included with this distribution.
 * EPICS pvData is distributed subject to a Software License Agreement found
 * in file LICENSE that is included with this distribution.
 */
/**
 * @author Bruno Martins
 * @date 2016.03.24
 */
#ifndef PVPORTDRIVER_H
#define PVPORTDRIVER_H

#include <pv/pvDatabase.h>
#include <pv/channelProviderLocal.h>

#include "recordProcessor.h"
#include "scalarParam.h"
#include "enumParam.h"
#include "ndarrayParam.h"

namespace epics { namespace pvPortDriver {

class epicsShareClass PVPortDriver : public RecordProcessor
{
private:
    POINTER_DEFINITIONS(PVPortDriver);
    std::string mPrefix;
    epics::pvDatabase::PVDatabasePtr mDatabase;
    epics::pvDatabase::ChannelProviderLocalPtr mProvider;

protected:
    epics::pvData::Mutex mMutex;

    void lock();
    void unlock();

public:
    PVPortDriver(std::string const & prefix);
    virtual ~PVPortDriver() {}

    template<typename T>
    std::tr1::shared_ptr< ScalarParam<T> >
    createParam (std::string const & name)
    {
        std::string fullName(mPrefix + name);
        std::tr1::shared_ptr< ScalarParam<T> >
            param(ScalarParam<T>::create(fullName, this));

        // Add record to database
        mDatabase->addRecord(param);
        param->start();
        return param;
    }

    template<typename T>
    std::tr1::shared_ptr< ScalarParam<T> > createParam (
            std::string const & name, T value)
    {
        std::tr1::shared_ptr< ScalarParam<T> > param(createParam<T>(name));
        param->put(value);
        return param;
    }

    EnumParamPtr createEnumParam (std::string const & name,
            std::vector<std::string> const & choices)
    {
        std::string fullName(mPrefix + name);
        EnumParamPtr param(EnumParam::create(fullName, choices, this));
        mDatabase->addRecord(param);
        param->start();
        return param;
    }

    NDArrayParamPtr createNDArrayParam (std::string const & name)
    {
        std::string fullName(mPrefix + name);
        NDArrayParamPtr param(NDArrayParam::create(fullName, this));
        mDatabase->addRecord(param);
        param->start();
        return param;
    }

    virtual void process (epics::pvDatabase::PVRecord * const param);

    epics::pvDatabase::PVRecordPtr findParam (std::string const & name);
};

}}

#endif  /* PVPORTDRIVER_H */

