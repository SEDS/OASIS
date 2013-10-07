// $Id: Software_Probe_Bridge_T.inl 2135 2012-02-16 15:39:18Z dfeiock $
// -*- C++ -*-

namespace OASIS
{

//
// initialize_t
//
template <typename T, typename P1>
initialize_t <T, P1>::initialize_t (FUNC_PTR funcptr)
: funcptr_ (funcptr)
{

}

//
// operator ()
//
template <typename T, typename P1>
OASIS_INLINE
bool initialize_t <T, P1>::operator () (T & t)
{
  (t.*this->funcptr_) (oasis_initial_value_t <P1>::result_type);
  return true;
}

//
// initialize
//
template <typename T, typename P1>
initialize_t <T, P1> initialize (void (T::*func) (P1))
{
  return initialize_t <T, P1> (func);
}

//
// initialize_t
// Specialized for ::std::string
//
template <typename T>
initialize_t <T, const ::std::string &>::initialize_t (FUNC_PTR funcptr)
: funcptr_ (funcptr)
{

}

//
// operator ()
// Specialized for ::std::string
//
template <typename T>
OASIS_INLINE
bool initialize_t <T, const ::std::string &>::operator () (T & t)
{
  (t.*this->funcptr_) (oasis_initial_value_t <const ::std::string &>::result_type);
  return true;
}

//
// initialize
// Specialized for ::std::string
//
template <typename T>
initialize_t <T, const ::std::string &> initialize (void (T::*func) (const ::std::string &))
{
  return initialize_t <T, const ::std::string &> (func);
}

//
// Software_Probe_Bridge
//
template <typename SDO>
OASIS_INLINE
Software_Probe_Bridge_T <SDO>::Software_Probe_Bridge_T (void)
{

}

//
// ~Software_Probe_Bridge
//
template <typename SDO>
OASIS_INLINE
Software_Probe_Bridge_T <SDO>::~Software_Probe_Bridge_T (void)
{

}

//
// updater_t
//
template <typename T, typename P1>
OASIS_INLINE
updater_t <T, P1>::updater_t (FUNC_PTR funcptr)
: funcptr_ (funcptr)
{

}

//
// updater_t
// Specialized for std::string
//
template <typename T>
OASIS_INLINE
updater_t <T, const ::std::string &>::updater_t (FUNC_PTR funcptr)
: funcptr_ (funcptr)
{

}

//
// updater
//
template <typename T, typename P1>
OASIS_INLINE
updater_t <T, P1> updater (void (T::*func) (P1))
{
  return updater_t <T, P1> (func);
}

//
// updater
// Specializaed for std::string
//

template <typename T, typename P1>
OASIS_INLINE
updater_t <T, const ::std::string &> updater (void (T::*func) (const ::std::string &))
{
  return updater_t <T, const ::std::string &> (func);
}

}
