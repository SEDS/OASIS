#include "Metric_Cursor_i.h"

namespace OASIS
{

//
// Metric_Cursor_i
//
Metric_Cursor_i::
Metric_Cursor_i (ADBC::SQLite::Query * query,
                 ADBC::SQLite::Record * record)
: query_ (query),
  record_ (record)
{
}

//
// ~Metric_Cursor_i
//
Metric_Cursor_i::~Metric_Cursor_i ()
{
  if (this->query_)
    delete this->query_;
}

//
// advance
//
void Metric_Cursor_i::advance (void)
{
  this->record_->advance ();
}

//
// is_done
//
bool Metric_Cursor_i::is_done (void)
{
  return this->record_->done ();
}

//
// get_data_size
//
::CORBA::ULong Metric_Cursor_i::get_data_size ()
{
  unsigned long size = 0;
  this->record_->get_data (0, size);
  return size;
}

}