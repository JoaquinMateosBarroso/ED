/**
 * @file ip_utils.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <algorithm>
#include "ip_utils.hpp"

std::uint64_t
IpToInt::operator() (const IP& ip) const
{
    std::uint64_t ret_val = 0l;
    //
    //Remember: casting to 64 bits unsigned integer to do not loss bits.
    //Hint: mult by 2^n means shift to left n bits.
    uint64_t multiplicando = 1l;
    for (int i = 1; i <= 4; i++)
    {
        ret_val += (uint64_t)ip.bytes[4-i]*multiplicando;
        multiplicando = multiplicando*256;
    }
    //
    return ret_val;
}

std::ostream&
operator<< (std::ostream& out, const IP& ip)
{
    //
    //Remember: we want to output the ascii code, not the char.
    for (int i = 0; i < 4; i++)
    {
        out << static_cast<int>(ip.bytes[i]) << (i==3? "": ".");
    }
    //
    return out;
}

std::istream&
operator>>(std::istream& in, IP& ip) noexcept(false)
{
    //
    //Hint: you can use a std::istringstream to convert from text to uint8_t.
    //Hint: you can use the std::replace algorithm to replace '.' by ' '.
    //Remember: if a wrong format is detected, throw an runtime_error exception.


    std::string aux;
    unsigned aux_T;

    in >> aux;
    if (in.fail())
    {
        throw std::runtime_error("Wrong input format.");
    }


    std::replace(aux.begin(), aux.end(), '.', ' ');
    std::istringstream auxin(aux);


    for (int i = 0; i < 4; i++)
    {
        auxin >> aux_T;
        if (auxin.fail() or (aux_T > 255))
        {
            throw std::runtime_error("Wrong input format.");
        }
        ip.bytes[i] = static_cast<uint16_t>(aux_T);
    }


    //
    return in;
}

IpToInt::Ref
IpToInt::create()
{
    return std::make_shared<IpToInt>();
}
