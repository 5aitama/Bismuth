#pragma once

#include <vector>
#include <iostream>

#include "vulkan_app.h"

namespace VulkanUtils {

/**
 * @brief A wrapper of the vulkan instance.
 */
struct Instance {

public:
	/**
	 * @brief Initialize the instance of a vulkan application.
	 */
	static void Init(VulkanApp& app);

	/**
	 * @brief Return a list that contains all available extensions for the current instance.
	 */
	static const std::vector<VkExtensionProperties> GetAvailableExtensions();

	/**
	 * @brief Return a list that contains all available validation layers for the current instance.
	 */
	static const std::vector<VkLayerProperties> GetAvailableValidationLayers();

	/**
	 * @brief Check if the required extensions was valid for this instance.
	 */
	static const bool IsExtensionsValid(const std::vector<const char*>& ext);

	/**
	 * @brief Check if the required validation layers was valid for this instance.
	 */
	static const bool IsValidationLayersValid(const std::vector<const char*>& lyr);
};

}