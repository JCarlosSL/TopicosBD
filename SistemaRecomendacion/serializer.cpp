#include "serializer.h"
typeMap1 Serializer::getUser() const
{
    return user;
}

void Serializer::setUser(const typeMap1 &value)
{
    user = value;
}

typeMap1 Serializer::getObject() const
{
    return object;
}

void Serializer::setObject(const typeMap1 &value)
{
    object = value;
}

typeMap3 Serializer::getDataUsers() const
{
    return dataUsers;
}

void Serializer::setDataUsers(const typeMap3 &value)
{
    dataUsers = value;
}

typeMap3 Serializer::getBandaUrsPuntaje() const
{
    return bandaUrsPuntaje;
}

void Serializer::setBandaUrsPuntaje(const typeMap3 &value)
{
    bandaUrsPuntaje = value;
}
