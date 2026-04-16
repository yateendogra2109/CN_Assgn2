//
// Generated file, do not edit! Created by opp_msgtool 6.3 from Messages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "Messages_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(SubtaskMsg)

SubtaskMsg::SubtaskMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

SubtaskMsg::SubtaskMsg(const SubtaskMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

SubtaskMsg::~SubtaskMsg()
{
    delete [] this->dataArr;
}

SubtaskMsg& SubtaskMsg::operator=(const SubtaskMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SubtaskMsg::copy(const SubtaskMsg& other)
{
    this->subtaskID = other.subtaskID;
    this->targetClientID = other.targetClientID;
    this->originClientID = other.originClientID;
    delete [] this->dataArr;
    this->dataArr = (other.dataArr_arraysize==0) ? nullptr : new int[other.dataArr_arraysize];
    dataArr_arraysize = other.dataArr_arraysize;
    for (size_t i = 0; i < dataArr_arraysize; i++) {
        this->dataArr[i] = other.dataArr[i];
    }
    this->dataSize = other.dataSize;
}

void SubtaskMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->subtaskID);
    doParsimPacking(b,this->targetClientID);
    doParsimPacking(b,this->originClientID);
    b->pack(dataArr_arraysize);
    doParsimArrayPacking(b,this->dataArr,dataArr_arraysize);
    doParsimPacking(b,this->dataSize);
}

void SubtaskMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->subtaskID);
    doParsimUnpacking(b,this->targetClientID);
    doParsimUnpacking(b,this->originClientID);
    delete [] this->dataArr;
    b->unpack(dataArr_arraysize);
    if (dataArr_arraysize == 0) {
        this->dataArr = nullptr;
    } else {
        this->dataArr = new int[dataArr_arraysize];
        doParsimArrayUnpacking(b,this->dataArr,dataArr_arraysize);
    }
    doParsimUnpacking(b,this->dataSize);
}

int SubtaskMsg::getSubtaskID() const
{
    return this->subtaskID;
}

void SubtaskMsg::setSubtaskID(int subtaskID)
{
    this->subtaskID = subtaskID;
}

int SubtaskMsg::getTargetClientID() const
{
    return this->targetClientID;
}

void SubtaskMsg::setTargetClientID(int targetClientID)
{
    this->targetClientID = targetClientID;
}

int SubtaskMsg::getOriginClientID() const
{
    return this->originClientID;
}

void SubtaskMsg::setOriginClientID(int originClientID)
{
    this->originClientID = originClientID;
}

size_t SubtaskMsg::getDataArrArraySize() const
{
    return dataArr_arraysize;
}

int SubtaskMsg::getDataArr(size_t k) const
{
    if (k >= dataArr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dataArr_arraysize, (unsigned long)k);
    return this->dataArr[k];
}

void SubtaskMsg::setDataArrArraySize(size_t newSize)
{
    int *dataArr2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = dataArr_arraysize < newSize ? dataArr_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        dataArr2[i] = this->dataArr[i];
    for (size_t i = minSize; i < newSize; i++)
        dataArr2[i] = 0;
    delete [] this->dataArr;
    this->dataArr = dataArr2;
    dataArr_arraysize = newSize;
}

void SubtaskMsg::setDataArr(size_t k, int dataArr)
{
    if (k >= dataArr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dataArr_arraysize, (unsigned long)k);
    this->dataArr[k] = dataArr;
}

void SubtaskMsg::insertDataArr(size_t k, int dataArr)
{
    if (k > dataArr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dataArr_arraysize, (unsigned long)k);
    size_t newSize = dataArr_arraysize + 1;
    int *dataArr2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        dataArr2[i] = this->dataArr[i];
    dataArr2[k] = dataArr;
    for (i = k + 1; i < newSize; i++)
        dataArr2[i] = this->dataArr[i-1];
    delete [] this->dataArr;
    this->dataArr = dataArr2;
    dataArr_arraysize = newSize;
}

void SubtaskMsg::appendDataArr(int dataArr)
{
    insertDataArr(dataArr_arraysize, dataArr);
}

