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
        std::vector<std::string> objectLayout;
        std::vector<std::string> methods;

        int getMethodIndex(std::string id);

    public:
        Scope *getScope() const;

        void setScope(Scope *scope);
        void addToLayout(const std::string &s);
        int getIndexInObjectLayout(const std::string &s);
        int getObjectLayoutSize();
        void addMethod(std::string id);
        int getMethodPosition(std::string id);
        int getVtableSize();
        bool hasMethod(std::string id);
        std::vector<std::string> getVtable();

    private:
        bool handleHierarchyCalled = false;
    public:
        const std::string &getParentName() const;

        void setParentName(const std::string &parentName);

        ClassType() = default;

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
