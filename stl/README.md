# Franka Emika Panda 无夹爪模型

[URDF](../urdf/Panda_nohand.urdf) 保留 7 个转动关节及固定法兰 `panda_link8`，以及官方质量、惯性和关节限位。

- `visual/link0.dae` 到 `visual/link7.dae` 提供 URDF 的精细外观和材质，无需外部贴图。
- `link0.stl` 到 `link7.stl` 用于 URDF 碰撞，单位为米。URDF 的 MuJoCo 编译设置使用 `meshdir="../stl"`、`strippath="true"` 和 `discardvisual="true"`，加载 STL 碰撞网格。
- `*.obj` 提供 MuJoCo Menagerie 模型的精细外观和第五连杆的分解碰撞网格。原始 [MJCF](source/mujoco_menagerie/panda_nohand.xml) 随上游说明和许可证保留。该文件保留上游的 `meshdir="assets"`，其中引用的网格位于本项目的 `stl/` 目录。

URDF 的活动关节名称为 `panda_joint1` 到 `panda_joint7`，MJCF 使用 `joint1` 到 `joint7`。URDF 的 `panda_link8` 沿 `panda_link7` 的 z 轴偏移 0.107 m。MJCF 的 `attachment_site` 偏移相同，另外绕 z 轴旋转约 135°。

## 网格来源

- [MuJoCo Menagerie](https://github.com/google-deepmind/mujoco_menagerie/tree/62ab00f2bc44f6f20c1c9b7a13f3fb1dd41a4e35/franka_emika_panda) 提供 MJCF、全部 OBJ，以及除 `link5.stl` 外的 STL。
- [Franka ROS](https://github.com/frankaemika/franka_ros/tree/ddd2fffd9de44b02ad15b4bbb2bfa2cec4d60d98/franka_description) 提供 DAE、`link5.stl` 及生成 URDF 所用的 Panda Xacro。

[SOURCES.json](SOURCES.json) 记录本地资产对应的上游版本、下载地址、字节数和 SHA-256。[Apache-2.0 许可证](source/mujoco_menagerie/LICENSE)随网格保留。

## URDF 生成

原始 URDF 通过 Xacro 2.1.1 展开官方 `robots/panda/panda.urdf.xacro`，参数为 `hand:=false gazebo:=true parent:=''`。其中 `gazebo:=true` 让上游模板输出各连杆的惯性参数。无需 ROS 时，可在临时源码副本中将 `$(find franka_description)` 替换为本地源码目录。

生成后移除了顶层 `gazebo` 和 `transmission` 标签，将网格引用改为项目内的相对路径，并添加了 MuJoCo 编译设置。上游生成的 8 个空 `*_sc` 固定子连杆仍保留。
