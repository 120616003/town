// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: user.proto

#include "user.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
class AccRegisterDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<AccRegister> _instance;
} _AccRegister_default_instance_;
static void InitDefaultsscc_info_AccRegister_user_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_AccRegister_default_instance_;
    new (ptr) ::AccRegister();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_AccRegister_user_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_AccRegister_user_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_user_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_user_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_user_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_user_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::AccRegister, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::AccRegister, type_),
  PROTOBUF_FIELD_OFFSET(::AccRegister, email_),
  PROTOBUF_FIELD_OFFSET(::AccRegister, phone_),
  PROTOBUF_FIELD_OFFSET(::AccRegister, accname_),
  PROTOBUF_FIELD_OFFSET(::AccRegister, passwd_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::AccRegister)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_AccRegister_default_instance_),
};

const char descriptor_table_protodef_user_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\nuser.proto\"Z\n\013AccRegister\022\014\n\004type\030\001 \001("
  "\005\022\r\n\005email\030\002 \001(\t\022\r\n\005phone\030\003 \001(\t\022\017\n\007accna"
  "me\030\004 \001(\t\022\016\n\006passwd\030\005 \001(\tb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_user_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_user_2eproto_sccs[1] = {
  &scc_info_AccRegister_user_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_user_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_user_2eproto = {
  false, false, descriptor_table_protodef_user_2eproto, "user.proto", 112,
  &descriptor_table_user_2eproto_once, descriptor_table_user_2eproto_sccs, descriptor_table_user_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_user_2eproto::offsets,
  file_level_metadata_user_2eproto, 1, file_level_enum_descriptors_user_2eproto, file_level_service_descriptors_user_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_user_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_user_2eproto)), true);

// ===================================================================

class AccRegister::_Internal {
 public:
};

AccRegister::AccRegister(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:AccRegister)
}
AccRegister::AccRegister(const AccRegister& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  email_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_email().empty()) {
    email_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_email(), 
      GetArena());
  }
  phone_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_phone().empty()) {
    phone_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_phone(), 
      GetArena());
  }
  accname_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_accname().empty()) {
    accname_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_accname(), 
      GetArena());
  }
  passwd_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_passwd().empty()) {
    passwd_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_passwd(), 
      GetArena());
  }
  type_ = from.type_;
  // @@protoc_insertion_point(copy_constructor:AccRegister)
}

void AccRegister::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_AccRegister_user_2eproto.base);
  email_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  phone_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  accname_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  passwd_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  type_ = 0;
}

AccRegister::~AccRegister() {
  // @@protoc_insertion_point(destructor:AccRegister)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void AccRegister::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  email_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  phone_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  accname_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  passwd_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void AccRegister::ArenaDtor(void* object) {
  AccRegister* _this = reinterpret_cast< AccRegister* >(object);
  (void)_this;
}
void AccRegister::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void AccRegister::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const AccRegister& AccRegister::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_AccRegister_user_2eproto.base);
  return *internal_default_instance();
}


void AccRegister::Clear() {
// @@protoc_insertion_point(message_clear_start:AccRegister)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  email_.ClearToEmpty();
  phone_.ClearToEmpty();
  accname_.ClearToEmpty();
  passwd_.ClearToEmpty();
  type_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* AccRegister::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string email = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_email();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "AccRegister.email"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string phone = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_phone();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "AccRegister.phone"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string accname = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          auto str = _internal_mutable_accname();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "AccRegister.accname"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string passwd = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
          auto str = _internal_mutable_passwd();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "AccRegister.passwd"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* AccRegister::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:AccRegister)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 type = 1;
  if (this->type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_type(), target);
  }

  // string email = 2;
  if (this->email().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_email().data(), static_cast<int>(this->_internal_email().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "AccRegister.email");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_email(), target);
  }

  // string phone = 3;
  if (this->phone().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_phone().data(), static_cast<int>(this->_internal_phone().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "AccRegister.phone");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_phone(), target);
  }

  // string accname = 4;
  if (this->accname().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_accname().data(), static_cast<int>(this->_internal_accname().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "AccRegister.accname");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_accname(), target);
  }

  // string passwd = 5;
  if (this->passwd().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_passwd().data(), static_cast<int>(this->_internal_passwd().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "AccRegister.passwd");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_passwd(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AccRegister)
  return target;
}

size_t AccRegister::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:AccRegister)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string email = 2;
  if (this->email().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_email());
  }

  // string phone = 3;
  if (this->phone().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_phone());
  }

  // string accname = 4;
  if (this->accname().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_accname());
  }

  // string passwd = 5;
  if (this->passwd().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_passwd());
  }

  // int32 type = 1;
  if (this->type() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_type());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void AccRegister::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:AccRegister)
  GOOGLE_DCHECK_NE(&from, this);
  const AccRegister* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<AccRegister>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:AccRegister)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:AccRegister)
    MergeFrom(*source);
  }
}

void AccRegister::MergeFrom(const AccRegister& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:AccRegister)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.email().size() > 0) {
    _internal_set_email(from._internal_email());
  }
  if (from.phone().size() > 0) {
    _internal_set_phone(from._internal_phone());
  }
  if (from.accname().size() > 0) {
    _internal_set_accname(from._internal_accname());
  }
  if (from.passwd().size() > 0) {
    _internal_set_passwd(from._internal_passwd());
  }
  if (from.type() != 0) {
    _internal_set_type(from._internal_type());
  }
}

void AccRegister::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:AccRegister)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AccRegister::CopyFrom(const AccRegister& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:AccRegister)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AccRegister::IsInitialized() const {
  return true;
}

void AccRegister::InternalSwap(AccRegister* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  email_.Swap(&other->email_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  phone_.Swap(&other->phone_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  accname_.Swap(&other->accname_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  passwd_.Swap(&other->passwd_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  swap(type_, other->type_);
}

::PROTOBUF_NAMESPACE_ID::Metadata AccRegister::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::AccRegister* Arena::CreateMaybeMessage< ::AccRegister >(Arena* arena) {
  return Arena::CreateMessageInternal< ::AccRegister >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
