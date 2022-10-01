#pragma once

namespace types {

class BuiltinType;
class StructType;
class PointerType;
class FnType;

//////////////////////////////////////////////////////////////////////

class Type {
 public:
  ~Type() = default;

  // To resolve the first type
  virtual bool IsEqual(Type* other) = 0;

  bool DiffersFrom(Type* other) {
    return !IsEqual(other);
  }

  // To resolve the second type
  virtual bool IsEqual(PointerType* other) = 0;
  virtual bool IsEqual(BuiltinType* other) = 0;
  virtual bool IsEqual(StructType* other) = 0;
  virtual bool IsEqual(FnType* other) = 0;
};

//////////////////////////////////////////////////////////////////////

};  // namespace types
