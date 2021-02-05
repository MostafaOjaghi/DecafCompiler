//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_INTERFACEDECL_H
#define DECAFCOMPILER_INTERFACEDECL_H

#include "Node.h"
#include "Prototypes.h"

namespace SyntaxTree {
    class InterfaceDecl : public Node {
    private:
        std::string interfaceId;
        Prototypes *prototypes;
    public:
        Prototypes *getPrototypes() const;

        void setPrototypes(Prototypes *prototypes);

    public:
        const std::string &getInterfaceId() const;

        void setInterfaceId(const std::string &interfaceId);
    };
}


#endif //DECAFCOMPILER_INTERFACEDECL_H
