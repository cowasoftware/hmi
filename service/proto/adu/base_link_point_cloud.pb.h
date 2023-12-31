// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: base_link_point_cloud.proto

#ifndef PROTOBUF_base_5flink_5fpoint_5fcloud_2eproto__INCLUDED
#define PROTOBUF_base_5flink_5fpoint_5fcloud_2eproto__INCLUDED

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
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace base_link_point_cloud {
class PointCloud;
class PointCloudDefaultTypeInternal;
extern PointCloudDefaultTypeInternal _PointCloud_default_instance_;
class PointCloudCollect;
class PointCloudCollectDefaultTypeInternal;
extern PointCloudCollectDefaultTypeInternal _PointCloudCollect_default_instance_;
class PointCloudDataType;
class PointCloudDataTypeDefaultTypeInternal;
extern PointCloudDataTypeDefaultTypeInternal _PointCloudDataType_default_instance_;
class PointXYZ;
class PointXYZDefaultTypeInternal;
extern PointXYZDefaultTypeInternal _PointXYZ_default_instance_;
}  // namespace base_link_point_cloud

namespace base_link_point_cloud {

namespace protobuf_base_5flink_5fpoint_5fcloud_2eproto {
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
}  // namespace protobuf_base_5flink_5fpoint_5fcloud_2eproto

// ===================================================================

class PointXYZ : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:base_link_point_cloud.PointXYZ) */ {
 public:
  PointXYZ();
  virtual ~PointXYZ();

  PointXYZ(const PointXYZ& from);

