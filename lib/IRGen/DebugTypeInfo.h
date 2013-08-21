//===--- DebugTypeInfo.h - Type Info for Debugging --------------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// This file defines the data structure that holds all the debug info
// we want to emit for types.
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_IRGEN_DEBUGTYPEINFO_H
#define SWIFT_IRGEN_DEBUGTYPEINFO_H

#include "swift/AST/Types.h"

namespace llvm {
  class Type;
}

namespace swift {
  namespace irgen {
    class Alignment;
    class Size;
    class TypeInfo;

    /// This data structure holds all the debug info we want to emit
    /// for types. It also provides a useful abstraction while we
    /// decide on what type of debug info we want to emit for types.
    class DebugTypeInfo {
    public:
      Type Ty;
      uint64_t SizeInBytes;
      uint64_t AlignInBytes;

      DebugTypeInfo()
        : Ty(),  SizeInBytes(0), AlignInBytes(0) {
      }
      DebugTypeInfo(Type Ty, uint64_t Size, uint64_t Align);
      DebugTypeInfo(Type Ty, Size Size, Alignment Align);
      DebugTypeInfo(Type Ty, const TypeInfo &Info);
      DebugTypeInfo(const ValueDecl &Decl, const TypeInfo &Info);
      DebugTypeInfo(const ValueDecl &Decl, Size Size, Alignment Align);

      bool operator==(DebugTypeInfo T) const;
      bool operator!=(DebugTypeInfo T) const;

    };
  }
}

namespace llvm {

  // Dense map specialization.
  template<> struct DenseMapInfo<swift::irgen::DebugTypeInfo> {
    static swift::irgen::DebugTypeInfo getEmptyKey() {
      return swift::irgen::DebugTypeInfo();
    }
    static swift::irgen::DebugTypeInfo getTombstoneKey() {
      return swift::irgen::DebugTypeInfo(llvm::DenseMapInfo<swift::Type>
                                         ::getTombstoneKey(), 0, 0);
    }
    static unsigned getHashValue(swift::irgen::DebugTypeInfo Val) {
      return DenseMapInfo<swift::CanType>::getHashValue(Val.Ty);
    }
    static bool isEqual(swift::irgen::DebugTypeInfo LHS,
                        swift::irgen::DebugTypeInfo RHS) {
      return LHS == RHS;
    }
  };
}

#endif
