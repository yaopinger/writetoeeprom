IviConfigServer.dll
IviConfigServerCAPI.dll
IviCShared.dll
是ivifgen的依赖库

ivifgen.dll ivifgen.so是ivi库

PCI9054_dll.dll pci9054_dll.lib是PXI接口驱动
visa.dll libvisa.so是visa库

如果提示找不到符号，可以尝试在link目录中添加该目录

所有的so库都是经过交叉编译的