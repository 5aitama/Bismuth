#include "queue_family_indices.h"

using namespace VulkanUtils;

const bool QueueFamilyIndices::IsComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
}