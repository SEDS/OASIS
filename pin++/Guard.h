// -*- C++ -*-

//==============================================================================
/**
 *  @file        Guard.h
 *
 *  $Id: Guard.h 2288 2013-09-19 19:09:57Z hillj $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_GUARD_H_
#define _OASIS_PIN_GUARD_H_

#include "RWMutex.h"

namespace OASIS
{
namespace Pin
{

/**
 * @class Guard
 *
 * Guard for restricting lock ownership to a scope.
 */
template <typename T>
class Guard
{
public:
  /// Default constructor, do not acquire the lock.
  Guard (T & lock);

  /**
   * Locking constructor
   *
   * @param[in]     block     Block when acquiring the lock
   */
  Guard (T & lock, bool block);

  /// Destructor.
  ~Guard (void);

  /// Acquire the lock (blocking)
  void acquire (void);

  /// Try to acquire the lock (non-blocking)
  bool try_acquire (void);

  /// Release the lock
  void release (void);

  /// Test if it is locked
  bool locked (void);

private:
  T & lock_;
};

/**
 * @class Read_Guard
 *
 * Guard for getting read locks
 */
class Read_Guard
{
public:
  /// Default constructor, do not acquire the lock
  Read_Guard (RWMutex & lock);

  /**
   * Locking constructor
   *
   * @param[in]   block     Block when acquiring the lock
   */
  Read_Guard (RWMutex & lock, bool block);

  /// Destructor.
  ~Read_Guard (void);

  /// Acquire the lock (blocking)
  void acquire (void);

  /// Try to acquire the lock (non-blocking)
  bool try_acquire (void);

  /// Release the lock
  void release (void);

  /// Test if it is locked
  bool locked (void);

private:
  RWMutex & lock_;
};

/**
 * @class Write_Guard
 *
 * Guard for getting write locks
 */
class Write_Guard 
{
public:
  /// Default constructor, do not acquire the lock
  Write_Guard (RWMutex & lock);

  /**
   * Locking constructor
   *
   * @param[in]   block     Block when acquiring the lock
   */
  Write_Guard (RWMutex & lock, bool block);

  /// Destructor.
  ~Write_Guard (void);

  /// Acquire the lock (blocking)
  void acquire (void);

  /// Try to acquire the lock (non-blocking)
  bool try_acquire (void);

  /// Release the lock
  void release (void);

  /// Test if it is locked
  bool locked (void);

private:
  RWMutex & lock_;
};

} // namespace OASIS
} // namespace Pin

#include "Guard.inl"

#endif  // _OASIS_PIN_GUARD_H_
