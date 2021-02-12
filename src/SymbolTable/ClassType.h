//
// Created by mostafa on 2/5/21.
//

#ifndef DECAFCOMPILER_CLASSTYPE_H
#define DECAFCOMPILER_CLASSTYPE_H

#include <string>
#include <map>
#include <vector>


namespace SymbolTable {
    class Scope;

    class ClassType {
        static std::map<std::string, ClassType *>mp;
        ClassType *parent;
        std::string parentName;
        std::string Id;
        SymbolTable::Scope *scope;
        std::vector<std::string>objectLayout;

    public:
        Scope *getScope() const;

        void setScope(Scope *scope);
        void addToLayout(const std::string &s);
        int getIndexInObjectLayout(const std::string &s);
        int getObjectLayoutSize();
    private:
        bool handleHierarchyCalled = false;
    public:
        const std::string &getParentName() const;

        void setParentName(const std::string &parentName);

        ClassType();

        explicit ClassType(const std::string &id);

        void handleHierarchy();

        void setParent(ClassType *parent);

        const std::string &getId() const;

        void setId(const std::string &id);

        ClassType *getParent() const;

        static void addType(ClassType *classType);
        static ClassType *getClass(std::string className);
    };
}

#endif //DECAFCOMPILER_CLASSTYPE_H