void SubtaskMsg::eraseDataArr(size_t k)
{
    if (k >= dataArr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dataArr_arraysize, (unsigned long)k);
    size_t newSize = dataArr_arraysize - 1;
    int *dataArr2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        dataArr2[i] = this->dataArr[i];
    for (i = k; i < newSize; i++)
        dataArr2[i] = this->dataArr[i+1];
    delete [] this->dataArr;
    this->dataArr = dataArr2;
    dataArr_arraysize = newSize;
}

int SubtaskMsg::getDataSize() const
{
    return this->dataSize;
}

void SubtaskMsg::setDataSize(int dataSize)
{
    this->dataSize = dataSize;
}

class SubtaskMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_subtaskID,
        FIELD_targetClientID,
        FIELD_originClientID,
        FIELD_dataArr,
        FIELD_dataSize,
    };
  public:
    SubtaskMsgDescriptor();
    virtual ~SubtaskMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SubtaskMsgDescriptor)

SubtaskMsgDescriptor::SubtaskMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(SubtaskMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

SubtaskMsgDescriptor::~SubtaskMsgDescriptor()
{
    delete[] propertyNames;
}

bool SubtaskMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SubtaskMsg *>(obj)!=nullptr;
}

const char **SubtaskMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SubtaskMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SubtaskMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int SubtaskMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_subtaskID
        FD_ISEDITABLE,    // FIELD_targetClientID
        FD_ISEDITABLE,    // FIELD_originClientID
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_dataArr
        FD_ISEDITABLE,    // FIELD_dataSize
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *SubtaskMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "subtaskID",
        "targetClientID",
        "originClientID",
        "dataArr",
        "dataSize",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int SubtaskMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "subtaskID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "targetClientID") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "originClientID") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "dataArr") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "dataSize") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *SubtaskMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_subtaskID
        "int",    // FIELD_targetClientID
        "int",    // FIELD_originClientID
        "int",    // FIELD_dataArr
        "int",    // FIELD_dataSize
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **SubtaskMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SubtaskMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SubtaskMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SubtaskMsg *pp = omnetpp::fromAnyPtr<SubtaskMsg>(object); (void)pp;
    switch (field) {
        case FIELD_dataArr: return pp->getDataArrArraySize();
        default: return 0;
    }
}

void SubtaskMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskMsg *pp = omnetpp::fromAnyPtr<SubtaskMsg>(object); (void)pp;
    switch (field) {
        case FIELD_dataArr: pp->setDataArrArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SubtaskMsg'", field);
    }
}

const char *SubtaskMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SubtaskMsg *pp = omnetpp::fromAnyPtr<SubtaskMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SubtaskMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SubtaskMsg *pp = omnetpp::fromAnyPtr<SubtaskMsg>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: return long2string(pp->getSubtaskID());
        case FIELD_targetClientID: return long2string(pp->getTargetClientID());
        case FIELD_originClientID: return long2string(pp->getOriginClientID());
        case FIELD_dataArr: return long2string(pp->getDataArr(i));
        case FIELD_dataSize: return long2string(pp->getDataSize());
        default: return "";
    }
}

void SubtaskMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskMsg *pp = omnetpp::fromAnyPtr<SubtaskMsg>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: pp->setSubtaskID(string2long(value)); break;
        case FIELD_targetClientID: pp->setTargetClientID(string2long(value)); break;
        case FIELD_originClientID: pp->setOriginClientID(string2long(value)); break;
        case FIELD_dataArr: pp->setDataArr(i,string2long(value)); break;
        case FIELD_dataSize: pp->setDataSize(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SubtaskMsg'", field);
    }
}

omnetpp::cValue SubtaskMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SubtaskMsg *pp = omnetpp::fromAnyPtr<SubtaskMsg>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: return pp->getSubtaskID();
        case FIELD_targetClientID: return pp->getTargetClientID();
        case FIELD_originClientID: return pp->getOriginClientID();
        case FIELD_dataArr: return pp->getDataArr(i);
        case FIELD_dataSize: return pp->getDataSize();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SubtaskMsg' as cValue -- field index out of range?", field);
    }
}

void SubtaskMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskMsg *pp = omnetpp::fromAnyPtr<SubtaskMsg>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: pp->setSubtaskID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_targetClientID: pp->setTargetClientID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_originClientID: pp->setOriginClientID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_dataArr: pp->setDataArr(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_dataSize: pp->setDataSize(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SubtaskMsg'", field);
    }
}

