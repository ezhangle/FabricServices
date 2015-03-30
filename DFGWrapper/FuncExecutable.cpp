// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "FuncExecutable.h"

using namespace FabricServices::DFGWrapper;

FuncExecutable::FuncExecutable(
  FabricCore::DFGBinding binding,
  FabricCore::DFGExec exec,
  const char * funcPath
  )
: Executable(binding, exec, funcPath)
{
}

FuncExecutablePtr FuncExecutable::Create(
  FabricCore::DFGBinding binding,
  FabricCore::DFGExec exec,
  const char * funcPath
  )
{
  return new FuncExecutable( binding, exec, funcPath );
}

FuncExecutable::~FuncExecutable()
{
}

char const* FuncExecutable::getCode()
{
  return getWrappedCoreExec().getCode();
}

void FuncExecutable::setCode(char const *code)
{
  getWrappedCoreExec().setCode(code);
}

