// ============================================================================
// compute_holder_phi_ranges.cpp  (updated version)
//
// 作用：
//   1. 在一个独立的小程序里重建 EMF 支撑环 + holder 的简化几何：
//      - 32 个倾斜 axis a 上的 holder 中性圆 (EMF_ZC_32 / EMF_RC_32)；
//      - 23 个绕 world Z 轴的支撑环圆环 (SUP_Z_23 / SUP_R_23)。
//   2. 对每个 holder，在其中性圆上用角 ψ ∈ [0, 2π) 采样 N 个点，
//      判断这些点是否进入任一支撑环的“危险壳”（带径向与 Z 安全裕度）。
//   3. 对于不在任何支撑环危险壳里的采样点：
//      - 如果 world Z 落在 “11–13 号支撑环之间 Z 带” ⇒ 归入 inner 区间；
//      - 否则归入 outer 区间。
//   4. 分别压缩并输出每个 holder 的 Outer / Inner 方位角区间（弧度 + 角度）。
//
// 几何假设（与 EMF 最终几何保持一致）：
//   - SUP_Z_23[i] 为第 i 个支撑环的“中心高度 Z_center”（不是底面 Z）。
//   - SUP_R_23[i] 为第 i 个支撑环的“外圆柱面半径 Rout_center”。
//   - 支撑环在 Z 方向的总高度取 L_leg_support = 75 mm：
//         z_center ± L_leg_support/2 为环体上下边界；
//   - 径向上：
//         Rout = SUP_R_23[i] - eps_ring_m;
//         Rin  = Rout - L_leg_support;
//     再在内外各扩一圈安全裕度 MARGIN_R；
//   - 11–13 号环之间的 Z 带用 “第 13 环底面 ~ 第 11 环顶面” 定义：
//         z_band_min = Z_center(13) - L_leg_support/2  （13 号 ring bottom）
//         z_band_max = Z_center(11) + L_leg_support/2  （11 号 ring top）
//
// 编译示例：
//   g++ -std=c++11 compute_holder_phi_ranges.cpp -o compute_holder_phi_ranges
//
// 运行：
//   ./compute_holder_phi_ranges > phi_ranges.txt
// ============================================================================

#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>

constexpr double PI = 3.14159265358979323846;

// ----------------------------- 简单三维向量 ---------------------------

struct Vec3 {
    double x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double X, double Y, double Z) : x(X), y(Y), z(Z) {}

    Vec3 operator+(const Vec3& o) const { return Vec3(x+o.x, y+o.y, z+o.z); }
    Vec3 operator-(const Vec3& o) const { return Vec3(x-o.x, y-o.y, z-o.z); }
    Vec3 operator*(double s)     const { return Vec3(x*s,   y*s,   z*s);   }

    double dot(const Vec3& o) const { return x*o.x + y*o.y + z*o.z; }

    Vec3 cross(const Vec3& o) const {
        return Vec3(
            y*o.z - z*o.y,
            z*o.x - x*o.z,
            x*o.y - y*o.x
        );
    }

    double norm() const { return std::sqrt(x*x + y*y + z*z); }

    Vec3 unit() const {
        double n = norm();
        if (n == 0.0) return Vec3(0,0,0);
        return Vec3(x/n, y/n, z/n);
    }
};

// ----------------------------- 输入数据（单位：m） ---------------------------

// N_SUP = 23 个支撑环
static const int N_SUP = 23;

// *** 修改点 1：这里把 SUP_Z_23 明确解释成“支撑环中心 Z_center”
static const double SUP_Z_23[N_SUP] = {
    21.47303, 21.140935, 20.555009, 19.619795, 18.26675, 16.54453,
    14.458793, 12.026127,  9.275543,  6.321882,  3.229238, 0.065506,
    -3.099646, -6.259168, -9.154038,-11.936654,-14.357259,-16.456139,
   -18.193031,-19.561866,-20.517241,-21.11586, -21.459724
};

