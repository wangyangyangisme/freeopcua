/// @author Alexander Rykovanov 2011
/// @email rykovanov.as@gmail.com
/// @brief Io Manager Addon implementation
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at 
/// http://www.gnu.org/licenses/lgpl.html)
///

#include "manager_impl.h"

#include <opc/managers/io_manager/factory.h>
#include <opc/managers/io_manager/id.h>
#include <opc/managers/io_manager/manager.h>
#include <opc/common/addons_core/addon.h>

namespace
{
  using namespace InputOutputManager;
  
  // Realization of addon
  class RequestManagerAddon 
    : public RequestManager
    , public Common::Addon
  {
  public:
    RequestManagerAddon()
      : Impl(CreateRequestManager().release())
    {
    }
  public: // InputOutput::RrequestManager
    virtual void RegisterDeviceManager(DeviceManager::Manager::SharedPtr manager)
    {
      GetImpl().RegisterDeviceManager(manager);
    }
    
    virtual void UnregisterDeviceManager(DeviceManager::Manager::SharedPtr manager)
    {
      GetImpl().UnregisterDeviceManager(manager);
    }
    
    virtual ReadRequest::UniquePtr CreateReadRequest(const std::set<Common::ObjectID>& ids) const
    {
      return GetImpl().CreateReadRequest(ids);
    }
    
    virtual WriteRequest::UniquePtr CreateWriteRequest(const std::set<Common::ObjectID>& ids) const
    {
      return GetImpl().CreateWriteRequest(ids);
    }

  public:  // Common::Addon
    virtual void Initialize(Common::AddonsManager&, const Common::AddonParameters&)
    {
    }

    virtual void Stop()
    {
    }
    
  private:
    RequestManager& GetImpl() const
    {
      return *Impl;
    }
    
  private:
    const RequestManager::UniquePtr Impl;
  };


  class RequestManagerFactory : public Common::AddonFactory
  {
  public:
    virtual Common::Addon::UniquePtr CreateAddon()
    {
      return Common::Addon::UniquePtr(new RequestManagerAddon());
    }
  };
} // namespace

Common::AddonFactory::UniquePtr InputOutputManager::CreateAddonFactory()
{
  return Common::AddonFactory::UniquePtr(new RequestManagerFactory());
}

