
import numpy as np

# Define tilt angles
tilt_theta = 56. * np.pi / 180.
tilt_phi = -54. * np.pi / 180.

# Input data
zc = np.fromstring("""
        21.271,  20.602,  19.554,  18.555,
        17.077,  15.600,  14.122,  12.644,
        11.166,   9.685,   8.207,   6.729,
         5.251,   3.773,   2.295,   0.817,
        -0.821,  -2.299,  -3.777,  -5.255,
        -6.733,  -8.210,  -9.688, -11.166,
       -12.644, -14.122, -15.600, -17.077,
       -18.555, -19.554, -20.602, -21.271
        """, sep="," )

rc = np.fromstring("""
        3.843,   6.509,   9.185,  11.053,
       13.210,  14.924,  16.325,  17.495,
       18.465,  19.282,  19.951,  20.502,
       20.930,  21.240,  21.450,  21.559,
       21.559,  21.450,  21.240,  20.930,
       20.502,  19.951,  19.282,  18.465,
       17.495,  16.325,  14.924,  13.210,
       11.053,   9.185,   6.509,   3.843
       """, sep="," )

# Number of points per ring (you can adjust this)
n_points_per_ring = 36  # for example, 10-degree increments

# Create rotation matrix to align z-axis with tilt axis
# First, rotation around y-axis by tilt_theta
R_y = np.array([
    [np.cos(tilt_theta), 0, np.sin(tilt_theta)],
    [0, 1, 0],
    [-np.sin(tilt_theta), 0, np.cos(tilt_theta)]
])

# Then rotation around z-axis by tilt_phi
R_z = np.array([
    [np.cos(tilt_phi), -np.sin(tilt_phi), 0],
    [np.sin(tilt_phi), np.cos(tilt_phi), 0],
    [0, 0, 1]
])

# Combined rotation matrix
R = R_z @ R_y

# Generate points for all rings
all_positions = []

for i in range(len(zc)):
    # Generate points around a circle in the untilted frame
    # Circle lies in xy-plane at z = zc[i] with radius rc[i]
    angles = np.linspace(0, 2*np.pi, n_points_per_ring, endpoint=False)
    
    # Points in untilted coordinates
    x_untilted = rc[i] * np.cos(angles)
    y_untilted = rc[i] * np.sin(angles)
    z_untilted = np.full_like(angles, zc[i])
    
    # Stack into array of shape (3, n_points)
    points_untilted = np.vstack([x_untilted, y_untilted, z_untilted])
    
    # Apply rotation to tilt the ring
    points_tilted = R @ points_untilted
    
    all_positions.append(points_tilted.T)  # Transpose to get (n_points, 3) shape

# Combine all rings into a single array
all_positions = np.vstack(all_positions)

# If you want to keep rings separate (as a list of arrays)
ring_positions = [R @ np.vstack([
    rc[i] * np.cos(np.linspace(0, 2*np.pi, n_points_per_ring, endpoint=False)),
    rc[i] * np.sin(np.linspace(0, 2*np.pi, n_points_per_ring, endpoint=False)),
    np.full(n_points_per_ring, zc[i])
]).T for i in range(len(zc))]

# Print results
print(f"Total number of points: {len(all_positions)}")
print(f"Shape: {all_positions.shape}")
print("\nFirst few points of first ring:")
print(ring_positions[0][:5])

# Example: access a specific ring and point
ring_index = 15  # 16th ring (0-indexed)
point_index = 10  # 11th point on that ring
print(f"\nPoint at ring {ring_index}, index {point_index}: {ring_positions[ring_index][point_index]}")

# Optional: if you need points in a specific order (e.g., for plotting)
# You could also create a structured array or dictionary
positions_dict = {f"ring_{i}": ring_positions[i] for i in range(len(zc))}

