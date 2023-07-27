// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CanService.proto

#ifndef PROTOBUF_CanService_2eproto__INCLUDED
#define PROTOBUF_CanService_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace COWA {
namespace CanService {
class CanData;
class CanDataDefaultTypeInternal;
extern CanDataDefaultTypeInternal _CanData_default_instance_;
class CanServiceMsg;
class CanServiceMsgDefaultTypeInternal;
extern CanServiceMsgDefaultTypeInternal _CanServiceMsg_default_instance_;
}  // namespace CanService
}  // namespace COWA

namespace COWA {
namespace CanService {

namespace protobuf_CanService_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_CanService_2eproto

enum EventId {
  EVENT_ID_INVALID = 0,
  EVENT_ID_SET_CAN_DATA = 1,
  EVENT_ID_HMI_GET_CAN_DATA = 2,
  EVENT_ID_HMI_GET_NETWORK_DATA = 3,
  EventId_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  EventId_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool EventId_IsValid(int value);
const EventId EventId_MIN = EVENT_ID_INVALID;
const EventId EventId_MAX = EVENT_ID_HMI_GET_NETWORK_DATA;
const int EventId_ARRAYSIZE = EventId_MAX + 1;

const ::google::protobuf::EnumDescriptor* EventId_descriptor();
inline const ::std::string& EventId_Name(EventId value) {
  return ::google::protobuf::internal::NameOfEnum(
    EventId_descriptor(), value);
}
inline bool EventId_Parse(
    const ::std::string& name, EventId* value) {
  return ::google::protobuf::internal::ParseNamedEnum<EventId>(
    EventId_descriptor(), name, value);
}
// ===================================================================

class CanData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:COWA.CanService.CanData) */ {
 public:
  CanData();
  virtual ~CanData();

  CanData(const CanData& from);

