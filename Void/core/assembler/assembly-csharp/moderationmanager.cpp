#include "moderationmanager.hpp"
#include "../il2cpp/il2cpp.hpp"

assembler::moderation_manager* assembler::moderation_manager::instance()
{
    using func_t = moderation_manager*(*)();
    static const auto func = memory::get_method<func_t>(MODERATIONMANAGER_INSTANCE);
    return func();
}

bool assembler::moderation_manager::check_moderation(il2cpp::il2cpp_string* user_id, const moderation_type type)
{
    using func_t = bool(*)(moderation_manager*, il2cpp::il2cpp_string*, moderation_type);
    static const auto func = memory::get_method<func_t>(MODERATIONMANAGER_CHECKMODERATION);
    return func(this, user_id, type);
}

bool assembler::moderation_manager::check_moderation(const std::string_view user_id, const moderation_type type)
{
    return check_moderation(il2cpp::string_new(user_id), type);
}
