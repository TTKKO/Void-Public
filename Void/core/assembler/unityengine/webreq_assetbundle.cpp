#include "webreq_assetbundle.hpp"

assembler::il2cpp::il2cpp_object* assembler::unity_engine::web_request::send_web_request()
{
    if (!send_web_request_func_) 
        send_web_request_func_ = static_cast<send_web_request_t>(il2cpp::resolve_icall(xorstr_("UnityEngine.Networking.UnityWebRequest::BeginWebRequest()")));

    const auto res = send_web_request_func_(this);
    if (res)
        *reinterpret_cast<web_request**>(reinterpret_cast<std::uint8_t*>(res) + 0x20) = this;

    return res;
}

assembler::unity_engine::web_request* assembler::unity_engine::webreq_assetbundle::get_asset_bundle(const std::string_view url)
{
    using func_t = web_request*(*)(il2cpp::il2cpp_string*);
    const auto func = memory::get_method<func_t>(0x5324700);
    return func(il2cpp::string_new(url));
}
