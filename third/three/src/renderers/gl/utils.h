#include "../../constants.h"
#include "../../core/array.h"

#include <cstdint>

namespace three::gl
{
	class Utils
	{
	public:
		static uint32_t Convert(Usage usage);
		static uint32_t Convert(Array::Type type);
		static uint32_t Convert(DrawMode mode);
	};
}
