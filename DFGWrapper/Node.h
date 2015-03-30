// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Node__
#define __DFGWrapper_Node__

#include <FabricCore.h>
#include <string>
#include <vector>
#include "Executable.h"
// #include "Pin.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Node : public Element
    {
      friend class Binding;
      friend class GraphExecutable;
      friend class View;

    public:

      Node();
      Node(const Node & other);
      virtual ~Node();

      FabricCore::DFGBinding getWrappedCoreBinding() const;
      char const *getNodePath() const
        { return getElementPath(); }

      Executable getParentExecutable();
      Executable getExecutable();

      virtual std::string getDesc();
      std::string getTitle();
      void setTitle(char const *title);
      std::vector<std::string> getDataTypes();

      FEC_DFGCacheRule getCacheRule() const;
      void setCacheRule(FEC_DFGCacheRule rule);

      virtual char const *getMetadata(char const * key) const;
      virtual void setMetadata(char const * key, char const * metadata, bool canUndo);

      // todo
      // std::vector<Pin> getPins();
      // Pin getPin(char const * name);
      // Pin getPin(uint32_t index);

    protected:
      
      Node(
        FabricCore::DFGBinding binding,
        FabricCore::DFGExec parentExec,
        char const *execPath,
        char const *nodePath
        );

    private:
      std::string m_execPath;
    };

  };

};


#endif // __DFGWrapper_Node__
