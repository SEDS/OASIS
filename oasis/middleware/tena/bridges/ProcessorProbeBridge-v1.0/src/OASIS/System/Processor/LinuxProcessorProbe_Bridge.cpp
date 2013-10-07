// $Id: LinuxProcessorProbe_Bridge.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "LinuxProcessorProbe_Bridge.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe.h"
#include "oasis/probes/Software_Probe_Header.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/middleware/tena/bridges/Configuration_Exception.h"
#include "ace/Message_Block.h"

#include "OASIS/System/Processor/ProcessorProbe_Bridge.h"

namespace OASIS
{
  namespace System
  {
    namespace Processor
    {
      //
      // _create
      //
      ::OASIS::Software_Probe_Bridge * LinuxProcessorProbe_Bridge::_create (void)
      {
        ::OASIS::Software_Probe_Bridge * bridge = 0;
        ACE_NEW_RETURN (bridge,
                        LinuxProcessorProbe_Bridge (),
                        0);

        return bridge;
      }

      //
      // LinuxProcessorProbe_Bridge
      //
      LinuxProcessorProbe_Bridge::LinuxProcessorProbe_Bridge (void)
      {

      }

      //
      // ~LinuxProcessorProbe_Bridge
      //
      LinuxProcessorProbe_Bridge::~LinuxProcessorProbe_Bridge (void)
      {

      }

      //
      // create_servant
      //
      int LinuxProcessorProbe_Bridge::
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
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_nice_time) (*initializer, "nice_time", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_iowait_time) (*initializer, "iowait_time", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_irq_time) (*initializer, "irq_time", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_soft_irq_time) (*initializer, "soft_irq_time", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_idle_time) (*initializer, "idle_time", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_system_time) (*initializer, "system_time", parent);
        ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_user_time) (*initializer, "user_time", parent);
        this->initialize_metadata (*initializer, einode, inst);

        // We are now ready to create the servant.
        this->servants_[inst.ext_id_.c_str ()] =
          this->factory_->createServant (*initializer, ::TENA::Middleware::Reliable);

        return 0;
      }

      //
      // publish
      //
      int LinuxProcessorProbe_Bridge::
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
        ::OASIS::System::Processor::LinuxProcessorProbe::ServantPtr servant = iter->second;

        if (!servant.isValid ())
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - invalid servant for %s\n"),
                             probe.name_.c_str ()),
                             -1);

        // Instantiate a new updater.
        std::auto_ptr < ::OASIS::System::Processor::LinuxProcessorProbe::PublicationStateUpdater >
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
      int LinuxProcessorProbe_Bridge::
      update (PublicationStateUpdater & updater, ACE_InputCDR & input)
      {
        // Let another bridge does it processing first.
        if (0 != ::OASIS::System::Processor::ProcessorProbe_Bridge::update (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to update base class %s\n"),
                             ACE_TEXT ("::OASIS::System::Processor::ProcessorProbe")),
                             -1);

        // Now, we can extract our contents from the packet.
        using namespace ::OASIS::System::Processor::LinuxProcessorProbe;
        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_nice_time) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage nice_time\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_iowait_time) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage iowait_time\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_irq_time) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage irq_time\n")),
                             -1);

        if (0 != ::OASIS::updater (&PublicationStateUpdater::set_soft_irq_time) (updater, input))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage soft_irq_time\n")),
                             -1);

        return 0;
      }

    }
  }
}
