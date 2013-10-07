/**
*@class UUID
*
*Mimics ACE_Utils::UUID class
*/

//
//Constructor
//
function UUID()
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
}
//UUID.prototype.to_string = function()
//{
//  return sprintf("%8.8x-%4.4x-%4.4x-%2.2x%2.2x-%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x-%s-%s",
//                 [this.time_low_,
//                  this.time_mid_,
//                  this.time_hi_and_version_,
//                  this.clock_seq_hi_and_reserved_,
//                  this.clock_seq_low_,
//                  this.node_[0],
//                    this.node_[1],
//                    this.node_[2],
//                    this.node_[3],
//                    this.node_[4],
//                    this.node_[5],
//                  //we do not have thread_id,
//                  //we do not have process_id]);
//}
//end_of_UUID