const char *SubtaskMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr SubtaskMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SubtaskMsg *pp = omnetpp::fromAnyPtr<SubtaskMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SubtaskMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskMsg *pp = omnetpp::fromAnyPtr<SubtaskMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SubtaskMsg'", field);
    }
}

Register_Class(ResultMsg)

ResultMsg::ResultMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

ResultMsg::ResultMsg(const ResultMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ResultMsg::~ResultMsg()
{
}

ResultMsg& ResultMsg::operator=(const ResultMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ResultMsg::copy(const ResultMsg& other)
{
    this->subtaskID = other.subtaskID;
    this->result = other.result;
    this->originClientID = other.originClientID;
    this->targetClientID = other.targetClientID;
}

void ResultMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->subtaskID);
    doParsimPacking(b,this->result);
    doParsimPacking(b,this->originClientID);
    doParsimPacking(b,this->targetClientID);
}

void ResultMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->subtaskID);
    doParsimUnpacking(b,this->result);
    doParsimUnpacking(b,this->originClientID);
    doParsimUnpacking(b,this->targetClientID);
}

int ResultMsg::getSubtaskID() const
{
    return this->subtaskID;
}

void ResultMsg::setSubtaskID(int subtaskID)
{
    this->subtaskID = subtaskID;
}

int ResultMsg::getResult() const
{
    return this->result;
}

void ResultMsg::setResult(int result)
{
    this->result = result;
}

int ResultMsg::getOriginClientID() const
{
    return this->originClientID;
}

void ResultMsg::setOriginClientID(int originClientID)
{
    this->originClientID = originClientID;
}

int ResultMsg::getTargetClientID() const
{
    return this->targetClientID;
}

void ResultMsg::setTargetClientID(int targetClientID)
{
    this->targetClientID = targetClientID;
}

class ResultMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_subtaskID,
        FIELD_result,
        FIELD_originClientID,
        FIELD_targetClientID,
    };
  public:
    ResultMsgDescriptor();
    virtual ~ResultMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ResultMsgDescriptor)

ResultMsgDescriptor::ResultMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ResultMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

ResultMsgDescriptor::~ResultMsgDescriptor()
{
    delete[] propertyNames;
}

bool ResultMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ResultMsg *>(obj)!=nullptr;
}

const char **ResultMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ResultMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ResultMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int ResultMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_subtaskID
        FD_ISEDITABLE,    // FIELD_result
        FD_ISEDITABLE,    // FIELD_originClientID
        FD_ISEDITABLE,    // FIELD_targetClientID
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *ResultMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "subtaskID",
        "result",
        "originClientID",
        "targetClientID",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int ResultMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "subtaskID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "result") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "originClientID") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "targetClientID") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *ResultMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_subtaskID
        "int",    // FIELD_result
        "int",    // FIELD_originClientID
        "int",    // FIELD_targetClientID
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **ResultMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ResultMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ResultMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ResultMsg *pp = omnetpp::fromAnyPtr<ResultMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ResultMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ResultMsg *pp = omnetpp::fromAnyPtr<ResultMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ResultMsg'", field);
    }
}

const char *ResultMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ResultMsg *pp = omnetpp::fromAnyPtr<ResultMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ResultMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ResultMsg *pp = omnetpp::fromAnyPtr<ResultMsg>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: return long2string(pp->getSubtaskID());
        case FIELD_result: return long2string(pp->getResult());
        case FIELD_originClientID: return long2string(pp->getOriginClientID());
        case FIELD_targetClientID: return long2string(pp->getTargetClientID());
        default: return "";
    }
}

void ResultMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ResultMsg *pp = omnetpp::fromAnyPtr<ResultMsg>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: pp->setSubtaskID(string2long(value)); break;
        case FIELD_result: pp->setResult(string2long(value)); break;
        case FIELD_originClientID: pp->setOriginClientID(string2long(value)); break;
        case FIELD_targetClientID: pp->setTargetClientID(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ResultMsg'", field);
    }
}

