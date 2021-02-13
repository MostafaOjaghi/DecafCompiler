//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_CLASSDECL_H
#define DECAFCOMPILER_CLASSDECL_H

#include "Node.h"
#include "Extends.h"
#include "Implements.h"
#include "Fields.h"

namespace SyntaxTree {
    class ClassDecl : public Node {
    private:
        std::string Id;
        Extends *extends;
        Implements *implements;
        Fields *fields;
    public:
        void handleClassHierarchy() override;

        void handleScope() override;

        const std::string &getId() const;

        void setId(const std::string &id);

        Extends *getExtends() const;

        void setExtends(Extends *extends);

        Implements *getImplements() const;

        void setImplements(Implements *implements);

        Fields *getFields() const;

        void setFields(Fields *fields);
    };
}


#endif //DECAFCOMPILER_CLASSDECL_H
