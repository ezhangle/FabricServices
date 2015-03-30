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

FuncExecutable::FuncExecutable(const Executable & other)
: Executable(other)
{
}

FuncExecutable::FuncExecutable(const FuncExecutable & other)
: Executable(other)
{
}

FuncExecutable::~FuncExecutable()
{
}

std::string FuncExecutable::getCode()
{
  // FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  // const FabricCore::Variant * codeVar = descVar.getDictValue("code");
  // return codeVar->getStringData();
  // todo
  return "";
}

void FuncExecutable::setCode(char const *code)
{
  getWrappedCoreExec().setCode(code);
}