omnetpp::cValue ResultMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ResultMsg *pp = omnetpp::fromAnyPtr<ResultMsg>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: return pp->getSubtaskID();
        case FIELD_result: return pp->getResult();
        case FIELD_originClientID: return pp->getOriginClientID();
        case FIELD_targetClientID: return pp->getTargetClientID();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ResultMsg' as cValue -- field index out of range?", field);
    }
}

void ResultMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ResultMsg *pp = omnetpp::fromAnyPtr<ResultMsg>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: pp->setSubtaskID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_result: pp->setResult(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_originClientID: pp->setOriginClientID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_targetClientID: pp->setTargetClientID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ResultMsg'", field);
    }
}

const char *ResultMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ResultMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ResultMsg *pp = omnetpp::fromAnyPtr<ResultMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ResultMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ResultMsg *pp = omnetpp::fromAnyPtr<ResultMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ResultMsg'", field);
    }
}

Register_Class(RoutingMsg)

RoutingMsg::RoutingMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

RoutingMsg::RoutingMsg(const RoutingMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RoutingMsg::~RoutingMsg()
{
}

RoutingMsg& RoutingMsg::operator=(const RoutingMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RoutingMsg::copy(const RoutingMsg& other)
{
    this->finalDestID = other.finalDestID;
    this->payloadType = other.payloadType;
}

void RoutingMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->finalDestID);
    doParsimPacking(b,this->payloadType);
}

void RoutingMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->finalDestID);
    doParsimUnpacking(b,this->payloadType);
}

int RoutingMsg::getFinalDestID() const
{
    return this->finalDestID;
}

void RoutingMsg::setFinalDestID(int finalDestID)
{
    this->finalDestID = finalDestID;
}

const char * RoutingMsg::getPayloadType() const
{
    return this->payloadType.c_str();
}

void RoutingMsg::setPayloadType(const char * payloadType)
{
    this->payloadType = payloadType;
}

class RoutingMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_finalDestID,
        FIELD_payloadType,
    };
  public:
    RoutingMsgDescriptor();
    virtual ~RoutingMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RoutingMsgDescriptor)

RoutingMsgDescriptor::RoutingMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(RoutingMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

RoutingMsgDescriptor::~RoutingMsgDescriptor()
{
    delete[] propertyNames;
}

bool RoutingMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RoutingMsg *>(obj)!=nullptr;
}

const char **RoutingMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RoutingMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RoutingMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RoutingMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_finalDestID
        FD_ISEDITABLE,    // FIELD_payloadType
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RoutingMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "finalDestID",
        "payloadType",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RoutingMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "finalDestID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "payloadType") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RoutingMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_finalDestID
        "string",    // FIELD_payloadType
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RoutingMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RoutingMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RoutingMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RoutingMsg *pp = omnetpp::fromAnyPtr<RoutingMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RoutingMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RoutingMsg *pp = omnetpp::fromAnyPtr<RoutingMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RoutingMsg'", field);
    }
}

const char *RoutingMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RoutingMsg *pp = omnetpp::fromAnyPtr<RoutingMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RoutingMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RoutingMsg *pp = omnetpp::fromAnyPtr<RoutingMsg>(object); (void)pp;
    switch (field) {
        case FIELD_finalDestID: return long2string(pp->getFinalDestID());
        case FIELD_payloadType: return oppstring2string(pp->getPayloadType());
        default: return "";
    }
}

void RoutingMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RoutingMsg *pp = omnetpp::fromAnyPtr<RoutingMsg>(object); (void)pp;
    switch (field) {
        case FIELD_finalDestID: pp->setFinalDestID(string2long(value)); break;
        case FIELD_payloadType: pp->setPayloadType((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RoutingMsg'", field);
    }
}

omnetpp::cValue RoutingMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RoutingMsg *pp = omnetpp::fromAnyPtr<RoutingMsg>(object); (void)pp;
    switch (field) {
        case FIELD_finalDestID: return pp->getFinalDestID();
        case FIELD_payloadType: return pp->getPayloadType();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RoutingMsg' as cValue -- field index out of range?", field);
    }
}

void RoutingMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RoutingMsg *pp = omnetpp::fromAnyPtr<RoutingMsg>(object); (void)pp;
    switch (field) {
        case FIELD_finalDestID: pp->setFinalDestID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_payloadType: pp->setPayloadType(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RoutingMsg'", field);
    }
}