  inline CanData& operator=(const CanData& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CanData& default_instance();

  static inline const CanData* internal_default_instance() {
    return reinterpret_cast<const CanData*>(
               &_CanData_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(CanData* other);

  // implements Message ----------------------------------------------

  inline CanData* New() const PROTOBUF_FINAL { return New(NULL); }

  CanData* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const CanData& from);
  void MergeFrom(const CanData& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(CanData* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes data = 2;
  void clear_data();
  static const int kDataFieldNumber = 2;
  const ::std::string& data() const;
  void set_data(const ::std::string& value);
  #if LANG_CXX11
  void set_data(::std::string&& value);
  #endif
  void set_data(const char* value);
  void set_data(const void* value, size_t size);
  ::std::string* mutable_data();
  ::std::string* release_data();
  void set_allocated_data(::std::string* data);

  // uint32 canId = 1;
  void clear_canid();
  static const int kCanIdFieldNumber = 1;
  ::google::protobuf::uint32 canid() const;
  void set_canid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:COWA.CanService.CanData)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr data_;
  ::google::protobuf::uint32 canid_;
  mutable int _cached_size_;
  friend struct protobuf_CanService_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class CanServiceMsg : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:COWA.CanService.CanServiceMsg) */ {
 public:
  CanServiceMsg();
  virtual ~CanServiceMsg();

  CanServiceMsg(const CanServiceMsg& from);

  inline CanServiceMsg& operator=(const CanServiceMsg& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CanServiceMsg& default_instance();

  static inline const CanServiceMsg* internal_default_instance() {
    return reinterpret_cast<const CanServiceMsg*>(
               &_CanServiceMsg_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(CanServiceMsg* other);

  // implements Message ----------------------------------------------

  inline CanServiceMsg* New() const PROTOBUF_FINAL { return New(NULL); }

  CanServiceMsg* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const CanServiceMsg& from);
  void MergeFrom(const CanServiceMsg& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(CanServiceMsg* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .COWA.CanService.CanData canData = 4;
  int candata_size() const;
  void clear_candata();
  static const int kCanDataFieldNumber = 4;
  const ::COWA::CanService::CanData& candata(int index) const;
  ::COWA::CanService::CanData* mutable_candata(int index);
  ::COWA::CanService::CanData* add_candata();
  ::google::protobuf::RepeatedPtrField< ::COWA::CanService::CanData >*
      mutable_candata();
  const ::google::protobuf::RepeatedPtrField< ::COWA::CanService::CanData >&
      candata() const;

  // uint32 eventId = 1;
  void clear_eventid();
  static const int kEventIdFieldNumber = 1;
  ::google::protobuf::uint32 eventid() const;
  void set_eventid(::google::protobuf::uint32 value);

  // uint32 seqNum = 2;
  void clear_seqnum();
  static const int kSeqNumFieldNumber = 2;
  ::google::protobuf::uint32 seqnum() const;
  void set_seqnum(::google::protobuf::uint32 value);

  // uint64 timestamp = 3;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 3;
  ::google::protobuf::uint64 timestamp() const;
  void set_timestamp(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:COWA.CanService.CanServiceMsg)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::COWA::CanService::CanData > candata_;
  ::google::protobuf::uint32 eventid_;
  ::google::protobuf::uint32 seqnum_;
  ::google::protobuf::uint64 timestamp_;
  mutable int _cached_size_;
  friend struct protobuf_CanService_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// CanData

// uint32 canId = 1;
inline void CanData::clear_canid() {
  canid_ = 0u;
}
inline ::google::protobuf::uint32 CanData::canid() const {
  // @@protoc_insertion_point(field_get:COWA.CanService.CanData.canId)
  return canid_;
}
inline void CanData::set_canid(::google::protobuf::uint32 value) {
  
  canid_ = value;
  // @@protoc_insertion_point(field_set:COWA.CanService.CanData.canId)
}

// bytes data = 2;
inline void CanData::clear_data() {
  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CanData::data() const {
  // @@protoc_insertion_point(field_get:COWA.CanService.CanData.data)
  return data_.GetNoArena();
}
inline void CanData::set_data(const ::std::string& value) {
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:COWA.CanService.CanData.data)
}
#if LANG_CXX11
inline void CanData::set_data(::std::string&& value) {
  
  data_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:COWA.CanService.CanData.data)
}
#endif
inline void CanData::set_data(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:COWA.CanService.CanData.data)
}
inline void CanData::set_data(const void* value, size_t size) {
  
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:COWA.CanService.CanData.data)
}
inline ::std::string* CanData::mutable_data() {
  
  // @@protoc_insertion_point(field_mutable:COWA.CanService.CanData.data)
  return data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CanData::release_data() {
  // @@protoc_insertion_point(field_release:COWA.CanService.CanData.data)
  
  return data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CanData::set_allocated_data(::std::string* data) {
  if (data != NULL) {
    
  } else {
    
  }
  data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), data);
  // @@protoc_insertion_point(field_set_allocated:COWA.CanService.CanData.data)
}

// -------------------------------------------------------------------

// CanServiceMsg

// uint32 eventId = 1;
inline void CanServiceMsg::clear_eventid() {
  eventid_ = 0u;
}
inline ::google::protobuf::uint32 CanServiceMsg::eventid() const {
  // @@protoc_insertion_point(field_get:COWA.CanService.CanServiceMsg.eventId)
  return eventid_;
}
inline void CanServiceMsg::set_eventid(::google::protobuf::uint32 value) {
  
  eventid_ = value;
  // @@protoc_insertion_point(field_set:COWA.CanService.CanServiceMsg.eventId)
}

// uint32 seqNum = 2;
inline void CanServiceMsg::clear_seqnum() {
  seqnum_ = 0u;
}
inline ::google::protobuf::uint32 CanServiceMsg::seqnum() const {
  // @@protoc_insertion_point(field_get:COWA.CanService.CanServiceMsg.seqNum)
  return seqnum_;
}
inline void CanServiceMsg::set_seqnum(::google::protobuf::uint32 value) {
  
  seqnum_ = value;
  // @@protoc_insertion_point(field_set:COWA.CanService.CanServiceMsg.seqNum)
}

// uint64 timestamp = 3;
inline void CanServiceMsg::clear_timestamp() {
  timestamp_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 CanServiceMsg::timestamp() const {
  // @@protoc_insertion_point(field_get:COWA.CanService.CanServiceMsg.timestamp)
  return timestamp_;
}
inline void CanServiceMsg::set_timestamp(::google::protobuf::uint64 value) {
  
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:COWA.CanService.CanServiceMsg.timestamp)
}

// repeated .COWA.CanService.CanData canData = 4;
inline int CanServiceMsg::candata_size() const {
  return candata_.size();
}
inline void CanServiceMsg::clear_candata() {
  candata_.Clear();
}
inline const ::COWA::CanService::CanData& CanServiceMsg::candata(int index) const {
  // @@protoc_insertion_point(field_get:COWA.CanService.CanServiceMsg.canData)
  return candata_.Get(index);
}
inline ::COWA::CanService::CanData* CanServiceMsg::mutable_candata(int index) {
  // @@protoc_insertion_point(field_mutable:COWA.CanService.CanServiceMsg.canData)
  return candata_.Mutable(index);
}
inline ::COWA::CanService::CanData* CanServiceMsg::add_candata() {
  // @@protoc_insertion_point(field_add:COWA.CanService.CanServiceMsg.canData)
  return candata_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::COWA::CanService::CanData >*
CanServiceMsg::mutable_candata() {
  // @@protoc_insertion_point(field_mutable_list:COWA.CanService.CanServiceMsg.canData)
  return &candata_;
}
inline const ::google::protobuf::RepeatedPtrField< ::COWA::CanService::CanData >&
CanServiceMsg::candata() const {
  // @@protoc_insertion_point(field_list:COWA.CanService.CanServiceMsg.canData)
  return candata_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace CanService
}  // namespace COWA

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::COWA::CanService::EventId> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::COWA::CanService::EventId>() {
  return ::COWA::CanService::EventId_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CanService_2eproto__INCLUDED
