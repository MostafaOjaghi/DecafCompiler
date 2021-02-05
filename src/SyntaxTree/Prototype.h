//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_PROTOTYPE_H
#define DECAFCOMPILER_PROTOTYPE_H

#include "Node.h"
#include "Formals.h"

namespace SyntaxTree {
    class Prototype : public Node {

    };

    class PrototypeToTypeIdent : public Prototype {
    private:
        Type *type;
    public:
        Type *getType() const;

        void setType(Type *type);

    private:
        std::string prototypeDeclId;
        Formals *formals;
    public:
        const std::string &getPrototypeDeclId() const;

        void setPrototypeDeclId(const std::string &prototypeDeclId);

        Formals *getFormals() const;

        void setFormals(Formals *formals);
    };

    class PrototypeToVoid : public Prototype {
    private:
        std::string prototypeDeclId;
        Formals *formals;
    public:
        const std::string &getPrototypeDeclId() const;

        void setPrototypeDeclId(const std::string &prototypeDeclId);

        Formals *getFormals() const;

        void setFormals(Formals *formals);
    };
}


#endif //DECAFCOMPILER_PROTOTYPE_H
