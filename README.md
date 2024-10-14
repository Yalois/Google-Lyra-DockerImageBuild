## 制作原因

CTF比赛中遇到过两次，一次是ISCC，然后就是最近的YLCTF。

记得ISCC那次我安装Lyra给我安装的我骂骂咧咧的想要把电脑砸了，主要是因为网络问题和依赖太多的问题，近期YLCTF又用到了，我又专门换回我的win系统里装好的wsl里的lyra解码的，安装确实有些麻烦。

为了提高使用效率，我决定将Lyra Linux环境封装成Docker镜像，并对lyra-1.3.2的WORKSPACE进行了修改，具体如下。

```yaml
# 原来的
git_repository(
    name = "com_google_glog",
    remote = "https://github.com/google/glog.git",
    branch = "master"
)
```
因为可能仓库更新过导致代码不一致的问题会报以下错误
```
ERROR: /root/.cache/bazel/_bazel_root/d75f5abc8330122e59e1289f475094d7/external/com_google_glog/BUILD.bazel:7:13: no such package '@gflags//': The repository '@gflags' could not be resolved: Repository '@gflags' is not defined and referenced by '@com_google_glog//:glog'
WARNING: /root/.cache/bazel/_bazel_root/d75f5abc8330122e59e1289f475094d7/external/com_google_audio_dsp/third_party/fft2d/BUILD:3:11: in linkstatic attribute of cc_library rule @com_google_audio_dsp//third_party/fft2d:fft2d: setting 'linkstatic=1' is recommended if there are no object files
WARNING: errors encountered while analyzing target '//lyra/cli_example:encoder_main': it will not be built
INFO: Analyzed target //lyra/cli_example:encoder_main (112 packages loaded, 3435 targets configured).
INFO: Found 0 targets...
ERROR: command succeeded, but not all targets were analyzed
INFO: Elapsed time: 36.286s, Critical Path: 0.01s
INFO: 1 process: 1 internal.
FAILED: Build did NOT complete successfully
```
于是我修改为了和lyra同一时期的commit
```
#修改后的
git_repository(
    name = "com_google_glog",
    remote = "https://github.com/google/glog.git",
    commit = "b33e3bad4c46c8a6345525fd822af355e5ef9446"
)
```

修过后就能build successful了。

其次就是代理一定要设置为你的代理地址



## Build

`docker build -t [镜像名字] [当前仓库下载到的目录]`

## Use

建议食用方法

`docker run -it --rm -v [你本机上容器需要访问的文件目录]:/data [镜像名] bash`

把本地目录挂载到data目录，方便操作

然后就是官方文档的使用方法

```bash
bazel-bin/lyra/cli_example/encoder_main --input_path=lyra/testdata/sample1_16kHz.wav --output_dir=$HOME/temp --bitrate=3200
bazel-bin/lyra/cli_example/decoder_main --encoded_path=$HOME/temp/sample1_16kHz.lyra --output_dir=$HOME/temp/ --bitrate=3200
```

## Source

本仓库的所有文件来自于

https://github.com/google/lyra

https://github.com/bazelbuild/bazel
