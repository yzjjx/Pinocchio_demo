#include <pinocchio/algorithm/aba.hpp>
#include <pinocchio/parsers/urdf.hpp>

#include <Eigen/Core>
#include <exception>
#include <iostream>
#include <string>

int main()
{
    // 以项目的 build/ 目录为工作目录读取 URDF
    const std::string urdf_path = "../urdf/Panda_nohand.urdf";

    try {
        pinocchio::Model model;
        pinocchio::urdf::buildModel(urdf_path, model);

        pinocchio::Data data(model);

        // 一组输入样例，按 panda_joint1 到 panda_joint7 的顺序排列
        Eigen::VectorXd q(model.nq);    // 关节角度，rad
        Eigen::VectorXd v(model.nv);    // 关节角速度，rad/s
        Eigen::VectorXd tau(model.nv);  // 关节驱动力矩，N·m
        q   << 0.0, -0.75,  0.0, -2.30, 0.0, 1.60, 0.80;
        v   << 0.1,  0.00, -0.2,  0.05, 0.0, 0.10, 0.00;
        tau << 1.0, -2.00,  0.5,  3.00, 0.0, 0.20, 0.10;

        // ABA 正向动力学：由当前关节状态和力矩求此刻的关节角加速度。
        const Eigen::VectorXd& ddq = pinocchio::aba(model, data, q, v, tau);
        std::cout << "ddq [rad/s^2] = " << ddq.transpose() << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}
