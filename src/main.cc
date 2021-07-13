
#include "main.h"

const std::vector<const char*> GetValidationLayers() {
	std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation",
	};

	return validationLayers;
}

const std::vector<const char*> GetExtensions() {
	uint32_t count;
	const char** ext = glfwGetRequiredInstanceExtensions(&count);

	std::vector<const char*> extensions(ext, ext + count);

	#ifndef NDEBUG
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	#endif

	#ifdef __APPLE__
	extensions.push_back("VK_KHR_get_physical_device_properties2");
	#endif

	return extensions;
}

const std::vector<const char*> GetDeviceExtensions() {
	return std::vector<const char*> {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,

		#ifdef __APPLE__
		"VK_KHR_portability_subset",
		#endif
	};
}

int main()
{
	std::cout << "Launch the app..." << std::endl;

	auto appName = "My app";

	try {
		Console::Log("> Setup window.");
		Window window(appName, 800, 600);
		OK_MSG

		Console::Log("> Create vulkan app");
		VulkanApp app("My app");

		// Assign the glfw window to the app... (Don't forget that!)
		app.window 				= window.GetGlfwWindow();

		// Assign the required instance extensions and layers...
		app.instanceExtensions 	= GetExtensions();
		app.instanceLayer 		= GetValidationLayers();
		app.deviceExtensions	= GetDeviceExtensions();

		OK_MSG

		Console::Log("> Setup instance");
		VulkanUtils::Instance::Init(app);
		OK_MSG
		
		#ifndef NDEBUG
		Console::Log("> Setup debug messenger");
		VkDebugUtilsMessengerCreateInfoEXT createInfo;
		DebugMessenger::PopulateDebugUtilsMessengerCreateInfoEXT(&createInfo);
		DebugMessenger::CreateDebugUtilsMessengerEXT(app.instance, &createInfo, nullptr, &app.callback);
		OK_MSG
		#endif

		Console::Log("> Create window surface");
		VulkanUtils::Surface::Init(app, window);
		OK_MSG

		Console::Log("> Setup physical device");
		VulkanUtils::PhysicalDevice::PickPhysicalDevice(app);
		OK_MSG

		Console::Log("> Setup logical device");
		VulkanUtils::LogicalDevice::Init(app);
		OK_MSG

		Console::Log("> Setup swap chain");
		VulkanUtils::SwapChain::Init(app);
		OK_MSG

		Console::Log("> Setup image views");
		VulkanUtils::ImageViews::Init(app);
		OK_MSG

		Console::Log("> Setup graphics pipeline");
		VulkanUtils::GraphicsPipeline::Init(app);
		OK_MSG

		std::cout << "Start the main loop..." << std::endl;
		window.Loop();
	}
	catch(const std::exception& e) {
		std::cerr << "\033[1;31mError : " << e.what() << "\033[0m" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "App closed !" << std::endl;

	return EXIT_SUCCESS;
}
