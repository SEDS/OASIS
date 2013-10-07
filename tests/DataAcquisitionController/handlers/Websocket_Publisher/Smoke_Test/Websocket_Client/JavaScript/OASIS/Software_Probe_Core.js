// -*- JavaScript -*-

//=================================================================================================
/**
* @file        Software_Probe_Core.js
*
* $Id: Software_Probe_Core.js 2155 2012-04-26 19:17:07Z dpuranik $
*
* @author      Darshan G. Puranik
*/
//=================================================================================================

/*-------------------------------------Cdr_Reader------------------------------------------------*/

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

//
//Cdr_Reader Memeber Functions
//
Cdr_Reader.prototype = {
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
    var alignment_offset = this.offset_ % Cdr_Reader.SHORT_SIZE;
    var short_val;

    if (0 == alignment_offset)
    {
      short_val = this.data_view_.getInt16(this.offset_, this.isLittleEndian_);
    }
    else
    {
      this.offset_ += alignment_offset;
      short_val = this.data_view_.getInt16(this.offset_, this.isLittleEndian_);
    }
    this.offset_ += 2;

    return short_val;
  },

  //
  //read Uint16
  //
  read_uint16: function()
  {
    var alignment_offset = this.offset_ % Cdr_Reader.USHORT_SIZE;
    var ushort_val;

    if (0 == alignment_offset)
    {
      ushort_val = this.data_view_.getUint16(this.offset_, this.isLittleEndian_);
    }
    else
    {
      this.offset_ += alignment_offset;
      ushort_val = this.data_view_.getUint16(this.offset_, this.isLittleEndian_);
    }
    this.offset_ += 2;

    return ushort_val;
  },

  //
  //read Int32
  //
  read_int32: function()
  {
    var alignment_offset = this.offset_ % Cdr_Reader.LONG_SIZE;
    var long_val;

    if (0 == alignment_offset)
    {
      long_val = this.data_view_.getInt32(this.offset_, this.isLittleEndian_);
    }
    else if (alignment_offset <= (Cdr_Reader.LONG_SIZE / 2))
    {
      alignment_offset = Cdr_Reader.LONG_SIZE - alignment_offset;
      this.offset_ += alignment_offset;

      long_val = this.data_view_.getInt32(this.offset_, this.isLittleEndian_);
    }
    this.offset_ += Cdr_Reader.LONG_SIZE;

    return long_val;
  },

  //
  //read UInt32
  //
  read_uint32: function()
  {
    var alignment_offset = this.offset_ % Cdr_Reader.ULONG_SIZE;
    var ulong_val;

    if (0 == alignment_offset)
    {
      ulong_val = this.data_view_.getUint32(this.offset_, this.isLittleEndian_);
    }
    else if (alignment_offset <= (Cdr_Reader.ULONG_SIZE / 2))
    {
      alignment_offset = Cdr_Reader.ULONG_SIZE - alignment_offset;
      this.offset_ += alignment_offset;

      ulong_val = this.data_view_.getUint32(this.offset_, this.isLittleEndian_);
    }
    this.offset_ += Cdr_Reader.ULONG_SIZE;

    return ulong_val;
  },

  //
  //read Float32
  //
  read_float32: function()
  {
    var alignment_offset = this.offset_ % Cdr_Reader.FLOAT_SIZE;
    var float_val;

    if (0 == alignment_offset)
    {
      float_val = this.data_view_.getFloat32(this.offset_, this.isLittleEndian_);
    }
    else if (alignment_offset <= (Cdr_Reader.FLOAT_SIZE / 2))
    {
      alignment_offset = Cdr_Reader.FLOAT_SIZE - alignment_offset;
      this.offset_ += alignment_offset;

      float_val = this.data_view_.getFloat32(this.offset_, this.isLittleEndian_);
    }
    this.offset_ += Cdr_Reader.FLOAT_SIZE;

    return float_val;
  },

  //
  //read Float64
  //
  read_float64: function()
  {
    var alignment_offset = this.offset_ % Cdr_Reader.DOUBLE_SIZE;
    var double_val;

    if (0 == alignment_offset)
    {
      double_val = this.data_view_.getFloat64(this.offset_, this.isLittleEndian_);
    }
    else if (alignment_offset <= (Cdr_Reader.DOUBLE_SIZE / 2))
    {
      alignment_offset = Cdr_Reader.DOUBLE_SIZE - alignment_offset;
      this.offset_ += alignment_offset;

      double_val = this.data_view_.getFloat64(this.offset_, this.isLittleEndian_);
    }
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
    var i = 0;
    for (i = 0; i < length; i++)
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

    var chunk = this.read_char_array(8);

    uuid.clock_seq_hi_and_reserved_ = chunk[0];
    uuid.clock_seq_low_ = chunk[1];

    var i = 0, j = 0;
    for (i = 2; i < 8; i++)
    {
      uuid.node_[j++] = chunk[i];
    }
    return uuid;
  }
}//end_of_Cdr_Reader

