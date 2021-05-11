# vulkan-tutorial-C-implementation
<br />
<br />
A C implementation from <a href="https://vulkan-tutorial.com">vulkan-tutorial.com</a>
<br />
<br />
<br />

# Why use C ?
<br />
<br />
Because C code has simple logic and it suits newbies who doesn't know C++ hardcore features or STL stuff.
<br />
<br />
<br />

# How to build ?
<br />
<br />
For Linux users:
<br />
<br />
Make sure you have a DESKTOP ENVIRONMENT !!!
<br />
<br />
<br />
<br />
STEP1: Install Necessary Programs
<br />
<br />
if you're using Debian, Fedora or Arch, vulkan is available from your repository.
Just type install command in console.
<br />
<br />
<br />
For Debian(or Ubuntu, or distros based on debian):
    
    sudo apt install libvulkan-dev mesa-vulkan-drivers vulkan-validationlayers-dev vulkan-tools vulkan-utils gcc make glslang-dev libglfw3-dev
<br />
<br />
NVIDIA GPU:
    
    sudo apt install nvidia-legacy-390xx-vulkan-icd nvidia-vulkan-icd nvidia-vulkan-common
<br />
<br />
<br />
<br />
For Feodra:
    
    sudo dnf install vulkan vulkan-headers vulkan-validation-layers vulkan-tools gcc make glslang glfw
<br />
<br />
NVIDIA GPU:
    
    dnf install https://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm https://download1.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
    dnf install xorg-x11-drv-nvidia akmod-nvidia
<br />
<br />
<br />
<br />
For Arch Linux(or Manjaro):

    sudo pacman -S base-devel vulkan-devel glslang xorg-drivers glfw-x11 --needed
<br />
<br />
INTEL GPU:

    sudo pacman -S vulkan-intel --needed
<br />
<br />
AMD READEON GPU:

    sudo pacman -S vulkan-radeon --needed
<br />
<br />
AMD RX GPU:

    sudo pacman -S amdvlk --needed
<br />
<br />
NVIDIA GPU:

    sudo pacman -S nvidia-utils --needed
<br />
<br />
<br />
For Raspberry Pi:
<br />
<br />
Download <a href="https://manjaro.org/download/#raspberry-pi-4-xfce">Manjaro ARM</a> image and burn it to your SD card, because only Manjaro ARM has built-in support for vulkan.

    sudo pacman -S base-devel vulkan-devel glslang xorg-drivers glfw-x11 vulkan-broadcom --needed
<br />
<br />
<br />
<br />
<br />
STEP2: Test the installation
<br />
<br />
type following commands:

    vulkaninfo
    vkcube
<br />
<br />
If no error occurs, vulkan is set correctly.
<br />
<br />
<br />
<br />
<br />
STEP3: Download Codes
<br />
<br />
Download via ZIP or Release Tarball
<br />
<br />
<br />
<br />
<br />
STEP4: use Makefile
<br />
<br />

    make            #install
    ./op            #run
    make cl         #remove
<br />
<br />
<br />
<br />
<br />
For Windows users:
<br />
<br />
I don't use Windows for programming, so follow the guide from <a href="https://vulkan-tutorial.com/Development_environment">The Original Site</a>.
<br />
By the way, Makefile is useless on Windows, copy the code in Visual Studio project and build it.
<br />
<br />
<br />
<br />
<br />
For MacOS users:
<br />
<br />
<a href="https://github.com/KhronosGroup/MoltenVK">MoltenVK official github page</a>
<br />
<br />
OR:
<br />
<br />

    brew install vulkan-headers molten-vk gcc make glslang glew glfw
<br />
<br />
<br />
<br />
