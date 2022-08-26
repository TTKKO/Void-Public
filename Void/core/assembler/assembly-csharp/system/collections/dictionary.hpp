/*
 *		assembler/assembly-csharp/system/collections/dictionary.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's Dictionary class replication
 */

#pragma once
#include "../../../il2cpp/il2cpp.hpp"

namespace assembler::system_replication::collections
{
    struct dictionary_enumerator_fields
    {
        il2cpp::il2cpp_object* dictionary;
        std::int32_t index;
        std::int32_t version;
        il2cpp::il2cpp_object* current_key;
    };

    struct dictionary_enumerator : il2cpp::il2cpp_object
    {
        dictionary_enumerator_fields fields;

	    bool move_next()
	    {
            return il2cpp::call_vfunc<bool>(this->klass, 6, this);
	    }
    };

    struct dictionary_key_map : il2cpp::il2cpp_object
    {
        dictionary_enumerator* get_enumerator()
        {
            return il2cpp::call_mifunc<dictionary_enumerator*>(this->klass, 10, this);
        }
    };

    struct __declspec(align(8)) dictionary_fields {
        il2cpp::il2cpp_array* buckets;
        il2cpp::il2cpp_object* entries;
        std::int32_t count;
        std::int32_t version;
        std::int32_t free_list;
        std::int32_t free_count;
        il2cpp::il2cpp_object* comparer;
        dictionary_key_map* keys;
        il2cpp::il2cpp_object* values;
        il2cpp::il2cpp_object* sync_root;
    };

    struct dictionary : il2cpp::il2cpp_object
    {
        dictionary_fields fields;

        template <typename T>
        T dictionary_get(void* value, const std::string_view type_name)
        {
            if (const auto box = il2cpp::value_box(type_name, value); this->contains_key(box))
            {
                if (const auto output = il2cpp::call_vfunc<il2cpp_object*>(this->klass, 21, this, box))
                    return *static_cast<T*>(object_unbox(output));
            }
            return NULL;
        }

        template <typename T>
        T dictionary_get(il2cpp::il2cpp_string* key)
        {
            if (this->contains_key(key))
            {
                return il2cpp::call_vfunc<T>(this->klass, 21, this, key);
            }

            return NULL;
        }

        dictionary_key_map* get_keys()
        {
            return il2cpp::call_vfunc<dictionary_key_map*>(this->klass, 6, this);
        }

        template <typename T>
        bool remove(T key)
        {
            return il2cpp::call_vfunc<bool>(this->klass, 10, this, key);
        }

        template <typename T>
        bool contains_key(T key)
        {
            return il2cpp::call_vfunc<bool>(this->klass, 25, this, key);
        }

        //3
    };

    struct hashtable : il2cpp::il2cpp_object
    {
	    template <typename T>
        T get_item(il2cpp::il2cpp_string* key)
	    {
		    if (this->contains_key(key))
		    {
			    return il2cpp::call_vfunc<T>(this->klass, 4, this, key);
		    }

            return NULL;
	    }

        template <typename T>
        T get_item(void* value, const std::string_view type_name)
        {
            if (const auto box = il2cpp::value_box(type_name, value); this->contains_key(box))
            {
                if (const auto output = il2cpp::call_vfunc<il2cpp_object*>(this->klass, 4, this, box))
                    return *static_cast<T*>(object_unbox(output));
            }
            return NULL;
        }

        template <typename T>
        bool contains_key(T key)
	    {
            return il2cpp::call_vfunc<bool>(this->klass, 8, this, key);
	    }
    };
}
