#include "instance.h"

using namespace VulkanUtils;

void Instance::Init(VulkanApp& app) {

	if (!IsExtensionsValid(app.instanceExtensions))
		throw std::runtime_error("Failed to create Instance : The given extension(s) was not valid !");

	if (!IsValidationLayersValid(app.instanceLayer))
		throw std::runtime_error("Failed to create Instance : The given validation layer(s) was not valid !");

	VkApplicationInfo appInfo {
		.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext				= nullptr,
		.pApplicationName	= "App name",
		.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0),
		.pEngineName		= "Bismuth",
		.engineVersion		= VK_MAKE_API_VERSION(0, 1, 0, 0),
		.apiVersion			= VK_MAKE_API_VERSION(0, 1, 0, 0),
	};

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo {};
	DebugMessenger::PopulateDebugUtilsMessengerCreateInfoEXT(&debugCreateInfo);

	VkInstanceCreateInfo createInfo{
		.sType						= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		
		#ifndef NDEBUG
		.pNext						= (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo,
		#elif
		.pNext						= nullptr,
		#endif

		.flags						= 0,
		.pApplicationInfo			= &appInfo,

		#ifndef NDEBUG
		.enabledLayerCount			= static_cast<uint32_t>(app.instanceLayer.size()),
		.ppEnabledLayerNames		= app.instanceLayer.data(),
		#elif
		.enabledLayerCount			= 0,
		.ppEnabledLayerNames		= nullptr,
		#endif

		.enabledExtensionCount		= static_cast<uint32_t>(app.instanceExtensions.size()),
		.ppEnabledExtensionNames	= app.instanceExtensions.data(),
	};

	if (vkCreateInstance(&createInfo, nullptr, &app.instance) != VK_SUCCESS)
		throw std::runtime_error("Failed to create vulkan instance !");
}

const std::vector<VkExtensionProperties> Instance::GetAvailableExtensions() {
	uint32_t count;
	vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
	
	auto extensions = std::vector<VkExtensionProperties>(count);
	vkEnumerateInstanceExtensionProperties(nullptr, &count, extensions.data());

	return extensions;
}

const std::vector<VkLayerProperties> Instance::GetAvailableValidationLayers() {
	uint32_t count;
	vkEnumerateInstanceLayerProperties(&count, nullptr);

	auto layers = std::vector<VkLayerProperties>(count);
	vkEnumerateInstanceLayerProperties(&count, layers.data());

	return layers;
}

const bool Instance::IsExtensionsValid(const std::vector<const char*>& ext) {
	auto availableExts = GetAvailableExtensions();

	for (const auto& extension : ext) {
		auto found = false;

		for (const auto& availableExtension : availableExts) {
			if (strcmp(extension, availableExtension.extensionName) == 0) {
				found = true;
				break;
			}
		}

		if (!found)
			return false;
	}

	return true;
}

const bool Instance::IsValidationLayersValid(const std::vector<const char*>& lyr) {
	auto availableLyrs = GetAvailableValidationLayers();
	
	for (const auto& layer : lyr) {
		auto found = false;

		for (const auto& availableLayer : availableLyrs) {
			if (strcmp(layer, availableLayer.layerName) == 0) {
				found = true;
				break;
			}
		}

		if (!found)
			return false;
	}

	return true;
}