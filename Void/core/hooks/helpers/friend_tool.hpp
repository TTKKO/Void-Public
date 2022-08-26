#pragma once
#include <future>
#include "../../assembler/vrc/core/apiuser.hpp"
#include "../../assembler/assembly-csharp/roommanager.hpp"
#include "../../config.hpp"

namespace helpers
{
	class friend_tool : public c_singleton<friend_tool>
	{
		std::vector<std::wstring> friends_{};
		std::future<void> task_;
		bool is_working_ = false;

		_NODISCARD bool is_ready() const;
		_NODISCARD bool save_temporary() const;
	public:
		static bool export_friends(const std::vector<assembler::il2cpp::il2cpp_string*>& v_friends);

		bool import_friends();
		void load_friends();
		bool start_load_task();
	};
}