  inline PointXYZ& operator=(const PointXYZ& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PointXYZ& default_instance();

  static inline const PointXYZ* internal_default_instance() {
    return reinterpret_cast<const PointXYZ*>(
               &_PointXYZ_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(PointXYZ* other);

  // implements Message ----------------------------------------------

  inline PointXYZ* New() const PROTOBUF_FINAL { return New(NULL); }

  PointXYZ* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const PointXYZ& from);
  void MergeFrom(const PointXYZ& from);
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
  void InternalSwap(PointXYZ* other);
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

  // required float x = 1;
  bool has_x() const;
  void clear_x();
  static const int kXFieldNumber = 1;
  float x() const;
  void set_x(float value);

  // required float y = 2;
  bool has_y() const;
  void clear_y();
  static const int kYFieldNumber = 2;
  float y() const;
  void set_y(float value);

  // required float z = 3;
  bool has_z() const;
  void clear_z();
  static const int kZFieldNumber = 3;
  float z() const;
  void set_z(float value);

  // optional uint32 intensity = 4;
  bool has_intensity() const;
  void clear_intensity();
  static const int kIntensityFieldNumber = 4;
  ::google::protobuf::uint32 intensity() const;
  void set_intensity(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:base_link_point_cloud.PointXYZ)
 private:
  void set_has_x();
  void clear_has_x();
  void set_has_y();
  void clear_has_y();
  void set_has_z();
  void clear_has_z();
  void set_has_intensity();
  void clear_has_intensity();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  float x_;
  float y_;
  float z_;
  ::google::protobuf::uint32 intensity_;
  friend struct protobuf_base_5flink_5fpoint_5fcloud_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class PointCloud : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:base_link_point_cloud.PointCloud) */ {
 public:
  PointCloud();
  virtual ~PointCloud();

  PointCloud(const PointCloud& from);

  inline PointCloud& operator=(const PointCloud& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PointCloud& default_instance();

  static inline const PointCloud* internal_default_instance() {
    return reinterpret_cast<const PointCloud*>(
               &_PointCloud_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(PointCloud* other);

  // implements Message ----------------------------------------------

  inline PointCloud* New() const PROTOBUF_FINAL { return New(NULL); }

  PointCloud* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const PointCloud& from);
  void MergeFrom(const PointCloud& from);
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
  void InternalSwap(PointCloud* other);
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

  // repeated .base_link_point_cloud.PointXYZ point = 1;
  int point_size() const;
  void clear_point();
  static const int kPointFieldNumber = 1;
  const ::base_link_point_cloud::PointXYZ& point(int index) const;
  ::base_link_point_cloud::PointXYZ* mutable_point(int index);
  ::base_link_point_cloud::PointXYZ* add_point();
  ::google::protobuf::RepeatedPtrField< ::base_link_point_cloud::PointXYZ >*
      mutable_point();
  const ::google::protobuf::RepeatedPtrField< ::base_link_point_cloud::PointXYZ >&
      point() const;

  // @@protoc_insertion_point(class_scope:base_link_point_cloud.PointCloud)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::base_link_point_cloud::PointXYZ > point_;
  friend struct protobuf_base_5flink_5fpoint_5fcloud_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class PointCloudCollect : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:base_link_point_cloud.PointCloudCollect) */ {
 public:
  PointCloudCollect();
  virtual ~PointCloudCollect();

  PointCloudCollect(const PointCloudCollect& from);

  inline PointCloudCollect& operator=(const PointCloudCollect& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PointCloudCollect& default_instance();

  static inline const PointCloudCollect* internal_default_instance() {
    return reinterpret_cast<const PointCloudCollect*>(
               &_PointCloudCollect_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(PointCloudCollect* other);

  // implements Message ----------------------------------------------

  inline PointCloudCollect* New() const PROTOBUF_FINAL { return New(NULL); }

  PointCloudCollect* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const PointCloudCollect& from);
  void MergeFrom(const PointCloudCollect& from);
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
  void InternalSwap(PointCloudCollect* other);
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

  // repeated .base_link_point_cloud.PointCloud point_cloud = 1;
  int point_cloud_size() const;
  void clear_point_cloud();
  static const int kPointCloudFieldNumber = 1;
  const ::base_link_point_cloud::PointCloud& point_cloud(int index) const;
  ::base_link_point_cloud::PointCloud* mutable_point_cloud(int index);
  ::base_link_point_cloud::PointCloud* add_point_cloud();
  ::google::protobuf::RepeatedPtrField< ::base_link_point_cloud::PointCloud >*
      mutable_point_cloud();
  const ::google::protobuf::RepeatedPtrField< ::base_link_point_cloud::PointCloud >&
      point_cloud() const;

  // @@protoc_insertion_point(class_scope:base_link_point_cloud.PointCloudCollect)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::base_link_point_cloud::PointCloud > point_cloud_;
  friend struct protobuf_base_5flink_5fpoint_5fcloud_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class PointCloudDataType : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:base_link_point_cloud.PointCloudDataType) */ {
 public:
  PointCloudDataType();
  virtual ~PointCloudDataType();

  PointCloudDataType(const PointCloudDataType& from);

  inline PointCloudDataType& operator=(const PointCloudDataType& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PointCloudDataType& default_instance();

  static inline const PointCloudDataType* internal_default_instance() {
    return reinterpret_cast<const PointCloudDataType*>(
               &_PointCloudDataType_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    3;

  void Swap(PointCloudDataType* other);

  // implements Message ----------------------------------------------

  inline PointCloudDataType* New() const PROTOBUF_FINAL { return New(NULL); }

  PointCloudDataType* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const PointCloudDataType& from);
  void MergeFrom(const PointCloudDataType& from);
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
  void InternalSwap(PointCloudDataType* other);
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

  // optional .base_link_point_cloud.PointCloudCollect point_cloud_collect = 2;
  bool has_point_cloud_collect() const;
  void clear_point_cloud_collect();
  static const int kPointCloudCollectFieldNumber = 2;
  const ::base_link_point_cloud::PointCloudCollect& point_cloud_collect() const;
  ::base_link_point_cloud::PointCloudCollect* mutable_point_cloud_collect();
  ::base_link_point_cloud::PointCloudCollect* release_point_cloud_collect();
  void set_allocated_point_cloud_collect(::base_link_point_cloud::PointCloudCollect* point_cloud_collect);

  // required uint64 sequence_id = 1;
  bool has_sequence_id() const;
  void clear_sequence_id();
  static const int kSequenceIdFieldNumber = 1;
  ::google::protobuf::uint64 sequence_id() const;
  void set_sequence_id(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:base_link_point_cloud.PointCloudDataType)
 private:
  void set_has_sequence_id();
  void clear_has_sequence_id();
  void set_has_point_cloud_collect();
  void clear_has_point_cloud_collect();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::base_link_point_cloud::PointCloudCollect* point_cloud_collect_;
  ::google::protobuf::uint64 sequence_id_;
  friend struct protobuf_base_5flink_5fpoint_5fcloud_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// PointXYZ

// required float x = 1;
inline bool PointXYZ::has_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PointXYZ::set_has_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PointXYZ::clear_has_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PointXYZ::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline float PointXYZ::x() const {
  // @@protoc_insertion_point(field_get:base_link_point_cloud.PointXYZ.x)
  return x_;
}
inline void PointXYZ::set_x(float value) {
  set_has_x();
  x_ = value;
  // @@protoc_insertion_point(field_set:base_link_point_cloud.PointXYZ.x)
}

// required float y = 2;
inline bool PointXYZ::has_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PointXYZ::set_has_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PointXYZ::clear_has_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PointXYZ::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline float PointXYZ::y() const {
  // @@protoc_insertion_point(field_get:base_link_point_cloud.PointXYZ.y)
  return y_;
}
inline void PointXYZ::set_y(float value) {
  set_has_y();
  y_ = value;
  // @@protoc_insertion_point(field_set:base_link_point_cloud.PointXYZ.y)
}

// required float z = 3;
inline bool PointXYZ::has_z() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PointXYZ::set_has_z() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PointXYZ::clear_has_z() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PointXYZ::clear_z() {
  z_ = 0;
  clear_has_z();
}
inline float PointXYZ::z() const {
  // @@protoc_insertion_point(field_get:base_link_point_cloud.PointXYZ.z)
  return z_;
}
inline void PointXYZ::set_z(float value) {
  set_has_z();
  z_ = value;
  // @@protoc_insertion_point(field_set:base_link_point_cloud.PointXYZ.z)
}

// optional uint32 intensity = 4;
inline bool PointXYZ::has_intensity() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PointXYZ::set_has_intensity() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PointXYZ::clear_has_intensity() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PointXYZ::clear_intensity() {
  intensity_ = 0u;
  clear_has_intensity();
}
inline ::google::protobuf::uint32 PointXYZ::intensity() const {
  // @@protoc_insertion_point(field_get:base_link_point_cloud.PointXYZ.intensity)
  return intensity_;
}
inline void PointXYZ::set_intensity(::google::protobuf::uint32 value) {
  set_has_intensity();
  intensity_ = value;
  // @@protoc_insertion_point(field_set:base_link_point_cloud.PointXYZ.intensity)
}

// -------------------------------------------------------------------

// PointCloud

// repeated .base_link_point_cloud.PointXYZ point = 1;
inline int PointCloud::point_size() const {
  return point_.size();
}
inline void PointCloud::clear_point() {
  point_.Clear();
}
inline const ::base_link_point_cloud::PointXYZ& PointCloud::point(int index) const {
  // @@protoc_insertion_point(field_get:base_link_point_cloud.PointCloud.point)
  return point_.Get(index);
}
inline ::base_link_point_cloud::PointXYZ* PointCloud::mutable_point(int index) {
  // @@protoc_insertion_point(field_mutable:base_link_point_cloud.PointCloud.point)
  return point_.Mutable(index);
}
inline ::base_link_point_cloud::PointXYZ* PointCloud::add_point() {
  // @@protoc_insertion_point(field_add:base_link_point_cloud.PointCloud.point)
  return point_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::base_link_point_cloud::PointXYZ >*
PointCloud::mutable_point() {
  // @@protoc_insertion_point(field_mutable_list:base_link_point_cloud.PointCloud.point)
  return &point_;
}
inline const ::google::protobuf::RepeatedPtrField< ::base_link_point_cloud::PointXYZ >&
PointCloud::point() const {
  // @@protoc_insertion_point(field_list:base_link_point_cloud.PointCloud.point)
  return point_;
}

// -------------------------------------------------------------------

// PointCloudCollect

// repeated .base_link_point_cloud.PointCloud point_cloud = 1;
inline int PointCloudCollect::point_cloud_size() const {
  return point_cloud_.size();
}
inline void PointCloudCollect::clear_point_cloud() {
  point_cloud_.Clear();
}
inline const ::base_link_point_cloud::PointCloud& PointCloudCollect::point_cloud(int index) const {
  // @@protoc_insertion_point(field_get:base_link_point_cloud.PointCloudCollect.point_cloud)
  return point_cloud_.Get(index);
}
inline ::base_link_point_cloud::PointCloud* PointCloudCollect::mutable_point_cloud(int index) {
  // @@protoc_insertion_point(field_mutable:base_link_point_cloud.PointCloudCollect.point_cloud)
  return point_cloud_.Mutable(index);
}
inline ::base_link_point_cloud::PointCloud* PointCloudCollect::add_point_cloud() {
  // @@protoc_insertion_point(field_add:base_link_point_cloud.PointCloudCollect.point_cloud)
  return point_cloud_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::base_link_point_cloud::PointCloud >*
PointCloudCollect::mutable_point_cloud() {
  // @@protoc_insertion_point(field_mutable_list:base_link_point_cloud.PointCloudCollect.point_cloud)
  return &point_cloud_;
}
inline const ::google::protobuf::RepeatedPtrField< ::base_link_point_cloud::PointCloud >&
PointCloudCollect::point_cloud() const {
  // @@protoc_insertion_point(field_list:base_link_point_cloud.PointCloudCollect.point_cloud)
  return point_cloud_;
}

// -------------------------------------------------------------------

// PointCloudDataType

// required uint64 sequence_id = 1;
inline bool PointCloudDataType::has_sequence_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PointCloudDataType::set_has_sequence_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PointCloudDataType::clear_has_sequence_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PointCloudDataType::clear_sequence_id() {
  sequence_id_ = GOOGLE_ULONGLONG(0);
  clear_has_sequence_id();
}
inline ::google::protobuf::uint64 PointCloudDataType::sequence_id() const {
  // @@protoc_insertion_point(field_get:base_link_point_cloud.PointCloudDataType.sequence_id)
  return sequence_id_;
}
inline void PointCloudDataType::set_sequence_id(::google::protobuf::uint64 value) {
  set_has_sequence_id();
  sequence_id_ = value;
  // @@protoc_insertion_point(field_set:base_link_point_cloud.PointCloudDataType.sequence_id)
}

// optional .base_link_point_cloud.PointCloudCollect point_cloud_collect = 2;
inline bool PointCloudDataType::has_point_cloud_collect() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PointCloudDataType::set_has_point_cloud_collect() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PointCloudDataType::clear_has_point_cloud_collect() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PointCloudDataType::clear_point_cloud_collect() {
  if (point_cloud_collect_ != NULL) point_cloud_collect_->::base_link_point_cloud::PointCloudCollect::Clear();
  clear_has_point_cloud_collect();
}
inline const ::base_link_point_cloud::PointCloudCollect& PointCloudDataType::point_cloud_collect() const {
  // @@protoc_insertion_point(field_get:base_link_point_cloud.PointCloudDataType.point_cloud_collect)
  return point_cloud_collect_ != NULL ? *point_cloud_collect_
                         : *::base_link_point_cloud::PointCloudCollect::internal_default_instance();
}
inline ::base_link_point_cloud::PointCloudCollect* PointCloudDataType::mutable_point_cloud_collect() {
  set_has_point_cloud_collect();
  if (point_cloud_collect_ == NULL) {
    point_cloud_collect_ = new ::base_link_point_cloud::PointCloudCollect;
  }
  // @@protoc_insertion_point(field_mutable:base_link_point_cloud.PointCloudDataType.point_cloud_collect)
  return point_cloud_collect_;
}
inline ::base_link_point_cloud::PointCloudCollect* PointCloudDataType::release_point_cloud_collect() {
  // @@protoc_insertion_point(field_release:base_link_point_cloud.PointCloudDataType.point_cloud_collect)
  clear_has_point_cloud_collect();
  ::base_link_point_cloud::PointCloudCollect* temp = point_cloud_collect_;
  point_cloud_collect_ = NULL;
  return temp;
}
inline void PointCloudDataType::set_allocated_point_cloud_collect(::base_link_point_cloud::PointCloudCollect* point_cloud_collect) {
  delete point_cloud_collect_;
  point_cloud_collect_ = point_cloud_collect;
  if (point_cloud_collect) {
    set_has_point_cloud_collect();
  } else {
    clear_has_point_cloud_collect();
  }
  // @@protoc_insertion_point(field_set_allocated:base_link_point_cloud.PointCloudDataType.point_cloud_collect)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace base_link_point_cloud

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_base_5flink_5fpoint_5fcloud_2eproto__INCLUDED
