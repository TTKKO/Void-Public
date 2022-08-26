/*
 *		assembler/tmpro/tmp_text.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of TMPro's TMP_Text class
 */

#pragma once

#include "../il2cpp/il2cpp.hpp"
#include "../common.hpp"
#include "../../../offsets.hpp"
#include "../../sdk/datatypes/color.h"
#include <array>
#include "../unityengine/component.hpp"

namespace assembler::tmpro
{
	struct tm_pro_tmp_text_fields {
		il2cpp::il2cpp_string* m_text;
	};
	struct tmp_text : il2cpp::il2cpp_object
	{
		tm_pro_tmp_text_fields fields;

		void set_is_overlay(bool value);
		void set_text(std::string_view text);
		void set_color(const sdk::color& c);
		void set_fontsize(float value);
		void set_word_wrapping(bool value);

	private:
		static il2cpp::il2cpp_class* get_global_class();
		inline static il2cpp::il2cpp_class* global_class_ = nullptr;
	};
}
