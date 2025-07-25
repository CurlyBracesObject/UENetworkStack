// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Person.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Person_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Person_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3020000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3020000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "MyBox.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Person_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Person_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Person_2eproto;
class Person;
struct PersonDefaultTypeInternal;
extern PersonDefaultTypeInternal _Person_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::Person* Arena::CreateMaybeMessage<::Person>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class Person final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Person) */ {
 public:
  inline Person() : Person(nullptr) {}
  ~Person() override;
  explicit PROTOBUF_CONSTEXPR Person(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Person(const Person& from);
  Person(Person&& from) noexcept
    : Person() {
    *this = ::std::move(from);
  }

  inline Person& operator=(const Person& from) {
    CopyFrom(from);
    return *this;
  }
  inline Person& operator=(Person&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Person& default_instance() {
    return *internal_default_instance();
  }
  static inline const Person* internal_default_instance() {
    return reinterpret_cast<const Person*>(
               &_Person_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Person& a, Person& b) {
    a.Swap(&b);
  }
  inline void Swap(Person* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Person* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Person* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Person>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Person& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Person& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Person* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Person";
  }
  protected:
  explicit Person(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kB1FieldNumber = 1,
  };
  // .MyBox b1 = 1;
  bool has_b1() const;
  private:
  bool _internal_has_b1() const;
  public:
  void clear_b1();
  const ::MyBox& b1() const;
  PROTOBUF_NODISCARD ::MyBox* release_b1();
  ::MyBox* mutable_b1();
  void set_allocated_b1(::MyBox* b1);
  private:
  const ::MyBox& _internal_b1() const;
  ::MyBox* _internal_mutable_b1();
  public:
  void unsafe_arena_set_allocated_b1(
      ::MyBox* b1);
  ::MyBox* unsafe_arena_release_b1();

  // @@protoc_insertion_point(class_scope:Person)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::MyBox* b1_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Person_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Person

// .MyBox b1 = 1;
inline bool Person::_internal_has_b1() const {
  return this != internal_default_instance() && b1_ != nullptr;
}
inline bool Person::has_b1() const {
  return _internal_has_b1();
}
inline const ::MyBox& Person::_internal_b1() const {
  const ::MyBox* p = b1_;
  return p != nullptr ? *p : reinterpret_cast<const ::MyBox&>(
      ::_MyBox_default_instance_);
}
inline const ::MyBox& Person::b1() const {
  // @@protoc_insertion_point(field_get:Person.b1)
  return _internal_b1();
}
inline void Person::unsafe_arena_set_allocated_b1(
    ::MyBox* b1) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(b1_);
  }
  b1_ = b1;
  if (b1) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:Person.b1)
}
inline ::MyBox* Person::release_b1() {
  
  ::MyBox* temp = b1_;
  b1_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::MyBox* Person::unsafe_arena_release_b1() {
  // @@protoc_insertion_point(field_release:Person.b1)
  
  ::MyBox* temp = b1_;
  b1_ = nullptr;
  return temp;
}
inline ::MyBox* Person::_internal_mutable_b1() {
  
  if (b1_ == nullptr) {
    auto* p = CreateMaybeMessage<::MyBox>(GetArenaForAllocation());
    b1_ = p;
  }
  return b1_;
}
inline ::MyBox* Person::mutable_b1() {
  ::MyBox* _msg = _internal_mutable_b1();
  // @@protoc_insertion_point(field_mutable:Person.b1)
  return _msg;
}
inline void Person::set_allocated_b1(::MyBox* b1) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(b1_);
  }
  if (b1) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(b1));
    if (message_arena != submessage_arena) {
      b1 = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, b1, submessage_arena);
    }
    
  } else {
    
  }
  b1_ = b1;
  // @@protoc_insertion_point(field_set_allocated:Person.b1)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Person_2eproto
