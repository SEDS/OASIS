// $Id: Data_Streams_T.cpp 1923 2011-09-22 15:07:33Z hillj $

#include "boost/bind.hpp"

//
// read_value
//
template <typename T>
inline bool read_value (ACE_InputCDR & in, T & value)
{
  in >> value;
  return in.good_bit ();
}

//
// write_value
//
template <typename T>
inline bool write_value (ACE_OutputCDR & out, const T & value)
{
  out << value;
  return out.good_bit ();
}

//
// operator >>
//
template <typename T>
bool operator >> (ACE_InputCDR & in, std::vector <T> & values)
{
  // Read the number of elements in the vector.
  ACE_UINT32 element_count = 0;
  if (!(in >> element_count))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read vector size\n")),
                       false);

  // Update the size of the vector.
  values.resize (element_count);

  // Read all the elements in the vector.
  if (0 != element_count)
    std::for_each (values.begin (),
                   values.end (),
                   boost::bind (&read_value <T>, boost::ref (in), _1));

  return in.good_bit ();
}

//
// operator <<
//
template <typename T>
bool operator << (ACE_OutputCDR & out, const std::vector <T> & values)
{
  // Write the number of elements in the vector.
  if (!(out << values.size ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to write the vector size\n")),
                       false);

  // Write each element in the vector to the stream.
  if (0 != values.size ())
    std::for_each (values.begin (),
                   values.end (),
                   boost::bind (&write_value <T>, boost::ref (out), _1));

  return out.good_bit ();
}
