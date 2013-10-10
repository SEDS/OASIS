// -*- C++ -*-
// $Id: RWMutex.inl 2288 2013-09-19 19:09:57Z hillj $

namespace OASIS
{
namespace Pin
{

inline
RW_Mutex::RW_Mutex (void)
: read_lock_ (false),
  write_lock_ (false)
{
  PIN_RWMutexInit (&this->mutex_);
}

inline
RW_Mutex::~RW_Mutex (void)
{
  PIN_RWMutexFini (&this->mutex_);
}

inline
void RW_Mutex::acquire_read (void)
{
  PIN_RWMutexReadLock (&this->mutex_);
  this->read_lock_ = true;
}

inline
void RW_Mutex::acquire_write (void)
{
  PIN_RWMutexWriteLock (&this->mutex_);
  this->write_lock_ = true;
}

inline
bool RW_Mutex::try_acquire_read (void)
{
  this->read_lock_ = PIN_RWMutexTryReadLock (&this->mutex_);
  return this->read_lock_;
}

inline
bool RW_Mutex::try_acquire_write (void)
{
  this->write_lock_ = PIN_RWMutexTryWriteLock (&this->mutex_);
  return this->write_lock_;
}

inline
void RW_Mutex::release (void)
{
  PIN_RWMutexUnlock (&this->mutex_);
  this->write_lock_ = false;
  this->read_lock_ = false;
}

inline
bool RW_Mutex::is_locked_read (void)
{
  return this->read_lock_;
}

inline
bool RW_Mutex::is_locked_write (void)
{
  return this->write_lock_;
}

} // namespace OASIS
} // namespace Pin
