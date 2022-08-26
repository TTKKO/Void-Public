/*
 *		assembler/mono/mono.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's replication of Mono
 */

#pragma once
#include "structures/structues.h"
#include "../../../utilities/memory.hpp"

namespace assembler::mono
{
	mono_domain* get_root_domain();
    mono_image* assembly_get_image(mono_assembly* assembly);
	mono_assembly* image_get_assembly(mono_image* image);
	char* image_get_name(mono_image* image);

	std::vector<mono_image*> fetch_images();
}

