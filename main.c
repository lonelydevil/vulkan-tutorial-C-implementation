#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"limits.h"
#include"time.h"

#include"vulkan/vulkan.h"
#include"GLFW/glfw3.h"
#define GLFW_INCLUDE_VULKAN

int main(int argc,char **argv){
	glfwInit();
	//
	//
	//instance creation part		line_15 to line_69
	//
	//create application info
	//
	VkApplicationInfo app_info;

	app_info.sType=VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pNext=NULL;
	char app_name[VK_MAX_EXTENSION_NAME_SIZE];
	strcpy(app_name,"vulkan_project");
	app_info.pApplicationName=app_name;
	app_info.applicationVersion=VK_MAKE_VERSION(0,0,1);
	char app_engine_name[VK_MAX_EXTENSION_NAME_SIZE];
	strcpy(app_engine_name,"vulkan_engine");
	app_info.pEngineName=app_engine_name;
	app_info.engineVersion=VK_MAKE_VERSION(0,0,1);
	app_info.apiVersion=VK_API_VERSION_1_0;
	//
	//create instance create info
	//
	VkInstanceCreateInfo inst_cre_info;

	inst_cre_info.sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	inst_cre_info.pNext=NULL;
	inst_cre_info.flags=0;
	inst_cre_info.pApplicationInfo=&app_info;
	uint32_t inst_layer_count=1;
	inst_cre_info.enabledLayerCount=
		inst_layer_count;
	char pp_inst_layers[inst_layer_count]
		[VK_MAX_EXTENSION_NAME_SIZE];
	strcpy(pp_inst_layers[0],"VK_LAYER_KHRONOS_validation");
	char *pp_inst_layer_names[inst_layer_count];
	for(uint32_t i=0;i<inst_layer_count;i++){
		pp_inst_layer_names[i]=
			pp_inst_layers[i];
	}
	inst_cre_info.ppEnabledLayerNames=
		(const char * const *)pp_inst_layer_names;
	uint32_t inst_ext_count=0;
	const char * const *pp_inst_ext_names=
		glfwGetRequiredInstanceExtensions
		(&inst_ext_count);
	inst_cre_info.enabledExtensionCount=inst_ext_count;
	inst_cre_info.ppEnabledExtensionNames=pp_inst_ext_names;
	//
	//create instance
	//
	VkInstance inst;

	vkCreateInstance(&inst_cre_info,
			NULL,&inst);
	printf("instance created.\n");
	//
	//
	//device creation part		line_70 to line_261
	//
	//enum physical device
	//
	uint32_t phy_devi_count=0;
	vkEnumeratePhysicalDevices
		(inst,&phy_devi_count,NULL);

	VkPhysicalDevice phy_devis
		[phy_devi_count];
	vkEnumeratePhysicalDevices
		(inst,&phy_devi_count,phy_devis);
	//
	//select physical device
	//
	VkPhysicalDeviceProperties
		phy_devis_props[phy_devi_count];
	uint32_t discrete_gpu_list[phy_devi_count];
	uint32_t discrete_gpu_count=0;
	uint32_t intergrated_gpu_list[phy_devi_count];
	uint32_t intergrated_gpu_count=0;

	VkPhysicalDeviceMemoryProperties
		phy_devis_mem_props[phy_devi_count];
	uint32_t
		phy_devis_mem_count[phy_devi_count];
	VkDeviceSize
		phy_devis_mem_total[phy_devi_count];

	for(uint32_t i=0;i<phy_devi_count;i++){
		vkGetPhysicalDeviceProperties
			(phy_devis[i],&phy_devis_props[i]);
		if(phy_devis_props[i].deviceType
				==VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
			discrete_gpu_list[discrete_gpu_count]=i;
			discrete_gpu_count++;
		}else if(phy_devis_props[i].deviceType
				==VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU){
			intergrated_gpu_list[intergrated_gpu_count]=i;
			intergrated_gpu_count++;
		}

		vkGetPhysicalDeviceMemoryProperties
			(phy_devis[i],&phy_devis_mem_props[i]);
		phy_devis_mem_count[i]=
			phy_devis_mem_props[i].memoryHeapCount;
		phy_devis_mem_total[i]=0;
		for(uint32_t j=0;j<phy_devis_mem_count[i];j++){
			phy_devis_mem_total[i]+=
				phy_devis_mem_props[i].memoryHeaps[j].size;
		}
	}

	VkDeviceSize max_mem_size=0;
	uint32_t phy_devi_best_index=0;

	if(discrete_gpu_count!=0){
		for(uint32_t i=0;i<discrete_gpu_count;i++){
			if(phy_devis_mem_total[i]>max_mem_size){
				phy_devi_best_index=discrete_gpu_list[i];
				max_mem_size=phy_devis_mem_total[i];
			}
		}
	}else if(intergrated_gpu_count!=0){
		for(uint32_t i=0;i<intergrated_gpu_count;i++){
			if(phy_devis_mem_total[i]>max_mem_size){
				phy_devi_best_index=intergrated_gpu_list[i];
				max_mem_size=phy_devis_mem_total[i];
			}
		}
	}

	printf("best device index:%u\n",phy_devi_best_index);
	printf("device name:%s\n",phy_devis_props
		[phy_devi_best_index].deviceName);
	printf("device type:");
	if(discrete_gpu_count!=0){
		printf("discrete gpu\n");
	}else if(intergrated_gpu_count!=0){
		printf("intergrated gpu\n");
	}else{
		printf("unknown\n");
	}
	printf("memory total:%llu\n",phy_devis_mem_total[
		phy_devi_best_index
	]);
	VkPhysicalDevice *phy_best_devi=
		&(phy_devis[phy_devi_best_index]);
	//
	//query queue families
	//
	uint32_t qf_prop_count=0;
	vkGetPhysicalDeviceQueueFamilyProperties
		(*phy_best_devi,&qf_prop_count,NULL);
	VkQueueFamilyProperties
		qf_props[qf_prop_count];
	vkGetPhysicalDeviceQueueFamilyProperties
		(*phy_best_devi,&qf_prop_count,qf_props);

	uint32_t qf_q_count[qf_prop_count];
	for(uint32_t i=0;i<qf_prop_count;i++){
		qf_q_count[i]=qf_props[i].queueCount;
	}
	//
	//create logical device
	//
	VkDeviceQueueCreateInfo dev_q_cre_infos[qf_prop_count];
	for(uint32_t i=0;i<qf_prop_count;i++){
		dev_q_cre_infos[i].sType=
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		dev_q_cre_infos[i].pNext=NULL;
		dev_q_cre_infos[i].flags=0;
		dev_q_cre_infos[i].queueFamilyIndex=i;
		dev_q_cre_infos[i].queueCount=qf_q_count[i];
		float q_prior[1]={1.0f};
		dev_q_cre_infos[i].pQueuePriorities=q_prior;
	}
	printf("using %d queue families.\n",qf_prop_count);

	VkDeviceCreateInfo dev_cre_info;
	dev_cre_info.sType=
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	dev_cre_info.pNext=NULL;
	dev_cre_info.flags=0;
	dev_cre_info.queueCreateInfoCount=qf_prop_count;
	dev_cre_info.pQueueCreateInfos=dev_q_cre_infos;
	dev_cre_info.enabledLayerCount=0;
	dev_cre_info.ppEnabledLayerNames=NULL;

	uint32_t dev_ext_count=1;
	dev_cre_info.enabledExtensionCount=dev_ext_count;
	char pp_dev_exts[dev_ext_count]
		[VK_MAX_EXTENSION_NAME_SIZE];
	strcpy(pp_dev_exts[0],"VK_KHR_swapchain");
	char *pp_dev_ext_names[dev_ext_count];
	for(uint32_t i=0;i<dev_ext_count;i++){
		pp_dev_ext_names[i]=
			pp_dev_exts[i];
	}
	dev_cre_info.ppEnabledExtensionNames=
		(const char * const *)pp_dev_ext_names;

	VkPhysicalDeviceFeatures phy_devi_feat;
	vkGetPhysicalDeviceFeatures
		(*phy_best_devi,&phy_devi_feat);
	dev_cre_info.pEnabledFeatures=
		&phy_devi_feat;

	VkDevice dev;
	vkCreateDevice(*phy_best_devi,&dev_cre_info,NULL,&dev);
	printf("logical device created.\n");
	//
	//select best queue
	//
	uint32_t qf_graph_count=0;
	uint32_t qf_graph_list[qf_prop_count];
	for(uint32_t i=0;i<qf_prop_count;i++){
		if((qf_props[i].queueFlags
				&VK_QUEUE_GRAPHICS_BIT) != 0){
			qf_graph_list[qf_graph_count]=i;
			qf_graph_count++;
		}
	}

	uint32_t max_q_count=0;
	uint32_t qf_best_index=0;
	for(uint32_t i=0;i<qf_graph_count;i++){
		if(qf_props[qf_graph_list[i]]
				.queueCount>max_q_count){
			qf_best_index=qf_graph_list[i];
		}
	}
	printf("best queue family index:%d\n",
			qf_best_index);

	VkQueue q_graph,q_pres;
	vkGetDeviceQueue
		(dev,qf_best_index,0,&q_graph);
	char single_queue=1;
	if(qf_props[qf_best_index]
			.queueCount<2){
		vkGetDeviceQueue
			(dev,qf_best_index,0,&q_pres);
		printf("using single queue for drawing.\n");
	}else{
		single_queue=0;
		vkGetDeviceQueue
			(dev,qf_best_index,1,&q_pres);
		printf("using double queues for drawing.\n");
	}
	//
	//
	//window and surface creation part		line_262 to line_276
	//
	//create window and surface
	//
	glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
	GLFWwindow *window=
		glfwCreateWindow(600,600,"",NULL,NULL);
	printf("window created.\n");
	VkSurfaceKHR surf;
	glfwCreateWindowSurface
		(inst,window,NULL,&surf);
	printf("surface created.\n");
	//
	//
	//swapchain and image view creation part		line_277 to line_476
	//
	//verify surface support
	//
	VkBool32 phy_surf_supported;
	vkGetPhysicalDeviceSurfaceSupportKHR
		(*phy_best_devi,qf_best_index,
		 surf,&phy_surf_supported);
	if(phy_surf_supported==VK_TRUE){
		printf("surface supported.\n");
	}else{
		printf("warning:surface unsupported!\n");
	}
	//
	//fetch surface capabilities
	//
	VkSurfaceCapabilitiesKHR surf_caps;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR
		(*phy_best_devi,surf,&surf_caps);
	printf("fetched caps from surface.\n");
	char extent_suitable=1;
	int wind_w,wind_h;
	glfwGetFramebufferSize(window,&wind_w,&wind_h);
	VkExtent2D actual_extent;
	actual_extent.width=wind_w;
	actual_extent.height=wind_h;
	if(surf_caps.currentExtent.width
			!=wind_w
			||surf_caps.currentExtent.height
			!=wind_h){
		extent_suitable=0;
		printf("actual extent size doesn't match framebuffers, resizing...\n");
		actual_extent.width=
			wind_w>surf_caps
			.maxImageExtent.width?
			surf_caps
			.maxImageExtent.width
			:wind_w;
		actual_extent.width=
			wind_w<surf_caps
			.minImageExtent.width?
			surf_caps
			.minImageExtent.width
			:wind_w;
		actual_extent.height=
			wind_h>surf_caps
			.maxImageExtent.height?
			surf_caps
			.maxImageExtent.height
			:wind_h;
		actual_extent.height=
			wind_h<surf_caps
			.minImageExtent.height?
			surf_caps
			.minImageExtent.height
			:wind_h;
	}
	//
	//fetch surface formats
	//
	uint32_t surf_form_count;
	vkGetPhysicalDeviceSurfaceFormatsKHR
		(*phy_best_devi,surf,&surf_form_count,NULL);
	VkSurfaceFormatKHR surf_forms[surf_form_count];
	vkGetPhysicalDeviceSurfaceFormatsKHR
		(*phy_best_devi,surf,&surf_form_count,surf_forms);
	printf("fetched %d surface formats.\n",surf_form_count);
	for(uint32_t i=0;i<surf_form_count;i++){
		printf("format:%d\tcolorspace:%d\n",
				surf_forms[i].format,
				surf_forms[i].colorSpace);
	}
	//
	//fetch surface present mode
	//
	uint32_t pres_mode_count;
	vkGetPhysicalDeviceSurfacePresentModesKHR
		(*phy_best_devi,surf,&pres_mode_count,NULL);
	VkPresentModeKHR pres_modes[pres_mode_count];
	vkGetPhysicalDeviceSurfacePresentModesKHR
		(*phy_best_devi,surf,&pres_mode_count,pres_modes);
	printf("fetched %d present modes.\n",pres_mode_count);
	char mailbox_mode_supported=0;
	for(uint32_t i=0;i<pres_mode_count;i++){
		printf("present mode:%d\n",pres_modes[i]);
		if(pres_modes[i]==VK_PRESENT_MODE_MAILBOX_KHR){
			printf("mailbox present mode supported.\n");
			mailbox_mode_supported=1;
		}
	}
	//
	//create swapchain
	//
	VkSwapchainCreateInfoKHR swap_cre_info;
	swap_cre_info.sType=
		VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swap_cre_info.pNext=NULL;
	swap_cre_info.flags=0;
	swap_cre_info.surface=surf;
	swap_cre_info.minImageCount=
		surf_caps.minImageCount+1;
	swap_cre_info.imageFormat=
		surf_forms[0].format;
	swap_cre_info.imageColorSpace=
		surf_forms[0].colorSpace;
	swap_cre_info.imageExtent=
		extent_suitable?
		surf_caps.currentExtent
		:actual_extent;
	swap_cre_info.imageArrayLayers=1;
	swap_cre_info.imageUsage=
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swap_cre_info.imageSharingMode=
		single_queue?
		VK_SHARING_MODE_EXCLUSIVE
		:VK_SHARING_MODE_CONCURRENT;
	swap_cre_info.queueFamilyIndexCount=
		single_queue?
		0:2;
	uint32_t qf_indices[2]={0,1};
	swap_cre_info.pQueueFamilyIndices=
		single_queue?
		NULL:qf_indices;
	swap_cre_info.preTransform=
		surf_caps.currentTransform;
	swap_cre_info.compositeAlpha=
		VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swap_cre_info.presentMode=
		mailbox_mode_supported?
		VK_PRESENT_MODE_MAILBOX_KHR:
		VK_PRESENT_MODE_FIFO_KHR;
	swap_cre_info.clipped=VK_TRUE;
	swap_cre_info.oldSwapchain=VK_NULL_HANDLE;

	VkSwapchainKHR swap;
	vkCreateSwapchainKHR(dev,&swap_cre_info,NULL,&swap);
	printf("swapchain created.\n");
	//
	//fetch image from swapchain
	//
	uint32_t swap_image_count=0;
	vkGetSwapchainImagesKHR
		(dev,swap,&swap_image_count,NULL);
	VkImage swap_images[swap_image_count];
	vkGetSwapchainImagesKHR
		(dev,swap,&swap_image_count,swap_images);
	printf("%d images fetched from swapchain.\n",swap_image_count);
	//
	//create image view
	//
	VkImageView image_views
		[swap_image_count];
	VkImageViewCreateInfo
		image_view_cre_infos
		[swap_image_count];

	VkComponentMapping
		image_view_rgba_comp;
	image_view_rgba_comp.r
		=VK_COMPONENT_SWIZZLE_IDENTITY;
	image_view_rgba_comp.g
		=VK_COMPONENT_SWIZZLE_IDENTITY;
	image_view_rgba_comp.b
		=VK_COMPONENT_SWIZZLE_IDENTITY;
	image_view_rgba_comp.a
		=VK_COMPONENT_SWIZZLE_IDENTITY;

	VkImageSubresourceRange
		image_view_subres;
	image_view_subres.aspectMask=VK_IMAGE_ASPECT_COLOR_BIT;
	image_view_subres.baseMipLevel=0;
	image_view_subres.levelCount=1;
	image_view_subres.baseArrayLayer=0;
	image_view_subres.layerCount=
		swap_cre_info.imageArrayLayers;

	for(uint32_t i=0;i<swap_image_count;i++){
		image_view_cre_infos[i].sType=
			VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		image_view_cre_infos[i]
			.pNext=NULL;
		image_view_cre_infos[i]
			.flags=0;
		image_view_cre_infos[i]
			.image=swap_images[i];
		image_view_cre_infos[i]
			.viewType=VK_IMAGE_VIEW_TYPE_2D;
		image_view_cre_infos[i]
			.format=surf_forms[0].format;
		image_view_cre_infos[i]
			.components=image_view_rgba_comp;
		image_view_cre_infos[i]
			.subresourceRange=image_view_subres;
		vkCreateImageView
			(dev,&image_view_cre_infos[i]
			 ,NULL,&image_views[i]);
		printf("image view %d created.\n",i);
	}
	//
	//
	//render pass creation part		line_477 to line_574
	//
	//fill attachment description
	//
	VkAttachmentDescription
		attach_descp;
	attach_descp.flags=0;
	attach_descp.format=
		swap_cre_info
		.imageFormat;
	attach_descp.samples=
		VK_SAMPLE_COUNT_1_BIT;
	attach_descp.loadOp=
		VK_ATTACHMENT_LOAD_OP_CLEAR;
	attach_descp.storeOp=
		VK_ATTACHMENT_STORE_OP_STORE;
	attach_descp.stencilLoadOp=
		VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attach_descp.stencilStoreOp=
		VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attach_descp.initialLayout=
		VK_IMAGE_LAYOUT_UNDEFINED;
	attach_descp.finalLayout=
		VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	printf("attachment description filled.\n");
	//
	//fill attachment reference
	//
	VkAttachmentReference attach_ref;
	attach_ref.attachment=0;
	attach_ref.layout=
		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	printf("attachment reference filled.\n");
	//
	//fill subpass description
	//
	VkSubpassDescription
		subp_descp;
	subp_descp.flags=0;
	subp_descp
		.pipelineBindPoint=
		VK_PIPELINE_BIND_POINT_GRAPHICS;
	subp_descp
		.inputAttachmentCount=0;
	subp_descp
		.pInputAttachments=NULL;
	subp_descp
		.colorAttachmentCount=1;
	subp_descp
		.pColorAttachments=&attach_ref;
	subp_descp
		.pResolveAttachments=NULL;
	subp_descp
		.pDepthStencilAttachment=NULL;
	subp_descp
		.preserveAttachmentCount=0;
	subp_descp
		.pPreserveAttachments=NULL;
	printf("subpass description filled.\n");
	//
	//fill subpass dependency
	//
	VkSubpassDependency
		subp_dep;
	subp_dep.srcSubpass=
		VK_SUBPASS_EXTERNAL;
	subp_dep.dstSubpass=0;
	subp_dep.srcStageMask=
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subp_dep.dstStageMask=
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	subp_dep.srcAccessMask=0;
	subp_dep.dstAccessMask=
		VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	subp_dep.dependencyFlags=0;
	printf("subpass dependency created.\n");
	//
	//create render pass
	//
	VkRenderPassCreateInfo
		rendp_cre_info;
	rendp_cre_info.sType=
		VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	rendp_cre_info.pNext=NULL;
	rendp_cre_info.flags=0;
	rendp_cre_info.attachmentCount=1;
	rendp_cre_info.pAttachments=
		&attach_descp;
	rendp_cre_info.subpassCount=1;
	rendp_cre_info.pSubpasses=&subp_descp;
	rendp_cre_info.dependencyCount=1;
	rendp_cre_info.pDependencies=&subp_dep;

	VkRenderPass rendp;
	vkCreateRenderPass(dev,&rendp_cre_info,NULL,&rendp);
	printf("render pass created.\n");
	//
	//
	//pipeline creation part		line_575 to line_935
	//
	//load shader
	//
	FILE *fp_vert=NULL,
		 *fp_frag=NULL;
	fp_vert=fopen("vert.spv","rb+");
	fp_frag=fopen("frag.spv","rb+");
	char shader_loaded=1;
	if(fp_vert==NULL||fp_frag==NULL){
		shader_loaded=0;
		printf("can't find SPIR-V binaries.\n");
	}
	fseek(fp_vert,0,SEEK_END);
	fseek(fp_frag,0,SEEK_END);
	uint32_t vert_size=ftell(fp_vert);
	uint32_t frag_size=ftell(fp_frag);

	char *p_vert_code=(char *)
		malloc(vert_size*sizeof(char));
	char *p_frag_code=(char *)
		malloc(frag_size*sizeof(char));

	rewind(fp_vert);
	rewind(fp_frag);
	fread(p_vert_code,1,
			vert_size,fp_vert);
	printf("vertex shader binaries loaded.\n");
	fread(p_frag_code,1,
			frag_size,fp_frag);
	printf("fragment shader binaries loaded.\n");

	fclose(fp_vert);
	fclose(fp_frag);
	//
	//create shader modules
	//
	VkShaderModuleCreateInfo
		vert_shad_mod_cre_info;
	vert_shad_mod_cre_info.sType=
		VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	vert_shad_mod_cre_info.pNext=NULL;
	vert_shad_mod_cre_info.flags=0;
	vert_shad_mod_cre_info.codeSize=shader_loaded?vert_size:0;
	vert_shad_mod_cre_info.pCode=
		shader_loaded?
		(const uint32_t *)p_vert_code:NULL;

	VkShaderModuleCreateInfo
		frag_shad_mod_cre_info;
	frag_shad_mod_cre_info.sType=
		VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	frag_shad_mod_cre_info.pNext=NULL;
	frag_shad_mod_cre_info.flags=0;
	frag_shad_mod_cre_info.codeSize=shader_loaded?frag_size:0;
	frag_shad_mod_cre_info.pCode=
		shader_loaded?
		(const uint32_t *)p_frag_code:NULL;

	VkShaderModule
		vert_shad_mod,
		frag_shad_mod;
	vkCreateShaderModule
		(dev,&vert_shad_mod_cre_info,NULL,&vert_shad_mod);
	printf("vertex shader module created.\n");
	vkCreateShaderModule
		(dev,&frag_shad_mod_cre_info,NULL,&frag_shad_mod);
	printf("fragment shader module created.\n");
	//
	//fill shader stage info
	//
	VkPipelineShaderStageCreateInfo
		vert_shad_stage_cre_info,
		frag_shad_stage_cre_info,
		shad_stage_cre_infos[2];

	vert_shad_stage_cre_info.sType=
		VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vert_shad_stage_cre_info.pNext=NULL;
	vert_shad_stage_cre_info.flags=0;
	vert_shad_stage_cre_info.stage=
		VK_SHADER_STAGE_VERTEX_BIT;
	vert_shad_stage_cre_info.module=
		vert_shad_mod;
	char vert_entry
		[VK_MAX_EXTENSION_NAME_SIZE];
	strcpy(vert_entry,"main");
	vert_shad_stage_cre_info.pName=vert_entry;
	vert_shad_stage_cre_info
		.pSpecializationInfo=NULL;
	printf("vertex shader stage info filled.\n");

	frag_shad_stage_cre_info.sType=
		VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	frag_shad_stage_cre_info.pNext=NULL;
	frag_shad_stage_cre_info.flags=0;
	frag_shad_stage_cre_info.stage=
		VK_SHADER_STAGE_FRAGMENT_BIT;
	frag_shad_stage_cre_info.module=
		frag_shad_mod;
	char frag_entry
		[VK_MAX_EXTENSION_NAME_SIZE];
	strcpy(frag_entry,"main");
	frag_shad_stage_cre_info.pName=frag_entry;
	frag_shad_stage_cre_info
		.pSpecializationInfo=NULL;
	printf("fragment shader stage info filled.\n");

	shad_stage_cre_infos[0]=vert_shad_stage_cre_info;
	shad_stage_cre_infos[1]=frag_shad_stage_cre_info;
	//
	//fill vertex input state info
	//
	VkPipelineVertexInputStateCreateInfo
		vert_input_info;
	vert_input_info.sType=
		VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vert_input_info.pNext=NULL;
	vert_input_info.flags=0;
	vert_input_info
		.vertexBindingDescriptionCount=0;
	vert_input_info
		.pVertexBindingDescriptions=NULL;
	vert_input_info
		.vertexAttributeDescriptionCount=0;
	vert_input_info
		.pVertexAttributeDescriptions=NULL;
	printf("vertex input state info filled.\n");
	//
	//fill input assembly state info
	//
	VkPipelineInputAssemblyStateCreateInfo
		input_asm_info;
	input_asm_info.sType=
		VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	input_asm_info.pNext=NULL;
	input_asm_info.flags=0;
	input_asm_info.topology=
		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	input_asm_info.primitiveRestartEnable=VK_FALSE;
	printf("input assembly info filled.\n");
	//
	//fill viewport
	//
	VkViewport viewport;
	viewport.x=0.0f;
	viewport.y=0.0f;
	viewport.width=
		(float)swap_cre_info
		.imageExtent.width;
	viewport.height=
		(float)swap_cre_info
		.imageExtent.height;
	viewport.minDepth=0.0f;
	viewport.maxDepth=1.0f;
	printf("viewport filled.\n");
	//
	//fill scissor
	//
	VkRect2D scissor;
	VkOffset2D sci_offset;
	sci_offset.x=0;
	sci_offset.y=0;
	scissor.offset=sci_offset;
	scissor.extent=swap_cre_info
		.imageExtent;
	printf("scissor filled.\n");
	//
	//fill viewport state info
	//
	VkPipelineViewportStateCreateInfo
		vwp_state_cre_info;
	vwp_state_cre_info.sType=
		VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	vwp_state_cre_info.pNext=NULL;
	vwp_state_cre_info.flags=0;
	vwp_state_cre_info.viewportCount=1;
	vwp_state_cre_info.pViewports=&viewport;
	vwp_state_cre_info.scissorCount=1;
	vwp_state_cre_info.pScissors=&scissor;
	printf("viewport state filled.\n");
	//
	//fill rasterizer state info
	//
	VkPipelineRasterizationStateCreateInfo
		rast_cre_info;
	rast_cre_info.sType=
		VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rast_cre_info.pNext=NULL;
	rast_cre_info.flags=0;
	rast_cre_info
		.depthClampEnable=VK_FALSE;
	rast_cre_info
		.rasterizerDiscardEnable=VK_FALSE;
	rast_cre_info
		.polygonMode=VK_POLYGON_MODE_FILL;
	rast_cre_info
		.cullMode=VK_CULL_MODE_BACK_BIT;
	rast_cre_info
		.frontFace=VK_FRONT_FACE_CLOCKWISE;
	rast_cre_info
		.depthBiasEnable=VK_FALSE;
	rast_cre_info
		.depthBiasConstantFactor=0.0f;
	rast_cre_info
		.depthBiasClamp=0.0f;
	rast_cre_info
		.depthBiasSlopeFactor=0.0f;
	rast_cre_info
		.lineWidth=1.0f;
	printf("rasterization info filled.\n");
	//
	//fill multisampling state info
	//
	VkPipelineMultisampleStateCreateInfo
		mul_sam_cre_info;
	mul_sam_cre_info.sType=
		VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	mul_sam_cre_info.pNext=NULL;
	mul_sam_cre_info.flags=0;
	mul_sam_cre_info
		.rasterizationSamples=VK_SAMPLE_COUNT_1_BIT;
	mul_sam_cre_info
		.sampleShadingEnable=VK_FALSE;
	mul_sam_cre_info
		.minSampleShading=1.0f;
	mul_sam_cre_info
		.pSampleMask=NULL;
	mul_sam_cre_info
		.alphaToCoverageEnable=VK_FALSE;
	mul_sam_cre_info
		.alphaToOneEnable=VK_FALSE;
	printf("multisample info filled.\n");
	//
	//fill color blend attachment state
	//
	VkPipelineColorBlendAttachmentState
		color_blend_attach;
	color_blend_attach
		.blendEnable=VK_FALSE;
	color_blend_attach
		.srcColorBlendFactor=
		VK_BLEND_FACTOR_ONE;
	color_blend_attach
		.dstColorBlendFactor=
		VK_BLEND_FACTOR_ZERO;
	color_blend_attach
		.colorBlendOp=
		VK_BLEND_OP_ADD;
	color_blend_attach
		.srcAlphaBlendFactor=
		VK_BLEND_FACTOR_ONE;
	color_blend_attach
		.dstAlphaBlendFactor=
		VK_BLEND_FACTOR_ZERO;
	color_blend_attach
		.alphaBlendOp=
		VK_BLEND_OP_ADD;
	color_blend_attach
		.colorWriteMask
		=VK_COLOR_COMPONENT_R_BIT
		|VK_COLOR_COMPONENT_G_BIT
		|VK_COLOR_COMPONENT_B_BIT
		|VK_COLOR_COMPONENT_A_BIT;
	printf("color blend attachment state filled.\n");
	//
	//fill color blend state info
	//
	VkPipelineColorBlendStateCreateInfo
		color_blend_cre_info;
	color_blend_cre_info.sType=
		VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	color_blend_cre_info.pNext=NULL;
	color_blend_cre_info.flags=0;
	color_blend_cre_info
		.logicOpEnable=VK_FALSE;
	color_blend_cre_info
		.logicOp=VK_LOGIC_OP_COPY;
	color_blend_cre_info
		.attachmentCount=1;
	color_blend_cre_info
		.pAttachments=
		&color_blend_attach;
	for(uint32_t i=0;i<4;i++){
		color_blend_cre_info.
			blendConstants[i]=0.0f;
	}
	printf("color blend state info filled.\n");
	//
	//create pipeline layout
	//
	VkPipelineLayoutCreateInfo
		pipe_lay_cre_info;
	pipe_lay_cre_info.sType=
		VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipe_lay_cre_info.pNext=NULL;
	pipe_lay_cre_info.flags=0;
	pipe_lay_cre_info.setLayoutCount=0;
	pipe_lay_cre_info.pSetLayouts=NULL;
	pipe_lay_cre_info
		.pushConstantRangeCount=0;
	pipe_lay_cre_info
		.pPushConstantRanges=NULL;

	VkPipelineLayout pipe_layout;
	vkCreatePipelineLayout(dev,&pipe_lay_cre_info,NULL,&pipe_layout);
	printf("pipeline layout created.\n");
	//
	//create pipeline
	//
	VkGraphicsPipelineCreateInfo
		pipe_cre_info;
	pipe_cre_info.sType=
		VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipe_cre_info.pNext=NULL;
	pipe_cre_info.flags=0;
	pipe_cre_info.stageCount=2;
	pipe_cre_info.pStages=
		shad_stage_cre_infos;
	pipe_cre_info.pVertexInputState=
		&vert_input_info;
	pipe_cre_info.pInputAssemblyState=
		&input_asm_info;
	pipe_cre_info.pTessellationState=NULL;
	pipe_cre_info.pViewportState=
		&vwp_state_cre_info;
	pipe_cre_info.pRasterizationState=
		&rast_cre_info;
	pipe_cre_info.pMultisampleState=
		&mul_sam_cre_info;
	pipe_cre_info.pDepthStencilState=NULL;
	pipe_cre_info.pColorBlendState=
		&color_blend_cre_info;
	pipe_cre_info.pDynamicState=NULL;

	pipe_cre_info.layout=pipe_layout;
	pipe_cre_info.renderPass=rendp;
	pipe_cre_info.subpass=0;
	pipe_cre_info.basePipelineHandle=
		VK_NULL_HANDLE;
	pipe_cre_info.basePipelineIndex=-1;

	VkPipeline pipe;
	vkCreateGraphicsPipelines
		(dev,VK_NULL_HANDLE,1,&pipe_cre_info,NULL,&pipe);
	printf("graphics pipeline created.\n");
	//
	//destroy shader module
	//
	vkDestroyShaderModule
		(dev,frag_shad_mod,NULL);
	printf("fragment shader module destroyed.\n");
	vkDestroyShaderModule
		(dev,vert_shad_mod,NULL);
	printf("vertex shader module destroyed.\n");
	free(p_frag_code);
	printf("fragment shader binaries released.\n");
	free(p_vert_code);
	printf("vertex shader binaries released.\n");
	//
	//
	//framebuffer creation		line_936 to line_967
	//
	//create framebuffer
	//
	VkFramebufferCreateInfo
		frame_buff_cre_infos[swap_image_count];
	VkFramebuffer
		frame_buffs[swap_image_count];
	VkImageView image_attachs[swap_image_count];
	for(uint32_t i=0;i<swap_image_count;i++){
		image_attachs[i]=image_views[i];
		frame_buff_cre_infos[i].sType=
			VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		frame_buff_cre_infos[i].pNext=NULL;
		frame_buff_cre_infos[i].flags=0;
		frame_buff_cre_infos[i].renderPass=rendp;
		frame_buff_cre_infos[i].attachmentCount=1;
		frame_buff_cre_infos[i].pAttachments=
			&(image_attachs[i]);
		frame_buff_cre_infos[i].width=
			swap_cre_info.imageExtent.width;
		frame_buff_cre_infos[i].height=
			swap_cre_info.imageExtent.height;
		frame_buff_cre_infos[i].layers=1;

		vkCreateFramebuffer
			(dev,&(frame_buff_cre_infos[i]),
			 NULL,&(frame_buffs[i]));
		printf("framebuffer %d created.\n",i);
	}
	//
	//
	//command buffer creation		line_968 to line_1001
	//
	//create command pool
	//
	VkCommandPoolCreateInfo cmd_pool_cre_info;
	cmd_pool_cre_info.sType=
		VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmd_pool_cre_info.pNext=NULL;
	cmd_pool_cre_info.flags=0;
	cmd_pool_cre_info.queueFamilyIndex=qf_best_index;

	VkCommandPool cmd_pool;
	vkCreateCommandPool(dev,&cmd_pool_cre_info,NULL,&cmd_pool);
	printf("command pool created.\n");
	//
	//allocate command buffers
	//
	VkCommandBufferAllocateInfo
		cmd_buff_alloc_info;
	cmd_buff_alloc_info.sType=
		VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmd_buff_alloc_info.pNext=NULL;
	cmd_buff_alloc_info.commandPool=cmd_pool;
	cmd_buff_alloc_info.level=
		VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	cmd_buff_alloc_info.commandBufferCount=
		swap_image_count;

	VkCommandBuffer cmd_buffers[swap_image_count];
	vkAllocateCommandBuffers
		(dev,&cmd_buff_alloc_info,cmd_buffers);
	printf("command buffers allocated.\n");
	//
	//
	//render preparation		line1002 to line1062
	//
	VkCommandBufferBeginInfo
		cmd_buff_begin_infos[swap_image_count];
	VkRenderPassBeginInfo
		rendp_begin_infos[swap_image_count];
	VkRect2D rendp_area;
	rendp_area.offset.x=0;
	rendp_area.offset.y=0;
	rendp_area.extent=
		swap_cre_info.imageExtent;
	VkClearValue clear_val={0.6f,0.2f,0.8f,0.0f};
	for(uint32_t i=0;i<swap_image_count;i++){


		cmd_buff_begin_infos[i].sType=
			VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		cmd_buff_begin_infos[i].pNext=NULL;
		cmd_buff_begin_infos[i].flags=0;
		cmd_buff_begin_infos[i]
			.pInheritanceInfo=NULL;
		printf("command buffer begin info %d filled.\n",i);

		rendp_begin_infos[i].sType=
			VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		rendp_begin_infos[i].pNext=NULL;
		rendp_begin_infos[i]
			.renderPass=rendp;
		rendp_begin_infos[i]
			.framebuffer=frame_buffs[i];
		rendp_begin_infos[i]
			.renderArea=rendp_area;
		rendp_begin_infos[i]
			.clearValueCount=1;
		rendp_begin_infos[i]
			.pClearValues=&clear_val;
		printf("render pass begin info %d filled.\n",i);

		vkBeginCommandBuffer
			(cmd_buffers[i],
			 &cmd_buff_begin_infos[i]);

		vkCmdBeginRenderPass(cmd_buffers[i],
				&(rendp_begin_infos[i]),
				VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline
			(cmd_buffers[i],
			 VK_PIPELINE_BIND_POINT_GRAPHICS,
			 pipe);

		vkCmdDraw(cmd_buffers[i],3,1,0,0);

		vkCmdEndRenderPass(cmd_buffers[i]);

		vkEndCommandBuffer(cmd_buffers[i]);

		printf("command buffer drawing recorded.\n");
	}
	//
	//
	//semaphores and fences creation part		line_1063 to line_1103
	//
	uint32_t max_frames=2;
	VkSemaphore
		semps_img_avl[max_frames];
	VkSemaphore
		semps_rend_fin[max_frames];
	VkFence fens[max_frames];

	VkSemaphoreCreateInfo
		semp_cre_info;
	semp_cre_info.sType=
		VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	semp_cre_info.pNext=NULL;
	semp_cre_info.flags=0;

	VkFenceCreateInfo
		fen_cre_info;
	fen_cre_info.sType=
		VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fen_cre_info.pNext=NULL;
	fen_cre_info.flags=
		VK_FENCE_CREATE_SIGNALED_BIT;

	for(uint32_t i=0;i<max_frames;i++){
		vkCreateSemaphore
			(dev,&semp_cre_info,NULL,&(semps_img_avl[i]));
		vkCreateSemaphore
			(dev,&semp_cre_info,NULL,&(semps_rend_fin[i]));
		vkCreateFence
			(dev,&fen_cre_info,NULL,&(fens[i]));
	}
	printf("semaphores and fences created.\n");

	uint32_t cur_frame=0;
	VkFence fens_img[swap_image_count];
	for(uint32_t i=0;i<swap_image_count;i++){
		fens_img[i]=VK_NULL_HANDLE;
	}
	//
	//
	//main present part		line_1104 to line_1197
	//
	printf("\n");
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		//
		//submit
		//
		vkWaitForFences
			(dev,1,&(fens[cur_frame]),
			 VK_TRUE,UINT64_MAX);

		uint32_t img_index=0;
		vkAcquireNextImageKHR
			(dev,swap,UINT64_MAX,
			 semps_img_avl[cur_frame],
			 VK_NULL_HANDLE,&img_index);

		if(fens_img[img_index]!=VK_NULL_HANDLE){
			vkWaitForFences
				(dev,1,&(fens_img[img_index]),
				 VK_TRUE,UINT64_MAX);
		}

		fens_img[img_index]=fens[cur_frame];

		VkSubmitInfo sub_info;
		sub_info.sType=
			VK_STRUCTURE_TYPE_SUBMIT_INFO;
		sub_info.pNext=NULL;

		VkSemaphore semps_wait[1];
		semps_wait[0]=
			semps_img_avl[cur_frame];
		VkPipelineStageFlags
			wait_stages[1];
		wait_stages[0]=
			VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		sub_info.waitSemaphoreCount=1;
		sub_info.pWaitSemaphores=&(semps_wait[0]);
		sub_info.pWaitDstStageMask=
			&(wait_stages[0]);
		sub_info.commandBufferCount=1;
		sub_info.pCommandBuffers=
			&(cmd_buffers[img_index]);

		VkSemaphore semps_sig[1];
		semps_sig[0]=
			semps_rend_fin[cur_frame];

		sub_info.signalSemaphoreCount=1;
		sub_info.pSignalSemaphores=
			&(semps_sig[0]);

		vkResetFences(dev,1,&(fens[cur_frame]));

		vkQueueSubmit(q_graph,1,
				&sub_info,fens[cur_frame]);
		//
		//present
		//
		VkPresentInfoKHR
			pres_info;

		pres_info.sType=
			VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		pres_info.pNext=NULL;
		pres_info
			.waitSemaphoreCount=1;
		pres_info
			.pWaitSemaphores=
			&(semps_sig[0]);

		VkSwapchainKHR swaps[1];
		swaps[0]=swap;
		pres_info
			.swapchainCount=1;
		pres_info
			.pSwapchains=
			&(swaps[0]);
		pres_info
			.pImageIndices=&img_index;
		pres_info
			.pResults=NULL;

		vkQueuePresentKHR(q_pres,&pres_info);

		cur_frame=(cur_frame+1)%max_frames;
	}
	vkDeviceWaitIdle(dev);
	printf("command buffers finished.\n");
	//
	//
	//destroy everything		line_1198 to line_1274
	//
	//free command buffer
	//
	vkFreeCommandBuffers
		(dev,cmd_pool,
		 swap_image_count,cmd_buffers);
	printf("command buffers freed.\n");
	//
	//destroy semaphores and fences
	//
	for(uint32_t i=0;i<max_frames;i++){
		vkDestroySemaphore
			(dev,semps_rend_fin[i],NULL);
		vkDestroySemaphore
			(dev,semps_img_avl[i],NULL);
		vkDestroyFence
			(dev,fens[i],NULL);
	}
	printf("semaphores and fences destroyed.\n");
	//
	//destroy command pool
	//
	vkDestroyCommandPool(dev,cmd_pool,NULL);
	printf("command pool destroyed.\n");
	//
	//destroy frambuffer
	//
	for(uint32_t i=0;i<swap_image_count;i++){
		vkDestroyFramebuffer(dev,frame_buffs[i],NULL);
		printf("frambuffer %d destroyed.\n",i);
	}
	//
	//destroy pipeline
	//
	vkDestroyPipeline(dev,pipe,NULL);
	printf("graphics pipeline destroyed.\n");
	//
	//destroy pipeline layout
	//
	vkDestroyPipelineLayout(dev,pipe_layout,NULL);
	printf("pipeline layout destroyed.\n");
	//
	//destroy render pass
	//
	vkDestroyRenderPass(dev,rendp,NULL);
	printf("render pass destroyed.\n");
	//
	//destroy imageview
	//
	for(uint32_t i=0;i<swap_image_count;i++){
		vkDestroyImageView(dev,image_views[i],NULL);
		printf("image view %d destroyed.\n",i);
	}
	//
	//destroy swapchain
	//
	vkDestroySwapchainKHR(dev,swap,NULL);
	printf("swapchain destroyed.\n");
	//
	//destroy surface and window
	//
	vkDestroySurfaceKHR(inst,surf,NULL);
	printf("surface destroyed.\n");
	glfwDestroyWindow(window);
	printf("window destroyed.\n");
	//
	//destroy device
	//
	vkDestroyDevice(dev,NULL);
	printf("logical device destroyed.\n");
	//
	//destroy instance
	//
	vkDestroyInstance(inst,NULL);
	printf("instance destroyed.\n");
	//
	glfwTerminate();
	return 0;
}
