
#include "main.h"

using namespace std;

const vector<const char*> GetValidationLayers() {
	vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	return validationLayers;
}

const vector<const char*> GetExtensions() {
	uint32_t count;
	const char** ext = glfwGetRequiredInstanceExtensions(&count);

	vector<const char*> extensions(ext, ext + count);

	#ifndef NDEBUG
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	#endif

	return extensions;
}

const vector<const char*> GetDeviceExtensions() {
	return vector<const char*> {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};
}

int main()
{
	cout << "Launch the app..." << endl;

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

		cout << "Start the main loop..." << endl;
		window.Loop();
	}
	catch(const std::exception& e) {
		FAIL_MSG
		std::cerr << e.what() << std::endl;
	}

	cout << "App closed !" << endl;

	return 0;
}
