#include "debug_msg.h"

using namespace std;

DebugMessenger::DebugMessenger(
    const VkInstance& instance, 
    const VkDebugUtilsMessengerCreateInfoEXT* createInfoExt
) : instance(instance) {

    #ifndef NDEBUG
    if(CreateDebugUtilsMessengerEXT(instance, createInfoExt, nullptr, &callback) != VK_SUCCESS)
        throw runtime_error("Failed to create debug messenger !");
    #endif
}

DebugMessenger::~DebugMessenger() {
    DestroyDebugUtilsMessengerEXT(instance, callback, nullptr);
}

VKAPI_ATTR VkBool32 VKAPI_CALL DebugMessenger::DebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT msgSeverity,
	VkDebugUtilsMessageTypeFlagsEXT msgType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {
        std::string str;

		if (msgSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
			str.append("\033[1;31m");
		} else if (msgSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
			str.append("\033[1;93m");
		} else if (msgSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
			str.append("\033[1;94m");
		} else {
			str.append("\033[3m");
		}

		if (msgType >= VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
			str.append("PERFORMANCE: ");
		} else if (msgType >= VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
			str.append("VALIDATION: ");
		} else {
			str.append("GENERAL: ");
		}

		cerr << str << pCallbackData->pMessage << "\033[0m" << endl;

		return VK_FALSE;
}

VkResult DebugMessenger::CreateDebugUtilsMessengerEXT(
    const VkInstance& instance, 
    const VkDebugUtilsMessengerCreateInfoEXT* createInfoExt, 
    const VkAllocationCallbacks* pAllocator, 
    VkDebugUtilsMessengerEXT*pCallback
) {
    
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if(func != nullptr) {
        return func(instance, createInfoExt, pAllocator, pCallback);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DebugMessenger::DestroyDebugUtilsMessengerEXT(const VkInstance& instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator) {

    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    
    if(func != nullptr) {
        func(instance, callback, pAllocator);
    }
}

void DebugMessenger::PopulateDebugUtilsMessengerCreateInfoEXT(VkDebugUtilsMessengerCreateInfoEXT* createInfo) {
    *createInfo = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            
        .messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT   ,

        .messageType = 
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT     |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT  |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT ,
        
        .pfnUserCallback = DebugCallback,
        .pUserData = nullptr,
    };
}