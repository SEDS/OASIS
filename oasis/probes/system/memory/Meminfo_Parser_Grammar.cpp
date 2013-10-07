// $Id: Meminfo_Parser_Grammar.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "MemoryProbeImpl.h"
#include "boost/spirit/include/phoenix_core.hpp"
#include "boost/spirit/include/phoenix_operator.hpp"
#include "boost/spirit/include/phoenix_object.hpp"
#include "boost/spirit/include/phoenix_fusion.hpp"
#include "boost/spirit/include/phoenix_bind.hpp"

namespace OASIS
{
namespace System
{
namespace Memory
{
  //
  // Meminfo_Parser_Grammar
  //
  template <typename IteratorT, typename SpaceT>
  Meminfo_Parser_Grammar <IteratorT, SpaceT>::Meminfo_Parser_Grammar (void)
    : Meminfo_Parser_Grammar::base_type (spec_)
  {
    namespace qi = boost::spirit::qi;
    namespace phoenix = boost::phoenix;

    // Define the values in the /proc/meminfo. It would be worth knowing
    // if the order of the metrics is different for each platform. If this
    // is the case, the we may have to define another rule for allowing
    // the OR-ing (or selection) of each metric. Finally, the metrics that
    // are not stored are omitted (i.e., marked with the qi::omit [] tag.
    this->spec_ = *this->metric_ (qi::_r1);

    this->metric_ =
      (qi::lit ("MemTotal:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::physical_memory_total, qi::_r1, qi::_1)]) |
      (qi::lit ("MemFree:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::physical_memory_avail, qi::_r1, qi::_1)]) |
      (qi::lit ("Buffers:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::buffers, qi::_r1, qi::_1)]) |
      (qi::lit ("Cached:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::system_cache, qi::_r1, qi::_1)]) |
      (qi::lit ("SwapCached:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::swap_cache, qi::_r1, qi::_1)]) |
      (qi::lit ("Active:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::active, qi::_r1, qi::_1)]) |
      (qi::lit ("Inactive:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::inactive, qi::_r1, qi::_1)]) |
      (qi::lit ("HighTotal:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::high_total, qi::_r1, qi::_1)]) |
      (qi::lit ("HighFree:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::high_free, qi::_r1, qi::_1)]) |
      (qi::lit ("LowTotal:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::low_total, qi::_r1, qi::_1)]) |
      (qi::lit ("LowFree:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::low_free, qi::_r1, qi::_1)]) |
      (qi::lit ("SwapTotal:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::swap_total, qi::_r1, qi::_1)]) |
      (qi::lit ("SwapFree:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::swap_free, qi::_r1, qi::_1)]) |
      (qi::lit ("Dirty:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::dirty, qi::_r1, qi::_1)]) |
      (qi::lit ("Writeback:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::write_back, qi::_r1, qi::_1)]) |
      (qi::lit ("CommitLimit:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::commit_limit, qi::_r1, qi::_1)]) |
      (qi::lit ("Committed_AS:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::commit_total, qi::_r1, qi::_1)]) |
      (qi::lit ("VmallocTotal:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::virtual_total, qi::_r1, qi::_1)]) |
      (qi::lit ("VmallocUsed:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::virtual_used, qi::_r1, qi::_1)]) |
      (qi::lit ("VmallocChunk:") >> this->kilobytes_[phoenix::bind (&LinuxMemoryProbeImpl::virtual_chunk, qi::_r1, qi::_1)]) |

      // Generic catch all for any metric found which we are not setting on the LinuxMemoryProbe
      (qi::ascii::char_);

    this->value_ %= qi::ulong_long;

    this->kilobytes_ %= qi::ulong_long >> qi::lit ("kB");
  }

}
}
}