// SUP_R_23[i] = 第 i 个支撑环的“外圆柱面半径 Rout_center”
static const double SUP_R_23[N_SUP] = {
     2.050,   4.290,   6.555,   8.985,  11.500,  13.880,
    16.055,  17.965,  19.540,  20.695,  21.400,  21.450,
    21.400,  20.715,  19.605,  18.030,  16.160,  14.000,
    11.635,   9.125,   6.690,   4.430,   2.195
};

// 32 个 axis-a 上的 holder
static const int N_HOLDER = 32;

static const double EMF_ZC_32[N_HOLDER] = {
     21.271,  20.602,  19.554,  18.555,
     17.077,  15.600,  14.122,  12.644,
     11.163,   9.685,   8.207,   6.729,
      5.251,   3.773,   2.295,   0.817,
     -0.821,  -2.299,  -3.777,  -5.255,
     -6.733,  -8.210,  -9.688, -11.166,
    -12.644, -14.122, -15.600, -17.077,
    -18.555, -19.554, -20.602, -21.271
};

static const double EMF_RC_32[N_HOLDER] = {
     3.843,   6.509,   9.185,  11.029,
    13.210,  14.924,  16.325,  17.495,
    18.465,  19.284,  19.953,  20.502,
    20.931,  21.241,  21.450,  21.559,
    21.559,  21.450,  21.240,  20.930,
    20.501,  19.951,  19.282,  18.463,
    17.495,  16.325,  14.924,  13.210,
    11.053,   9.185,   6.509,   3.843
};

// ----------------------------- 工具函数 ---------------------------

// 角度归一化到 [0, 2π)
double norm_angle(double x)
{
    const double TWO_PI = 2.0 * PI;
    x = std::fmod(x, TWO_PI);
    if (x < 0) x += TWO_PI;
    return x;
}

// 把 good/bad 采样点压成若干 [phi_start, phi_end) 区间（弧度制）
std::vector<std::pair<double,double>>
collect_good_segments(const std::vector<bool>& bad, double dphi)
{
    std::vector<std::pair<double,double>> segs;
    const int N = static_cast<int>(bad.size());
    if (N == 0) return segs;

    bool prev_good = !bad[0];
    int  start_idx = prev_good ? 0 : -1;

    for (int k = 1; k < N; ++k) {
        bool good = !bad[k];
        if (good && !prev_good) {
            // bad → good：新区间开始
            start_idx = k;
        } else if (!good && prev_good) {
            // good → bad：区间结束 [start_idx, k-1]
            int end_idx = k - 1;
            double phi_start = start_idx * dphi;
            double phi_end   = (end_idx + 1) * dphi;
            segs.emplace_back(phi_start, phi_end);
            start_idx = -1;
        }
        prev_good = good;
    }

    // 收尾：最后是 good 的情况
    if (prev_good && start_idx >= 0) {
        int end_idx   = N - 1;
        double phi_start = start_idx * dphi;
        double phi_end   = (end_idx + 1) * dphi;
        segs.emplace_back(phi_start, phi_end);
    }

    return segs;
}

