/**
* @struct Cdr_Reader
*
* Binary reader class which comply to Common Data Representation requirements
*/

//
//constructor
//
function Cdr_Reader(arraybuffer, isLittleEndian)
{
  this.data_view_ = new DataView(arraybuffer);
  this.offset_ = 0;
  this.isLittleEndian_ = (typeof isLittleEndian == "undefined") ? false : isLittleEndian;
}

//
//Static Constants
//
Cdr_Reader.SHORT_SIZE = 2;
Cdr_Reader.USHORT_SIZE = 2;
Cdr_Reader.LONG_SIZE = 4;
Cdr_Reader.ULONG_SIZE = 4;
Cdr_Reader.FLOAT_SIZE = 4;
Cdr_Reader.DOUBLE_SIZE = 8;
Cdr_Reader.LONG_LONG_SIZE = 8;

//
//Cdr_Reader Memeber Functions
//
Cdr_Reader.prototype = {
  //
  //calculate_offset
  calculate_offset: function (size)
  {
	var temp = size - 1;
    this.offset_ = (this.offset_ + temp) & (~temp);
  },
  //
  //
  //read int8
  //
  read_int8: function()
  {
    return this.data_view_.getInt8(this.offset_++);
  },

  //
  //read Uint8
  //
  read_uint8: function()
  {
    return this.data_view_.getUint8(this.offset_++);
  },

  //
  //read Int16
  //
  read_int16: function()
  {
	this.calculate_offset (Cdr_Reader.SHORT_SIZE);
    var short_val = this.data_view_.getInt16(this.offset_, this.isLittleEndian_);
    this.offset_ += Cdr_Reader.SHORT_SIZE;

    return short_val;
  },

  //
  //read Uint16
  //
  read_uint16: function()
  {
    this.calculate_offset (Cdr_Reader.USHORT_SIZE);
    var ushort_val = this.data_view_.getUint16(this.offset_, this.isLittleEndian_);
    this.offset_ += Cdr_Reader.USHORT_SIZE;

    return ushort_val;
  },

  //
  //read Int32
  //
  read_int32: function()
  {
    this.calculate_offset (Cdr_Reader.LONG_SIZE);
    var long_val = this.data_view_.getInt32(this.offset_, this.isLittleEndian_);
    this.offset_ += Cdr_Reader.LONG_SIZE;

    return long_val;
  },

  //
  //read UInt32
  //
  read_uint32: function()
  {
    this.calculate_offset (Cdr_Reader.ULONG_SIZE);
    var ulong_val = this.data_view_.getUint32(this.offset_, this.isLittleEndian_);
    this.offset_ += Cdr_Reader.ULONG_SIZE;

    return ulong_val;
  },

  //
  //read Int64
  //
  read_uint64: function()
  {
    //2^53 = 00000000 00100000 00000000 00000000 00000000 00000000 00000000 00000000
                    //11111111 11111111 11111110 01010110 11110100 01110000 00000000
    //     = 9007199254740992
    // is the maximum value you can represent in JavaScript.

    //reading each byte seperatly of 8byte number
	this.calculate_offset (Cdr_Reader.LONG_LONG_SIZE);
    var b0 = this.read_uint8();
    var b1 = this.read_uint8();
    var b2 = this.read_uint8();
    var b3 = this.read_uint8();
    var b4 = this.read_uint8();
    var b5 = this.read_uint8();

    // first two bits of b6 has to be 00
    var b6 = this.read_uint8();

    // b7 has to be 00000000
    var b7 = this.read_uint8();

    if (this.isLittleEndian_)
    {
      var number = ((b6 * Math.pow(2, 48)) + (b5 * Math.pow(2, 40)) + (b4 * Math.pow(2, 32)) +
                    (b3 * Math.pow(2, 24)) + (b2 * Math.pow(2, 16)) + (b1 * Math.pow(2, 8)) +
                    b0);
    }
    else
    {
      // TODO : Implementation for big-endian is necessary.
      //        Logic for swiping bytes needs to be done while
      //        calculating the return value.
    }
    if (number > 9007199254740992)
      return "NaN";

    return number;
  },
  //
  //read Float32
  //
  read_float32: function()
  {
    this.calculate_offset (Cdr_Reader.FLOAT_SIZE);
    var float_val = this.data_view_.getFloat32(this.offset_, this.isLittleEndian_);
    this.offset_ += Cdr_Reader.FLOAT_SIZE;

    return float_val;
  },

  //
  //read Float64
  //
  read_float64: function()
  {
    this.calculate_offset (Cdr_Reader.DOUBLE_SIZE);
    var double_val = this.data_view_.getFloat64(this.offset_, this.isLittleEndian_);
    this.offset_ += Cdr_Reader.DOUBLE_SIZE;

    return double_val;
  },

  //
  //read char
  //
  read_char: function()
  {
    return String.fromCharCode(this.read_uint8());
  },

  //
  //read_char_array
  //
  read_char_array: function(length)
  {
    var array = new Array(length);
    for (var i = 0; i < length; i++)
    {
      array[i] = this.read_char();
    }

    return array;
  },

  //
  //read string
  //
  read_string: function()
  {
    var value = '';
    var length = this.read_uint32();
    var end_of_stream = this.offset_ + length;

    while (this.offset_ < end_of_stream)
    {
      value += String.fromCharCode(this.read_uint8());
    }

    return value;
  },

  //
  //read UUID
  //
  read_uuid: function()
  {
    var uuid = new UUID();

    uuid.time_low_ = this.read_uint32();
    uuid.time_mid_ = this.read_uint16();
    uuid.time_hi_and_version_ = this.read_uint16();
    var chunk = new Array(8);
    chunk = this.read_char_array(8);

    uuid.clock_seq_hi_and_reserved_ = chunk[0];
    uuid.clock_seq_low_ = chunk[1];

    for (var i = 2, j = 0; i < 8; i++)
    {
      uuid.node_[j++] = chunk[i];
    }
    return uuid;
  }
}//end_of_Cdr_Reader