const char *RoutingMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RoutingMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RoutingMsg *pp = omnetpp::fromAnyPtr<RoutingMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RoutingMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RoutingMsg *pp = omnetpp::fromAnyPtr<RoutingMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RoutingMsg'", field);
    }
}

Register_Class(GossipMsg)

GossipMsg::GossipMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

GossipMsg::GossipMsg(const GossipMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

GossipMsg::~GossipMsg()
{
}

GossipMsg& GossipMsg::operator=(const GossipMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void GossipMsg::copy(const GossipMsg& other)
{
    this->content = other.content;
    this->originID = other.originID;
    this->fromID = other.fromID;
}

void GossipMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->content);
    doParsimPacking(b,this->originID);
    doParsimPacking(b,this->fromID);
}

void GossipMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->content);
    doParsimUnpacking(b,this->originID);
    doParsimUnpacking(b,this->fromID);
}

const char * GossipMsg::getContent() const
{
    return this->content.c_str();
}

void GossipMsg::setContent(const char * content)
{
    this->content = content;
}

int GossipMsg::getOriginID() const
{
    return this->originID;
}

void GossipMsg::setOriginID(int originID)
{
    this->originID = originID;
}

int GossipMsg::getFromID() const
{
    return this->fromID;
}

void GossipMsg::setFromID(int fromID)
{
    this->fromID = fromID;
}

class GossipMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_content,
        FIELD_originID,
        FIELD_fromID,
    };
  public:
    GossipMsgDescriptor();
    virtual ~GossipMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(GossipMsgDescriptor)

GossipMsgDescriptor::GossipMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(GossipMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

GossipMsgDescriptor::~GossipMsgDescriptor()
{
    delete[] propertyNames;
}

bool GossipMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GossipMsg *>(obj)!=nullptr;
}

const char **GossipMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GossipMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GossipMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int GossipMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_content
        FD_ISEDITABLE,    // FIELD_originID
        FD_ISEDITABLE,    // FIELD_fromID
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *GossipMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "content",
        "originID",
        "fromID",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int GossipMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "content") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "originID") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "fromID") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *GossipMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_content
        "int",    // FIELD_originID
        "int",    // FIELD_fromID
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **GossipMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GossipMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GossipMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GossipMsg *pp = omnetpp::fromAnyPtr<GossipMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GossipMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMsg *pp = omnetpp::fromAnyPtr<GossipMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GossipMsg'", field);
    }
}

const char *GossipMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GossipMsg *pp = omnetpp::fromAnyPtr<GossipMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GossipMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GossipMsg *pp = omnetpp::fromAnyPtr<GossipMsg>(object); (void)pp;
    switch (field) {
        case FIELD_content: return oppstring2string(pp->getContent());
        case FIELD_originID: return long2string(pp->getOriginID());
        case FIELD_fromID: return long2string(pp->getFromID());
        default: return "";
    }
}

void GossipMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMsg *pp = omnetpp::fromAnyPtr<GossipMsg>(object); (void)pp;
    switch (field) {
        case FIELD_content: pp->setContent((value)); break;
        case FIELD_originID: pp->setOriginID(string2long(value)); break;
        case FIELD_fromID: pp->setFromID(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GossipMsg'", field);
    }
}

omnetpp::cValue GossipMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GossipMsg *pp = omnetpp::fromAnyPtr<GossipMsg>(object); (void)pp;
    switch (field) {
        case FIELD_content: return pp->getContent();
        case FIELD_originID: return pp->getOriginID();
        case FIELD_fromID: return pp->getFromID();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GossipMsg' as cValue -- field index out of range?", field);
    }
}

void GossipMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMsg *pp = omnetpp::fromAnyPtr<GossipMsg>(object); (void)pp;
    switch (field) {
        case FIELD_content: pp->setContent(value.stringValue()); break;
        case FIELD_originID: pp->setOriginID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_fromID: pp->setFromID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GossipMsg'", field);
    }
}

const char *GossipMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr GossipMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GossipMsg *pp = omnetpp::fromAnyPtr<GossipMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GossipMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMsg *pp = omnetpp::fromAnyPtr<GossipMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GossipMsg'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

