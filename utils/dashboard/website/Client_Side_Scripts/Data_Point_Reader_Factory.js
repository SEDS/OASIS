/**
* @class Data_Point_Reader_Factory
*
*
*/

//
//Constructor
//
function Data_Point_Reader_Factory()
{

}

//
//get_reader
//
Data_Point_Reader_Factory.prototype.get_reader = function(type)
{
  switch (type)
  {
    case "xsd:long":
      {
        this.create_int64_reader();
        break;
      }

    case "xsd:int":
      {
        this.create_int32_reader();
        break;
      }

    case "xsd:short":
      {
        this.create_int16_reader();
        break;
      }

    case "xsd:byte":
      {
        this.create_int8_reader();
        break;
      }

    case "xsd:unsignedLong":
      {
        return this.create_uint64_reader();
        break;
      }

    case "xsd:unsignedInt":
      {
        this.create_uint32_reader();
        break;
      }

    case "xsd:unsignedShort":
      {
        this.create_uint16_reader();
        break;
      }

    case "xsd:unsignedByte":
      {
        this.create_char_reader();
        break;
      }

    case "xsd:string":
      {
        this.create_string_reader();
        break;
      }
  }
}


//
//
//
Data_Point_Reader_Factory.prototype.create_int8_reader = function()
{
  return new Int8_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_int16_reader = function()
{
  return new Int16_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_int32_reader = function()
{
  return new Int32_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_int64_reader = function()
{
  return new Int64_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_uint8_reader = function()
{
  return new Uint8_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_uint16_reader = function()
{
  return new Uint16_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_uint32_reader = function()
{
  return new Uint32_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_uint64_reader = function()
{
  return new Uint64_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_float32_reader = function()
{
  return new Float32_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_float64_reader = function()
{
  return new Float64_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_char_reader = function()
{
  return new Char_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_string_reader = function()
{
  return new String_Reader();
}

//
//
//
Data_Point_Reader_Factory.prototype.create_uuid_reader = function()
{
  return new Uuid_Reader();
}