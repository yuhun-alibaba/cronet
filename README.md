# cronet 编译说明
chromium48 net
Chromium相关apk编译说明
参考链接
https://chromium.googlesource.com/chromium/src/+/master/docs/android_build_instructions.md
https://www.chromium.org/developers/how-tos/android-build-instructions
如果出现问题可能是编译参数问题可参考 http://www.jianshu.com/p/9d7a6e9ed777

简易介绍,在chromium-origin-test/目录下执行下面命令...
echo "{ 'GYP_DEFINES': 'OS=android', }" > chromium.gyp_env
src/build/install-build-deps-android.sh
可能遇到su权限问题，需要以su权限运行
可能找不到soft源，需要改源，setting中修改源为http://ftp.sjtu.edu.cn
或改etc/apt/source.list
ninja -C out/Debug chrome_public_apk 可以编译出各种apk
可能会遇到lint  NewApi问题
在文件中加@SuppressLint("NewApi") 

编译Cronet
参考链接http://www.jianshu.com/p/9d7a6e9ed777
（1）执行如下命令：
   $ gclient runhooks
	$ cd src
	$ ./build/install-build-deps.sh
	$ ./build/install-build-deps-android.sh
（2）构建之前需要对构建进行配置。编辑out/Default/args.gn文件，参照 Chromium Android编译指南 的说明，输入如下内容：
   target_os = "android"
	target_cpu = "arm"  # (default)
	is_debug = false  # (default)
	# Other args you may want to set:
	is_component_build = true
	is_clang = false
	symbol_level = 1  # Faster build with fewer symbols. -g1 rather than -g2
	enable_incremental_javac = false  # Much faster; experimental
	android_ndk_root = "~/dev_tools/Android/android-ndk-r10e"
	android_sdk_root = "~/dev_tools/Android/sdk"
	android_sdk_build_tools_version = "23.0.2"
	disable_file_support = true
	disable_ftp_support = true
	enable_websockets = false
	use_platform_icu_alternatives = true
保存out/Default/args.gn文件退出，执行如下命令：
$ gn gen out/Default
产生ninja构建所需的 .ninja 文件。
（3）输入如下命令编译net模块：
$ ninja -C out/Default net
（4）基于前面看到的配置文件out/Default/args.gn，编辑该文件将is_component_build配置选项置为false。执行如下命令：
$ gn gen out/Default
产生ninja构建所需的 .ninja 文件
（5）执行如下命令生成cronet so文件：
$ ninja -C out/Default/ cronet
（6）执行如下命令生成jar和test apk
$ ninja -C out/Default/ cronet_package cronet_sample_apk

其他参考
参考链接
https://www.chromium.org/developers/how-tos/android-build-instructions
cd到src目录,执行
ninja -C out/Debug chrome_public_apk
可能会遇到lint  NewApi问题
在文件中加@SuppressLint("NewApi") 
即开始编译,用时1小时左右后,执行安装apk即可
build/android/adb_install_apk.py out/Debug/apks/ChromePublic.apk
