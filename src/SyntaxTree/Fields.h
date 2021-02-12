//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_FIELDS_H
#define DECAFCOMPILER_FIELDS_H

#include "Node.h"
#include "Field.h"

namespace SyntaxTree {
    class Fields : public Node {
    private:
        std::vector<Field *>fields;
    public:
        void handleScope() override;

        const std::vector<Field *> &getFields() const;
        void addField(Field *field);
    };

}


#endif //DECAFCOMPILER_FIELDS_H
