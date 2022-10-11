#pragma once

#include <types/type.hpp>

namespace types {

// Built-in type singletons
extern BuiltinType  //
    builtin_unit,   //
    builtin_int,    //
    builtin_bool,   //
    builtin_string;

//////////////////////////////////////////////////////////////////////

class BuiltinType : public Type {
 public:
  bool IsEqual(Type* other) override {
    return other->IsEqual(this);
  }

  bool IsEqual(BuiltinType* other) override {
    return other == this;
  }

  bool IsEqual(PointerType*) override {
    // Allow initializing pointers with unit
    return this == &builtin_unit;
  }

  bool IsEqual(StructType*) override {
    return false;
  }

  bool IsEqual(FnType*) override {
    return false;
  }
};

//////////////////////////////////////////////////////////////////////

}  // namespace types
