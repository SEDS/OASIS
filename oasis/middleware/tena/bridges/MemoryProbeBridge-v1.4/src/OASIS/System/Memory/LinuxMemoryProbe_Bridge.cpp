// $Id: LinuxMemoryProbe_Bridge.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "LinuxMemoryProbe_Bridge.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe.h"
#include "oasis/probes/Software_Probe_Header.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/middleware/tena/bridges/Configuration_Exception.h"

#include "OASIS/System/Memory/MemoryProbe_Bridge.h"

namespace OASIS
{
  namespace System
  {
    namespace Memory
    {
      //
      // _create
      //
      ::OASIS::Software_Probe_Bridge * LinuxMemoryProbe_Bridge::_create (void)
      {
        ::OASIS::Software_Probe_Bridge * bridge = 0;
        ACE_NEW_RETURN (bridge,
                        LinuxMemoryProbe_Bridge (),
                        0);

        return bridge;
      }

      //
      // LinuxMemoryProbe_Bridge
      //
      LinuxMemoryProbe_Bridge::LinuxMemoryProbe_Bridge (void)
      {

      }

      //
      // ~LinuxMemoryProbe_Bridge
      //
      LinuxMemoryProbe_Bridge::~LinuxMemoryProbe_Bridge (void)
      {

      }

      //
      // create_servant
      //
      int LinuxMemoryProbe_Bridge::
      create_servant (const ACE_Utils::UUID & einode,
                      const ::OASIS::DAC::Software_Probe_Instance & inst)
      {
        // Make sure there is no servant already associated with this // instance.
        if (this->servants_.find (inst.ext_id_.c_str ()) != this->servants_.end ())
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - servant already exist for %s\n"),
                             inst.ext_id_.c_str ()),
                             -1);

        // Create the initializer for the new servant.
        std::auto_ptr < sdo_type::PublicationStateInitializer > initializer (this->factory_->createInitializer ());

        // Initialize the initial value trunk
        OASIS::Configuration_Member_Container * parent = 0;
        try
        {
          parent = &this->group_[inst.ext_id_];
        }
        catch (Invalid_Child & ex)
        {
          parent = 0;
        }

        // Initialize software probe bridge attributes.
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_buffers) (*initializer, "buffers", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_swap_cache) (*initializer, "swap_cache", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_inactive) (*initializer, "inactive", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_active) (*initializer, "active", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_high_total) (*initializer, "high_total", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_high_free) (*initializer, "high_free", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_low_total) (*initializer, "low_total", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_low_free) (*initializer, "low_free", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_swap_total) (*initializer, "swap_total", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_swap_free) (*initializer, "swap_free", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_dirty) (*initializer, "dirty", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_write_back) (*initializer, "write_back", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_virtual_chunk) (*initializer, "virtual_chunk", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_physical_memory_avail) (*initializer, "physical_memory_avail", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_physical_memory_total) (*initializer, "physical_memory_total", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_system_cache) (*initializer, "system_cache", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_commit_limit) (*initializer, "commit_limit", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_commit_total) (*initializer, "commit_total", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_virtual_total) (*initializer, "virtual_total", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_virtual_used) (*initializer, "virtual_used", parent);
        this->initialize_metadata (*initializer, einode, inst);

        // We are now ready to create the servant.
        this->servants_[inst.ext_id_.c_str ()] =
          this->factory_->createServant (*initializer, ::TENA::Middleware::Reliable);

        return 0;
      }

      //
      // publish
      //
      int LinuxMemoryProbe_Bridge::
      publish (const ::OASIS::DAC::Data_Packet & packet)
      {
        // Extract the base contents of the packet.
        OASIS::Software_Probe_Header probe;
        probe.recall (packet.probe_data (),
                      packet.probe_data_length (),
                      packet.byte_order ());

        // Locate the servant for this software probe instance.
        ServantPtr_Map::const_iterator iter =
          this->servants_.find (probe.name_);

        if (iter == this->servants_.end ())
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - servant does not exist for %s\n"),
                             probe.name_.c_str ()),
                             -1);

        // Locate the probe in the mapping.
        ::OASIS::System::Memory::LinuxMemoryProbe::ServantPtr servant = iter->second;

        if (!servant.isValid ())
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - invalid servant for %s\n"),
                             probe.name_.c_str ()),
                             -1);

        // Instantiate a new updater.
        std::auto_ptr < ::OASIS::System::Memory::LinuxMemoryProbe::PublicationStateUpdater >
          updater (servant->createUpdater ());

        // Update the servant values.
        Software_Probe_Data_Preparer prep (packet.probe_data (),
                                           packet.probe_data_length ());
        ACE_InputCDR input (prep.message_block (),
                            packet.byte_order ());

        if (0 != this->update (*updater, input))
          return -1;

        // We are now ready to commit the updater.
        servant->commitUpdater (updater);
        return 0;
      }

      //
      // update
      //
      int LinuxMemoryProbe_Bridge::
      update (PublicationStateUpdater & updater, ACE_InputCDR & input)
      {
        // Let another bridge does it processing first.
        if (0 != ::OASIS::System::Memory::MemoryProbe_Bridge::update (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to update base class %s\n"),
                             ACE_TEXT ("::OASIS::System::Memory::MemoryProbe")),
                             -1);

        // Now, we can extract our contents from the packet.
        using namespace ::OASIS::System::Memory::LinuxMemoryProbe;
        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_buffers) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage buffers\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_swap_cache) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage swap_cache\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_inactive) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage inactive\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_active) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage active\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_high_total) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage high_total\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_high_free) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage high_free\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_low_total) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage low_total\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_low_free) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage low_free\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_swap_total) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage swap_total\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_swap_free) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage swap_free\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_dirty) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage dirty\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_write_back) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage write_back\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_virtual_chunk) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage virtual_chunk\n")),
                             -1);

        return 0;
      }

    }
  }
}
