#ifndef _NAVAGRAHA_EXTENSIONS_SERIALIZABLE_H
#define _NAVAGRAHA_EXTENSIONS_SERIALIZABLE_H

#include "extensions/serializer_helper.hpp"
#include "extensions/field.hpp"
#include <sstream>

namespace navagraha {
namespace extensions {

template <typename T_Obj>
class serializable {
public:
    T_Obj & serialize(std::ostringstream & str)
    {
        return *serializer_helper()
            .serialize(&T_Obj::bind, reinterpret_cast<T_Obj *>(this), str);
    }

    T_Obj & deserialize(std::istringstream & str)
    {
        return *serializer_helper()
            .deserialize(&T_Obj::bind, reinterpret_cast<T_Obj *>(this), str);
    }

    static T_Obj deserialize(std::string & payload)
    {
        if (payload.length() == 0) {
            payload = "{}";
        }
        std::istringstream str(payload);
        T_Obj obj;

        obj.deserialize(str);
        return obj;
    }

    abstract_object to_abstract()
    {
        return serializer_helper()
            .to_abstract(&T_Obj::bind, reinterpret_cast<T_Obj *>(this));
    }

    static T_Obj to_special(abstract_object & obj)
    {
        return serializer_helper()
            .to_special(&T_Obj::bind, T_Obj(), obj);
    }
};

}
}

#endif