/*-------------------------------------UUID--------------------------------------------------------*/

/**
*@class UUID
*
*Mimics ACE_Utils::UUID class
*/

//
//Constructor
//
function UUID ()
{
  /// Time low
  this.time_low_ = 0;

  /// Time mid.
  this.time_mid_ = 0;

  /// Time high and version.
  this.time_hi_and_version_ = 0;

  /// Clock sequence high and reserved space.
  this.clock_seq_hi_and_reserved_ = '';

  /// Clock sequence low.
  this.clock_seq_low_ = '';

  ///Holds the MAC-address of the UUID
  this.node_ = new Array(6);
} //end_of_UUID

/*-------------------------------------Time_Value------------------------------------------------*/

/**
* @class Time_Value
*
* mimics ACE_Time_Value class
*/

//
//Constructor
//
function Time_Value()
{
  this.sec_ = 0;
  this.usec_ = 0;
}

Time_Value.prototype =
{
  //
  //set_value()
  //
  set_value: function(sec, 
                      usec)
  {
    this.sec_ = sec;
    this.usec_ = usec;
  }
}//end_of_Time_Value

/*-------------------------------------Software_Probe_Header-------------------------------------*/

/**
* @struct Software_Probe_Header
*
* Header for all software probes. It contains infomration related
* to the latest collect metrics.
*/

//
// Constructor
//
function Software_Probe_Header ()
{
  /// UUID assigned to this software probe.
  this.uuid_ = new UUID();

  /// The lastest timestamp.
  this.last_ts_ = new Time_Value();

  /// The current sequence number for the data.
  this.seqnum_ = 0;

  /// The state of the software probe.
  this.state_ = 0;

  /// The size of the software probe's data.
  this.datasize_ = 0;
} // end_of_Software_Probe_Header

/*-------------------------------------Software_Probe_Metadata-----------------------------------*/

/**
* @class Software_Probe_Metadata
*
* The metadata for a software probe. All the information below
* is required for each software probe.
*/

//
// Constructor
//
function Software_Probe_Metadata(uuid,
                                 type_info,
                                 version_major,
                                 version_minor,
                                 schema)
{
  /// Unique id for the software probe.
  this.uuid_ = uuid;

  /// Unique typename for the software probe.
  this.type_info_ = type_info;

  /// Version major number.
  this.version_major_ = version_major;

  /// Version minor number.
  this.version_minor_ = version_minor;

  /// Schema definition for the software probe.
  this.schema_ = schema;
} //end_of_Software_Probe_Metadata

/*-------------------------------------Software_Probe--------------------------------------------*/

/**
* @class Software_Probe
*
* Base class for all software probes stubs. The software probe stub
* constains the metadata for a given probe. In addition, it contains
* a method for recalling a software probe's data that was previously
* packaged by an implementation.
*/

//
// Constructor
//
function Software_Probe ()
{
  /// Metadata associated with the software probe.
  this.header_ = new Software_Probe_Header();

  /// Instance name assigned to the probe.
  this.name_ = "";
}

Software_Probe.prototype =
{
  //
  // header()
  //
  header: function()
  {
    return this.header_;
  },

  //
  // name()
  //
  name: function()
  {
    return this.name_;
  },

  //
  //recall()
  //
  recall_with_reader: function(input)
  {
    var magic = input.read_char_array(4);

    var version = input.read_char_array(2);

    this.header_.uuid_ = input.read_uuid();

    var sec = input.read_uint32();
    var usec = input.read_uint32();
    this.header_.last_ts_.set_value(sec, usec);

    this.header_.seqnum_ = input.read_uint32();

    this.header_.state_ = input.read_uint16();

    this.header_.datasize_ = input.read_uint32();

    this.name_ = input.read_string();

    // TODO : alignment for start of data is necessary
    //       look c# code
  },

  //
  //recall()
  //
  recall: function(packet, byte_order)
  {
    var reader = new Cdr_Reader(packet, byte_order);
    this.recall_with_reader(reader);
  }
}//end_of_Software_Probe

/*-------------------------------------ProcessorProbe--------------------------------------------*/

/**
* @class ProcessorProbe
*
*
*/

//
//Constructor
//
function ProcessorProbe()
{
  this.idle_time_ = 0;
  this.system_time_ = 0;
  this.user_time_ = 0;
}

//
//Dynamic inheritance 
//
ProcessorProbe.prototype = new Software_Probe();

//
//recall()
//
ProcessorProbe.prototype.recall_with_reader = function(input)
{
  //calling the base class recall() to read the header
  Software_Probe.prototype.recall.call(this,
                                       input);

  //read the actual data of probe
  this.idle_time_ = input.read_float64();
  this.system_time_ = input.read_float64();
  this.user_time_ = input.read_float64();

}

//
//recall()
//
ProcessorProbe.prototype.recall = function(packet, byte_order)
{
  var reader = new Cdr_Reader(packet,
                              byte_order);
  this.recall_with_reader(reader);
}
//end_of_ProcessorProbe 