int main()
{
    // ------------------------ 几何常量 / 参数 -----------------------------

    // holder L 截面参数（mm → m）
    const double L_leg_holder_mm = 56.0;               // holder 腿长
    const double t_mm            = 4.0;                // 厚度
    // holder 中性圆中心相对 web 底的偏移（沿 axis a）
    const double holder_center_offset_m =
        (L_leg_holder_mm * 0.5 - t_mm) * 1e-3;         // 24mm → 0.024m

    const double eps_r_mm = 2.0;                       // Rc → Rc+2mm
    const double eps_r_m  = eps_r_mm * 1e-3;

    // 支撑环参数
    const double L_leg_support_m = 75.0 * 1e-3;        // 支撑环 L 截面沿 Z 高度 ≈ 0.075m
    const double eps_ring_mm     = 2.0;                // 环外半径 shrink 2mm
    const double eps_ring_m      = eps_ring_mm * 1e-3;

    // 危险壳安全裕度（可以按需要调小/调大）
    const double MARGIN_R = 0.06;  // 6 cm 径向安全裕度
    const double MARGIN_Z = 0.03;  // 3 cm 高度安全裕度

    // Axis a（倾斜轴）：θ=56°, φ=-54°
    const double theta = 56.0 * PI / 180.0;
    const double phi   = -54.0 * PI / 180.0;

    const Vec3 axis_a(
        std::sin(theta) * std::cos(phi),
        std::sin(theta) * std::sin(phi),
        std::cos(theta)
    );
    const Vec3 zprime = axis_a.unit();   // local z' = axis_a

    // 构造 (x', y', z') 右手坐标系
    Vec3 preferX(1.0, 0.0, 0.0);
    Vec3 xseed = preferX - zprime * (preferX.dot(zprime));
    if (xseed.norm() < 1e-12) {
        // 如果 axis_a 偶然接近 world X，就用 world Y 做 seed
        Vec3 alt(0.0, 1.0, 0.0);
        xseed = alt - zprime * (alt.dot(zprime));
    }
    const Vec3 xprime = xseed.unit();
    const Vec3 yprime = zprime.cross(xprime).unit();

    // 采样数：N_SAMPLE 越大，φ 分辨率越高
    const int    N_SAMPLE = 3600;                      // 3600 → 0.1° 一点
    const double dphi     = 2.0 * PI / (double)N_SAMPLE;

    // ------------------------ 11–13 环之间恒定 Z 带 -----------------------
    //
    // *** 修改点 2：这里改成“中心 ± L/2”的形式，
    //   13 号环中心 Z = SUP_Z_23[12]
    //   11 号环中心 Z = SUP_Z_23[10]
    //   Z 带 = [13号底面, 11号顶面] = [z13 - L/2, z11 + L/2]
    //
    const double z11_center = SUP_Z_23[10];
    const double z13_center = SUP_Z_23[12];

    const double z_band_min = z13_center - 0.5 * L_leg_support_m;
    const double z_band_max = z11_center + 0.5 * L_leg_support_m;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "# z_band_min = " << z_band_min
              << " m, z_band_max = " << z_band_max << " m\n\n";

    // ------------------------ 主循环：逐个 holder 处理 -------------------

    for (int ih = 0; ih < N_HOLDER; ++ih) {

        // holder 几何：沿 axis a 的“web 底部”坐标 + 中心偏移
        const double Z_bottom_m = EMF_ZC_32[ih];               // web 底沿 axis a
        const double Zc_m       = Z_bottom_m + holder_center_offset_m;
        const double R0_m       = EMF_RC_32[ih] + eps_r_m;     // 中性圆 + 2mm

        // holder 中心 world 坐标：沿 axis a (z') 方向走 Zc_m
        const Vec3 center = zprime * Zc_m;

        // bad_outer[k] / bad_inner[k] 标记
        std::vector<bool> bad_outer(N_SAMPLE, false);
        std::vector<bool> bad_inner(N_SAMPLE, false);

        // ----------------- 对 ψ 采样并判定每个采样点 ------------------
        for (int k = 0; k < N_SAMPLE; ++k) {
            double psi = k * dphi;      // [0, 2π)

            // holder 中性圆在 (x', y') 平面上的点
            double c = std::cos(psi);
            double s = std::sin(psi);
            Vec3 local(R0_m * c, R0_m * s, 0.0);

            // worldP = center + local.x * x' + local.y * y'
            Vec3 worldP = center + xprime * local.x + yprime * local.y;
            double x = worldP.x;
            double y = worldP.y;
            double z = worldP.z;

            double R_xy = std::sqrt(x*x + y*y);

            // ---------- 1) 是否落入任一支撑环危险壳 ------------------
            bool inside_any_support = false;

            for (int is = 0; is < N_SUP; ++is) {

                // *** 修改点 3：使用“center ± L/2”来定义环在 Z 上的范围，
                //    再加上 MARGIN_Z
                double z_center_sup = SUP_Z_23[is];

                double zmin_band = z_center_sup - 0.5 * L_leg_support_m - MARGIN_Z;
                double zmax_band = z_center_sup + 0.5 * L_leg_support_m + MARGIN_Z;

                if (z < zmin_band || z > zmax_band) {
                    continue;   // 不在这个环的危险高度范围
                }

                // 径向：以 SUP_R_23 为外半径，再 shrink 2mm
                double Rout_ring_m = SUP_R_23[is] - eps_ring_m;
                double Rin_ring_m  = Rout_ring_m - L_leg_support_m;

                // 再在内外加上径向安全裕度
                double Rmin_band = Rin_ring_m - MARGIN_R;
                double Rmax_band = Rout_ring_m + MARGIN_R;

                if (R_xy >= Rmin_band && R_xy <= Rmax_band) {
                    inside_any_support = true;
                    break;
                }
            }

            // ---------- 2) 是否在“11–13 环之间 Z 带” -----------------
            bool in_inner_Z_band = (z >= z_band_min) && (z <= z_band_max);

            // ---------- 3) 填写 outer / inner 的 bad 标记 --------------
            if (inside_any_support) {
                // 落入支撑环危险壳：outer / inner 都禁用
                bad_outer[k] = true;
                bad_inner[k] = true;
            } else {
                // 没有进入环危险壳，则由 Z 带决定归属
                if (in_inner_Z_band) {
                    // 在 11–13 环 Z 带内：只允许 inner
                    bad_outer[k] = true;   // outer 禁止
                    bad_inner[k] = false;  // inner 允许
                } else {
                    // 不在该 Z 带：只允许 outer
                    bad_outer[k] = false;  // outer 允许
                    bad_inner[k] = true;   // inner 禁止
                }
            }
        }

        // ----------------- 从 bad 标记中提取 φ 区间 -------------------
        auto outerSegs = collect_good_segments(bad_outer, dphi);
        auto innerSegs = collect_good_segments(bad_inner, dphi);

        // ----------------- 输出结果 ----------------------------------
        std::cout << "Holder #" << (ih+1)
                  << "  (Z_bottom=" << Z_bottom_m
                  << " m, Zc=" << Zc_m
                  << " m, R0=" << R0_m << " m)\n";

        // Outer
        if (outerSegs.empty()) {
            std::cout << "  [Outer]  No allowed phi segments.\n";
        } else {
            std::cout << "  [Outer]  Allowed phi ranges "
                         "(exclude support rings & 11-13 Z band):\n";
            int seg_index = 0;
            for (const auto& seg : outerSegs) {
                double phi_start = norm_angle(seg.first);
                double phi_end   = norm_angle(seg.second);
                double deg_start = phi_start * 180.0 / PI;
                double deg_end   = phi_end   * 180.0 / PI;

                std::cout << "    Outer " << seg_index++
                          << ": [ " << phi_start << ", " << phi_end << " ] rad"
                          << "  == [ " << deg_start << ", " << deg_end << " ] deg\n";
            }
        }

        // Inner
        if (innerSegs.empty()) {
            std::cout << "  [Inner]  No allowed phi segments inside ring-11~13 Z band.\n";
        } else {
            std::cout << "  [Inner]  Allowed phi ranges (inside ring-11~13 Z band):\n";
            int seg_index = 0;
            for (const auto& seg : innerSegs) {
                double phi_start = norm_angle(seg.first);
                double phi_end   = norm_angle(seg.second);
                double deg_start = phi_start * 180.0 / PI;
                double deg_end   = phi_end   * 180.0 / PI;

                std::cout << "    Inner " << seg_index++
                          << ": [ " << phi_start << ", " << phi_end << " ] rad"
                          << "  == [ " << deg_start << ", " << deg_end << " ] deg\n";
            }
        }

        std::cout << "\n";
    }

    return 0;
}
