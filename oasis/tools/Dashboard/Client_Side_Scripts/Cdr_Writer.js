/**
* @struct Cdr_Writer
*
* Binary writer class which comply to Common Data Representation requirements
*/

//
//constructor
//
function Cdr_Writer(arraybuffer, isLittleEndian)
{
  this.data_view_ = new DataView(arraybuffer);
  this.offset_ = 0;
  this.isLittleEndian_ = (typeof isLittleEndian == "undefined") ? false : isLittleEndian;
}

//
//Static Constants
//
Cdr_Writer.SHORT_SIZE = 2;
Cdr_Writer.USHORT_SIZE = 2;
Cdr_Writer.LONG_SIZE = 4;
Cdr_Writer.ULONG_SIZE = 4;
Cdr_Writer.FLOAT_SIZE = 4;
Cdr_Writer.DOUBLE_SIZE = 8;

//
//Cdr_Writer Memeber Functions
//
Cdr_Writer.prototype = {
  //
  //calculate_offset
  //
  calculate_offset: function (size)
  {
    var temp = size - 1;
    this.offset_ = (this.offset_ + temp) & (~temp);
  },
  //
  //write int8
  //
  write_int8: function(value)
  {
    this.data_view_.setInt8(this.offset_++, value);
  },

  //
  //write Uint8
  //
  write_uint8: function(value)
  {
    this.data_view_.setUint8(this.offset_++, value);
  },

  //
  //write Int16
  //
  write_int16: function(value)
  {
    this.calculate_offset (Cdr_Writer.SHORT_SIZE)
    this.data_view_.setInt16(this.offset_, value, this.isLittleEndian_);
    this.offset_ += Cdr_Writer.SHORT_SIZE;
  },

  //
  //write Uint16
  //
  write_uint16: function(value)
  {
    this.calculate_offset(Cdr_Writer.USHORT_SIZE);
    this.data_view_.setUint16(this.offset_, value, this.isLittleEndian_);
    this.offset_ += Cdr_Writer.USHORT_SIZE;
  },

  //
  //write Int32
  //
  write_int32: function(value)
  {
    this.calculate_offset(Cdr_Writer.LONG_SIZE);
    this.data_view_.setInt32(this.offset_, value, this.isLittleEndian_);
    is.offset_ += Cdr_Writer.LONG_SIZE;
  },

  //
  //write UInt32
  //
  write_uint32: function(value)
  {
    this.calculate_offset (Cdr_Writer.ULONG_SIZE);
	this.data_view_.setUint32(this.offset_, value, this.isLittleEndian_);
	this.offset_ += Cdr_Writer.ULONG_SIZE;
  },

  //
  //write Int64
  //
  write_uint64: function(value)
  {
    //TODO: Implementation
  },
  
  //
  //write Float32
  //
  write_float32: function(value)
  {
    this.calculate_offset (Cdr_Writer.FLOAT_SIZE);
    this.data_view_.setFloat32(this.offset_, value, this.isLittleEndian_);
    this.offset_ += Cdr_Writer.FLOAT_SIZE;
  },

  //
  //write Float64
  //
  write_float64: function(value)
  {
    this.calculate_offset (Cdr_Writer.DOUBLE_SIZE);
	this.data_view_.setFloat64(this.offset_, value, this.isLittleEndian_);
    this.offset_ += Cdr_Writer.DOUBLE_SIZE;
  },

  //
  //write char
  //
  write_char: function(value)
  {
    // TODO : Implementation
  },

  //
  //write_char_array
  //
  write_char_array: function(buf, length)
  {
    // TODO : Implementation
  },

  //
  //write string
  //
  write_string: function(buf, length)
  {
    this.write_uint32(length + 1);

    for (var i = 0; i < length; i++)
      this.write_int8 (buf.charCodeAt (i));
	 
	this.write_int8 (0x00);
  },

  //
  //write UUID
  //
  write_uuid: function(uuid)
  {
    // TODO: Implementation is required in future.
  }
}//end_of_Cdr_Writer
