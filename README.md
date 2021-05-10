# vulkan-tutorial-C-implementation
<br />
A C implementation from [vulkan-tutorial.com](https://vulkan-tutorial.com)
<br />
<br />
<br />

# Why use C ?
<br />
Because C code has simple logic and it suits newbies who doesn't know C++ hardcore features or STL stuff.
<br />
<br />
<br />

# How to build ?
<br />
For Linux users:
<br />
Make sure you have a DESKTOP ENVIRONMENT !!!
<br />
<br />
<br />
<br />
STEP1: Install Necessary Programs
<br />
if you're using Debian, Fedora or Arch, vulkan is available from your repository.
Just type install command in console.
<br />
<br />
<br />
For Debian(or Ubuntu, or distros based on debian):
    
    sudo apt install libvulkan1 vulkan-mesa-drivers vulkan-utils gcc make glslang
<br />
NVIDIA GPU:
    
    sudo add-apt-repository ppa:graphics-drivers/ppa
    sudo apt upgrade
    sudo apt install nvidia-graphics-drivers-396 nvidia-settings
<br />
<br />
<br />
<br />
For Feodra:
    
    sudo dnf install vulkan vulkan-info vulkan-tools gcc make glslang
<br />
NVIDIA GPU:
    
    dnf install https://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm https://download1.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
    dnf install xorg-x11-drv-nvidia akmod-nvidia
<br />
<br />
<br />
<br />
For Arch Linux(or Manjaro):

    sudo pacman -S base-devel vulkan-devel glslang xorg-drivers --needed
<br />
INTEL GPU:

    sudo pacman -S vulkan-intel --needed
<br />
AMD READEON GPU:

    sudo pacman -S vulkan-radeon --needed
<br />
AMD RX GPU:

    sudo pacman -S amdvlk --needed
<br />
NVIDIA GPU:

    sudo pacman -S nvidia-utils --needed
<br />
<br />
<br />
For Raspberry Pi:
<br />
Download [Manjaro ARM](https://manjaro.org/download/#raspberry-pi-4-xfce) image and burn it to your SD card, because only Manjaro ARM has built-in support for vulkan.

    sudo pacman -S base-devel vulkan-devel glslang xorg-drivers vulkan-broadcom --needed
<br />
<br />
<br />
<br />
<br />
STEP2: Test the installation
<br />
type following commands:

    vulkaninfo
    vkcube
<br />
If no error occurs, vulkan is set correctly.
<br />
<br />
<br />
<br />
<br />
STEP3: Download Codes
<br />
Download via ZIP or Release Tarball
<br />
<br />
<br />
<br />
<br />
STEP4: use Makefile

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
I don't use Windows for programming, so follow the guide from [The Original Site](https://vulkan-tutorial.com/Development_environment).
<br />
By the way, Makefile is useless on Windows, copy the code in Visual Studio project and build it.
<br />
<br />
<br />
<br />
<br />
For MacOS users:
<br />
[MoltenVK official github page](https://github.com/KhronosGroup/MoltenVK)
<br />
OR:

    brew install vulkan-headers molten-vk gcc make glslang
<br />
<br />
<br />
<br />
