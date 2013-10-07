// $Id: Analog_TemperatureProbe_Impl.cpp 2233 2013-01-30 18:33:54Z dfeiock $

#include "Analog_TemperatureProbe_Impl.h"

#include "ace/ARGV.h"
#include "ace/CORBA_macros.h"
#include "ace/Get_Opt.h"

extern "C" {
#include "twl4030-madc.h"
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>


namespace OASIS
{
namespace HardwareProbes
{
namespace Temperature
{

//
// create_MemoryProbe_Impl_Factory
//
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_IMPL (create_OASIS_HardwareProbes_Temperature_AnalogTemperatureProbe_Impl_Factory,
                                          AnalogTemperatureProbe_Impl_Factory);

//
// AnalogTemperatureProbe_Impl
//
AnalogTemperatureProbe_Impl::AnalogTemperatureProbe_Impl (void)
 : temperature_correction_ (0.0),
   fd_ (0),
   channel_ (0),
   debug_ (false)
{
}

//
// ~AnalogTemperatureProbe_Impl
//
AnalogTemperatureProbe_Impl::~AnalogTemperatureProbe_Impl (void)
{
}

int AnalogTemperatureProbe_Impl::read_channel(void)
{
  int ret;
  struct twl4030_madc_user_parms param;
  double voltage;
  float temperature;
  temperature = 0;

  memset(&param, 0, sizeof(param));

  param.channel = this->channel_;
  param.average = 1;  //smooth out the value by averaging it.

  ret = ioctl(this->fd_, TWL4030_MADC_IOCX_ADC_RAW_READ, &param);

  if (ret < 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - ioctl error: %q\n"),
                       ret),
                       -1);

  if (param.status == -1)
     ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - madc[%d]: status = -1\n"),
                       this->channel_),
                       -1);
  else
  {
    /* 10 bit ADC, reference voltage 2.88v */
    voltage = (param.result * 2.88) / 1024.0;

    // Vmin = .25, Vmax = 1.75, so subtract .25 from the reading
    // Tmin=-40 Tmax = 125 range is (125+40 = 165), subtract 40 from the solution
    this->temperatureCelcius ((( (voltage-0.25) * (165.0/1.75)) - 40.0 ) + this->temperature_correction_);
  }

  return 0;
}

int AnalogTemperatureProbe_Impl::init (const char * params, const char * name)
{
  if (0 != TemperatureProbeImpl::init (params, name))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - Failed to parse command-line\n")),
                       -1);
  if (0 != this->parse_args (params))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - Failed to parse command-line\n")),
                       -1);

  //TODO: make this read the args.  Also set the date.
  this->channel_ = 5;

  if (!this->debug_)
  {
    this->fd_ = open("/dev/twl4030-madc", O_RDWR | O_NONBLOCK, 0);
    if (this->fd_ < 0)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - Unable to open /dev/twl4030-madc\n")),
                         -1);
  }
  return 0;
}

int AnalogTemperatureProbe_Impl::fini (void)
{
  if (this->fd_ > 0)
    close (this->fd_);

  return 0;
}


//
// handle_collect_data
//
int AnalogTemperatureProbe_Impl::handle_collect_data (void)
{
  if (!this->debug_)
  {
    if (this->fd_ > 0)
      if (0 != this->read_channel ())
       ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - Error collecting temperature probe data\n")),
                         -1);
  }
  else
    this->temperatureCelcius (37.5);

  return 0;
}

//
// parse_args
//
int AnalogTemperatureProbe_Impl::parse_args (const char * args)
{
  // Conver the command string into a vector of commands.
  ACE_ARGV_T <char> argv (args);
  const char * optargs = "d";

  // Parse the command-line options.
  ACE_Get_Opt get_opt (argv.argc (), argv.argv (), optargs, 0);
  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);

  int opt = 0;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("debug", get_opt.long_option ()))
        this->debug_ = true;
        break;

    case 'd':
      this->debug_ = true;
      break;
    }
  }

  return 0;
}



}
}
}
