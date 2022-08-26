/*
 *		assembler/assembly-csharp/system/collections/queue.hpp
 *		Void
 *
 *		Copyright © 2021 Azurilex. All rights reserved.
 *		Void's queue class replication
 */

#pragma once
#include "../../../common.hpp"

namespace assembler::system_replication::collections
{
	struct __declspec(align(8)) system_collections_queue_fields {
		il2cpp::il2cpp_array* array;
		int32_t head;
		int32_t tail;
		int32_t size;
		int32_t grow_factor;
		int32_t version;
		il2cpp::il2cpp_object* sync_root;
	};

	struct queue {
		il2cpp::il2cpp_class* klass;
		void* monitor;
		system_collections_queue_fields fields;

		void clear();
		std::int32_t get_count();
		il2cpp::il2cpp_object* dequeue();
		void enqueue(il2cpp::il2cpp_object* obj);
	};
}
