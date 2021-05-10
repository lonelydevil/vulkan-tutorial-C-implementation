# vulkan-tutorial-C-implementation
A C implementation from vulkan-tutorial.com

# Why use C ?

Because C code has simple logic and it suits newbies who doesn't know C++ hardcore features or STL stuff.



# How to build ?

For Linux users:

Make sure you have a DESKTOP ENVIRONMENT !!!

STEP1: Install Necessary Programs

if you're using Debian, Fedora or Arch, vulkan is available from your repository.
Just type install command in console.



For Debian(or Ubuntu, or distros based on debian):

    sudo apt install libvulkan1 vulkan-mesa-drivers vulkan-utils gcc make glslang

NVIDIA GPU:

    sudo add-apt-repository ppa:graphics-drivers/ppa
    sudo apt upgrade
    sudo apt install nvidia-graphics-drivers-396 nvidia-settings




For Feodra:

    sudo dnf install vulkan vulkan-info vulkan-tools gcc make glslang

NVIDIA GPU:

    dnf install https://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm https://download1.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
    dnf install xorg-x11-drv-nvidia akmod-nvidia




For Arch Linux(or Manjaro):

    sudo pacman -S base-devel vulkan-devel glslang xorg-drivers --needed

INTEL GPU:

    sudo pacman -S vulkan-intel --needed
    
AMD READEON GPU:

    sudo pacman -S vulkan-radeon --needed

AMD RX GPU:

    sudo pacman -S amdvlk --needed

NVIDIA GPU:

    sudo pacman -S nvidia-utils --needed


For Raspberry Pi:

Download Manjaro ARM image and burn it to your SD card, because only Manjaro ARM has built-in support for vulkan.

    sudo pacman -S base-devel vulkan-devel glslang xorg-drivers vulkan-broadcom --needed




STEP2: Test the installation

type following commands:

    vulkaninfo
    vkcube

If no error occurs, vulkan is set correctly.



STEP3: Download Codes

Download via ZIP





STEP4: use Makefile

    make            #install
    ./op            #run
    make cl         #remove




For Windows users:

I don't use Windows for programming, so follow the guide from [The Original Site](https://vulkan-tutorial.com/Development_environment).

By the way, Makefile is useless on Windows, copy the code in Visual Studio project and build it.




For MacOS users:

[MoltenVK official github page](https://github.com/KhronosGroup/MoltenVK)

OR:

    brew install vulkan-headers molten-vk gcc make glslang





