#include "pipeline_manager.hpp"

std::string assembler::vrc::core::pipeline_manager::get_blueprint_id() const
{
    if (this == nullptr) return "INVALID_STRING";
    return s_chars(this->fields.blueprint_id);
}

std::string assembler::vrc::core::pipeline_manager::get_assetbundle_version() const
{
    if (this == nullptr) return "INVALID_STRING";
    return s_chars(this->fields.asset_bundle_unity_version);
}

assembler::vrc::core::api_user* assembler::vrc::core::pipeline_manager::get_api_user() const
{
    if (this == nullptr) return nullptr;
    return this->fields.user;
}
