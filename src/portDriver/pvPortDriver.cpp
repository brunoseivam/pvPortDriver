#include <pv/pvAccess.h>
#include <pv/pvDatabase.h>

#include "pv/pvPortDriver.h"

using namespace epics::pvDatabase;
using namespace epics::pvAccess;
using namespace std;

namespace epics { namespace pvPortDriver {

PVPortDriver::PVPortDriver(string const & prefix)
: mPrefix(prefix),
  mDatabase(PVDatabase::getMaster()),
  mProvider(getChannelProviderLocal()),
  mMutex()
{}

PVRecordPtr PVPortDriver::findParam (string const & name)
{
    return mDatabase->findRecord(mPrefix + name);
}

void PVPortDriver::process (epics::pvDatabase::PVRecord * const param)
{
    printf("PVPortDriver::process([%s] %s)\n", mProvider->getProviderName().c_str(),
            param->getRecordName().c_str());
}

void PVPortDriver::lock (void)
{
    mMutex.lock();
}

void PVPortDriver::unlock (void)
{
    mMutex.unlock();
}

}}
