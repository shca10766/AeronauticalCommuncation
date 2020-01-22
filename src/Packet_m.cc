//
// Generated file, do not edit! Created by nedtool 5.5 from Packet.msg.
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
#include "Packet_m.h"

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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(Packet)

Packet::Packet(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->id_aircraft = 0;
    this->id_baseStation = 0;
    this->x_aircraft = 0;
    this->y_aircraft = 0;
    this->distant_AC_BS = 0;
    this->departureAC_time = 0;
    this->arrivalBS_time = 0;
    this->departureBS_time = 0;
    this->arrivalCT_time = 0;
}

Packet::Packet(const Packet& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

Packet::~Packet()
{
}

Packet& Packet::operator=(const Packet& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void Packet::copy(const Packet& other)
{
    this->id_aircraft = other.id_aircraft;
    this->id_baseStation = other.id_baseStation;
    this->x_aircraft = other.x_aircraft;
    this->y_aircraft = other.y_aircraft;
    this->distant_AC_BS = other.distant_AC_BS;
    this->departureAC_time = other.departureAC_time;
    this->arrivalBS_time = other.arrivalBS_time;
    this->departureBS_time = other.departureBS_time;
    this->arrivalCT_time = other.arrivalCT_time;
}

void Packet::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->id_aircraft);
    doParsimPacking(b,this->id_baseStation);
    doParsimPacking(b,this->x_aircraft);
    doParsimPacking(b,this->y_aircraft);
    doParsimPacking(b,this->distant_AC_BS);
    doParsimPacking(b,this->departureAC_time);
    doParsimPacking(b,this->arrivalBS_time);
    doParsimPacking(b,this->departureBS_time);
    doParsimPacking(b,this->arrivalCT_time);
}

void Packet::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->id_aircraft);
    doParsimUnpacking(b,this->id_baseStation);
    doParsimUnpacking(b,this->x_aircraft);
    doParsimUnpacking(b,this->y_aircraft);
    doParsimUnpacking(b,this->distant_AC_BS);
    doParsimUnpacking(b,this->departureAC_time);
    doParsimUnpacking(b,this->arrivalBS_time);
    doParsimUnpacking(b,this->departureBS_time);
    doParsimUnpacking(b,this->arrivalCT_time);
}

int Packet::getId_aircraft() const
{
    return this->id_aircraft;
}

void Packet::setId_aircraft(int id_aircraft)
{
    this->id_aircraft = id_aircraft;
}

int Packet::getId_baseStation() const
{
    return this->id_baseStation;
}

void Packet::setId_baseStation(int id_baseStation)
{
    this->id_baseStation = id_baseStation;
}

double Packet::getX_aircraft() const
{
    return this->x_aircraft;
}

void Packet::setX_aircraft(double x_aircraft)
{
    this->x_aircraft = x_aircraft;
}

double Packet::getY_aircraft() const
{
    return this->y_aircraft;
}

void Packet::setY_aircraft(double y_aircraft)
{
    this->y_aircraft = y_aircraft;
}

double Packet::getDistant_AC_BS() const
{
    return this->distant_AC_BS;
}

void Packet::setDistant_AC_BS(double distant_AC_BS)
{
    this->distant_AC_BS = distant_AC_BS;
}

double Packet::getDepartureAC_time() const
{
    return this->departureAC_time;
}

void Packet::setDepartureAC_time(double departureAC_time)
{
    this->departureAC_time = departureAC_time;
}

double Packet::getArrivalBS_time() const
{
    return this->arrivalBS_time;
}

void Packet::setArrivalBS_time(double arrivalBS_time)
{
    this->arrivalBS_time = arrivalBS_time;
}

double Packet::getDepartureBS_time() const
{
    return this->departureBS_time;
}

void Packet::setDepartureBS_time(double departureBS_time)
{
    this->departureBS_time = departureBS_time;
}

double Packet::getArrivalCT_time() const
{
    return this->arrivalCT_time;
}

void Packet::setArrivalCT_time(double arrivalCT_time)
{
    this->arrivalCT_time = arrivalCT_time;
}

class PacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PacketDescriptor();
    virtual ~PacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(PacketDescriptor)

PacketDescriptor::PacketDescriptor() : omnetpp::cClassDescriptor("Packet", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

PacketDescriptor::~PacketDescriptor()
{
    delete[] propertynames;
}

bool PacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Packet *>(obj)!=nullptr;
}

const char **PacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount() : 9;
}

unsigned int PacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *PacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "id_aircraft",
        "id_baseStation",
        "x_aircraft",
        "y_aircraft",
        "distant_AC_BS",
        "departureAC_time",
        "arrivalBS_time",
        "departureBS_time",
        "arrivalCT_time",
    };
    return (field>=0 && field<9) ? fieldNames[field] : nullptr;
}

int PacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id_aircraft")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "id_baseStation")==0) return base+1;
    if (fieldName[0]=='x' && strcmp(fieldName, "x_aircraft")==0) return base+2;
    if (fieldName[0]=='y' && strcmp(fieldName, "y_aircraft")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "distant_AC_BS")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "departureAC_time")==0) return base+5;
    if (fieldName[0]=='a' && strcmp(fieldName, "arrivalBS_time")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "departureBS_time")==0) return base+7;
    if (fieldName[0]=='a' && strcmp(fieldName, "arrivalCT_time")==0) return base+8;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "double",
        "double",
        "double",
        "double",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : nullptr;
}

const char **PacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *PacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int PacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Packet *pp = (Packet *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Packet *pp = (Packet *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Packet *pp = (Packet *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getId_aircraft());
        case 1: return long2string(pp->getId_baseStation());
        case 2: return double2string(pp->getX_aircraft());
        case 3: return double2string(pp->getY_aircraft());
        case 4: return double2string(pp->getDistant_AC_BS());
        case 5: return double2string(pp->getDepartureAC_time());
        case 6: return double2string(pp->getArrivalBS_time());
        case 7: return double2string(pp->getDepartureBS_time());
        case 8: return double2string(pp->getArrivalCT_time());
        default: return "";
    }
}

bool PacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Packet *pp = (Packet *)object; (void)pp;
    switch (field) {
        case 0: pp->setId_aircraft(string2long(value)); return true;
        case 1: pp->setId_baseStation(string2long(value)); return true;
        case 2: pp->setX_aircraft(string2double(value)); return true;
        case 3: pp->setY_aircraft(string2double(value)); return true;
        case 4: pp->setDistant_AC_BS(string2double(value)); return true;
        case 5: pp->setDepartureAC_time(string2double(value)); return true;
        case 6: pp->setArrivalBS_time(string2double(value)); return true;
        case 7: pp->setDepartureBS_time(string2double(value)); return true;
        case 8: pp->setArrivalCT_time(string2double(value)); return true;
        default: return false;
    }
}

const char *PacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *PacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Packet *pp = (Packet *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


