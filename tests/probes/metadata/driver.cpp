// $Id: driver.cpp 2213 2012-08-01 14:05:58Z dfeiock $

#include "mdtest_Metadata.h"

//
// validate_base
//
bool validate_base (void)
{
  // Expected values
  ACE_CString schema =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='OASIS.Test_Probe_Base' />"
  "<xsd:complexType name='OASIS.Test_Probe_Base'>"
  "<xsd:sequence>"
  "<xsd:element name='value_a' type='xsd:int'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  ACE_Utils::UUID uuid  ("28C6948E-A2B4-43E9-ACF7-5BBE71B77C3B");
  ACE_CString type_info = "OASIS.Test_Probe_Base";


  ::OASIS::Test_Probe_Base_Metadata metadata;

  if (metadata.uuid_ != uuid
      || metadata.type_info_ != type_info
      || metadata.schema_ != schema)
   ACE_ERROR_RETURN ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - Unexpected metadata values.\n")),
                      false);

  return true;
}

//
// validate_subclass
//
bool validate_subclass (void)
{
  // Expected values
  ACE_CString schema =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='OASIS.Test_Probe_Subclass' />"
  "<xsd:complexType name='OASIS.Test_Probe_Subclass'>"
  "<xsd:sequence>"
  "<xsd:element name='value_b' type='xsd:int'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  ACE_Utils::UUID uuid ("E5D76992-7D08-485E-AB60-8EDB379652C3");
  ACE_CString type_info = "OASIS.Test_Probe_Subclass";

  ::OASIS::Test_Probe_Subclass_Metadata metadata;

  if (metadata.uuid_ != uuid
      || metadata.type_info_ != type_info
      || metadata.schema_ != schema)
   ACE_ERROR_RETURN ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - Unexpected metadata values.\n")),
                      false);

  return true;
}

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  if (validate_base () && validate_subclass ())
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - test completed successfully\n")));

    return 0;
  }
  return 1;
}
