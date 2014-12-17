// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Executable.h"

using namespace FabricServices::DFGWrapper;

Executable::Executable(FabricCore::DFGBinding binding, std::string path)
{
  m_binding = binding;
  m_path = path;
}

Executable::Executable(const Executable & other)
{
  m_binding = other.m_binding;
  m_path = other.m_path;
  m_objectType = other.m_objectType;
}

Executable::~Executable()
{
}

bool Executable::isValid() const
{
  return m_binding.isValid();
}


FabricCore::DFGBinding Executable::getWrappedCoreBinding() const
{
  return m_binding;
}

std::string Executable::getDesc()
{
  return m_binding.getDesc(m_path.c_str()).getCString();
}

std::string Executable::getObjectType()
{
  if(m_objectType.length() == 0)
  {
    FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
    m_objectType = descVar.getDictValue("objectType")->getStringData();    
  }
  return m_objectType;
}

std::string Executable::getPath()
{
  return m_path;
}

std::string Executable::getTitle()
{
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  return descVar.getDictValue("title")->getStringData();    
}

std::vector<Port> Executable::getPorts()
{
  std::vector<Port> result;

  std::string prefix = getPath();
  if(prefix.length() > 0)
    prefix += ".";

  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * portsVar = descVar.getDictValue("ports");
  for(uint32_t i=0;i<portsVar->getArraySize();i++)
  {
    const FabricCore::Variant * portVar = portsVar->getArrayElement(i);
    const FabricCore::Variant * nameVar = portVar->getDictValue("name");
    std::string nameStr = nameVar->getStringData();
    result.push_back(Port(getWrappedCoreBinding(), prefix + nameStr));
  }
  return result;
}

Port Executable::getPort(char const * name)
{
  std::string prefix = getPath();
  if(prefix.length() > 0)
    prefix += ".";
  return Port(getWrappedCoreBinding(), prefix + name);
}

Port Executable::getPort(uint32_t index)
{
  return getPorts()[index];
}

void Executable::removePort(Port port)
{
  removePort(port.getName().c_str());
}

void Executable::removePort(char const * name)
{
  std::string prefix = getPath();
  if(prefix.length() > 0)
    prefix += ".";
  m_binding.destroy((prefix + name).c_str());
}

void Executable::removePort(uint32_t index)
{
  removePort(getPorts()[index]);
}

std::vector<std::string> Executable::getErrors()
{
  std::vector<std::string> result;
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * errorsVar = descVar.getDictValue("errors");
  if(!errorsVar)
    return result;
  for(uint32_t i=0;i<errorsVar->getArraySize();i++)
  {
    const FabricCore::Variant * errorVar = errorsVar->getArrayElement(i);
    std::string errorStr = errorVar->getStringData();
    result.push_back(errorStr);
  }
  return result;
}

std::string Executable::exportJSON()
{
  return m_binding.exportJSON(m_path.c_str()).getCString();
}

std::string Executable::getMetadata(char const * key)
{
  return m_binding.getMetadata(m_path.c_str(), key);
}

void Executable::setMetadata(char const *key, char const * metadata, bool canUndo)
{
  return m_binding.setMetadata(m_path.c_str(), key, metadata, canUndo);
}

void Executable::addExtensionDependency(char const * ext)
{
  m_binding.addExtDep(m_path.c_str(), ext);
}

std::string Executable::getImportPathname()
{
  return m_binding.getImportPathname(m_path.c_str());
}

void Executable::setImportPathname( char const *importPathname )
{
  m_binding.setImportPathname(m_path.c_str(), importPathname);
}

Port Executable::addPort(char const *title, FabricCore::DFGPortType portType, char const *dataType)
{
  std::string result = m_binding.addPort(m_path.c_str(), title, portType, dataType).getCString();
  return Port(m_binding, result);
}

void Executable::attachPreset(char const *parentPresetPath, char const *desiredName)
{
  m_binding.attachPreset(m_path.c_str(), parentPresetPath, desiredName);
}